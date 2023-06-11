#ifndef _SETUP_CPP_
#define _SETUP_CPP_

#include "../include/setup.h"

void handle_interrupt(int sig) {
    cout << "c" << endl;
    cout << "c caught signal... exiting" << endl;

    if(best_step < LONG_LONG_MAX) {
        check_best_solution();
        output();
    } else cout << "c solution initialization not yet complete" << endl;
    free_memory();
    exit(-1);
}

void setup_signal_handler() {
    signal(SIGTERM, handle_interrupt);
    signal(SIGINT, handle_interrupt);
    signal(SIGQUIT, handle_interrupt);
    //signal(SIGABRT, handle_interrupt);
    signal(SIGKILL, handle_interrupt);
}

int setup(int argc, char **argv) {
    setup_signal_handler();

    print_general_information(argv[0]);

    if (!parse_arguments(argc, argv)) {
        cout << "c" << endl;
        cout << "c Arguments Error!" << endl;
        cout << "c" << endl;
        return -1;
    }

    // cout << "setting up complete\n";
    best_step = LONG_LONG_MAX;
    rng.seed(seed);
    return 0;
}

void default_algorithm_settings() {
    seed = 0;
    cutoff_time = 1000;
    max_step = LONG_LONG_MAX;
    flag_auto_select = true;
    flag_print_sol = true;
    flag_print_smart_format = true;
    flag_print_step = true;
    flag_perform_bms = true;
    BMS_T = 80;
    flag_subset_score_calculation = 2;
    mu = 5;
    flag_solution_initialization = 4;
    flag_perform_cc = true;
    flag_perform_iscc = false;
    flag_perform_tabu = true;
    tabu_alpha = 4;
    flag_reconstruction = 2;
    reconstruct_with_prob = false;
    reconstruct_prob = 0.8;
    reconstruct_swap_T = 5;
    flag_subset_removal_scheme = 1;
    flag_subset_addition = 4;
    flag_perform_alternate_method = 4;
    flag_update_item_weight_scheme = 3;
    SAPS_T = 100;
    SAPS_R = 0.9;
    PAWS_P = 0.8;
    novel_addition_prob = 0.1;
    flag_subset_selection_scheme = 9;
    SAinitN = 5;
    SAt = 10000;
}


void Rail_settings() {
    flag_perform_bms = true;
    BMS_T = 5000;
    flag_subset_score_calculation = 2;
    mu = 3;
    flag_solution_initialization = 1;
    flag_perform_cc = true;
    flag_perform_iscc = false;
    flag_perform_tabu = true;
    tabu_alpha = 80;
    flag_reconstruction = 2;
    reconstruct_with_prob = true;
    reconstruct_prob = 0.55;
    flag_subset_removal_scheme = 1;
    flag_subset_addition = 4;
    flag_perform_alternate_method = 4;
    flag_update_item_weight_scheme = 3;
    novel_addition_prob = 0.21;
    flag_subset_selection_scheme = 8;
}

void CLR_settings() {
    flag_perform_bms = true;
    BMS_T = 170;
    flag_subset_score_calculation = 2;
    mu = 80;
    flag_solution_initialization = 4;
    flag_perform_cc = true;
    flag_perform_iscc = false;
    flag_perform_tabu = true;
    tabu_alpha = 5;
    flag_reconstruction = 2;
    reconstruct_with_prob = false;
    flag_subset_removal_scheme = 1;
    flag_subset_addition = 4;
    flag_perform_alternate_method = 4;
    flag_update_item_weight_scheme = 3;
    novel_addition_prob = 0.5;
    flag_subset_selection_scheme = 9;
}

void CYC_settings() {
    flag_perform_bms = true;
    BMS_T = 230;
    flag_subset_score_calculation = 2;
    mu = 200;
    flag_solution_initialization = 3;
    flag_perform_cc = false;
    flag_perform_iscc = true;
    flag_perform_tabu = false;
    flag_reconstruction = 1;
    reconstruct_with_prob = false;
    flag_subset_removal_scheme = 2;
    SAinitN = 4;
    SAt = 50000;
    flag_subset_addition = 2;
    flag_perform_alternate_method = 2;
    flag_update_item_weight_scheme = 3;
    novel_addition_prob = 0.1;
    flag_subset_selection_scheme = 8;
}

void STS_settings() {
    flag_perform_bms = true;
    BMS_T = 150;
    flag_subset_score_calculation = 2;
    mu = 70;
    flag_solution_initialization = 3;
    flag_perform_cc = true;
    flag_perform_iscc = false;
    flag_perform_tabu = true;
    tabu_alpha = 3;
    flag_reconstruction = 1;
    reconstruct_with_prob = true;
    reconstruct_prob = 0.6911661598134515;
    flag_subset_removal_scheme = 1;
    flag_subset_addition = 3;
    flag_perform_alternate_method = 4;
    flag_update_item_weight_scheme = 3;
    flag_subset_selection_scheme = 8;
}

void ST_Small_settings() {
    flag_perform_bms = false;
    flag_subset_score_calculation = 2;
    mu = 11;
    flag_solution_initialization = 1;
    flag_perform_cc = false;
    flag_perform_iscc = false;
    flag_perform_tabu = true;
    tabu_alpha = 30;
    flag_reconstruction = 1;
    reconstruct_with_prob = true;
    reconstruct_prob = 0.39478121245637254;
    flag_subset_removal_scheme = 1;
    flag_subset_addition = 3;
    flag_perform_alternate_method = 1;
    flag_update_item_weight_scheme = 3;
    flag_subset_selection_scheme = 7;
}

void ST_Medium_settings() {
    flag_perform_bms = true;
    BMS_T = 800;
    flag_subset_score_calculation = 2;
    mu = 4;
    flag_solution_initialization = 4;
    flag_perform_cc = false;
    flag_perform_iscc = false;
    flag_perform_tabu = true;
    tabu_alpha = 100;
    flag_reconstruction = 2;
    reconstruct_with_prob = false;
    flag_subset_removal_scheme = 2;
    SAinitN = 4;
    SAt = 30000;
    flag_subset_addition = 3;
    flag_perform_alternate_method = 2;
    flag_update_item_weight_scheme = 3;
    flag_subset_selection_scheme = 9;
}

void ST_Large_settings() {
    flag_perform_bms = true;
    BMS_T = 300;
    flag_subset_score_calculation = 2;
    mu = 15;
    flag_solution_initialization = 1;
    flag_perform_cc = false;
    flag_perform_iscc = false;
    flag_perform_tabu = true;
    tabu_alpha = 10;
    flag_reconstruction = 2;
    reconstruct_with_prob = false;
    flag_subset_removal_scheme = 1;
    flag_subset_addition = 3;
    flag_perform_alternate_method = 2;
    flag_update_item_weight_scheme = 3;
    flag_subset_selection_scheme = 9;
}


void SQL_settings() {
    flag_perform_bms = false;
    flag_subset_score_calculation = 2;
    mu = 30;
    flag_solution_initialization = 4;
    flag_perform_cc = false;
    flag_perform_iscc = true;
    flag_perform_tabu = true;
    tabu_alpha = 80;
    flag_reconstruction = 2;
    reconstruct_with_prob = true;
    reconstruct_prob = 0.6629727311167818;
    flag_subset_removal_scheme = 1;
    flag_subset_addition = 4;
    flag_perform_alternate_method = 2;
    flag_update_item_weight_scheme = 3;
    novel_addition_prob = 0.6022492909461983;
    flag_subset_selection_scheme = 4;
}

void BDBC_settings() {
    flag_perform_bms = false;
    flag_subset_score_calculation = 1;
    flag_solution_initialization = 1;
    flag_perform_cc = false;
    flag_perform_iscc = true;
    flag_perform_tabu = true;
    tabu_alpha = 50;
    flag_reconstruction = 1;
    reconstruct_with_prob = true;
    reconstruct_prob = 0.6926109857331707;
    flag_subset_removal_scheme = 1;
    flag_subset_addition = 3;
    flag_perform_alternate_method = 3;
    flag_update_item_weight_scheme = 3;
    flag_subset_selection_scheme = 1;
}

void x264_settings() {
    flag_perform_bms = true;
    BMS_T = 1000;
    flag_subset_score_calculation = 2;
    mu = 30;
    flag_solution_initialization = 3;
    flag_perform_cc = false;
    flag_perform_iscc = true;
    flag_perform_tabu = false;
    flag_reconstruction = 1;
    reconstruct_with_prob = false;
    flag_subset_removal_scheme = 1;   
    flag_subset_addition = 3;
    flag_perform_alternate_method = 1;
    flag_update_item_weight_scheme = 3;
    flag_subset_selection_scheme = 5;
}

void Rail_Small_LLVM_settings() {
    flag_perform_bms = true;
    BMS_T = 80;
    flag_subset_score_calculation = 2;
    mu = 5;
    flag_solution_initialization = 4;
    flag_perform_cc = true;
    flag_perform_iscc = false;
    flag_perform_tabu = true;
    tabu_alpha = 4;
    flag_reconstruction = 2;
    reconstruct_with_prob = false;
    flag_subset_removal_scheme = 1;   
    flag_subset_addition = 4;
    flag_perform_alternate_method = 4;
    flag_update_item_weight_scheme = 3;
    novel_addition_prob = 0.1;
    flag_subset_selection_scheme = 9;
}

void BDBJ_settings() {
    flag_perform_bms = true;
    BMS_T = 170;
    flag_subset_score_calculation = 2;
    mu = 80;
    flag_solution_initialization = 4;
    flag_perform_cc = true;
    flag_perform_iscc = false;
    flag_perform_tabu = true;
    tabu_alpha = 5;
    flag_reconstruction = 2;
    reconstruct_with_prob = false;
    flag_subset_removal_scheme = 1;
    flag_subset_addition = 4;
    flag_perform_alternate_method = 4;
    flag_update_item_weight_scheme = 3;
    novel_addition_prob = 0.5;
    flag_subset_selection_scheme = 9;
}

void CYC_Large_settings() {
    flag_perform_bms = true;
    BMS_T = 181;
    flag_subset_score_calculation = 2;
    mu = 344;
    flag_solution_initialization = 3;
    flag_perform_cc = true;
    flag_perform_iscc = false;
    flag_perform_tabu = false;
    flag_reconstruction = 1;
    reconstruct_with_prob = false;
    flag_subset_removal_scheme = 1;
    flag_subset_addition = 4;
    flag_perform_alternate_method = 2;
    flag_update_item_weight_scheme = 3;
    novel_addition_prob = 0.7762903966465247;
    flag_subset_selection_scheme = 9;
}
#endif