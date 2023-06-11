#ifndef _UPDATE_VARIABLES_H_
#define _UPDATE_VARIABLES_H_

#include "basis.h"
#include "scoring_function.h"

extern void (*update_variables_item_weighting_ptr)();

extern int SAPS_T;
extern double SAPS_R;
extern double PAWS_P;

void update_variables();

void update_variables_no_item_weighting();
void update_variables_NuSC();
void update_variables_SAPS();
void update_variables_PAWS();

#endif