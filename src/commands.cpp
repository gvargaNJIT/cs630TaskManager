#include <iostream>
#include "commands.h"

std::unordered_map<std::string, std::function<void()>> commands;

void CommandList::register_command(const std::string& command_name, std::function<void()> command) {
    commands[command_name] = command;
}

void CommandList::execute_command(const std::string& command_name) const{
    auto it = commands.find(command_name);
    if (it != commands.end()) {
        it->second();
    } else {
        std::cout << "Command not found!" << std::endl;
    }
}