#include "../include/basis.h"
#include "../include/setup.h"
#include "../include/init.h"
#include "../include/preprocess.h"
#include "../include/solution_init.h"
#include "../include/reconstruct.h"
#include "../include/subset_removal.h"
#include "../include/subset_addition.h"
#include "../include/update_variables.h"

int main(int argc, char **argv) {
    if(setup(argc, argv) == -1)
        return -1;
    preprocessing();
    init_variables();
    solution_initialization();
    for(step=0;step<max_step;step++) {
        if(uncover_stack_fill_pointer == 0) {
            if (zero_stack_fill_pointer > 0)
            {
                int flip_set = select_set_from_zero_stack();
                if (flip_set == -1)
                    break;
                flip(flip_set);
                time_stamp[flip_set] = step;
                continue;
            }
            else {
                update_best_to_cur();
                reconstruct();
            }
        }
        if(uncover_stack_fill_pointer > 0) {
            int best_set = subset_addition();
            if(flag_perform_alternate_method == 1) {
                // int flip_set = subset_removal();
                // flip(flip_set);
                flip(best_set);
                // time_stamp[flip_set] = step;
                time_stamp[best_set] = step;
                // reconstruct();
                update_variables();
                if (step % 1000 == 0)
                    if (get_runtime() > cutoff_time)
                        break;
                continue;
            }

            if(best_set == -1)
                break;
            else if (cur_weight + weight[best_set] >= best_weight)
            {
                if(flag_perform_alternate_method == 2 || flag_perform_alternate_method == 3) {
                    int rmN = sets_rmN();
                    int flip_set = subset_removal();
                    long long best_set_score, flip_set_score;
                    int best_set_weight, flip_set_weight;
                    double best_set_div, flip_set_div, eps = 1e-6;
                    compute_score(best_set, best_set_score, best_set_weight);
                    compute_score(flip_set, flip_set_score, flip_set_weight);
                    best_set_div = best_set_score/(double)best_set_weight;
                    flip_set_div = flip_set_score/(double)flip_set_weight;
                    if(flag_perform_alternate_method == 2) {
                        if (best_set_div + flip_set_div > eps)
                        {
                            flip(flip_set);
                            best_set_div += flip_set_div;
                            time_stamp[flip_set] = step;
                            rmN--;
                            while(rmN > 0) {
                                flip_set = subset_removal();
                                compute_score(flip_set, flip_set_score, flip_set_weight);
                                flip_set_div = flip_set_score/(double)flip_set_weight;
                                if(best_set_div + flip_set_div > eps) {
                                    flip(flip_set);
                                    best_set_div += flip_set_div;
                                    time_stamp[flip_set] = step;
                                    rmN--;
                                } else break;
                            }
                            flip(best_set);
                            time_stamp[best_set] = step;
                        }
                        else
                        {
                            // flip_set = subset_removal();
                            flip(flip_set);
                            time_stamp[flip_set] = step;

                            flip_set = subset_removal();
                            flip(flip_set);
                            time_stamp[flip_set] = step;

                        }
                    }
                    else if(flag_perform_alternate_method == 3) {
                        flip(flip_set);
                        best_set_div += flip_set_div;
                        time_stamp[flip_set] = step;
                        rmN--;
                        while(rmN > 0) {
                            flip_set = subset_removal();
                            compute_score(flip_set, flip_set_score, flip_set_weight);
                            flip_set_div = flip_set_score/(double)flip_set_weight;
                            if(best_set_div + flip_set_div > eps) {
                                flip(flip_set);
                                best_set_div += flip_set_div;
                                time_stamp[flip_set] = step;
                                rmN--;
                            } else break;
                        }
                    }
                    update_variables();
                    if (step % 1000 == 0)
                        if (get_runtime() > cutoff_time)
                            break;
                    continue;
                }
            
                if(flag_perform_alternate_method == 4) { // rmN=1
                    int flip_set = subset_removal();
                    if (flip_set == -1) 
                        break;
                    else {
                        long long mult1, mult2, score1, score2;
                        score1 = -score[flip_set], score2 = score[best_set];
                        int weight1 = weight[flip_set], weight2 = weight[best_set];
                        mult1 = score1*weight2;
                        mult2 = score2*weight1;
                        if(mult1 < mult2) {
                            if(flip_set == -1 || best_set == -1)
                                break;

                            flip(flip_set);
                            flip(best_set);
                            time_stamp[flip_set] = step;
                            time_stamp[best_set] = step;
                            
                            if (step % 1000 == 0)
                                if (get_runtime() > cutoff_time)
                                    break;
                            continue;
                        } else {
                            // flip_set = subset_removal();
                            // if(flip_set == -1)
                            //     break;
                            flip(flip_set);
                            time_stamp[flip_set] = step;

                            flip_set = subset_removal();
                            if(flip_set == -1)
                                break;
                            if(flip_set >= 0) {
                                flip(flip_set);
                                time_stamp[flip_set] = step;
                            }
                                        
                            if (step % 1000 == 0)
                                if (get_runtime() > cutoff_time)
                                    break;
                            continue;
                        }
                    }
                }
            }
            else {
                flip(best_set);
                time_stamp[best_set] = step;
                update_variables();
                if (step % 1000 == 0)
                    if (get_runtime() > cutoff_time)
                        break;
                continue;
            }
        }
        // reconstruct();
        if (step % 1000 == 0)
            if (get_runtime() > cutoff_time)
                break;
    }
    check_best_solution();
    output();
    free_memory();
    return 0;
}
