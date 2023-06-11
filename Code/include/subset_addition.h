#ifndef _SUBSET_ADDITION_H_
#define _SUBSET_ADDITION_H_

#include "basis.h"
#include "set_states.h"
#include "break_ties.h"
#include "cc_and_tabu.h"
#include "reconstruct.h"

extern int (*get_select_set_ptr)();
extern int set_to_select;

void subset_addition_init(int);
void subset_addition_delete();

int subset_addition();

int greedy_addition();
int novel_addition();
int prob_dis_addition();
int local_greedy_addition();
int local_novel_addition();
int local_novel_addition_no_bms();

void greedy_addition_for_reconstruct_swap_t(bool *, int *);

#endif