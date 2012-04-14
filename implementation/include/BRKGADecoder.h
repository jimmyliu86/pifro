#ifndef PIFRO2_BRKGADECODER_H_
#define PIFRO2_BRKGADECODER_H_

#include <list>
#include <vector>
#include <algorithm>
#include <time.h>
#include "Graph.h"
#include "Request.h"
#include "Greedy.h"

class BRKGADecoder
{
public:
  BRKGADecoder();
  BRKGADecoder(Graph& graph, std::vector<Request>& vecrequest);
  virtual ~BRKGADecoder();

  double decode(const std::vector< double >& chromosome) const;

protected:

private:
  std::vector<Request> Vecrequest;
  Graph objGraph;
};

#endif // PIFRO2_BRKGADECODER_H_
