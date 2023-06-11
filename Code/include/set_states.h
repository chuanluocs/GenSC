#ifndef _SET_STATES_H_
#define _SET_STATES_H_

#include "basis.h"
#include "scoring_function.h"
#include "cc_and_tabu.h"

void cover(int);
void uncover(int);
void add_set(int);
void remove_set(int);
void flip(int);

#endif