#ifndef _UPDATE_VARIABLES_CPP_
#define _UPDATE_VARIABLES_CPP_

#include "../include/update_variables.h"

void (*update_variables_item_weighting_ptr)();

int SAPS_T;
double SAPS_R;
double PAWS_P;

// static int cout_flag = 0;

void update_variables() {
    (*update_variables_item_weighting_ptr)();
}

void update_variables_no_item_weighting() {}

void update_variables_NuSC() {
    // if(cout_flag == 0) {
    //     cout << "updating variables NuSC\n";
    //     cout_flag = 1;
    // }
    int cur_set, cur_var;
    for (int i = 0; i < uncover_stack_fill_pointer; ++i)
    {
        cur_var = uncover_stack[i];
        value[cur_var]++;
        for (int j = 0; j < item_set_num[cur_var]; ++j)
        {
            cur_set = item_set[cur_var][j];
            score[cur_set]++;
        }
    }    
}

void update_variables_SAPS() {
    int cur_set, cur_var;
    for (int i = 0; i < uncover_stack_fill_pointer; ++i)
    {
        cur_var = uncover_stack[i];
        value[cur_var]++;
        for (int j = 0; j < item_set_num[cur_var]; ++j)
        {
            cur_set = item_set[cur_var][j];
            score[cur_set]++;
        }
    }
    long long sum = 0;
    int temp_weight;
    for(int i=0;i<item_num;i++)
        sum += value[i];
    if(sum > (long long)SAPS_T * item_num) {
        for(int i=0;i<item_num;i++) {
            temp_weight = value[i];
            value[i] = (int)(value[i] * SAPS_R);
            if(value[i] < 1)
                value[i] = 1;
            for(int j=0;j<item_set_num[cur_var];++j) {
                cur_set = item_set[cur_var][j];
                score[cur_set] += value[i] - temp_weight;
            }
        }
    }
}

void update_variables_PAWS() {
    int cur_set, cur_var;
    if(rng.nextClosed() < PAWS_P) {
        for (int i = 0; i < uncover_stack_fill_pointer; ++i)
        {
            cur_var = uncover_stack[i];
            value[cur_var]++;
            for (int j = 0; j < item_set_num[cur_var]; ++j)
            {
                cur_set = item_set[cur_var][j];
                score[cur_set]++;
            }
        }
    } else {
        for(int i=0;i<item_num;i++) {
            if(value[i] <= 1) continue;
            value[i]--;
            for (int j = 0; j < item_set_num[cur_var]; ++j)
            {
                cur_set = item_set[cur_var][j];
                score[cur_set]--;
            }
        }
    }
}

#endif