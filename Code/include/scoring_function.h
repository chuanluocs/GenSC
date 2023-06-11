#ifndef _SCORING_FUNCTION_H_
#define _SCORING_FUNCTION_H_

#include "basis.h"

extern long long *score;
extern long long *pscore;
extern long long *value;

extern long long (*compute_score_ptr)(int);
extern void (*init_scores_ptr)(int, int);
extern void (*delete_scores_ptr)();

void init_scores(int, int);
void delete_scores();

void compute_score(int, long long &, int &);

void init_scores_no_weighting(int, int);
void init_scores_basic(int, int);
void init_scores_united(int, int);

void delete_scores_no_weighting();
void delete_scores_basic();
void delete_scores_united();

long long compute_score_no_weighting(int);
long long compute_score_basic(int);
long long compute_score_united(int);

#endif