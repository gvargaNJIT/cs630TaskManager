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
    void listing();
    void processkill();
    void monitorProcess();
};

#endif // PROCESS_LIST_H

