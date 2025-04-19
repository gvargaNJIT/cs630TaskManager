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
    mqd_t mq;
    struct mq_attr attr{};
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = sizeof(Message);
    attr.mq_curmsgs = 0;
    
    mq = mq_open(QUEUE_NAME, O_RDWR | O_CREAT, 0644, &attr);
    if (mq == -1) {
        perror("mq_open");
        return false;
    }

    Message msg;
    msg.pid = pid;

    char path[256];
    snprintf(path, sizeof(path), "/proc/%d/stat", pid);
    FILE* file = fopen(path, "r");

    if (!file) {
        strcpy(msg.status, "not found");
        mq_send(mq, (char*)&msg, sizeof(msg), 0);
        mq_close(mq);
        mq_unlink(QUEUE_NAME);
        return false;
    }

    char state;
    char comm[256];
    int read_pid;

    if (fscanf(file, "%d %255s %c", &read_pid, comm, &state) != 3) {
        fclose(file);
        strcpy(msg.status, "invalid");
        mq_send(mq, (char*)&msg, sizeof(msg), 0);
        mq_close(mq);
        mq_unlink(QUEUE_NAME);
        return false;
    }

    fclose(file);

    if (state == 'Z' || state == 'X') {
        strcpy(msg.status, "dead");
        mq_send(mq, (char*)&msg, sizeof(msg), 0);
        mq_close(mq);
        mq_unlink(QUEUE_NAME);
        return false;
    }

    strcpy(msg.status, "alive");
    mq_send(mq, (char*)&msg, sizeof(msg), 0);
    mq_close(mq);
    mq_unlink(QUEUE_NAME);
    return true;
}
