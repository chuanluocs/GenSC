#ifndef _PREPROCESS_CPP_
#define _PREPROCESS_CPP_

#include "../include/preprocess.h"

void preprocessing() {
    // cout << "preprocessing\n";
    ifstream infile(inst_filename);
    if (!infile.is_open()) {
        cout << "infile error" << endl;
        exit(1);
    }

    infile >> item_num >> set_num;

    allocate_memory();

    for (int i = 0; i < set_num; ++i) {
        infile >> weight[i];
        org_weight[i] = weight[i];
    }
    memset(set_item_num, 0, set_num * sizeof(int));
    memset(fix, 0, set_num * sizeof(bool));
    for (int i = 0; i < item_num; ++i) {
        infile >> item_set_num[i];
        item_set[i] = new int[item_set_num[i] + 1];
        for (int j = 0; j < item_set_num[i]; ++j) {
            infile >> item_set[i][j];
            --item_set[i][j];
            ++set_item_num[item_set[i][j]];
        }
    }

    for (int i = 0; i < set_num; ++i) {
        set_var[i] = new int[set_item_num[i] + 1];
        set_item_num[i] = 0; //reset for building set_var
    }
    //build set_var
    for (int i = 0; i < item_num; ++i) {
        for (int j = 0; j < item_set_num[i]; ++j) {
            int cur_set = item_set[i][j];
            set_var[cur_set][set_item_num[cur_set]++] = i;
        }
    }
    // cout << "reading and initializing varaibles complete\n";

    infile.close();
    simplify();
}

void simplify_degree1(int i) {
    // if(fix[item_set[i][0]] != 0) return; 
    fix[item_set[i][0]] = 1;
    // cout << "fixed: " << item_set[i][0] << endl; 
    return;
}

void simplify_degree2(int i) {
    int s1 = item_set[i][0];
    int s2 = item_set[i][1];
    if (fix[s1] != 0 || fix[s2] != 0)
        return;
    if (set_item_num[s1] < set_item_num[s2]) {
        int flag1 = 0;
        for (int j = 0; j < set_item_num[s1]; ++j) {
            int v = set_var[s1][j];
            int flag = 0;
            for (int k = 0; k < item_set_num[v]; ++k) {
                if (item_set[v][k] == s2) {
                    flag = 1;
                    break;
                }
            }
            if (flag == 0) {
                flag1 = 1;
                break;
            }
        }
        if (flag1 == 0) {
            if (weight[s1] >= weight[s2]) {
                fix[s1] = -1;
                fix[s2] = 1;
                // cout << "fixed: " << s2 << endl; 
            } else if (weight[s1] < weight[s2]) {
                fix[s1] = s2 + 10;
                weight[s2] -= weight[s1];
                reduce_weight += weight[s1];
            }
        }
    } else {
        int flag1 = 0;
        for (int j = 0; j < set_item_num[s2]; ++j) {
            int v = set_var[s2][j];
            int flag = 0;
            for (int k = 0; k < item_set_num[v]; ++k) {
                if (item_set[v][k] == s1) {
                    flag = 1;
                    break;
                }
            }
            if (flag == 0) {
                flag1 = 1;
                break;
            }
        }
        if (flag1 == 0) {
            if (set_item_num[s1] == set_item_num[s2]) {
                if (weight[s1] <= weight[s2]) {
                    fix[s1] = 1;
                    fix[s2] = -1;
                    // cout << "fixed: " << s1 << endl; 
                }
            } else if (weight[s2] >= weight[s1]) {
                fix[s2] = -1;
                fix[s1] = 1;
                // cout << "fixed: " << s1 << endl;
            } else if (weight[s2] < weight[s1]) {
                fix[s2] = s1 + 10;
                weight[s1] -= weight[s2];
                reduce_weight += weight[s2];
            }
        }
    }
    return;
}

void simplify_degree3(int i) {
    int s1 = item_set[i][0];
    int s2 = item_set[i][1];
    int s3 = item_set[i][2];
    if (fix[s1] != 0 || fix[s2] != 0 || fix[s3] != 0)
        return;
    if (set_item_num[s1] == set_item_num[s2] && set_item_num[s1] < set_item_num[s3]) {
        int flag1 = 0;
        for (int j = 0; j < set_item_num[s1]; ++j) {
            int v = set_var[s1][j];
            int flag2 = 0;
            int flag3 = 0;
            for (int k = 0; k < item_set_num[v]; ++k) {
                if (item_set[v][k] == s2) 
                    flag2 = 1;
                else if (item_set[v][k] == s3) 
                    flag3 = 1;
                if (flag2 == 1 && flag3 == 1)
                    break;
            }
            if (flag2 != 1 || flag3 != 1) {
                flag1 = 1;
                break;
            }
        }
        if (flag1 == 0) {
            if (fix[s3] == 1) {
                fix[s1] = -1;
                fix[s2] = -1;
            } else if (weight[s1] >= weight[s3] && weight[s2] >= weight[s3]) {
                fix[s1] = -1;
                fix[s2] = -1;
                fix[s3] = 1;
                // cout << "fixed: " << s3 << endl; 
            } else {
                if (weight[s1] > weight[s2]) {
                    fix[s1] = -1;
                    fix[s2] = 10 + s3;
                    weight[s3] -= weight[s2];
                    reduce_weight += weight[s2];
                } else {
                    fix[s2] = -1;
                    fix[s1] = 10 + s3;
                    weight[s3] -= weight[s1];
                    reduce_weight += weight[s1];
                }
            }
        }
    } else if (set_item_num[s1] == set_item_num[s3] && set_item_num[s1] < set_item_num[s2]) {
        int flag1 = 0;
        for (int j = 0; j < set_item_num[s1]; ++j) {
            int v = set_var[s1][j];
            int flag2 = 0;
            int flag3 = 0;
            for (int k = 0; k < item_set_num[v]; ++k) {
                if (item_set[v][k] == s2) {
                    flag2 = 1;
                } else if (item_set[v][k] == s3) {
                    flag3 = 1;
                }
                if (flag2 == 1 && flag3 == 1)
                    break;
            }
            if (flag2 != 1 || flag3 != 1) {
                flag1 = 1;
                break;
            }
        }
        if (flag1 == 0) {
            if (fix[s2] == 1) {
                fix[s1] = -1;
                fix[s3] = -1;
            } else if (weight[s1] >= weight[s2] && weight[s3] >= weight[s2]) {
                fix[s1] = -1;
                fix[s3] = -1;
                fix[s2] = 1;
                // cout << "fixed: " << s2 << endl;
            } else {
                if (weight[s1] > weight[s3]) {
                    fix[s1] = -1;
                    fix[s3] = 10 + s2;
                    weight[s2] -= weight[s3];
                    reduce_weight += weight[s3];
                } else {
                    fix[s3] = -1;
                    fix[s1] = 10 + s2;
                    weight[s2] -= weight[s1];
                    reduce_weight += weight[s1];
                }
            }
        }
    } else if (set_item_num[s3] == set_item_num[s2] && set_item_num[s3] < set_item_num[s1]) {
        int flag1 = 0;
        for (int j = 0; j < set_item_num[s3]; ++j) {
            int v = set_var[s3][j];
            int flag2 = 0;
            int flag3 = 0;
            for (int k = 0; k < item_set_num[v]; ++k) {
                if (item_set[v][k] == s2) 
                    flag2 = 1;
                else if (item_set[v][k] == s1) 
                    flag3 = 1;
                if (flag2 == 1 && flag3 == 1)
                    break;
            }
            if (flag2 != 1 || flag3 != 1) {
                flag1 = 1;
                break;
            }
        }
        if (flag1 == 0) {
            if (fix[s1] == 1) {
                fix[s2] = -1;
                fix[s3] = -1;
            }
            if (weight[s3] >= weight[s1] && weight[s2] >= weight[s1]) {
                fix[s3] = -1;
                fix[s2] = -1;
                fix[s1] = 1;
                // cout << "fixed: " << s1 << endl;
            } else {
                if (weight[s2] > weight[s3]) {
                    fix[s2] = -1;
                    fix[s3] = 10 + s1;
                    weight[s1] -= weight[s3];
                    reduce_weight += weight[s3];
                } else {
                    fix[s3] = -1;
                    fix[s2] = 10 + s1;
                    weight[s1] -= weight[s2];
                    reduce_weight += weight[s2];
                }
            }
        }
    } else if (set_item_num[s3] == set_item_num[s2] && set_item_num[s3] == set_item_num[s1]) {
        int flag1 = 0;
        for (int j = 0; j < set_item_num[s3]; ++j) {
            int v = set_var[s3][j];
            int flag2 = 0;
            int flag3 = 0;
            for (int k = 0; k < item_set_num[v]; ++k) {
                if (item_set[v][k] == s2) 
                    flag2 = 1;
                else if (item_set[v][k] == s1) 
                    flag3 = 1;
                if (flag2 == 1 && flag3 == 1)
                    break;
            }
            if (flag2 != 1 || flag3 != 1) {
                flag1 = 1;
                break;
            }
        }
        if (flag1 == 0) {
            if (weight[s1] <= weight[s2] && weight[s1] <= weight[s3]) {
                fix[s1] = 1;
                fix[s2] = -1;
                fix[s3] = -1;
                // cout << "fixed: " << s1 << endl;
            } else if (weight[s2] <= weight[s1] && weight[s2] <= weight[s3]) {
                fix[s2] = 1;
                fix[s1] = -1;
                fix[s3] = -1;
                // cout << "fixed: " << s2 << endl;
            } else if (weight[s3] <= weight[s1] && weight[s3] <= weight[s2]) {
                fix[s3] = 1;
                fix[s2] = -1;
                fix[s1] = -1;
                // cout << "fixed: " << s3 << endl;
            }
        }
    }
    return;
}

void fix1(int s) {
    int v, tem_s, top_s;
    for (int i = 0; i < set_item_num[s]; ++i) {
        v = set_var[s][i];
        if (item_delete[v] == 1)
            continue;
        for (int j = 0; j < item_set_num[v]; ++j)
        {
            tem_s = item_set[v][j];
            if (fix[tem_s] == 0)
            {
                for (int k = 0; k < set_item_num[tem_s]; ++k)
                {
                    if (set_var[tem_s][k] == v)
                    {
                        top_s = set_var[tem_s][--set_item_num[tem_s]];
                        set_var[tem_s][set_item_num[tem_s]] = set_var[tem_s][k];
                        set_var[tem_s][k] = top_s;
                        if (set_item_num[tem_s] == 0)
                            fix[tem_s] = -1;
                        break;
                    }
                }
            }
        }
        item_delete[v] = 1;
    }
}

void fix9(int s) {
    int v, tem_s, top_s;
    for (int i = 0; i < set_item_num[s]; ++i)
    {
        v = set_var[s][i];
        if (item_delete[v] == 1)
            continue;
        for (int j = 0; j < item_set_num[v]; ++j)
        {
            tem_s = item_set[v][j];
            if (fix[tem_s] == 0)
            {
                for (int k = 0; k < set_item_num[tem_s]; ++k)
                {
                    if (set_var[tem_s][k] == v)
                    {
                        top_s = set_var[tem_s][--set_item_num[tem_s]];
                        set_var[tem_s][set_item_num[tem_s]] = set_var[tem_s][k];
                        set_var[tem_s][k] = top_s;
                        if (set_item_num[tem_s] == 0)
                            fix[tem_s] = -1;
                        break;
                    }
                }
            }
        }
        item_delete[v] = 1;
    }
}

/*
fix : init 0
-1 : won't be selected
1 : must be selected and in solution
>9 : must be selected but not in solution
*/
void simplify() {
    // cout << "simplifying dataset\n";
    reduce_weight = 0;
    memset(fix, 0, set_num * sizeof(int));
    for (int i = 0; i < item_num; ++i) {
        if(item_set_num[i] == 1)
            simplify_degree1(i);
        else if(item_set_num[i] == 2)
            simplify_degree2(i);
        else if(item_set_num[i] == 3)
            simplify_degree3(i);
    }

    // int fix_size = count(fix, fix+set_num, 1);
    // cout << "c simplified dataset: fixed " << fix_size << " sets" << endl;

    memset(item_delete, 0, item_num * sizeof(int));
    for(int s = 0; s < set_num;++s) {
        if(fix[s] == 1)
            fix1(s);
        else if(fix[s] > 9)
            fix9(s);
    }
}

#endif

