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
  float act = 0;

  // Gerando S0 e S (o metodo ja constroi e refina)
  Greedy s  = greedy;
  s.ExecuteWithRefine();
  min_cost_ = s.getMinCost();

  // Condicao de parada
  time_t t_stop = time(NULL);
  while ((t_stop - t_start) < execution_time) {
    // Desconstrucao de S
    Greedy s_line(s.GetGraph(), s.GetDemand());
    // Pertubacao (S, K)
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
      qt_it_wo_imp = 0;
    }else{
      qt_it_wo_imp++;
      // Piorando resultado
      if(qt_it_wo_imp >= s_line.GetDemand().GetQtRequest()) {
      // if(qt_it_wo_imp >= 5) {
        if((s_line.getMinCost() > s.getMinCost()) && (s_line.getMinCost() > greedy.getMinCost())) {
          s = s_line;
        }else if((greedy.getMinCost() > s_line.getMinCost()) && (greedy.getMinCost() > s.getMinCost())) {
          s = greedy;
        }else {
          s.ExecuteWithRefine();
        }
        qt_it_wo_imp = 0;
      }
    }

    // Aumentando K
    if(k <= greedy.GetDemand().GetQtRequest() - 1) {
    // if(k <= 3) {
      k++;
    }else{
      k = 1;
    }

    t_stop = time(NULL);
    cout << "Execution at: " << (t_stop - t_start) << " - COST: " << act / 1000000 << " - K: " << k << endl;
  }

  return min_cost_;
}
