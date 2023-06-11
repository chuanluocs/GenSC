#ifndef _CC_AND_TABU_CPP_
#define _CC_AND_TABU_CPP_

#include "../include/cc_and_tabu.h"

bool *cc;
bool *iscc;
int tabu_alpha;

void init_cc_and_tabu(int set_n) {
    if(flag_perform_cc) 
        cc = new bool[set_n];
    if(flag_perform_iscc)
        iscc = new bool[set_n];
}

void delete_cc_and_tabu() {
    if(flag_perform_cc) 
        delete[] cc;
    if(flag_perform_iscc)
        delete[] iscc;
}

bool filter_cc(int s) {
    if(flag_perform_cc)
        return cc[s];
    return true;
}

bool filter_iscc(int s) {
    if(flag_perform_iscc)
        return iscc[s];
    return true;
}

bool filter_tabu(int s) {
    if(flag_perform_tabu)
        return step-time_stamp[s] >= tabu_alpha;
    return true;
}

#endif