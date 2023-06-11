#ifndef _SUBSET_ADDITION_CPP_
#define _SUBSET_ADDITION_CPP_

#include "../include/subset_addition.h"

int (*get_select_set_ptr)();
int set_to_select;
static double *sets_score;
static int *sets_selected;
static int sets_score_num;

void subset_addition_init(int num) {
    sets_score = new double[num];
    sets_selected = new int[num];
}

void subset_addition_delete() {
    delete[] sets_score;
    delete[] sets_selected;
}

int subset_addition() {
    // if(set_to_select == -1) 
    //     cout << "subset_addition selecting -1" << endl;
    return (*get_select_set_ptr)();
}

int greedy_addition() {
    int best_set = -1, cur_set;
    if(flag_perform_bms && BMS_T < not_set_count) {
        for (int j = 0; j < BMS_T; ++j)
        {
            cur_set = not_set_solu[rng.next(not_set_count)];
            if(best_set == -1) 
                best_set = cur_set;
            if(!filter_cc(cur_set)) continue;
            if(!filter_iscc(cur_set)) continue;
            if(!filter_tabu(cur_set)) continue;
            if(compare(cur_set, best_set, 1) > 0)
                best_set = cur_set;
        }
    } else {
        for (int j = 0; j < not_set_count; ++j)
        {
            cur_set = not_set_solu[j];
            if(best_set == -1) 
                best_set = cur_set;
            if(!filter_cc(cur_set)) continue;
            if(!filter_iscc(cur_set)) continue;
            if(!filter_tabu(cur_set)) continue;
            if(compare(cur_set, best_set, 1) > 0)
                best_set = cur_set;
        }
    }
    return best_set;
}

int novel_addition() {
    int best_set = -1, sec_best_set = -1, cur_set;
    if(flag_perform_bms && BMS_T < not_set_count) {
        for (int j = 0; j < BMS_T; ++j)
        {
            cur_set = not_set_solu[rng.next(not_set_count)];
            if(best_set == -1) best_set = cur_set;
            if(!filter_cc(cur_set)) continue;
            if(!filter_iscc(cur_set)) continue;
            if(!filter_tabu(cur_set)) continue;
            if(best_set != -1) {
                if(compare(cur_set, best_set, 1) > 0) {
                    sec_best_set = best_set;
                    best_set = cur_set;
                } else {
                    if(sec_best_set == -1)
                        sec_best_set = cur_set;
                    else if(compare(cur_set, sec_best_set, 1) > 0) 
                        sec_best_set = cur_set;
                }
            }
        }
    } else {
        for (int j = 0; j < not_set_count; ++j)
        {
            cur_set = not_set_solu[j];
            if(best_set == -1) best_set = cur_set;
            else if(sec_best_set == -1) sec_best_set = cur_set;
            if(!filter_cc(cur_set)) continue;
            if(!filter_iscc(cur_set)) continue;
            if(!filter_tabu(cur_set)) continue;
            if(best_set != -1) {
                if(compare(cur_set, best_set, 1) > 0) {
                    sec_best_set = best_set;
                    best_set = cur_set;
                } else {
                    if(sec_best_set == -1)
                        sec_best_set = cur_set;
                    else if(compare(cur_set, sec_best_set, 1) > 0) 
                        sec_best_set = cur_set;
                }
            }
        }
    }
    if(sec_best_set != -1 && rng.nextClosed() < novel_addition_prob)
        best_set = sec_best_set;
    return best_set;
}

int prob_dis_addition() {
    double sum_score = 0.0, cur_exact_score, rand_v;
    long long cur_score;
    int cur_weight;
    int cur_set, select_set;
    sets_score_num = 0;
    if(flag_perform_bms && BMS_T < not_set_count) {
        for(int i=0;i<BMS_T;i++) {
            cur_set = not_set_solu[rng.next(not_set_count)];
            compute_score(cur_set, cur_score, cur_weight);
            cur_exact_score = cur_score/(double)cur_weight;
            sets_score[sets_score_num] = cur_exact_score;
            sets_score[sets_score_num] = cur_set;
            sets_score_num++;
            sum_score += cur_exact_score;
        }
    } else {
        for (int j = 0; j < not_set_count; ++j) {
            cur_set = not_set_solu[j];
            compute_score(cur_set, cur_score, cur_weight);
            cur_exact_score = cur_score/(double)cur_weight;
            sets_score[sets_score_num] = cur_exact_score;
            sets_score[sets_score_num] = cur_set;
            sets_score_num++;
            sum_score += cur_exact_score;
        }
    }
    rand_v = rng.nextClosed();
    select_set = 0;
    double score_ratio;
    while(select_set < sets_score_num) {
        score_ratio = sets_score[select_set] / sum_score;
        if(rand_v - score_ratio < 1e-6 || score_ratio - rand_v < 1e-6)
            return sets_selected[select_set];
        rand_v -= score_ratio;
        select_set++;
    } 
    return sets_selected[--select_set];
}

int local_greedy_addition() {
    int best_set = -1, cur_set;
    int selected_uncover_var = uncover_stack[rng.next(uncover_stack_fill_pointer)];
    int total_num = item_set_num[selected_uncover_var];
    if(total_num < BMS_T) {
        for(int i=0;i<total_num;i++) {
            cur_set = item_set[selected_uncover_var][i];
            if(best_set == -1) best_set = cur_set;
            if(!filter_cc(cur_set)) continue;
            if(!filter_iscc(cur_set)) continue;
            if(!filter_tabu(cur_set)) continue;
            if(compare(cur_set, best_set, 1) > 0)
                best_set = cur_set;
        }
    } else {
        for(int i=0;i<BMS_T;i++) {
            cur_set = item_set[selected_uncover_var][rng.next(total_num)];
            if(best_set == -1) best_set = cur_set;
            if(!filter_cc(cur_set)) continue;
            if(!filter_iscc(cur_set)) continue;
            if(!filter_tabu(cur_set)) continue;
            if(compare(cur_set, best_set, 1) > 0)
                best_set = cur_set;
        } 
    }
    return best_set;
}

int local_novel_addition() {
    // if(cout_flag == 0) {
    //     cout << "selecting set NuSC\n";
    //     cout_flag = 1;
    // }
    int best_set = -1, sec_best_set = -1, cur_set;
    int selected_uncover_var = uncover_stack[rng.next(uncover_stack_fill_pointer)];
    int total_num = item_set_num[selected_uncover_var];
    if(total_num < BMS_T) {
        for(int i=0;i<total_num;i++) {
            cur_set = item_set[selected_uncover_var][i];
            if(best_set == -1) best_set = cur_set;
            if(!filter_cc(cur_set)) continue;
            if(!filter_iscc(cur_set)) continue;
            if(!filter_tabu(cur_set)) continue;
            if(best_set != -1) {
                if(compare(cur_set, best_set, 1) > 0) {
                    sec_best_set = best_set;
                    best_set = cur_set;
                } else {
                    if(sec_best_set == -1)
                        sec_best_set = cur_set;
                    else if(compare(cur_set, sec_best_set, 1) > 0) 
                        sec_best_set = cur_set;
                }
            }
        }
    } else {
        for(int i=0;i<BMS_T;i++) {
            cur_set = item_set[selected_uncover_var][rng.next(total_num)];
            if(best_set == -1) best_set = cur_set;
            if(!filter_cc(cur_set)) continue;
            if(!filter_iscc(cur_set)) continue;
            if(!filter_tabu(cur_set)) continue;
            if(best_set != -1) {
                if(compare(cur_set, best_set, 1) > 0) {
                    sec_best_set = best_set;
                    best_set = cur_set;
                } else {
                    if(sec_best_set == -1)
                        sec_best_set = cur_set;
                    else if(compare(cur_set, sec_best_set, 1) > 0) 
                        sec_best_set = cur_set;
                }
            }
        }
    }
    if(sec_best_set != -1 && rng.nextClosed() < novel_addition_prob)
        best_set = sec_best_set;
    return best_set;
}

int local_novel_addition_no_bms() {
    // if(cout_flag == 0) {
    //     cout << "selecting set NuSC\n";
    //     cout_flag = 1;
    // }
    int best_set = -1, sec_best_set = -1, cur_set;
    int selected_uncover_var = uncover_stack[rng.next(uncover_stack_fill_pointer)];
    int total_num = item_set_num[selected_uncover_var];
    for(int i=0;i<total_num;i++) {
        cur_set = item_set[selected_uncover_var][i];
        if(best_set == -1) best_set = cur_set;
        if(!filter_cc(cur_set)) continue;
        if(!filter_iscc(cur_set)) continue;
        if(!filter_tabu(cur_set)) continue;
        if(best_set != -1) {
            if(compare(cur_set, best_set, 1) > 0) {
                sec_best_set = best_set;
                best_set = cur_set;
            } else {
                if(sec_best_set == -1)
                    sec_best_set = cur_set;
                else if(compare(cur_set, sec_best_set, 1) > 0) 
                    sec_best_set = cur_set;
            }
        }
    }
    if(sec_best_set != -1 && rng.nextClosed() < novel_addition_prob)
        best_set = sec_best_set;
    return best_set;
}

void greedy_addition_for_reconstruct_swap_t(bool *selected, int *swapTsets) {
    for(int i=0;i<reconstruct_swap_T-1;i++) {
        int best_set = -1, cur_set;
        if(flag_perform_bms && BMS_T < not_set_count) {
            for (int j = 0; j < BMS_T; ++j)
            {
                cur_set = not_set_solu[rng.next(not_set_count)];
                if(selected[cur_set]) continue;
                if(best_set == -1) 
                    best_set = cur_set;
                if(!filter_cc(cur_set)) continue;
                if(!filter_iscc(cur_set)) continue;
                if(!filter_tabu(cur_set)) continue;
                if(compare(cur_set, best_set, 1) > 0)
                    best_set = cur_set;
            }
        } else {
            for (int j = 0; j < not_set_count; ++j)
            {
                cur_set = not_set_solu[j];
                if(selected[cur_set]) continue;
                if(best_set == -1) 
                    best_set = cur_set;
                if(!filter_cc(cur_set)) continue;
                if(!filter_iscc(cur_set)) continue;
                if(!filter_tabu(cur_set)) continue;
                if(compare(cur_set, best_set, 1) > 0)
                    best_set = cur_set;
            }
        }
        swapTsets[i] = best_set;
    }
}

#endif