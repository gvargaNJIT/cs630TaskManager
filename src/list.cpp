#include "list.h"
#include <iostream>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <mqueue.h>
#include <cstring>
#include <sys/stat.h>
#include <fcntl.h>
#define QUEUE_NAME "/process_status_queue"

struct Message {
    pid_t pid;
    char status[64];
};

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

void ProcessList::processkill() {
    pid_t pid;
    std::cout << "Enter the PID of the process to terminate: ";
    while (true) {
        std::cin >> pid;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "Invalid input. Please enter a valid PID (numeric only): ";
        } else {
            break;
        }
    }

    if (kill(pid, SIGKILL) == 0) {
        std::cout << "Process " << pid << " terminated." << std::endl;
    } else {
        std::cerr << "Failed to terminate process " << pid << "." << std::endl;
    }
}

void ProcessList::monitorProcess() {
        pid_t target_pid;
        std::cout << "Enter PID to monitor: ";
        std::cin >> target_pid;
        if (kill(target_pid, 0) == 0) {
            std::cout << "Process " << target_pid << " is Running." << std::endl;
        } else {
            std::cout << "Process " << target_pid << " is Terminated." << std::endl;
        }
    }
    
    