#include "BRKGADecoder.h"

BRKGADecoder::BRKGADecoder(Graph graph, Demand demand)
{
  graph_ = graph;
  demand_ = demand;
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
  float cost = greedy.ExecuteWithRefine(permutation);

  return cost;
}
