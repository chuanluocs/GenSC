#ifndef _BREAK_TIES_CPP_
#define _BREAK_TIES_CPP_

#include "../include/break_ties.h"

int (*break_ties_ptr)(int, int, int);

/*
flag = 1 select
flag = -1 remove
return 1 set1 better, 0 equals, -1 set2 better
*/
int compare(int set1, int set2, int flag) {
    long long score1, score2;
    int weight1, weight2;
    compute_score(set1, score1, weight1);
    compute_score(set2, score2, weight2);
    long long mult1 = score1*weight2;
    long long mult2 = score2*weight1;
    if(mult1 == mult2) {
        int re = (*break_ties_ptr)(set1, set2, flag);
        if(re == 0)
            return rng.next(3) - 1;
        return re;
    }
    else if(mult1 > mult2) return 1;
    else return -1;
}

int break_ties_score(int set1, int set2, int op) {
    long long mult1 = score[set1] * weight[set2];
    long long mult2 = score[set2] * weight[set1];
    if(mult1 > mult2) return 1;
    if(mult1 < mult2) return -1;
    return 0;
}

int break_ties_score_subscore(int set1, int set2, int op) {
    int score_re = break_ties_score(set1, set2, op);
    if(score_re == 0) {
        if(pscore[set1] < pscore[set2]) return -1;
        if(pscore[set1] > pscore[set2]) return 1;
        return 0;
    }
    return score_re;
}

int break_ties_score_subscore_age(int set1, int set2, int op) {
    int score_re = break_ties_score_subscore(set1, set2, op);
    if(score_re == 0) {
        if(time_stamp[set1] < time_stamp[set2]) return 1;
        if(time_stamp[set1] > time_stamp[set2]) return -1;
        return 0;
    }
    return score_re;
}

int break_ties_random(int set1, int set2, int op) {
    return 0;
}

int break_ties_weight(int set1, int set2, int op) {
    if(weight[set1] > weight[set2]) 
        return -1*op;
    if(weight[set1] < weight[set2])
        return 1*op;
    return 0;
}

int break_ties_age(int set1, int set2, int op) {
    if(time_stamp[set1] > time_stamp[set2]) 
        return -1;
    if(time_stamp[set1] < time_stamp[set2])
        return 1;
    return 0;
}

int break_ties_subscore_random(int set1, int set2, int op) {
    if(pscore[set1] > pscore[set2])
        return 1;
    if(pscore[set1] < pscore[set2])
        return -1;
    return 0;
}

int break_ties_subscore_weight(int set1, int set2, int op) {
    if(pscore[set1] > pscore[set2])
        return 1;
    if(pscore[set1] < pscore[set2])
        return -1;
    if(weight[set1] > weight[set2]) 
        return -1*op;
    if(weight[set1] < weight[set2])
        return 1*op;
    return 0;
}

int break_ties_subscore_age(int set1, int set2, int op) {
    if(pscore[set1] > pscore[set2])
        return 1;
    if(pscore[set1] < pscore[set2])
        return -1;
    if(time_stamp[set1] > time_stamp[set2]) 
        return -1;
    if(time_stamp[set1] < time_stamp[set2])
        return 1;
    return 0;
}

#endif