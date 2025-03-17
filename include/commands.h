#ifndef COMMANDS_H
#define COMMANDS_H

#include <string>
#include <unordered_map>
#include <functional>
#include <memory>

class CommandList {
public:
    void register_command(const std::string& command_name, std::function<void()> command);
    void execute_command(const std::string& command_name) const;

private:
    std::unordered_map<std::string, std::function<void()>> commands; 
};

#endif // COMMANDS_H