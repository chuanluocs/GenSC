#ifndef _PARSE_ARGUMENTS_H_
#define _PARSE_ARGUMENTS_H_

#include "basis.h"
#include "solution_init.h"
#include "update_variables.h"
#include "scoring_function.h"
#include "break_ties.h"
#include "reconstruct.h"
#include "setup.h"

extern string inst_filename;
extern int seed;
extern bool flag_auto_select;
extern bool flag_print_sol;
extern bool flag_print_smart_format;
extern bool flag_print_step;
extern bool flag_perform_bms;
extern int flag_subset_score_calculation;
extern int flag_solution_initialization;
extern int flag_reconstruction;
extern int flag_subset_removal_scheme;
extern int flag_subset_addition;
extern int flag_perform_alternate_method;
extern int flag_update_item_weight_scheme;
extern bool flag_perform_cc;
extern bool flag_perform_iscc;
extern bool flag_perform_tabu;
extern int flag_subset_selection_scheme;

bool parse_arguments(int argc, char **argv);

#endif
