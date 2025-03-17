#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>

namespace fs = std::filesystem;

#ifndef PROCESS_LIST_H
#define PROCESS_LIST_H

class ProcessList {
public:
    ProcessList();
    ~ProcessList();
    void listing();
    void processkill();
};

#endif // PROCESS_LIST_H

