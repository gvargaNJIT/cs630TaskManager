#include <iostream>
#include "list.h"
#include "commands.h"
#include "app.h"
#include <unordered_map>
#include <string>
#include <memory>
#include <functional>
#include <algorithm>
#include <cctype>
#include <locale>


int App::start() {
    ProcessList processList;
    processList.listing(); 

    CommandList commandList;

    commandList.register_command("terminate", std::bind(&ProcessList::processkill, std::ref(processList)));
    commandList.register_command("refresh", std::bind(&ProcessList::listing, std::ref(processList)));
    commandList.register_command("status", std::bind(&ProcessList::monitorProcess, std::ref(processList)));

    std::string user_input;

    while (true) {
        std::cout << "Enter a command: ";
        std::cin >> user_input;
        if (user_input == "exit") {
            break;
        }
        commandList.execute_command(user_input);
    }
    return 0;
}
