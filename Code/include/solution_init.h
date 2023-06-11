#ifndef _SOLUTION_INIT_H_
#define _SOLUTION_INIT_H_

#include "basis.h"
#include "set_states.h"

extern void (*init_sol_heuristic_ptr)();

void solution_initialization(); 

void init_solu_best_score_no_bms();
void init_solu_item_based_no_bms();
void init_solu_item_based();
void init_solu_best_score();

#endif