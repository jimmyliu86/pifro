#include "BRKGADecoder.h"

BRKGADecoder::BRKGADecoder(Graph graph, Demand demand, time_t tstart, int tex)
{
  graph_ = graph;
  demand_ = demand;
  TStart = tstart;
  Tex = tex;
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

  Greedy greedy(graph_, demand_);
  greedy.min_cost_ = FLT_MAX;
  float cost = greedy.ExecuteWithRefine(permutation, TStart, Tex);

  return cost;
}
