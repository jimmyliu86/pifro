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

  // Gerando S0
  Greedy s  = greedy;
  s.Execute(true);

  // Gerando S*
  Greedy s_star = s;
  min_cost_ = s_star.ExecuteWithRefine(1);

  time_t t_stop = time(NULL);

  int i = 0, qt_it_wo_imp = 0;
  float min_cost_s_line = 0, min_cost_s_star_line = 0, act = 0;
  // Condicao de parada
  while ((t_stop - t_start) < execution_time) {
    // Pertubacao em s_star
    Greedy s_line = s_star;
    min_cost_s_line = s_line.ExecuteWithRefine(i);
    // Busca local em s_line
    Greedy s_star_line = s_line;
    min_cost_s_star_line = s_star_line.ExecuteWithRefine();

    // Criterio de aceitacao (BETTER)
    if (min_cost_s_line < min_cost_s_star_line) {
      act = min_cost_s_line;
      s_star = s_line;
    } else {
      act = min_cost_s_star_line;
      s_star = s_star_line;
    }

    if(act < min_cost_) {
      min_cost_ = act;
    }else{
      qt_it_wo_imp++;
    }

    // Aumentando K
    i++;
    t_stop = time(NULL);
  }

  return min_cost_;
}
