#ifndef TRAFFIC_HAND_H_
#define TRAFFIC_HAND_H_

#include <cstdio>

#include <string>

#include "graph2.h"

class TrafficHand {
 public:
  TrafficHand(char *net_filename, char *trf_filename, char *path_filename,
      char *sol_filename);
  ~TrafficHand();
  
  void Process();
  
 private:
   std::string net_filename_;
   std::string trf_filename_;
   std::string path_filename_;
   std::string sol_filename_;
   
   bool NetFile2Graph(const std::string &net_filename, Graph* graph);
   bool TrfFile2Graph(const std::string &trf_filename, int size, Graph* graph);
   bool GeneratePathFile(const std::string &path_filename,
       const std::vector< std::vector<int> > &paths);
   bool GenerateSolFile(const std::string &sol_filename, int size,
       const std::vector< std::vector< std::vector<double> > > &links);
};

#endif  // TRAFFIC_HAND_H_
