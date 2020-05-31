#ifndef L2LOG_LOGGER_H
#define L2LOG_LOGGER_H

#include <bits/stdc++.h>

enum class PRIORITY {
    CRITICAL = 50,
    ERROR = 40,
    WARNING = 30,
    INFO = 20,
    DEBUG = 10,
    NOTSET = 0
};

class logger {
private:
    std::string filename_;
    bool console_ = true;
    bool file_ = false;
    std::mutex console_mutex;
    std::mutex file_mutex;
    std::fstream file;

public:
    explicit logger(const std::string &filename, bool console = true, bool file = false) : filename_(filename),
                                                                                           console_(console),
                                                                                           file_(file) {
        // Open the file for logging


    };

    void log(std::string &log_message) {

    }

    void debug(std::string &log_message) {
    }

    void info(std::string &log_message) {
    }

    void warning(std::string &log_message) {
    }

    void error(std::string &log_message) {
    }

    void critical(std::string &log_message) {
    }

    ~logger() = default;

};


#endif //L2LOG_LOGGER_H
