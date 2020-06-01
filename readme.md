## Low Latency Logger (L2Log)
L2Log is a modern low-latency concurrent c++ based logger.

### Features
* Concurrent thread-safe logging
* Logging member functions can take any number of arguments.
* Easily discoverable method names
* Set different priority of logs
* Filter logs based on priority
* Append logs to older file
* Can write logs to file as well as console 

### Platform Support
* Tested for C++11 to C++20
* Build support for CMake
* Tested for Linux 18.04

### Compile
```
cd l2log
mkdir build
cd build
cmake ..
make
```

### Sample Code


### Upcoming features
* Add support for Clang.
* Add suport for Bazel build
* Test for Windows 10.