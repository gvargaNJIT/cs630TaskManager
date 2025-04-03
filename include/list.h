#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>
#include "commands.h"

namespace fs = std::filesystem;

#ifndef PROCESS_LIST_H
#define PROCESS_LIST_H

class ProcessList {
public:
    ProcessList();
    ~ProcessList();
    std::vector<std::pair<pid_t, std::string>> listing();
    void processkill(pid_t pid);
    bool monitorProcess(pid_t pid);
};

#endif // PROCESS_LIST_H

