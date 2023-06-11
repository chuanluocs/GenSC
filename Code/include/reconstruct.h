#ifndef _RECONSTRUCT_H_
#define _RECONSTRUCT_H_

#include "basis.h"
#include "set_states.h"
#include "subset_removal.h"

extern bool reconstruct_with_prob;
extern double reconstruct_prob;
extern int reconstruct_swap_T;
extern void (*reconstruct_solu_ptr)();
extern void (*reconstruct_swapT_init)(int);
extern void (*reconstruct_swapT_delete)();

void reconstruct();

void reconstruct_init(int);
void reconstruct_delete();

void reconstruct_swapT_delete_none();
void reconstruct_swapT_delete_do();
void reconstruct_swapT_init_none(int);
void reconstruct_swapT_init_do(int);

void reconstruct_remove_one_randomly();
void reconstruct_swap_t();
void reconstruct_remove_one_best();

#endif