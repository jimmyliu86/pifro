#ifndef PIFRO_COMPARISIONS_H_
#define PIFRO_COMPARISIONS_H_


struct comparision_request_by_qtroadm {
    public:
        bool operator()(Request a, Request b) {
            return a.getQtROADM() < b.getQtROADM();
        }
};


struct comparision_request_by_key {
    public:
        bool operator()(Request a, Request b) {
            return a.getKey() < b.getKey();
        }
};

/*struct comparision_chromosome_by_cost {
    public:
        bool operator()(Chromosome a, Chromosome b) {
            return a.getCost() < b.getCost();
        }
};

struct comparision_ranking_by_cost {
    public:
        bool operator()(std::pair< Chromosome, unsigned > a, std::pair< Chromosome, unsigned > b) {
            return a.first.getCost() < b.first.getCost();
        }
};*/

#endif
