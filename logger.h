#ifndef L2LOG_LOGGER_H
#define L2LOG_LOGGER_H

#include <bits/stdc++.h>

// What time you want to set? UTC Time, Mountain Time, etc?
// The default format of logger file should be csv because that can be analysed

enum class PRIORITY {
    CRITICAL = 50,
    ERROR = 40,
    WARNING = 30,
    INFO = 20,
    DEBUG = 10,
    NOTSET = 0
};

class Logger {
private:
    std::string filename;
    bool console = true;
    bool persistent = false;
    bool log_datetime = false;
    std::mutex write_mutex;
    std::fstream file;

    PRIORITY priority = PRIORITY::NOTSET; // logs that are less severe than priority will be ignored.
    time_t timeptr = time(nullptr);
    struct tm *curtime = nullptr;

public:
    explicit Logger(const std::string &filename,
                    bool console = true,
                    bool persistent = false,
                    bool log_datetime = true,
                    PRIORITY priority = PRIORITY::NOTSET) : filename(filename),
                                                            console(console),
                                                            persistent(persistent),
                                                            log_datetime(log_datetime) {

        file.open(filename, std::ios_base::out | std::ios_base::app | std::ios_base::in);
        if (!file) throw std::runtime_error("Failed to successfully read/open the file " + filename);
    };

    void add_timestamp(std::string &message) {
        if (log_datetime) {
            message += asctime(localtime(&timeptr));
        }
        message += '\n';
    }

    void log(std::string &log_message) {
        if (priority > PRIORITY::NOTSET)
            return;

        std::string message = "LOG, " + log_message + ", ";

        add_timestamp(message);

        if (console) {
            std::cout << message;
        }

        if (persistent) {
            file << message;
        }
    }

    void debug(std::string &log_message) {
        std::unique_lock<std::mutex> file_lock(write_mutex);

        if (priority > PRIORITY::DEBUG)
            return;

        std::string message = "DEBUG, " + log_message + ", ";

        add_timestamp(message);

        if (console) {
            std::cout << message;
        }

        if (persistent) {
            file << message;
        }
    }

    void info(std::string &log_message) {
        std::unique_lock<std::mutex> file_lock(write_mutex);

        if (priority > PRIORITY::INFO)
            return;

        std::string message = "INFO, " + log_message + ", ";

        add_timestamp(message);

        if (console) {
            std::cout << message;
        }

        if (persistent) {
            file << message;
        }
    }

    void warning(std::string &log_message) {
        std::unique_lock<std::mutex> file_lock(write_mutex);

        if (priority > PRIORITY::WARNING)
            return;

        std::string message = "WARNING, " + log_message + ", ";

        add_timestamp(message);

        if (console) {
            std::cout << message;
        }

        if (persistent) {
            file << message;
        }
    }

    void error(std::string &log_message) {
        std::unique_lock<std::mutex> file_lock(write_mutex);

        if (priority > PRIORITY::ERROR)
            return;

        std::string message = "ERROR, " + log_message + ", ";

        add_timestamp(message);

        if (console) {
            std::cout << message;
        }

        if (persistent) {
            file << message;
        }
    }

    void critical(std::string &log_message) {
        std::unique_lock<std::mutex> file_lock(write_mutex);

        if (priority > PRIORITY::CRITICAL)
            return;

        std::string message = "CRITICAL, " + log_message + ", ";

        add_timestamp(message);

        if (console) {
            std::cout << message;
        }

        if (persistent) {
            file << message;
        }
    }

    void set_priority(PRIORITY priority) {
        this->priority = priority;
    }

    auto get_priority() const {
        return priority;
    }

    ~Logger() {
        file.close();
    };

};


#endif //L2LOG_LOGGER_H
