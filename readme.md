## Low Latency Logger (L2Log)
L2Log is a modern low-latency concurrent c++ based logger.

### Features
* Easily discoverable method names
* Set different priority of logs
* Filter logs based on priority
* Append logging to older file
* Can append to file as well as console

### Platform Support
* Tested for C++11 to C++20
* Build support for Bazel and CMake
* Tested for Windows 10 and Linux 18.04

### Compile
```
cd l2log
mkdir build
cd build
cmake ..
make
```

### Upcoming features
* Add support for Clang.