#ifndef _SUBSET_REMOVAL_H_
#define _SUBSET_REMOVAL_H_

#include "basis.h"
#include "break_ties.h"
#include "scoring_function.h"
#include "set_states.h"

extern int (*get_rmN_ptr)();
extern int (*get_remove_set_ptr)();

extern int SAinitN;
extern int SAt;
extern int rmN;

void subset_removal_init(int);

int sets_rmN();
int subset_removal();

int remove_one();
int adaptive_removal();

int remove_best_score();

#endif