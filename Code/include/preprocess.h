#ifndef _PREPROCESS_H_
#define _PREPROCESS_H_

#include "setup.h"
#include "basis.h"

void preprocessing();
void simplify();

void simplify_degree1(int);
void simplify_degree2(int);
void simplify_degree3(int);

void fix1(int);
void fix9(int);

#endif
