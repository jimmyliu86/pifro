#include "BRKGA.h"

bool compare_QtROADM(const Request& i, const Request& j) {
    return i.QtROADM > j.QtROADM;
}

// Função de custo alterada para (i.key + i.hop). Ordenação decrescente.
bool compare_key(const Request& i, const Request& j)
{
    return ((i.Key+i.QtROADM) > (j.Key+j.QtROADM));
}

bool compare_cost(const Chromosome& i, const Chromosome& j)
{
    return i.cost < j.cost;
}


BRKGA::BRKGA(int population_size,
             int size_of_setA,
             int size_of_setB,
             int size_of_setC,
             float prob_crossover,
             std::vector<Request>& vecrequest,
             Graph& graph)
{
    population_size_ = population_size;
    size_setA_ = size_of_setA;
    size_setB_ = size_of_setB;
    size_setC_ = size_of_setC;
    original_ = vecrequest;
    prob_crossover_ = prob_crossover;
    objGraph = graph;

    TStart=time(NULL);

    // Pre-ordena requisições por caminho mais curto.
    std::sort(original_.begin(), original_.end(), compare_QtROADM);
    //std::sort(original_.begin(), original_.end(), compare_key);
}

void BRKGA::InitializePopulation()
{
    // Inicializa população inicial gerada
    // de forma aleatória.
    population_.reserve(population_size_);
    for (int i = 0; i < population_size_; ++i)
    {
        Chromosome individual;
        Request g;
        for (int j = 0; j < original_.size(); ++j)
        {
            g.setSrc(original_[j].getSrc());
            g.setDst(original_[j].getDst());
            g.setId(original_[j].getId());

            time_t t2 = time(NULL);
            g.setKey(rand() / static_cast<float>(t2));
            //g.setKey(rand() / static_cast<float>(RAND_MAX));
            g.setQtROADM(original_[j].getQtROADM());
            g.setQt(original_[j].getQt());
            individual.gen.push_back(g);
            //individual.cost = FLT_MAX;
        }
        //memset (individual.gen, 0x7f, sizeof (individual.gen));
        population_.push_back(individual);
    }
    // Inicializa lista de individuos temporários
    // Usada na operação de crossover.
    cross_pop_.resize(size_setB_);
    for (int i = 0; i < size_setB_; ++i)
    {
        cross_pop_[i].gen.resize(original_.size());
    }

    // Inicializa melhor individuo.
    best_individual_.gen.resize(original_.size());
    best_individual_.cost = DBL_MAX;
}

BRKGA::~BRKGA()
{
}

void BRKGA::SortRequest()
{
    for (int i = 0; i < population_size_; ++i)
    {
        std::sort(population_[i].gen.begin(), population_[i].gen.end(),
                  compare_key);
    }
}

void BRKGA::SortPopulation()
{
    std::sort(population_.begin(), population_.end(), compare_cost);
}


void BRKGA::UpdateCrossoverPopulation()
{
    int k = size_setA_;
    for (int i = 0; i < size_setB_; ++i)
    {
        for (int j = 0; j < original_.size(); ++j)
            population_[k].gen[j] = cross_pop_[i].gen[j];
        std::sort(population_[k].gen.begin(), population_[k].gen.end(), compare_key);
        ++k;
    }
}

// Crossover baseado em biased key genetic algorithm.
void BRKGA::Crossover()
{
    int current = 0;
    for (int i = 0; i < size_setB_; ++i)
    {
        int elite = rand() % size_setA_;
        int non_elite = (rand() % size_setB_) + size_setA_;
        float crossover;
        for (int j = 0; j < original_.size(); ++j)
        {
            time_t t2 = time(NULL);
            crossover = rand() / static_cast<float>(t2);
            //crossover = rand() / static_cast<float>(RAND_MAX);
            if(crossover < prob_crossover_)
            {
                cross_pop_[current].gen[j].setKey(population_[elite].gen[j].getKey());
            }
            else
            {
                cross_pop_[current].gen[j].setKey(population_[non_elite].gen[j].getKey());
            }
            cross_pop_[current].gen[j].setSrc(original_[j].getSrc());
            cross_pop_[current].gen[j].setDst(original_[j].getDst());
        }
        ++current;
    }
    UpdateCrossoverPopulation();
}

// Crossover baseado em algoritmo genético tradicional.
void BRKGA::Crossover2()
{
    std::vector<int> mask;
    std::list<int> unfilled;
    mask.resize(original_.size());
    int current = 0;
    for (int i = 0; i < size_setB_; ++i)
    {
        int elite = rand() % size_setA_;
        int non_elite = (rand() % size_setB_) + size_setA_;
        float crossover;
        for (int j = 0; j < original_.size(); ++j)
        {

            time_t t2 = time(NULL);
            crossover = rand() / static_cast<float>(t2);
            //crossover = rand() / static_cast<float>(RAND_MAX);
            if(crossover < prob_crossover_)
            {
                mask[population_[elite].gen[j].getId()]  = 1;
                cross_pop_[current].gen[j] = population_[elite].gen[j];
            }
            else
            {
                mask[population_[elite].gen[j].getId()] = 0;
                unfilled.push_back(j);
            }
        }
        // Preenche restande do cromossomo com valores
        // de indivíduo não-elite.
        int j = 0, unfilled_position;
        while(!unfilled.empty() && j < original_.size())
        {
            int index_non_elite = population_[non_elite].gen[j].getId();
            if (mask[index_non_elite] == 0)
            {
                unfilled_position = unfilled.front();
                unfilled.pop_front();
                cross_pop_[current].gen[unfilled_position] =
                    population_[non_elite].gen[j];
            }
            ++j;
        }
        ++current;
    }
    UpdateCrossoverPopulation();
}

void BRKGA::GenerateMutation()
{
    int start = population_.size() - size_setC_;
    for (int i = 0; i < size_setC_; ++i)
    {
        for (int j = 0; j < original_.size(); ++j)
        {
            population_[start].gen[j] = original_[j];

            //population_[start].gen[j].setKey(rand() / static_cast<float>(RAND_MAX));
            time_t t2 = time(NULL);
            population_[start].gen[j].setKey(rand() / static_cast<float>(t2));
        }
        population_[start].cost = 0.0f;
        ++start;
    }
    start = population_.size() - size_setC_;
    for (int i = start; i < population_.size(); ++i)
        std::sort(population_[i].gen.begin(),population_[i].gen.end(),
                  compare_key);
}

void BRKGA::SaveBestIndividual()
{
    //sort(population_.begin(), population_.end(), compare_cost);
    double cost_elite = population_[0].cost;
    if (cost_elite < best_individual_.cost)
    {
        best_individual_.cost = cost_elite;
        for (int i = 0; i < original_.size(); ++i)
            best_individual_.gen[i] = population_[0].gen[i];

        /*struct rusage times;
        getrusage(0, &times);
        float telapsed = times.ru_utime.tv_sec + times.ru_utime.tv_usec*0.000001;
        printf("GA - custo: %lf, tempo: %lf\n", cost_elite, telapsed);*/


        time_t t2 = time(NULL);
        float totaltime = t2 - TStart;

        //cout << "CALCULATE FITNESS - TOTALTIME " << totaltime << " - TIMEEXEC " << TimeExec << " - POPULATIONACT: " << i << endl;
        //system("PAUSE");

        if(totaltime >= TimeExec)
        {
            //break;
            cout << "Custo da rede pelo GA: " << cost_elite << endl;
        }
    }
}

void BRKGA::CalculateFitness()
{
    float cost;
    //Heuristic psc;
    Greedy greedy;
    int i = 0;
    while(i < population_.size())
    {
        //cost = psc.Execute(population_[i].gen, 0, 100);
        //objGraph.cleanCosts();
        cost = greedy.executeWithRefine(objGraph, population_[i].gen);
        population_[i].cost = cost;
        i++;

    }
}

void BRKGA::PrintToFile(float time)
{
    //printf("%f\n", time);
    printf("%.0lf\n", best_individual_.cost);
}

float BRKGA::ExecuteWithGreedy(int timeexec)
{

    //time_t t1=time(NULL);
    //time_t t2=time(NULL);

    TimeExec = timeexec;

    InitializePopulation();
    SortRequest();
    CalculateFitness();
    SortPopulation();
    SaveBestIndividual();

    int i = 0;
    bool flag = true;
    while(flag)
    {
        Crossover();
        GenerateMutation();
        CalculateFitness();
        SortPopulation();
        SaveBestIndividual();
        i++;

        time_t t2 = time(NULL);
        float totaltime = t2 - TStart;
        cout << "ExecuteWithGreedy - TOTALTIME " << totaltime << " - TIMEEXEC " << TimeExec << " - TOTAL Executions: " << i << endl;
        //system("PAUSE");

        if(totaltime >= TimeExec)
        {
            flag = false;
            //break;
        }
    }
    //PrintToFile(telapsed);
    return best_individual_.cost;
}
