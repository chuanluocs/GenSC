#ifndef _BREAK_TIES_H_
#define _BREAK_TIES_H_

#include "basis.h"
#include "scoring_function.h"

extern int (*compare_ptr)(long long, long long, int, long long, long long, int, int, int);
extern int (*break_ties_ptr)(int, int, int);

int compare(int, int, int);

int break_ties_score(int set1, int set2, int op);
int break_ties_score_subscore(int set1, int set2, int op);
int break_ties_score_subscore_age(int set1, int set2, int op);
int break_ties_NuSC(int, int, int);
int break_ties_random(int, int, int);
int break_ties_weight(int, int, int);
int break_ties_age(int, int, int);
int break_ties_subscore_random(int, int, int);
int break_ties_subscore_weight(int, int, int);
int break_ties_subscore_age(int, int, int);

#endif