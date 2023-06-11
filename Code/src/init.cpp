#ifndef _INIT_CPP_
#define _INIT_CPP_

#include "../include/init.h"

void init_variables() {
    // cout << "initializing basic variables\n";
    if(flag_print_smart_format) {
        cout << "c best_weight best_time";
        if(flag_print_step)
            cout << " best_step" << endl;
        else
            cout << endl;
    }
    start_timing();
        
    cur_weight = reduce_weight;
    best_weight = LONG_LONG_MAX;
    best_step = LONG_LONG_MAX;
    not_set_count = 0;
    for (int i = 0; i < set_num; ++i)
    {
        best_solu[i] = -1;
        if (fix[i] == 1)
        {
            cur_solu[i] = 1;
            cur_weight += weight[i];
            continue;
        } 
        if (fix[i] != 0) {
            cur_solu[i] = 0;
            continue;
        }
        cur_solu[i] = 0;
        index_in_set_solu[i] = -1;
        index_in_zero_stack[i] = -1;
        time_stamp[i] = 0;
        
        score[i] = set_item_num[i];
        if(flag_subset_score_calculation == 2)
            pscore[i] = 0;
        if(flag_perform_cc)
            cc[i] = true;
        if(flag_perform_iscc)
            iscc[i] = true;

        index_in_not_in_set_solu[i] = not_set_count;
        not_set_solu[not_set_count++] = i;
    }
    for (int i = 0; i < item_num; ++i)
    {
        if (item_delete[i] == 1)
            continue;
        value[i] = 1;
        cover_count[i] = 0;
    }

    uncover_stack_fill_pointer = 0;
    set_count = 0;
    for (int i = 0; i < item_num; ++i)
    {
        if (item_delete[i] == 1)
            continue;
        index_in_uncover_stack[i] = uncover_stack_fill_pointer;
        mypush(i, uncover_stack);
    }
    check_cur_solution();

    // cout << "initialization for basic variables complete\n";
}


#endif