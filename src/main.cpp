#include <iostream>
#include "logger.h"

using namespace std;

void read_log(string &filename) {
    ifstream file(filename, std::ios_base::in);
    if (!file) {
        throw ::runtime_error("Could not open the file " + filename + " for writing");
    }

    string line;
    while (!file.eof()) {
        getline(file, line);
        cout << line << endl;
    }
    cout << "Reading file" << endl;
}

int main() {
    string filename = "log.csv";
    Logger logger(filename, false, true);

//    std::string first = "just random log";
//    std::string error_message = "yo error message log";
//
//    logger.log(first, "Aru pani haleko first log message ma");
//    logger.error(error_message, "Yesma ma aru halnu paryo ni error ho");

    read_log(filename);
    return 0;
}