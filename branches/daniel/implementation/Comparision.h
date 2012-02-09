#ifndef PIFRO_COMPARISIONS_H_
#define PIFRO_COMPARISIONS_H_


struct comparison_request_by_qtroadm {
    public:
        bool operator()(Request a, Request b) {
            return a.getQtROADM() < b.getQtROADM();
        }
};


struct comparison_request_by_key {
    public:
        bool operator()(Request a, Request b) {
            return a.getKey() < b.getKey();
        }
};




#endif
