#ifndef _SUBSET_REMOVAL_CPP_
#define _SUBSET_REMOVAL_CPP_

#include "../include/subset_removal.h"

int (*get_rmN_ptr)();
int (*get_remove_set_ptr)();

int SAinitN;
int SAt;
int rmN;

void subset_removal_init(int set_n) {
    rmN = -1;
}

int sets_rmN() {
    return (*get_rmN_ptr)();
}

int subset_removal() {
    return remove_best_score();
}

int remove_one() {
    return 1;
}

int adaptive_removal() {
    if(rmN == -1) 
        rmN = SAinitN;
    else if(step - best_step > SAt && (step - best_step) % SAt == 0 && rmN > 1)
        rmN--;
    return rmN;
}

int remove_best_score() {
    int best_set = -1, cur_set;
    if(flag_perform_bms && BMS_T < set_count) {
        for (int j = 0; j < BMS_T; ++j)
        {
            cur_set = set_solu[rng.next(set_count)];
            if(fix[cur_set]) continue;
            if(!cur_solu[cur_set]) continue;
            if(best_set == -1 || compare(best_set, cur_set, -1) < 0) 
                best_set = cur_set;
        }
    } else {
        for (int j = 0; j < set_count; ++j)
        {
            cur_set = set_solu[j];
            if(fix[cur_set]) continue;
            if(!cur_solu[cur_set]) continue;
            if(best_set == -1 || compare(best_set, cur_set, -1) < 0) 
                best_set = cur_set;
        }
    }
    return best_set;
}

#endif