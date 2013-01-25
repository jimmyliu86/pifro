#include "differentialevolution.h"

DifferentialEvolution::DifferentialEvolution(Graph graph, Demand demand, time_t t_start, int tex, int heuristic, int d, int np, double cr, double f, int mutation_type, int qt_pond, int cross_type)
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
      //cout << "Custo alterado na populacao inicial" << endl;
      //system("PAUSE");
    }

    // cout << "Initial Population - Custo minimo: " << min_cost_ << " - custo temporario: " << tmp.cost_ << endl;
  }

}

float DifferentialEvolution::evolve() {

  srand(time(NULL));
  createInitialPopulation();

  //solutions.size ?????
  //for(int i = 0; i < solutions_.size(); i++) {
  int gen_num = 1;
  std::vector<Solution> trial_population;

  while((time(NULL) - t_start_) < tex_) {
    int w = 0;

    while((w < np_) && ((time(NULL) - t_start_) < tex_)) {
      std::vector<int> randons;
      /*int target = (rand() % np_);
      int randomselect1 = (rand() % np_);
      int randomselect2 = (rand() % np_);
      int randomselect3 = (rand() % np_);
      int randomselect4 = (rand() % np_);
      int mutationtarget = (rand() % np_);*/

      //Procurando alvos repetidos
      for(int g=0; g<6; g++) {
        //int tmp = rand() % np_;
        int f=0;
        int tmp = myrand * np_;

        if(randons.size() == 0) {
          while((tmp >= np_)) {
            tmp = myrand * np_;
          }
        } else {
          do {
            if((tmp == randons[f]) || (tmp >= np_)) {
              f=0;
              tmp = myrand * np_;
            } else {
              f++;
            }
          } while((f<randons.size()) || (tmp >=np_));
        }
        randons.push_back(tmp);
        //cout << "TMP: " << tmp << endl;
      }
      //system("PAUSE");

      // cout << "Target: " << randons[0] << " - RS1: " << randons[1] << " - RS2: " << randons[2] << " - RS3: " << randons[3] << " - RS4: " << randons[4] << " - MT: " << randons[5] << " - NP_: " << np_ <<endl;
      //system("PAUSE");
      float val = 0;

      std::vector<double> noise;
      std::vector< std::pair< double, int > > newindividual(d_);
      double cross_rand;

      cross_rand = ((float)(rand()) / (float(RAND_MAX)));
      //cout << "CR: " << cr_ << "CROSS_RAND: " << cross_rand << endl;

      //for(int w = 0; w < np_; w++) {
      bool exp = false;
      for(int i=0; i<d_; i++) {

        if(mutation_type_ != 2) {
          if(qt_pond_ <= 1) {
            val = f_ * (solutions_[randons[1]].ranking_[i].first - solutions_[randons[2]].ranking_[i].first);
            //cout << "RandomSelect 1: " << solutions_[randomselect1].ranking_[i].first << " - RandomSelect 2: " <<solutions_[randomselect2].ranking_[i].first << " - VAL: " << val <<endl;
          } else {
            val = f_ * ((solutions_[randons[1]].ranking_[i].first - solutions_[randons[2]].ranking_[i].first) + (solutions_[randons[3]].ranking_[i].first - solutions_[randons[4]].ranking_[i].first));
          }
        } else {
          if(qt_pond_ <= 1) {
            val = f_ * (solutions_[best_].ranking_[i].first - solutions_[prev_best_].ranking_[i].first);
          } else {
            val = f_ * ((solutions_[best_].ranking_[i].first - solutions_[prev_best_].ranking_[i].first) + (solutions_[randons[3]].ranking_[i].first - solutions_[randons[4]].ranking_[i].first));
          }
        }

        //cout << "F Value: " << f_ << " - VAL: " << val << endl;

        if(mutation_type_ == 0) {
          //rand
          noise.push_back(solutions_[randons[5]].ranking_[i].first + val);
          //cout << "Noise VALUE: " << (solutions_[mutationtarget].ranking_[i].first + val) << endl;
          if(cross_type_ <= 0) {
            if((cross_rand <= cr_) || (i == randons[5])) {
              newindividual[i] = (std::pair< double, int >(noise[i], solutions_[randons[5]].ranking_[i].second));
            } else {
              newindividual[i] = (std::pair< double, int >(solutions_[randons[0]].ranking_[i].first, solutions_[randons[5]].ranking_[i].second));
            }
          } else {
            if((solutions_[randons[0]].ranking_[i].first <= cr_) && (exp != true)) {
              newindividual[i] = (std::pair< double, int >(noise[i], solutions_[randons[5]].ranking_[i].second));
            } else {
              exp = true;
              newindividual[i] = (std::pair< double, int >(solutions_[randons[0]].ranking_[i].first, solutions_[randons[5]].ranking_[i].second));
            }
          }
        } else if(mutation_type_ == 1) {
          //best
          noise.push_back(solutions_[best_].ranking_[i].first + val);
          if(cross_type_ <= 0) {
            if((cross_rand <= cr_) || (i == randons[5])) {
              newindividual[i] = (std::pair< double, int >(noise[i], solutions_[randons[5]].ranking_[i].second));
            } else {
              newindividual[i] = (std::pair< double, int >(solutions_[randons[0]].ranking_[i].first, solutions_[randons[5]].ranking_[i].second));
            }
          } else {
            if((solutions_[randons[0]].ranking_[i].first <= cr_) && (exp != true)) {
              newindividual[i] = (std::pair< double, int >(noise[i], solutions_[randons[5]].ranking_[i].second));
            } else {
              exp = true;
              newindividual[i] = (std::pair< double, int >(solutions_[randons[0]].ranking_[i].first, solutions_[randons[5]].ranking_[i].second));
            }
          }
        } else {
          //rand-to-best
          noise.push_back(solutions_[prev_best_].ranking_[i].first + val);
          if(cross_type_ <= 0) {
            if((cross_rand <= cr_) || (i==randons[5])) {
              newindividual[i] = (std::pair< double, int >(noise[i], solutions_[randons[0]].ranking_[i].second));
            } else {
              newindividual[i] = (std::pair< double, int >(solutions_[randons[0]].ranking_[i].first, solutions_[randons[5]].ranking_[i].second));
            }
          } else {
            if((solutions_[randons[0]].ranking_[i].first <= cr_) && (exp != true)) {
              newindividual[i] = (std::pair< double, int >(noise[i], solutions_[randons[5]].ranking_[i].second));
            } else {
              exp = true;
              newindividual[i] = (std::pair< double, int >(solutions_[randons[0]].ranking_[i].first, solutions_[randons[5]].ranking_[i].second));
            }
          }
        }
      }


      std::sort(newindividual.begin(), newindividual.end());
      std::vector< int > permutation;
      for(std::vector< std::pair< double, int > >::const_iterator y = newindividual.begin(); y != newindividual.end(); ++y) {
        permutation.push_back(y->second);
      }

      /*cout << "Permutacao Nova\t-\tPermutacao Antiga"<<endl;
      for(int r=0; r<permutation.size(); r++){
        cout << permutation[r] << "\t-\t" << solutions_[randons[0]].ranking_[r].second << endl;
      }*/

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
      trial_population.push_back(tmp);
      w++;
      //Remover
      /*if(cost < min_cost_){
        min_cost_ = cost;
        cout << "Custo alterado!!!";
        system("PAUSE");
      }*/
      //Remover
    }

    // int o = 0;
    // while((o<trial_population.size()) && ((time(NULL) - t_start_) < tex_)) {
    for(int o=0; o<trial_population.size(); o++) {
      if(trial_population[o].cost_ <= solutions_[o].cost_) {
        solutions_[o] = trial_population[o];

        // Encontrando XBest
        if(solutions_[o].cost_ < min_cost_) {
          prev_best_ = best_;
          best_ = o;
          // cout << "Custo alterado!!! De " << min_cost_ << " para " << solutions_[o].cost_ << endl;
          // system("PAUSE");
          min_cost_ = solutions_[o].cost_;
        }
      }
      // o++;
    }
    trial_population.clear();
    gen_num++;
    // cout << "Nova Geracao -> " << gen_num << endl;
  }

  return min_cost_;

}
