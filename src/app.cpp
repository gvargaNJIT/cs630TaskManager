#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QString>
#include <iostream>
#include "include/list.h"
#include "include/commands.h"
#include "include/app.h"
#include <vector>

int App::start(int argc, char *argv[]) {
    QApplication app(argc, argv);

    ProcessList processList;
    CommandList commandList;

    QWidget window;
    QVBoxLayout layout(&window);

    QTextEdit processListTextEdit(&window);
    processListTextEdit.setReadOnly(true);
    layout.addWidget(&processListTextEdit);

    QTextEdit statusTextEdit(&window);
    statusTextEdit.setReadOnly(true);
    layout.addWidget(&statusTextEdit);
    statusTextEdit.setFixedHeight(100);

    auto updateProcessList = [&processList, &processListTextEdit]() {
        processListTextEdit.clear();
        std::vector<std::pair<pid_t, std::string>> processes = processList.listing();
        for (const auto& process : processes) {
            QString processInfo = "PID: " + QString::number(process.first) + " | " + QString::fromStdString(process.second);
            processListTextEdit.append(processInfo);
        }
    };

    updateProcessList();

    QPushButton terminateButton("Terminate", &window);
    QPushButton statusButton("Status", &window);
    QPushButton refreshButton("Refresh", &window);
    layout.addWidget(&terminateButton);
    layout.addWidget(&statusButton);
    layout.addWidget(&refreshButton);

    QLineEdit pidInput(&window);
    pidInput.setPlaceholderText("Enter PID here...");
    layout.addWidget(&pidInput);

    QObject::connect(&refreshButton, &QPushButton::clicked, [&]() {
        updateProcessList();
        statusTextEdit.append("Process list refreshed.");
    });

    QObject::connect(&terminateButton, &QPushButton::clicked, [&]() {
        bool ok;
        int pid = pidInput.text().toInt(&ok);
        if (ok) {
            processList.processkill(pid);
            statusTextEdit.append("Terminated process: " + QString::number(pid));
        } else {
            statusTextEdit.append("Invalid PID entered.");
        }
    });

    QObject::connect(&statusButton, &QPushButton::clicked, [&]() {
        bool ok;
        int pid = pidInput.text().toInt(&ok);
        if (ok) {
            std::string status = processList.monitorProcess(pid) ? "Running" : "Terminated";
            statusTextEdit.append("Process " + QString::number(pid) + " is " + QString::fromStdString(status));
        } else {
            statusTextEdit.append("Invalid PID entered.");
        }
    });

    window.setWindowTitle("Process Manager");
    window.setMinimumSize(300, 800);
    window.show();

    return app.exec();
}


