#ifndef APP_H
#define APP_H
#include "commands.h"
#include "list.h"

class App {
public:
    int start(int argc, char *argv[]);;
private:
    int argc;
    char *argv[];
};

#endif // APP_H