#ifndef _PARSE_ARGUMENTS_CPP
#define _PARSE_ARGUMENTS_CPP

#include "../include/parse_arguments.h"

string inst_filename;
int seed;
bool flag_auto_select;
bool flag_print_sol;
bool flag_print_smart_format;
bool flag_print_step;
bool flag_perform_bms;
int flag_subset_score_calculation; 
int flag_solution_initialization;
int flag_reconstruction;
int flag_subset_removal_scheme;
int flag_subset_addition;
int flag_perform_alternate_method;
int flag_update_item_weight_scheme;
bool flag_perform_cc;
bool flag_perform_iscc;
bool flag_perform_tabu;
int flag_subset_selection_scheme;

bool parse_arguments(int argc, char **argv) {
    int i;
    bool flag_inst = false;
    bool flag_seed = false;
    bool flag_time = false;

    default_algorithm_settings();

    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-inst") == 0) {
            i++;
            if (i >= argc) return false;
            inst_filename = argv[i];
            flag_inst = true;
            continue;
        } else if (strcmp(argv[i], "-auto") == 0) {
            i++;
            if (i >= argc) return false;
            if (strcmp(argv[i], "0") == 0) {
                flag_auto_select = false;
                continue;
            } else if (strcmp(argv[i], "1") == 0) {
                flag_auto_select = true;
                continue;
            } else return false;
        } else if (strcmp(argv[i], "-formatted_print") == 0) {
            i++;
            if (i >= argc) return false;
            if (strcmp(argv[i], "0") == 0) {
                flag_print_smart_format = false;
                continue;
            } else if (strcmp(argv[i], "1") == 0) {
                flag_print_smart_format = true;
                continue;
            } else return false;
        } else if (strcmp(argv[i], "-seed") == 0) {
            i++;
            if (i >= argc) return false;
            sscanf(argv[i], "%d", &seed);
            if(seed < 0) return false;
            flag_seed = true;
            continue;
        } else if (strcmp(argv[i], "-max_step") == 0) {
            i++;
            if (i >= argc) return false;
            sscanf(argv[i], "%lld", &max_step);
            if(max_step <= 0) return false;
            continue;
        } else if (strcmp(argv[i], "-cutoff_time") == 0) {
            i++;
            if (i >= argc) return false;
            sscanf(argv[i], "%d", &cutoff_time);
            if(cutoff_time <= 0) return false;
            flag_time = true;
            continue;
        } else if (strcmp(argv[i], "-print_sol") == 0) {
            i++;
            if (i >= argc) return false;
            if (strcmp(argv[i], "0") == 0) {
                flag_print_sol = false;
                continue;
            } else if (strcmp(argv[i], "1") == 0) {
                flag_print_sol = true;
                continue;
            } else return false;
        }  else if (strcmp(argv[i], "-print_step") == 0) {
            i++;
            if (i >= argc) return false;
            if (strcmp(argv[i], "0") == 0) {
                flag_print_step = false;
                continue;
            } else if (strcmp(argv[i], "1") == 0) {
                flag_print_step = true;
                continue;
            } else return false;
        } else if(strcmp(argv[i], "-perform_bms") == 0) {
            i++;
            if(i >= argc) return false;
            if(strcmp(argv[i], "0") == 0) {
                flag_perform_bms = false;
                continue;
            } else if(strcmp(argv[i], "1") == 0) {
                flag_perform_bms = true;
                continue;
            } else return false;
        } else if(strcmp(argv[i], "-bms_t") == 0) {
            i++;
            if(i >= argc) return false;
            sscanf(argv[i], "%d", &BMS_T);
            if(BMS_T <= 0) return false;
            continue;
        } else if(strcmp(argv[i], "-subset_score_calculation") == 0) {
            i++;
            if(i >= argc) return false;
            sscanf(argv[i], "%d", &flag_subset_score_calculation);
            if(flag_subset_score_calculation < 0 || flag_subset_score_calculation > 2) return false;
            continue;
        } else if(strcmp(argv[i], "-solution_initialization_scheme") == 0) {
            i++;
            if(i >= argc) return false;
            sscanf(argv[i], "%d", &flag_solution_initialization);
            if(flag_solution_initialization < 1 || flag_solution_initialization > 4) return false;
            continue;
        } else if(strcmp(argv[i], "-perform_cc") == 0) {
            i++;
            if(i >= argc) return false;
            if(strcmp(argv[i], "0") == 0) {
                flag_perform_cc = false;
                continue;
            } else if(strcmp(argv[i], "1") == 0) {
                flag_perform_cc = true; 
                continue;
            } else return false;
        } else if(strcmp(argv[i], "-perform_iscc") == 0) {
            i++;
            if(i >= argc) return false;
            if(strcmp(argv[i], "0") == 0) {
                flag_perform_iscc = false;
                continue;
            } else if(strcmp(argv[i], "1") == 0) {
                flag_perform_iscc = true; 
                continue;
            } else return false;
        } else if(strcmp(argv[i], "-perform_tabu") == 0) {
            i++;
            if(i >= argc) return false;
            if(strcmp(argv[i], "0") == 0) {
                flag_perform_tabu = false;
                continue;
            } else if(strcmp(argv[i], "1") == 0) {
                flag_perform_tabu = true; 
                continue;
            } else return false;
        } else if(strcmp(argv[i], "-tabu_alpha") == 0) {
            i++;
            if(i >= argc) return false;
            sscanf(argv[i], "%d", &tabu_alpha);
            if(tabu_alpha <= 0) return false;
            continue;
        } else if(strcmp(argv[i], "-reconstruction_scheme") == 0) {
            i++;
            if(i >= argc) return false;
            sscanf(argv[i], "%d", &flag_reconstruction);
            if(flag_reconstruction < 1 || flag_reconstruction > 3) return false;
            continue;
        } else if(strcmp(argv[i], "-reconstruct_swap_T") == 0) {
            i++;
            if(i >= argc) return false;
            sscanf(argv[i], "%d", &reconstruct_swap_T);
            if(reconstruct_swap_T <= 1) return false;
            continue;
        } else if(strcmp(argv[i], "-reconstruction_with_prob") == 0) {
            i++;
            if(i >= argc) return false;
            if(strcmp(argv[i], "0") == 0) {
                reconstruct_with_prob = false;
                continue;
            } else if(strcmp(argv[i], "1") == 0) {
                reconstruct_with_prob = true;
                continue;
            } else return false;
        } else if(strcmp(argv[i], "-reconstruction_prob") == 0) {
            i++;
            if(i >= argc) return false;
            sscanf(argv[i], "%lf", &reconstruct_prob);
            if(reconstruct_prob < 0.0 || reconstruct_prob > 1.0) return false;
            continue;
        } else if(strcmp(argv[i], "-subset_removal_scheme") == 0) {
            i++;
            if(i >= argc) return false;
            sscanf(argv[i], "%d", &flag_subset_removal_scheme);
            if(flag_subset_removal_scheme < 1 || flag_subset_removal_scheme > 2) return false;
            continue;
        } else if(strcmp(argv[i], "-subset_addition_scheme") == 0) {
            i++;
            if(i >= argc) return false;
            sscanf(argv[i], "%d", &flag_subset_addition);
            if(flag_subset_addition < 1 || flag_subset_addition > 6) return false;
            continue;
        } else if(strcmp(argv[i], "-perform_alternate_method") == 0) {
            i++;
            if(i >= argc) return false;
            sscanf(argv[i], "%d", &flag_perform_alternate_method);
            if(flag_perform_alternate_method < 1 || flag_perform_alternate_method > 4) return false;
            continue;
        } else if(strcmp(argv[i], "-update_item_values_scheme") == 0) {
            i++;
            if(i >= argc) return false;
            sscanf(argv[i], "%d", &flag_update_item_weight_scheme);
            if(flag_update_item_weight_scheme < 1 || flag_update_item_weight_scheme > 4) return false;
            continue;
        } else if(strcmp(argv[i], "-update_item_values_SAPST") == 0) {
            i++;
            if(i >= argc) return false;
            sscanf(argv[i], "%d", &SAPS_T);
            if(SAPS_T <= 0) return false;
            continue;
        } else if(strcmp(argv[i], "-update_item_values_SAPSR") == 0) {
            i++;
            if(i >= argc) return false;
            sscanf(argv[i], "%lf", &SAPS_R);
            if(SAPS_R < 0.0 || SAPS_R > 1.0) return false;
            continue;
        } else if(strcmp(argv[i], "-update_item_values_PAWSP") == 0) {
            i++;
            if(i >= argc) return false;
            sscanf(argv[i], "%lf", &PAWS_P);
            if(PAWS_P < 0.0 || PAWS_P > 1.0) return false;
            continue;
        } else if(strcmp(argv[i], "-united_calculation_mu") == 0) {
            i++;
            if(i >= argc) return false;
            sscanf(argv[i], "%d", &mu);
            if(mu <= 1) return false;
            continue;
        } else if(strcmp(argv[i], "-novel_addition_prob") == 0) {
            i++;
            if(i >= argc) return false;
            sscanf(argv[i], "%lf", &novel_addition_prob);
            if(novel_addition_prob < 0.0 || novel_addition_prob > 1.0) return false;
            continue;
        } else if(strcmp(argv[i], "-subset_selection_scheme") == 0) {
            i++;
            if(i >= argc) return false;
            sscanf(argv[i], "%d", &flag_subset_selection_scheme);
            if(flag_subset_selection_scheme < 1 || flag_subset_selection_scheme > 9) return false;
            continue;
        } else if(strcmp(argv[i], "-SAinitN") == 0) {
            i++;
            if(i >= argc) return false;
            sscanf(argv[i], "%d", &SAinitN);
            if(SAinitN < 2 || SAinitN > 5) return false;
            continue;
        } else if(strcmp(argv[i], "-SAt") == 0) {
            i++;
            if(i >= argc) return false;
            sscanf(argv[i], "%d", &SAt);
            if(SAt < 1) return false;
            continue;
        } else return false;
    }
    if(flag_auto_select) {
        if(!flag_inst) return false;
        ifstream infile(inst_filename);
        if (!infile.is_open()) {
            cout << "infile error" << endl;
            exit(1);
        }
        infile >> item_num >> set_num;

        if(item_num > 2500 && item_num < 5000 && set_num > 920000 && set_num < 1100000) // rail
            Rail_settings();

        if((item_num > 500 && item_num < 520 && set_num > 200 && set_num < 220) || 
            (item_num > 1000 && item_num < 1100 && set_num > 300 && set_num < 350) || 
            (item_num > 2000 && item_num < 2050 && set_num > 450 && set_num < 500) ||
            (item_num > 4000 && item_num < 4100 && set_num > 700 && set_num < 800))
            CLR_settings();

        if((item_num > 200 && item_num < 250 && set_num > 150 && set_num < 200) ||
            (item_num > 650 && item_num < 700 && set_num > 400 && set_num < 450) ||
            (item_num > 1700 && item_num < 1800 && set_num > 1000 && set_num < 1100) ||
            (item_num > 4600 && item_num < 4700 && set_num > 2300 && set_num < 2400))
            CYC_settings();

        if((item_num > 3000 && item_num < 3100 && set_num > 100 && set_num < 150) ||
            (item_num > 9800 && item_num < 9900 && set_num > 200 && set_num < 250) ||
            (item_num > 27200 && item_num < 27300 && set_num > 400 && set_num < 450) ||
            (item_num > 88400 && item_num < 88500 && set_num > 700 && set_num < 750))
            STS_settings();

        if(item_num > 100 && item_num < 150 && set_num > 150 && set_num < 200)
            ST_Small_settings();

        if((item_num > 450 && item_num < 500 && set_num > 2500 && set_num < 2600) ||
            (item_num > 450 && item_num < 500 && set_num > 2300 && set_num < 2400) ||
            (item_num > 600 && item_num < 650 && set_num > 3450 && set_num < 3500) ||
            (item_num > 2800 && item_num < 2850 && set_num > 13400 && set_num < 13500))
            ST_Medium_settings();

        if((item_num > 19100 && item_num < 19200 && set_num > 62500 && set_num < 62600) ||
            (item_num > 74000 && item_num < 75000 && set_num > 166000 && set_num < 167000))
            ST_Large_settings();

        if(item_num > 500 && item_num < 600 && set_num > 45000 && set_num < 65000) // rail507-582
            Rail_Small_LLVM_settings();

        if(item_num > 500 && item_num < 550 && set_num > 150 && set_num < 200) // BDBJ
            BDBJ_settings();

        if(item_num > 2800 && item_num < 2900 && set_num > 4500 && set_num < 4600)  // SQL
            SQL_settings();
        
        if(item_num > 450 && item_num < 500 && set_num > 2500 && set_num < 2600)  // BDBC
            BDBC_settings();
        
        if(item_num > 300 && item_num < 310 && set_num > 1100 && set_num < 1200)  // x264
            x264_settings();
        
        if(item_num > 150 && item_num < 200 && set_num > 1000 && set_num < 1050)  // LLVM
            Rail_Small_LLVM_settings();
        
        if(item_num > 11000 && item_num < 28500 && set_num > 5000 && set_num < 12000)  // scpcyc10-11
            CYC_Large_settings();
    }

    // cout << "reading params complete\n";

    switch(flag_subset_score_calculation) {
        case 1:
            compute_score_ptr = compute_score_basic;
            init_scores_ptr = init_scores_basic;
            delete_scores_ptr = delete_scores_basic;
            break;
        case 2:
            compute_score_ptr = compute_score_united;
            init_scores_ptr = init_scores_united;
            delete_scores_ptr = delete_scores_united;
            break;
    }

    switch(flag_solution_initialization) {
        case 1:
            init_sol_heuristic_ptr = init_solu_best_score;
            break;
        case 2:
            init_sol_heuristic_ptr = init_solu_best_score_no_bms;
            break;
        case 3:
            init_sol_heuristic_ptr = init_solu_item_based;
            break;
        case 4:
            init_sol_heuristic_ptr = init_solu_item_based_no_bms;
            break;
    }

    switch(flag_reconstruction) {
        case 1:
            reconstruct_solu_ptr = reconstruct_remove_one_randomly;
            reconstruct_swapT_init = reconstruct_swapT_init_none;
            reconstruct_swapT_delete = reconstruct_swapT_delete_none;
            break;
        case 2:
            reconstruct_solu_ptr = reconstruct_remove_one_best;
            reconstruct_swapT_init = reconstruct_swapT_init_none;
            reconstruct_swapT_delete = reconstruct_swapT_delete_none;
            break;
        case 3:
            reconstruct_solu_ptr = reconstruct_swap_t;
            reconstruct_swapT_init = reconstruct_swapT_init_do;
            reconstruct_swapT_delete = reconstruct_swapT_delete_do;
            break;
    }

    switch(flag_subset_removal_scheme) {
        case 1:
            get_rmN_ptr = remove_one;
            break;
        case 2:
            get_rmN_ptr = adaptive_removal;
            break;
    }

    switch(flag_subset_addition) {
        case 1:
            get_select_set_ptr = greedy_addition;
            break;
        case 2:
            get_select_set_ptr = novel_addition;
            break;
        case 3:
            get_select_set_ptr = local_greedy_addition;
            break;
        case 4:
            get_select_set_ptr = local_novel_addition_no_bms;
            break;
        case 5:
            get_select_set_ptr = prob_dis_addition;
            break;
        case 6:
            get_select_set_ptr = local_novel_addition;
            break;
    }

    switch(flag_update_item_weight_scheme) {
        case 1:
            update_variables_item_weighting_ptr = update_variables_SAPS;
            break;
        case 2:
            update_variables_item_weighting_ptr = update_variables_PAWS;
            break;
        case 3:
            update_variables_item_weighting_ptr = update_variables_NuSC;
            break;
        case 4:
            update_variables_item_weighting_ptr = update_variables_no_item_weighting;
            break;
    }

    switch(flag_subset_selection_scheme) {
        case 1:
            break_ties_ptr = break_ties_random;
            break;
        case 2:
            break_ties_ptr = break_ties_weight;
            break;
        case 3:
            break_ties_ptr = break_ties_age;
            break;
        case 4:
            break_ties_ptr = break_ties_subscore_random;
            break;
        case 5:
            break_ties_ptr = break_ties_subscore_weight;
            break;
        case 6:
            break_ties_ptr = break_ties_subscore_age;
            break;
        case 7:
            break_ties_ptr = break_ties_score;
            break;
        case 8:
            break_ties_ptr = break_ties_score_subscore;
            break;
        case 9:
            break_ties_ptr = break_ties_score_subscore_age;
            break;
    }

    // cout << "parsing arguments complete\n";

    if(flag_subset_score_calculation == 1) 
        if(flag_subset_selection_scheme > 3)
            return false;
    if(flag_perform_alternate_method == 4 && flag_subset_removal_scheme == 2) return false;
    return flag_inst;
}

#endif
