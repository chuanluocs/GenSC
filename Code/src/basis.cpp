#ifndef _BASIS_CPP_
#define _BASIS_CPP_

#include "../include/basis.h"

Mersenne_rng rng;

// set(variable, soft clause) information
long long *time_stamp;
int *weight;
int *org_weight;
int *fix;
set<int> tabu_list;
int *zero_stack;
int zero_stack_fill_pointer;
int *index_in_zero_stack;

// variable(hard clause)
int *cover_count;
int *cover_set;
int *cover_set2;
int *uncover_stack;
int *index_in_uncover_stack;
int uncover_stack_fill_pointer;

// solution information
int *cur_solu;
long long cur_weight;
int reduce_weight;
int *best_solu;
long long best_weight;
double best_time;
long long best_step;
int *set_solu;
int *index_in_set_solu;
int set_count;
int last_improve;

int *not_set_solu;
int *index_in_not_in_set_solu;
int not_set_count;

// data structure
int cutoff_time;
int BMS_T;
long long step;
long long max_step;

int item_num;
int set_num;

int *item_delete;
int *set_delete;
int **item_set;
int *item_set_num;
int *org_item_set_num;
int **set_var;
int *set_item_num;
int *org_set_item_num;

int mu;
double novel_addition_prob;

struct tms start_time;

double get_runtime()
{
    struct tms stop;
    times(&stop);
    return (double)(stop.tms_utime - start_time.tms_utime + stop.tms_stime - start_time.tms_stime) / sysconf(_SC_CLK_TCK);
}

void start_timing()
{
    times(&start_time);
}

void allocate_memory()
{
    // cout << "allocating memory\n";
    // cout << "set_num: " << set_num << " item_num: " << item_num << endl; 
    int max_set_num = set_num + 10;
    int max_item_num = item_num + 10;

    // cout << "allocating memory for advanced variables\n";
    init_scores(max_set_num, max_item_num);
    subset_addition_init(max_set_num);
    init_cc_and_tabu(max_set_num);
    subset_removal_init(max_set_num);
    reconstruct_init(max_set_num);

    // cout << "allocating memory for basic variables\n";

    time_stamp = new long long[max_set_num];
    weight = new int[max_set_num];
    org_weight = new int[max_set_num];
    fix = new int[max_set_num];
    zero_stack = new int[max_set_num];
    index_in_zero_stack = new int[max_set_num];

    // variable(hard clause)
    cover_count = new int[max_item_num];
    cover_set = new int[max_item_num];
    cover_set2 = new int[max_item_num];
    uncover_stack = new int[max_item_num];
    index_in_uncover_stack = new int[max_item_num];

    // solution information
    cur_solu = new int[max_set_num];
    best_solu = new int[max_set_num];
    set_solu = new int[max_set_num];
    index_in_set_solu = new int[max_set_num];

    not_set_solu = new int[max_set_num];
    index_in_not_in_set_solu = new int[max_set_num];

    // data structure
    item_delete = new int[max_item_num];
    item_set = new int *[max_item_num];
    item_set_num = new int[max_item_num];
    org_item_set_num = new int[max_item_num];
    set_var = new int *[max_set_num];
    set_item_num = new int[max_set_num];
    org_set_item_num = new int[max_set_num];
    // cout << "memory allocation complete\n";
}

void free_memory()
{
    delete_scores();
    subset_addition_delete();
    delete_cc_and_tabu();
    reconstruct_delete();

    delete[] time_stamp;
    delete[] weight;
    delete[] org_weight;
    delete[] fix;
    delete[] zero_stack;
    delete[] index_in_zero_stack;

    delete[] cover_count;
    delete[] cover_set;
    delete[] cover_set2;
    delete[] uncover_stack;
    delete[] index_in_uncover_stack;

    delete[] cur_solu;
    delete[] best_solu;
    delete[] set_solu;
    delete[] index_in_set_solu;

    delete[] not_set_solu;
    delete[] index_in_not_in_set_solu;

    for (int i = 0; i < item_num; ++i)
        delete[] item_set[i];

    delete[] item_delete;
    delete[] item_set;
    delete[] item_set_num;
    delete[] org_item_set_num;
    delete[] org_set_item_num;

    for (int i = 0; i < set_num; ++i)
        delete[] set_var[i];
    delete[] set_var;
    delete[] set_item_num;
}

void check_cur_solution()
{
    long long tem_weight = 0;
    for (int i = 0; i < set_num; ++i)
    {
        if (fix[i] == 1 && cur_solu[i] != 1)
            cout << "wrong 11" << endl;
        if (fix[i] < 0 && cur_solu[i] != 0)
            cout << "wrong 22" << endl;
        if (fix[i] > 9)
        {
            if (cur_solu[i] != 0)
                cout << "wrong 33" << endl;
        }
    }

    for (int i = 0; i < set_num; ++i)
    {
        if (cur_solu[i] == 1)
            tem_weight += org_weight[i];
        else if (fix[i] > 9 && cur_solu[fix[i] - 10] == 0)
            tem_weight += org_weight[i];
    }
    if (tem_weight != cur_weight)
        cout << "some thing wrong in cur weight and tem_weight " << endl;
}

void check_best_solution() {
    long long tem_weight = 0;
    for (int i = 0; i < set_num; ++i)
    {
        if (fix[i] == 1 && best_solu[i] != 1)
            cout << "wrong 1" << endl;
        if (fix[i] < 0 && best_solu[i] != 0)
            cout << "wrong 2" << endl;
        if (fix[i] > 9)
        {
            int s = fix[i] - 10;
            if (best_solu[i] != 0)
                cout << "wrong 3" << endl;
            if (best_solu[s] == 0)
                best_solu[i] = 1;
        }
    }
    for (int i = 0; i < item_num; ++i)
    {
        int flag = 0;
        for (int j = 0; j < item_set_num[i]; ++j)
        {
            if (best_solu[item_set[i][j]] == 1)
            {
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            cout << "best solu is wrong in 0 " << endl;
            return;
        }
    }
    for (int i = 0; i < set_num; ++i)
    {
        if (best_solu[i] == 1)
            tem_weight += org_weight[i];
    }

    tem_weight = 0;
    for (int i = 0; i < item_num; ++i)
    {
        int flag = 0;
        for (int j = 0; j < item_set_num[i]; ++j)
        {
            if (best_solu[item_set[i][j]] == 1 || fix[item_set[i][j]] == 1 || fix[item_set[i][j]] == -2)
            {
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            cout << "best solu is wrong in 1" << endl;
            return;
        }
    }
    for (int i = 0; i < set_num; ++i)
    {
        if (fix[i] == 1 || best_solu[i] == 1)
            tem_weight += org_weight[i];

        if (fix[i] == -2)
        {

            for (int j = 0; j < org_set_item_num[i]; ++j)
            {
                int flag = 0;
                int v = set_var[i][j];
                for (int k = 0; k < item_set_num[v]; ++k)
                {
                    if (fix[item_set[v][k]] == 1 || best_solu[item_set[v][k]] == 1)
                    {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0)
                {
                    tem_weight += org_weight[i];
                    break;
                }
            }
        }
    }

    if (tem_weight != best_weight)
        cout << "best solu is wrong in 5 " << endl;

    tem_weight = 0;
    for (int i = 0; i < set_num; ++i)
    {
        if (fix[i] == 1 || best_solu[i] == 1)
            tem_weight += org_weight[i];
    }
    for (int i = 0; i < item_num; ++i)
    {
        int flag = 0;
        for (int j = 0; j < item_set_num[i]; ++j)
        {
            if (fix[item_set[i][j]] == 1 || best_solu[item_set[i][j]] == 1)
            {
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            if (item_set_num[i] == 2)
            {
                tem_weight += org_weight[i];
            }
        }
    }
}

bool check_cover() {
    bool covered_var[item_num];
    fill(covered_var, covered_var+item_num, false);
    for(int i=0;i<set_num;i++) 
        if(set_solu[i] || fix[i]) 
            for(int j=0;j<set_item_num[i];j++)
                covered_var[set_var[i][j]] = true;
    for(int i=0;i<item_num;i++)
        if(!covered_var[i])
            return false;
    return true;
}

bool test_termination()
{
    if (step >= max_step)
        return true;
    if (step % 1000 == 0)
        if (get_runtime() > cutoff_time)
            return true;
    return false;
}

bool solution_feasible()
{
    return uncover_stack_fill_pointer == 0;
}

void update_best_to_cur()
{
    if (cur_weight < best_weight)
    {
        for (int i = 0; i < set_num; ++i)
            best_solu[i] = cur_solu[i];
        best_weight = cur_weight;
        best_time = get_runtime();
        best_step = step;
        cout << "o ";
        if(!flag_print_smart_format) {
            cout << best_weight << endl;
            return;
        }
        cout.width(11);
        cout.setf(ios::right);
        cout << best_weight << " ";
        cout.width(9);
        cout.setf(ios::right);
        cout << best_time << " ";

        if(flag_print_step) {
            cout.width(9);
            cout.setf(ios::right);
            cout << best_step << endl;
        } else cout << endl;
    }
}

int select_set_from_zero_stack()
{
    int best_set = -1, best_weight = 0;
    int tem_set;
    if (flag_perform_bms && BMS_T < zero_stack_fill_pointer)
    {
        for (int i = 0; i < BMS_T; ++i)
        {
            tem_set = zero_stack[rng.next(zero_stack_fill_pointer)];
            if (weight[tem_set] > best_weight)
            {
                best_weight = weight[tem_set];
                best_set = tem_set;
            }
        }
    }
    else
    {
        for (int i = 0; i < zero_stack_fill_pointer; ++i)
        {
            tem_set = zero_stack[i];
            if (weight[tem_set] > best_weight)
            {
                best_weight = weight[tem_set];
                best_set = tem_set;
            }
        }
    }
    return best_set;
}

void output() {
    if(flag_print_step)
        cout << "c total step: " << step << endl;
    cout << "c set cover weight: " << best_weight << " runtime: " << best_time;
    if(flag_print_step)
        cout << " best step: " << best_step << endl;
    else cout << endl;
    if(!flag_print_sol) return;
    cout << "c detailed set cover: " << endl;
    cout << "v ";
    for (int i = 0; i < set_num; ++i)
       cout << best_solu[i] << " ";
    cout << endl;
}

#endif
