#ifndef _CC_AND_TABU_H_
#define _CC_AND_TABU_H_

#include "basis.h"

extern bool *cc;
extern bool *iscc;
extern int tabu_alpha;

void init_cc_and_tabu(int);
void delete_cc_and_tabu();

bool filter_cc(int s);
bool filter_iscc(int s);
bool filter_tabu(int s);

#endif