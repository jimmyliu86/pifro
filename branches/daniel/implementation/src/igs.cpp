#include "igs.h"

IGS::IGS()
{
  //ctor
}

IGS::~IGS()
{
  //dtor
}

float IGS::execute(Greedy greedy, int execution_time) {
  time_t t_start = time(NULL);

  int k = 1, qt_it_wo_imp = 0;
  float min_cost_s_line = 0, min_cost_s_star_line = 0, act = 0;

  // Gerando S0 e S (o metodo ja constroi e refina)
  Greedy s  = greedy;
  s.ExecuteWithRefine();

  Greedy s_line(greedy.GetGraph(), greedy.GetDemand());

  // Condicao de parada
  time_t t_stop = time(NULL);
  while ((t_stop - t_start) < execution_time) {
    s_line = s;
    s_line.ExecuteWithRefine(k);

    // Criterio de aceitacao (BETTER)
    if (s_line.getMinCost() < s.getMinCost()) {
      s = s_line;
      act = s_line.getMinCost();
    }else{
      act = s.getMinCost();
    }

    if(act < min_cost_) {
      min_cost_ = act;
    }else{
      qt_it_wo_imp++;
      // Piorando resultado para escapar de otimos locais
      if(qt_it_wo_imp >= 20) {
        if(s_line.getMinCost() > s.getMinCost()) {
          s = s_line;
        }else if(greedy.getMinCost() > s.getMinCost()) {
          s = greedy;
        }
      }
    }

    // Aumentando K
    if(k <= greedy.GetDemand().GetQtRequest() - 1) {
      k++;
    }else{
      k = 1;
    }

    t_stop = time(NULL);
    cout << "Execution at: " << (t_stop - t_start) << " - COST: " << act / 1000000 << " - K: " << k << endl;
  }

  return min_cost_;
}
