#include "list.h"
#include <iostream>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>


ProcessList::ProcessList() {}
ProcessList::~ProcessList() {}

void ProcessList::listing() {
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
                    
                    std::cout << "PID: " << dirName << " | Process Name: " << processName << std::endl;
                }
            }
        }
    }
}

void ProcessList::processkill(){
    pid_t pid;

    std::cout << "Enter the PID of the process to terminate: ";
    std::cin >> pid;

    if (kill(pid, SIGTERM) == 0) {
        std::cout << "Process " << pid << " terminated gracefully." << std::endl;
    } else {
        std::cerr << "Failed to terminate process " << pid << " gracefully. Trying SIGKILL." << std::endl;
        if (kill(pid, SIGKILL) == 0) {
             std::cout << "Process " << pid << " terminated immediately." << std::endl;
        } else {
            std::cerr << "Failed to terminate process " << pid << "." << std::endl;
        }
    }
}
