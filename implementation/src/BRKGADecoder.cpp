#include "BRKGADecoder.h"

BRKGADecoder::BRKGADecoder(Graph& graph, std::vector<Request>& vecrequest)
{
  graph_ = graph;
  vec_request_ = vecrequest;
}

BRKGADecoder::~BRKGADecoder()
{
  //dtor
}

// Runs in \Theta(n \log n):
double BRKGADecoder::decode(const std::vector< double >& chromosome) const {
  std::vector< std::pair< double, int > > ranking(chromosome.size());

  for(int i = 0; i < chromosome.size(); ++i) {
    ranking[i] = std::pair< double, int >(chromosome[i], i);
  }

  // Here we sort 'permutation', which will then produce a permutation of [n] in pair::second:
  std::sort(ranking.begin(), ranking.end());

  // permutation[i].second is in {0, ..., n - 1}; a permutation can be obtained as follows
  std::vector< int > permutation;
  for(std::vector< std::pair< double, int > >::const_iterator i = ranking.begin();
      i != ranking.end(); ++i) {
    permutation.push_back(i->second);
  }

  // sample fitness is the first allele
  //return chromosome.front();
  Greedy greedy;
  return greedy.ExecuteWithRefine(graph_, vec_request_, permutation);
}
