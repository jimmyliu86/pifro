#include "igs.h"

IGS::IGS()
{
  //ctor
}

IGS::~IGS()
{
  //dtor
}

float IGS::execute(Graph graph, Demand demand, int execution_time) {
  time_t t_start = time(NULL);

  int k = (demand.GetVecRequest().size() * 0.10);
  float act = 0, beta = 0.05;

  Greedy s0(graph, demand);
  s0.Execute(true, true);

  Greedy s = s0;
  s.ExecuteWithRefine(true, false);

  Greedy s_star = s;
  min_cost_ = s_star.getMinCost();

  Greedy s1 = s, s2 = s;

  time_t t_stop = time(NULL);
  while ((t_stop - t_start) < execution_time) {
    Greedy s1 = s;
    s1.ExecuteWithRefine(k);

    Greedy s2 = s1;
    s2.ExecuteWithRefine(true, false);

    if(s2.getMinCost() <= ((1 + beta) * s_star.getMinCost())) {
      s = s2;
    }

    if(s.getMinCost() < s_star.getMinCost()) {
      s_star = s;
    }

    t_stop = time(NULL);
//-->     cout << "IGS TMP S*: " << s_star.getMinCost()/1000000 << " - S'' COST: " << s2.getMinCost()/1000000 << " - S COST: " << s.getMinCost() / 1000000 << endl;
  }

  min_cost_ = s_star.getMinCost();
  return min_cost_;
}
