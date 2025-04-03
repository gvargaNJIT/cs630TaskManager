#include <iostream>
#include "include/app.h"
#include <unordered_map>
#include <string>
#include <memory>
#include <functional>

int main(int argc, char *argv[]) {  // argc and argv are available here
    App app;
    return app.start(argc, argv);   // Pass them to start()
}

