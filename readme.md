# CS 630 Task Manager

## Task Manager for Linux Processes

### To start program in bash:

For this project, I was using WSL2 and Ubuntu so if not using that make sure the Linux libraries are downloaded and a g++ complier. 

Make sure you have Qt on Ubuntu with: 

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