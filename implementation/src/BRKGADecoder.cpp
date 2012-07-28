#include "BRKGADecoder.h"

BRKGADecoder::BRKGADecoder(Graph graph, Demand demand, time_t tstart, int tex, int heuristic)
{
  graph_ = graph;
  demand_ = demand;
  TStart = tstart;
  Tex = tex;
  Heuristic = heuristic;
}

BRKGADecoder::~BRKGADecoder()
{
}

double BRKGADecoder::decode(const std::vector< double >& chromosome) const {
  std::vector< std::pair< double, int > > ranking(chromosome.size());

  for(int i = 0; i < chromosome.size(); ++i) {
    ranking[i] = std::pair< double, int >(chromosome[i], i);
  }

  std::sort(ranking.begin(), ranking.end());

  std::vector< int > permutation;
  for(std::vector< std::pair< double, int > >::const_iterator i = ranking.begin();
      i != ranking.end(); ++i) {
    permutation.push_back(i->second);
  }

  //Heuristic Greedy = 0, PSC = 1
  float cost = FLT_MAX;
  if(Heuristic == 0){
    Greedy greedy(graph_, demand_);
    greedy.min_cost_ = FLT_MAX;
    cost = greedy.ExecuteWithRefine(permutation, TStart, Tex);
  }else if(Heuristic == 1){
    PSC psc(graph_, demand_);
    psc.min_cost_ = FLT_MAX;
    cost = psc.ExecuteWithRefine(permutation, TStart, Tex);
  }

  return cost;
}
