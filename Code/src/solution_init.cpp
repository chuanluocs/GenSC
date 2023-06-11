#ifndef _SOLUTION_INIT_CPP_
#define _SOLUTION_INIT_CPP_

#include "../include/solution_init.h"

void (*init_sol_heuristic_ptr)();

void solution_initialization() {
    // cout << "initializing solution\n";
    (*init_sol_heuristic_ptr)();
    // cout << "solution initialization complete\n";
    return;
}

void init_solu_best_score_no_bms() {
    int best_set, cur_set;
    long long best_set_score, cur_set_score;
    int best_set_weight, cur_set_weight;
    long long cur_mult_re, best_mult_re;
    zero_stack_fill_pointer = 0;
    while (uncover_stack_fill_pointer > 0)
    {
        best_set = -1;
        for (int i = 0; i < not_set_count; ++i)
        {
            int cur_set = not_set_solu[i];
            if(best_set == -1 || compare(best_set, cur_set, 1) < 0) 
                best_set = cur_set;
        }
        if(best_set != -1)
            flip(best_set);
        // else cout << "selecting wrong set" << endl;
    }
}

void init_solu_item_based_no_bms() {
    // cout << "initializing solution NuSC\n";
    int best_set, cur_set;
    zero_stack_fill_pointer = 0;
    while (uncover_stack_fill_pointer > 0)
    {
        int selected_uncover_var = uncover_stack[rng.next(uncover_stack_fill_pointer)];
        best_set = -1;
        int total_num = item_set_num[selected_uncover_var];
        for (int i = 0; i < total_num; ++i)
        {
            int cur_set = item_set[selected_uncover_var][i];
            if(best_set == -1 || compare(best_set, cur_set, 1) < 0) 
                best_set = cur_set;
        }
        if(best_set != -1)
            flip(best_set);
    }
}

void init_solu_item_based() {
    int best_set, cur_set;
    zero_stack_fill_pointer = 0;
    while (uncover_stack_fill_pointer > 0)
    {
        int selected_uncover_var = uncover_stack[rng.next(uncover_stack_fill_pointer)];
        best_set = -1;
        int total_num = item_set_num[selected_uncover_var];
        if(flag_perform_bms && BMS_T < total_num) {
            for (int i = 0; i < BMS_T; ++i)
            {
                int cur_set = item_set[selected_uncover_var][rng.next(total_num)];
                if(best_set == -1 || compare(best_set, cur_set, 1) < 0) 
                    best_set = cur_set;
            }
        } else {
            for (int i = 0; i < total_num; ++i)
            {
                int cur_set = item_set[selected_uncover_var][i];
                if(best_set == -1 || compare(best_set, cur_set, 1) < 0) 
                    best_set = cur_set;
            }
        }
        // cout << "selecting set: " << best_set << endl;
        if(best_set != -1)
            flip(best_set);
        // else cout << "selecting wrong set" << endl;
        // if(check_cover())
        //     cout << "now cover feasible" << endl;
        // else cout << "now cover not feasible" << endl;
    }
}

void init_solu_best_score() {
    int best_set, cur_set;
    long long best_set_score, cur_set_score;
    int best_set_weight, cur_set_weight;
    long long cur_mult_re, best_mult_re;
    zero_stack_fill_pointer = 0;
    while (uncover_stack_fill_pointer > 0)
    {
        best_set = -1;
        if(flag_perform_bms && BMS_T < not_set_count) {
            for (int i = 0; i < BMS_T; ++i)
            {
                int cur_set = not_set_solu[rng.next(not_set_count)];
                if(best_set == -1 || compare(best_set, cur_set, 1) < 0) 
                    best_set = cur_set;
            }
        } else {
            for (int i = 0; i < not_set_count; ++i)
            {
                int cur_set = not_set_solu[i];
                if(best_set == -1 || compare(best_set, cur_set, 1) < 0) 
                    best_set = cur_set;
            }
        }
        if(best_set != -1)
            flip(best_set);
        // else cout << "selecting wrong set" << endl;
    }
}
#endif