#ifndef _SET_STATES_CPP_
#define _SET_STATES_CPP_

#include "../include/set_states.h"

void cover(int selected_var)
{
    int index = index_in_uncover_stack[selected_var];
    int top_set = mypop(uncover_stack);
    index_in_uncover_stack[selected_var] = -1;
    uncover_stack[index] = top_set;
    index_in_uncover_stack[top_set] = index;
}

void uncover(int selected_var)
{
    index_in_uncover_stack[selected_var] = uncover_stack_fill_pointer;
    mypush(selected_var, uncover_stack);
}

void add_set(int s)
{
    index_in_set_solu[s] = set_count;
    set_solu[set_count++] = s;

    int index = index_in_not_in_set_solu[s];
    int top_set = not_set_solu[--not_set_count];
    index_in_not_in_set_solu[top_set] = index;
    not_set_solu[index] = top_set;
    index_in_not_in_set_solu[s] = -1;
}

void remove_set(int s)
{
    int index = index_in_set_solu[s];
    int top_set = set_solu[--set_count];
    index_in_set_solu[top_set] = index;
    set_solu[index] = top_set;
    index_in_set_solu[s] = -1;

    index_in_not_in_set_solu[s] = not_set_count;
    not_set_solu[not_set_count++] = s;
}

void flip(int flip_set)
{
    // cout << (cur_solu[flip_set] == 1 ? "removing" : "selecting");
    // cout << " set: " << flip_set << endl;
    if(flip_set == -1)
        return;
    int cur_set, cur_var;
    long long flip_set_score = score[flip_set];
    long long flip_set_pscore;
    if(flag_subset_score_calculation == 2)
        flip_set_pscore = pscore[flip_set];
    cur_solu[flip_set] = 1 - cur_solu[flip_set];

    if (index_in_zero_stack[flip_set] != -1 && cur_solu[flip_set] == 0)
    {
        int index = index_in_zero_stack[flip_set];
        int top_set = mypop(zero_stack);
        zero_stack[index] = top_set;
        index_in_zero_stack[top_set] = index;
        index_in_zero_stack[flip_set] = -1;
    }

    if (cur_solu[flip_set] == 1)
    {
        add_set(flip_set);
        cur_weight += weight[flip_set];
        for (int i = 0; i < set_item_num[flip_set]; ++i)
        {
            cur_var = set_var[flip_set][i];
            if(flag_perform_cc)
                for (int j = 0; j < item_set_num[cur_var]; ++j)
                    cc[item_set[cur_var][j]] = true;
            ++cover_count[cur_var];
            if (cover_count[cur_var] == 1) //0->1
            {
                for (int j = 0; j < item_set_num[cur_var]; ++j)
                {
                    cur_set = item_set[cur_var][j];
                    score[cur_set] -= value[cur_var];
                    if(flag_subset_score_calculation == 2)
                        pscore[cur_set] += value[cur_var];

                    if(flag_perform_iscc)
                        iscc[cur_set] = true;
                }
                cover_set[cur_var] = flip_set;
                cover(cur_var);
            }
            else if (cover_count[cur_var] == 2) //1->2
            {
                cur_set = cover_set[cur_var];
                score[cur_set] += value[cur_var];
                if (score[cur_set] == 0 && index_in_zero_stack[cur_set] == -1)
                {
                    index_in_zero_stack[cur_set] = zero_stack_fill_pointer;
                    mypush(cur_set, zero_stack);
                }
                if(flag_subset_score_calculation == 2)
                    for (int j = 0; j < item_set_num[cur_var]; ++j)
                        pscore[item_set[cur_var][j]] -= value[cur_var];
                cover_set2[cur_var] = flip_set;
            }
            else if (cover_count[cur_var] == 3) {
                if(flag_subset_score_calculation == 2) {
                    pscore[cover_set[cur_var]] += value[cur_var];
                    pscore[cover_set2[cur_var]] += value[cur_var];
                }
            }
        }
    }
    else
    {
        remove_set(flip_set);
        cur_weight -= weight[flip_set];
        for (int i = 0; i < set_item_num[flip_set]; ++i)
        {
            cur_var = set_var[flip_set][i];
            if(flag_perform_cc)
                for (int j = 0; j < item_set_num[cur_var]; ++j)
                    cc[item_set[cur_var][j]] = true;
            --cover_count[cur_var];

            if (cover_count[cur_var] == 2)
            {
                int flag = 0;
                for (int j = 0; j < item_set_num[cur_var]; ++j)
                {
                    cur_set = item_set[cur_var][j];
                    if (cur_solu[cur_set] == 1)
                    {
                        if(flag_subset_score_calculation == 2)
                            pscore[cur_set] -= value[cur_var];
                        if (flag == 0)
                        {
                            cover_set[cur_var] = cur_set;
                            flag = 1;
                        }
                        else
                        {
                            cover_set2[cur_var] = cur_set;
                            break;
                        }
                    }
                }
            }
            else if (cover_count[cur_var] == 1) //2->1
            {
                if (cover_set[cur_var] == flip_set)
                    cover_set[cur_var] = cover_set2[cur_var];
                
                score[cover_set[cur_var]] -= value[cur_var];  
                if(flag_subset_score_calculation == 2)
                    for (int j = 0; j < item_set_num[cur_var]; ++j)
                        pscore[item_set[cur_var][j]] += value[cur_var];
                if (index_in_zero_stack[cover_set[cur_var]] != -1 && score[cover_set[cur_var]] != 0)
                {
                    int top_set = mypop(zero_stack);
                    int index = index_in_zero_stack[cover_set[cur_var]];
                    zero_stack[index] = top_set;
                    index_in_zero_stack[top_set] = index;
                    index_in_zero_stack[cover_set[cur_var]] = -1;
                }
            }
            else if (cover_count[cur_var] == 0) //1->0
            {
                for (int j = 0; j < item_set_num[cur_var]; ++j)
                {
                    cur_set = item_set[cur_var][j];
                    score[cur_set] += value[cur_var];
                    if(flag_subset_score_calculation == 2)
                        pscore[cur_set] -= value[cur_var];

                    if(flag_perform_iscc)
                        iscc[cur_set] = true;
                }
                uncover(cur_var);
            }
        }
        if(flag_perform_cc)
            cc[flip_set] = false;
        if(flag_perform_iscc)
            iscc[flip_set] = false;
    }
    if(flag_subset_score_calculation == 2)
        pscore[flip_set] = -flip_set_pscore;
    score[flip_set] = -flip_set_score;
}

#endif