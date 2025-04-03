# CS 630 Task Manager

## Task Manager for Linux Processes

### To start program in bash:

Make sure you have Qt with: 

```sh 
sudo apt install qt5-qmake qtbase5-dev
sudo apt update 
```

Execute these commands in the Linux command line:

```sh
qmake project_manager.pro
make
./project_manager
```

Then you can type a PID number from the list and check status on it or terminate it. You can also refresh the PID list as well.