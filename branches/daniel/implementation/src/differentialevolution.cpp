#include "differentialevolution.h"

DifferentialEvolution::DifferentialEvolution(Graph graph, Demand demand, time_t t_start, int tex, int heuristic, int d, int np, int cr, int f, int mutation_type, int qt_pond, int cross_type)
{
  graph_ = graph;
  demand_ = demand;
  t_start_ = t_start;
  t_stop_ = tex;
  tex_ = tex;
  heuristic_ = heuristic;
  d_ = d;
  np_ = np;
  cr_ = cr;
  f_ = f;

  // Tipo de mutacao
  // 0 = rand
  // 1 = best
  // 2 = rand_to_best
  mutation_type_ = mutation_type;

  // Quantidade de vetores ponderados
  qt_pond_ = qt_pond;

  // Tipo de cruzamento
  // 0 = binomial
  // 1 = exponencial
  cross_type_ = cross_type;

  min_cost_ = FLT_MAX;
  best_ = -1;
  prev_best_ = -1;
}

DifferentialEvolution::~DifferentialEvolution()
{
}

void DifferentialEvolution::createInitialPopulation() {
  for(int x = 0; x < np_; x++) {
    std::vector< std::pair< double, int > > ranking(d_);
    for(int i = 0; i < d_; ++i) {
      double val = ((float)(rand()) / (float(RAND_MAX)));
      ranking[i] = std::pair< double, int >(val, i);
    }
    std::sort(ranking.begin(), ranking.end());

    std::vector< int > permutation;
    for(std::vector< std::pair< double, int > >::const_iterator y = ranking.begin();
        y != ranking.end(); ++y) {
      permutation.push_back(y->second);
    }

    //Heuristic Greedy = 0, PSC = 1
    float cost = FLT_MAX;
    if(heuristic_ == 0) {
      Greedy greedy(graph_, demand_);
      greedy.min_cost_ = FLT_MAX;
      cost = greedy.ExecuteWithRefine(permutation, t_start_, tex_);
    } else if(heuristic_ == 1) {
      PSC psc(graph_, demand_);
      psc.min_cost_ = FLT_MAX;
      cost = psc.ExecuteWithRefine(permutation, t_start_, tex_);
    }

    Solution tmp;
    tmp.cost_ = cost;
    tmp.ranking_ = ranking;

    solutions_.push_back(tmp);

    // Encontrando XBest
    if (solutions_[x].cost_ < min_cost_) {
      prev_best_ = best_;
      best_ = x;
      min_cost_ = solutions_[x].cost_;
    }

     cout << "Initial Population - Custo minimo: " << min_cost_ << " - custo temporario: " << tmp.cost_ << endl;
  }

}

float DifferentialEvolution::evolve() {

  srand(time(NULL));
  createInitialPopulation();

  //solutions.size ?????
  //for(int i = 0; i < solutions_.size(); i++) {
  int gen_num = 1;
  while((time(NULL) - t_start_) < tex_) {
    std::vector<Solution> next_generation;
    int w = 0;

    while((w < np_) && ((time(NULL) - t_start_) < tex_)) {
      int target = (rand() % np_);
      int randomselect1 = (rand() % np_);
      int randomselect2 = (rand() % np_);
      int randomselect3 = (rand() % np_);
      int randomselect4 = (rand() % np_);
      int mutationtarget = (rand() % np_);
      float val = 0;

      std::vector<double> noise;
      std::vector< std::pair< double, int > > newindividual(d_);
      double cross_rand;

      cross_rand = ((float)(rand()) / (float(RAND_MAX)));


      //for(int w = 0; w < np_; w++) {
      bool exp = false;
      for(int i=0; i<d_; i++) {

        if(mutation_type_ != 2) {
          if(qt_pond_ <= 1) {
            val = f_ * (solutions_[randomselect1].ranking_[i].first - solutions_[randomselect2].ranking_[i].first);
          } else {
            val = f_ * ((solutions_[randomselect1].ranking_[i].first - solutions_[randomselect2].ranking_[i].first) + (solutions_[randomselect3].ranking_[i].first - solutions_[randomselect4].ranking_[i].first));
          }
        } else {
          if(qt_pond_ <= 1) {
            val = f_ * (solutions_[best_].ranking_[i].first - solutions_[prev_best_].ranking_[i].first);
          } else {
            val = f_ * ((solutions_[best_].ranking_[i].first - solutions_[prev_best_].ranking_[i].first) + (solutions_[randomselect3].ranking_[i].first - solutions_[randomselect4].ranking_[i].first));
          }
        }

        if(mutation_type_ == 0) {
          //rand
          noise.push_back(solutions_[mutationtarget].ranking_[i].first + val);
          if(cross_type_ <= 0) {
            if(cross_rand <= cr_) {
              newindividual[i] = (std::pair< double, int >(noise[i], solutions_[mutationtarget].ranking_[i].second));
            } else {
              newindividual[i] = (std::pair< double, int >(solutions_[target].ranking_[i].first, solutions_[mutationtarget].ranking_[i].second));
            }
          } else {
            if((solutions_[target].ranking_[i].first <= cr_) && (exp != true)) {
              newindividual[i] = (std::pair< double, int >(noise[i], solutions_[mutationtarget].ranking_[i].second));
            } else {
              exp = true;
              newindividual[i] = (std::pair< double, int >(solutions_[target].ranking_[i].first, solutions_[mutationtarget].ranking_[i].second));
            }
          }
        } else if(mutation_type_ == 1) {
          //best
          noise.push_back(solutions_[best_].ranking_[i].first + val);
          if(cross_type_ <= 0) {
            if(cross_rand <= cr_) {
              newindividual[i] = (std::pair< double, int >(noise[i], solutions_[mutationtarget].ranking_[i].second));
            } else {
              newindividual[i] = (std::pair< double, int >(solutions_[target].ranking_[i].first, solutions_[mutationtarget].ranking_[i].second));
            }
          } else {
            if((solutions_[target].ranking_[i].first <= cr_) && (exp != true)) {
              newindividual[i] = (std::pair< double, int >(noise[i], solutions_[mutationtarget].ranking_[i].second));
            } else {
              exp = true;
              newindividual[i] = (std::pair< double, int >(solutions_[target].ranking_[i].first, solutions_[mutationtarget].ranking_[i].second));
            }
          }
        } else {
          //rand-to-best
          noise.push_back(solutions_[prev_best_].ranking_[i].first + val);
          if(cross_type_ <= 0) {
            if(cross_rand <= cr_) {
              newindividual[i] = (std::pair< double, int >(noise[i], solutions_[mutationtarget].ranking_[i].second));
            } else {
              newindividual[i] = (std::pair< double, int >(solutions_[target].ranking_[i].first, solutions_[mutationtarget].ranking_[i].second));
            }
          } else {
            if((solutions_[target].ranking_[i].first <= cr_) && (exp != true)) {
              newindividual[i] = (std::pair< double, int >(noise[i], solutions_[mutationtarget].ranking_[i].second));
            } else {
              exp = true;
              newindividual[i] = (std::pair< double, int >(solutions_[target].ranking_[i].first, solutions_[mutationtarget].ranking_[i].second));
            }
          }
        }
      }


      std::sort(newindividual.begin(), newindividual.end());
      std::vector< int > permutation;
      for(std::vector< std::pair< double, int > >::const_iterator y = newindividual.begin(); y != newindividual.end(); ++y) {
        permutation.push_back(y->second);
      }


      //Heuristic Greedy = 0, PSC = 1
      float cost = FLT_MAX;
      if(heuristic_ == 0) {
        Greedy greedy(graph_, demand_);
        greedy.min_cost_ = FLT_MAX;
        cost = greedy.ExecuteWithRefine(permutation, t_start_, tex_);
      } else if(heuristic_ == 1) {
        PSC psc(graph_, demand_);
        psc.min_cost_ = FLT_MAX;
        cost = psc.ExecuteWithRefine(permutation, t_start_, tex_);
      }

      Solution tmp;
      tmp.cost_ = cost;
      tmp.ranking_ = newindividual;

      if(tmp.cost_ < solutions_[target].cost_) {
        next_generation.push_back(tmp);
        // solutions_[target] = tmp;

        // Encontrando XBest
        if(tmp.cost_ < min_cost_) {
          prev_best_ = best_;
          best_ = next_generation.size() - 1;
          min_cost_ = tmp.cost_;
        }
      } else {
        next_generation.push_back(solutions_[target]);
      }

      cout << "Custo minimo: " << min_cost_ << " - custo temporario: " << tmp.cost_ << endl;
      w++;
    }
    solutions_.clear();
    solutions_ = next_generation;
    next_generation.clear();
    gen_num++;
    cout << "Nova Geracao -> " << gen_num << endl;
  }

  return min_cost_;

}
