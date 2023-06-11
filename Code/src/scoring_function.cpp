#ifndef _SCORING_FUNCTION_CPP_
#define _SCORING_FUNCTION_CPP_

#include "../include/scoring_function.h"

long long *score;
long long *pscore;
long long *value;

long long (*compute_score_ptr)(int);
void (*init_scores_ptr)(int, int);
void (*delete_scores_ptr)();

void init_scores(int set_n, int item_n) {
    // cout << "initializing scores\n";
    (*init_scores_ptr)(set_n, item_n);
    // cout << "initialization for scores complete\n";
}

void delete_scores() {
    (*delete_scores_ptr)();
}

void compute_score(int compute_set, long long & set_score, int & set_weight) {
    set_score = (*compute_score_ptr)(compute_set);
    set_weight = weight[compute_set];
}

void init_scores_basic(int set_n, int item_n) {
    score = new long long[set_n];
    value = new long long[item_n];
}

void init_scores_united(int set_n, int item_n) {
    score = new long long[set_n];
    pscore = new long long[set_n];
    value = new long long[item_n];
}

void delete_scores_no_weighting() {
    delete[] score;
    delete[] value;
}

void delete_scores_basic() {
    delete[] score;
    delete[] value;
}

void delete_scores_united() {
    delete[] score;
    delete[] pscore;
    delete[] value;
}

long long compute_score_basic(int compute_set) {
    return score[compute_set];
}

long long compute_score_united(int compute_set) {
    return (long long)(score[compute_set]*mu) + pscore[compute_set];
}

#endif