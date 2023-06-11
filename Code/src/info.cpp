#ifndef _INFO_CPP
#define _INFO_CPP

#include "../include/info.h"

string version_str = "1.0";

string get_last_level_name(string file_path) {
    long long file_path_size = file_path.size();
    if (file_path[file_path_size - 1] == '/')
        file_path = file_path.substr(0, file_path_size - 1);
    long long pos = file_path.find_last_of('/');
    if (pos < 0 || pos >= file_path.size())
        return file_path;
    else return file_path.substr(pos + 1, file_path.size() - pos - 1);
}

void print_general_information(char *executable_name) {
    string executable_name_str = executable_name;
    executable_name_str = get_last_level_name(executable_name_str);
    cout << "c" << endl;
    cout << "c GenSC -- A Novel and General Local Search Framework for Set Covering Problem (SCP)" << endl;
    cout << "c Version: " << version_str << endl;
    cout << "c" << endl;

    return;
}
#endif
