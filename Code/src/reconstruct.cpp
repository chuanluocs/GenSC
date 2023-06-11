#ifndef _RECONSTRUCT_CPP_
#define _RECONSTRUCT_CPP_

#include "../include/reconstruct.h"

bool reconstruct_with_prob;
double reconstruct_prob;
int reconstruct_swap_T;
int *swapTsets;
bool *swapT_selected;
void (*reconstruct_solu_ptr)();
void (*reconstruct_swapT_init)(int);
void (*reconstruct_swapT_delete)();

void reconstruct() {
    if(reconstruct_with_prob) 
        if(rng.nextClosed() > reconstruct_prob)
            return;

    (*reconstruct_solu_ptr)();
}

void reconstruct_init(int set_n) {
    (*reconstruct_swapT_init)(set_n);
}

void reconstruct_delete() {
    (*reconstruct_swapT_delete)();
}

void reconstruct_swapT_delete_none() {}

void reconstruct_swapT_delete_do() {
    delete[] swapTsets;
    delete[] swapT_selected;
}

void reconstruct_swapT_init_none(int set_n) {}

void reconstruct_swapT_init_do(int set_n) {
    swapTsets = new int[reconstruct_swap_T];
    swapT_selected = new bool[set_n];
}

void reconstruct_remove_one_randomly() {
    int flip_set = set_solu[rng.next(set_count)];
    
    int random_s = 0;
    while(!cur_solu[flip_set] || fix[flip_set]) {
        flip_set = set_solu[rng.next(set_count)];
        random_s++;
        if(random_s > 1000) return;
    }

    if (flip_set == -1)
        return;
    flip(flip_set);

    time_stamp[flip_set] = step;
}

void reconstruct_swap_t() {
    fill(swapT_selected, swapT_selected+set_num, 0);
    int cur_set, random_s;
    for(int i=0;i<reconstruct_swap_T;i++) {
        cur_set = rng.next(set_num);
        random_s = 0;
        while(!cur_solu[cur_set] || fix[cur_set]) {
            cur_set = rng.next(set_num);
            random_s++;
            if(random_s > 1000) return;
        }
        swapT_selected[cur_set] = 1;
    }
    greedy_addition_for_reconstruct_swap_t(swapT_selected, swapTsets);
    for(int i=0;i<reconstruct_swap_T-1;i++) {
        flip(swapTsets[i]);
        time_stamp[swapTsets[i]] = step;
    }
}

void reconstruct_remove_one_best() {
    int set_to_remove = remove_best_score();
    flip(set_to_remove);
    time_stamp[set_to_remove] = step;
}

#endif