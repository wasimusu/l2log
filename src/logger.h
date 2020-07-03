#ifndef L2LOG_LOGGER_H
#define L2LOG_LOGGER_H

#include <iostream>
#include <string>
#include <mutex>
#include <fstream>
#include <ctime>
#include <chrono>
#include <unordered_map>
#include <atomic>

/**
 * @file
 * Feature request
 *
 * What time you want to set? UTC Time, Mountain Time, etc?
 * What are the possible exceptions that can occur?
 * Accept time formatting function?
 * What guarantees do you provide?
 * */

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
    const std::string filename;
    bool console = true;
    bool persistent = false;
    bool log_datetime = false;
    std::mutex write_mutex;
    std::fstream file;

    PRIORITY priority = PRIORITY::NOTSET;
    time_t timeptr = time(nullptr);

public:
    /**
     * @brief default constructor of the logger
     *
     * */
    explicit Logger(const std::string &filename = "",
                    bool console = true,
                    bool persistent = false,
                    bool log_datetime = true,
                    PRIORITY priority = PRIORITY::NOTSET) : filename(filename),
                                                            console(console),
                                                            persistent(persistent),
                                                            log_datetime(log_datetime) {

        if (!console && !persistent) {
            throw std::invalid_argument("both console and persistent can not be false");
        }

        if (persistent) {
            file.open(filename, std::ios_base::out | std::ios_base::app | std::ios_base::in);
            if (!file) throw std::runtime_error("Failed to successfully read/open the file " + filename);
        }
    };

    /**
     * @brief adds timestamp to the log message
     * @param[&in] message: user log message
     * */
    void add_timestamp(std::string &message) {
        if (log_datetime) {
            message += ", ";
            message += asctime(localtime(&timeptr));
        }
        message += '\n';
    }

    /**
     * @brief Base case for variadic message construction.
     * @param[in] message: user log message
     * */
    template<class T>
    T build_message(T &message) {
        return message;
    }

    /**
     * @brief Construct message from string variadic
     * @param[in] message: user log message
     * */
    template<class T, class... Args>
    std::string build_message(T &message, Args...messages) {
        return message + ", " + build_message(messages...);
    }

    /**
     * @brief Use thing to log messages after constructing the user log messages
     * @param[in] message: user log message
     * */
    void basic_log(std::string &message) {
        add_timestamp(message);

        std::unique_lock<std::mutex> file_lock(write_mutex);

        if (console) {
            std::cout << message;
        }

        if (persistent) {
            file << message;
        }

    }

    /**
     * @brief log memeber with minimum priority.
     * @param[in] messages: user log message. supports any number of input argument of type string
     * @returns: void
     * */
    template<class... Args>
    void log(Args... messages) {
        if (priority > PRIORITY::NOTSET)
            return;

        std::string message = "LOG, " + build_message(messages...);
        basic_log(message);
    }

    /**
     * @brief logs message with debug priority.
     * @param[in] messages: user log message. supports any number of input argument of type string
     * @returns: void
     * */
    template<class... Args>
    void debug(Args... messages) {

        if (priority > PRIORITY::DEBUG)
            return;

        std::string message = "DEBUG, " + build_message(messages...);

        basic_log(message);
    }

    /**
     * @brief logs message with info priority.
     * @param[in] messages: user log message. supports any number of input argument of type string
     * @returns: void
     * */
    template<class... Args>
    void info(Args... messages) {

        if (priority > PRIORITY::INFO) {
            return;
        }

        std::string message = "INFO, " + build_message(messages...);

        basic_log(message);
    }

    /**
     * @brief logs message with warning priority.
     * @param[in] messages: user log message. supports any number of input argument of type string
     * @returns: void
     * */
    template<class... Args>
    void warning(Args... messages) {

        if (priority > PRIORITY::WARNING)
            return;

        std::string message = "WARNING, " + build_message(messages...);

        basic_log(message);
    }

    /**
     * @brief logs message with error priority.
     * @param[in] messages: user log message. supports any number of input argument of type string
     * @returns: void
     * */
    template<class...Args>
    void error(Args... messages) {

        if (priority > PRIORITY::ERROR)
            return;

        std::string message = "ERROR, " + build_message(messages...);

        basic_log(message);
    }

    /**
     * @brief logs message with critical priority.
     * @param[in] messages: user log message. supports any number of input argument of type string
     * @returns: void
     * */
    template<class... Args>
    void critical(Args... messages) {

        if (priority > PRIORITY::CRITICAL)
            return;

        std::string message = "CRITICAL, " + build_message(messages...);

        basic_log(message);
    }

    /**
     * @brief Changes the priority of the logger.
     * Only messages with priority higher than or equal to priority are logged.
     *
     * @param[in] priority: new value for PRIORITY for priority
     * @returns: void
     * */
    void set_priority(PRIORITY priority) {
        this->priority = priority;
    }

    /**
     * @brief Changes the priority of the logger.
     * Only messages with priority higher than or equal to priority are logged.
     *
     * @param[in] priority: new value for PRIORITY for priority
     * @returns: void
     * */
    int get_priority() const {
        return static_cast<int>(priority);
    }

    ~Logger() {
        file.close();
    };

};


#endif //L2LOG_LOGGER_H
