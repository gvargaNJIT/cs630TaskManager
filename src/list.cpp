#include "include/list.h"
#include <iostream>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <mqueue.h>
#include <cstring>
#include <sys/stat.h>
#include <fcntl.h>
#include <fstream>
#include <filesystem>
#define QUEUE_NAME "/process_status_queue"

struct Message {
    pid_t pid;
    char status[64];
};

ProcessList::ProcessList() {}
ProcessList::~ProcessList() {}

std::vector<std::pair<pid_t, std::string>> ProcessList::listing() {
    std::vector<std::pair<pid_t, std::string>> processes;
    std::string procPath = "/proc";

    for (const auto& entry : fs::directory_iterator(procPath)) {
        if (entry.is_directory()) {
            std::string dirName = entry.path().filename().string();

            if (std::all_of(dirName.begin(), dirName.end(), ::isdigit)) {
                std::string commPath = entry.path().string() + "/comm";
                std::ifstream commFile(commPath);

                if (commFile.is_open()) {
                    std::string processName;
                    std::getline(commFile, processName);
                    commFile.close();

                    pid_t pid = std::stoi(dirName);
                    processes.push_back({pid, processName});
                }
            }
        }
    }

    return processes;
}


void ProcessList::processkill(pid_t pid) {
    kill(pid, SIGKILL);
}

bool ProcessList::monitorProcess(pid_t pid) {
    return kill(pid, 0) == 0;
}

