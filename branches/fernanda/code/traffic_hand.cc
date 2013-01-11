#include "traffic_hand.h"

#include  <cassert>

#include "dijkstra.h"

TrafficHand::TrafficHand(char *net_filename, char *trf_filename,
    char *path_filename, char *sol_filename)
    : net_filename_(net_filename), trf_filename_(trf_filename),
    path_filename_(path_filename), sol_filename_(sol_filename) {
}

TrafficHand::~TrafficHand() {
}

bool TrafficHand::NetFile2Graph(const std::string &net_filename, Graph* graph) {
  assert(graph != NULL);
  
  FILE *file = fopen(net_filename.c_str(), "r");
  if (file == NULL) {
    return false;
  }
  
  int size = 0;
  int links = 0;
  fscanf(file, "%d %d", &size, &links);
  
  graph->Init(size);
  
  for (int i = 0; i < size; ++i) {
    graph->Link(i, i, 0.0); 
  }
  
  int from = 0;
  int to = 0;
  double weight = 0.0;
  for (int i = 0; i < links; ++i) {
    fscanf(file, "%d %d %lf", &from, &to, &weight);
    graph->Link(from, to, weight);
    graph->Link(to, from, weight);
  }
  
  fclose(file);
  file = NULL;

  return true;
}

bool TrafficHand::TrfFile2Graph(const std::string &trf_filename, int size, Graph* graph) {
  assert(graph != NULL);
  
  FILE *file = fopen(trf_filename.c_str(), "r");
  if (file == NULL) {
    return false;
  }
  
  int links = 0;
  fscanf(file, "%d", &links);
  
  graph->Init(size);
  
  for (int i = 0; i < size; ++i) {
    graph->Link(i, i, 0.0); 
  }
  
  int from = 0;
  int to = 0;
  double weight = 0.0;
  for (int i = 0; i < links; ++i) {
    fscanf(file, "%d %d %lf", &from, &to, &weight);
    graph->Link(from, to, weight);
    graph->Link(to, from, weight);
  }
  
  fclose(file);
  file = NULL;

  return true;
}

void TrafficHand::Process() {
  // read nodes
  Graph graph;
  Graph clone_graph;
  Dijkstra dijkstra;
  Dijkstra clone_dijkstra;
  
  if (NetFile2Graph(net_filename_, &graph)) {
    // calculate paths
    
    // set graph
    dijkstra.set_graph(graph);
    
    // get number of paths
    int size = graph.Size();
    
    // store paths
    std::vector<int> shortest_path;
    std::vector<int> second_shortest_path;
    std::vector< std::vector<int> > paths;

    for (int i = 0; i < size; ++i) {
      // calculate all paths from i to elsewhere
      dijkstra.Calculate(i);
      
      // for any other calculate the second shortest path
      for (int j = i+1; j < size; ++j) {
        // get shotest path
        shortest_path = dijkstra.Path(j);
        assert(shortest_path.size() >= 1);

        // copy graph
        clone_graph = graph;

        // unlink path in the graph
        for (int k = 1; k < shortest_path.size() ; ++k) {
          clone_graph.Unlink(shortest_path[k-1], shortest_path[k]);
        }
        
        // calculate all paths from i to elsewhere
        clone_dijkstra.set_graph(clone_graph);
        clone_dijkstra.Calculate(i);

        // get the second shortest path
        second_shortest_path = clone_dijkstra.Path(j);

        // check if it is valid 
        if (second_shortest_path.size() == 1) {
          // use the shortest instead
          second_shortest_path = shortest_path;
        }
        
        // save the path
        paths.push_back(second_shortest_path);

      }
    }

    // write pat file
    GeneratePathFile(path_filename_, paths);
    
    int node1 = 0;
    int node2 = 0;
    int from = 0;
    int to = 0;

    std::vector< std::vector< std::vector<double> > > links;
    links.resize(size);
    for (int i = 0; i < size; ++i) {
      links[i].resize(size);
    }

    Graph logic_graph;
    if (TrfFile2Graph(trf_filename_, size, &logic_graph)) {
      for (int i = 0; i < paths.size(); ++i) {
        from = paths[i].back();
        to = paths[i].front();

        for (int j = 1; j < paths[i].size(); ++j) {
          if (paths[i][j-1] < paths[i][j]) {
            node1 = paths[i][j-1];
            node2 = paths[i][j];
          } else {
            node1 = paths[i][j];
            node2 = paths[i][j-1];
          }

          // avoid incompleted trf
          if (logic_graph.IsLinked(from,to)) {
            links[node1][node2].push_back(logic_graph.Weight(from, to));
          }
        }
      }
    }

    int counter = 0;
    double cumulative = 0.0;
    for(int i = 0; i < links.size(); ++i) {
      for(int j = 0; j < links[i].size(); ++j) {
        cumulative = 0.0;
        for (int k = 0; k < links[i][j].size(); ++k) {
          //fprintf(stderr, " [%d %d] %lf\n", i, j, links[i][j][k]);
          cumulative += links[i][j][k];
          ++counter;
        }

        // sum cumulative to multiples of 100
        if ((static_cast<int>(cumulative) % 100) > 0) {
          links[i][j].push_back(100 - (static_cast<int>(cumulative) % 100));
          ++counter;
        }
      }
    }

    // generate sol file
    GenerateSolFile(sol_filename_, counter, links);
  } else {
    fprintf(stdout, "Ops.\n"); 
  }
}

bool TrafficHand::GeneratePathFile(const std::string &path_filename,
    const std::vector< std::vector<int> > &paths) {
  FILE *file = fopen(path_filename.c_str(), "w");
  if (file == NULL) {
    return false;
  }
  
  fprintf(file, "%d\n", static_cast<int>(paths.size()));
  for (int i = 0; i < paths.size(); ++i) {
    for (int j = 0; j < paths[i].size(); ++j) {
      if (j != (paths[i].size() -1)) {
        fprintf(file, "%d ", paths[i][j]);
      } else {
        fprintf(file, "%d", paths[i][j]);
      }
    }

    if (i != (paths.size() -1)) {
      fprintf(file, "\n");
    }
  }
  
  fclose(file);
  file = NULL;

  return true;
}

bool TrafficHand::GenerateSolFile(const std::string &sol_filename, int size,
    const std::vector< std::vector< std::vector<double> > > &links) {
  FILE *file = fopen(sol_filename.c_str(), "w");
  if (file == NULL) {
    return false;
  }
  
  fprintf(file, "%d\n", size);
  for(int i = 0; i < links.size(); ++i) {
    for(int j = 0; j < links[i].size(); ++j) {
      for (int k = 0; k < links[i][j].size(); ++k) {
        fprintf(file, "%d %d %d", i, j, static_cast<int>(links[i][j][k]));

        if ((i != (links.size() - 1)) || (j != (links[i].size() - 1))
            || (k != (links[i][j].size() - 1))) {
          fprintf(file, "\n");
        }
      }
    }
  }
  
  fclose(file);
  file = NULL;

  return true;
}
