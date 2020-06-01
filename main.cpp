#include <iostream>
#include "logger.cpp"

using namespace std;

void read_log(string filename) {
    ifstream file(filename, std::ios_base::in);
    if (!file) {
        throw ::runtime_error("Could not open the file " + filename + " for writing");
    }

    string line;
    while (!file.eof()) {
        getline(file, line);
        cout << line << endl;
    }
    return;
}

int main() {
    string filename = "log.csv";
    Logger logger(filename);

    std::string first = "just random log";
    std::string error_message = "yo error message log";

    logger.log(first);
    logger.error(error_message);

    read_log(filename);

//    std::ifstream file("log.csv");
//    char line[80];
//    std::string line;
//    if (!file) {
//        std::cout << "File not read" << std::endl;
//    }
//    std::cout << file.eof() << std::endl;
//    while(!file.eof()){
////        getline(file, line);
////        getline(line, file);
//        std::cout << line << std::endl;
//    }

    return 0;
}