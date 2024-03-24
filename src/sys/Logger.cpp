#include "Logger.h"

#include <iostream>
#include <string>

#include "Files.h"
#include "Timer.h"

#include "../core/Application.h"

namespace {
    bool outLogFile = true;
    bool newSessionOpened = false;

    // Helper function to parse log messages with file and line information
    void parseLogWithFileLine(const std::string& log, const char* file, int line) {
        /** example: Thu 28 Sep 23:06:49 2023 - Error: error message:1533 
        *             path/to/file:15*/
        std::string result = timer::getOStime() + " - " + log + "\n  " + std::string(file) + ":" + std::to_string(line) + "\n";

        if (App::isDebugging()) {
            std::cout << result << std::endl;

            if (outLogFile) {
                if (!newSessionOpened) {
                    result = "\n\n-----------------New Session-----------------\n\n" + result;
                    newSessionOpened = true;
                }

                files::writeFile("./bin/Debug/logs/debug_logs.txt", result, true);
            }
        }

        else {
            if (!newSessionOpened) {
                result = "\n\n-----------------New Session-----------------\n\n" + result;
                newSessionOpened = true;
            }

            files::writeFile("./logs/release_logs.txt", result, true);
        }
    }

    // Helper function to parse log messages without file and line information
    void parseLogWithoutFileLine(std::string log) {
        /** example: Thu 28 Sep 23:06:49 2023 - Info: info message */
        std::string result = timer::getOStime() + " - " + log + "\n";

        if (App::isDebugging()) {
            std::cout << result << std::endl;

            if (outLogFile) {
                if (!newSessionOpened) {
                    result = "\n\n-----------------New Session-----------------\n\n" + result;
                    newSessionOpened = true;
                }

                files::writeFile("./bin/logs/debug_logs.txt", result, true);
            }
        }

        else {
            if (!newSessionOpened) {
                result = "\n\n-----------------New Session-----------------\n\n" + result;
                newSessionOpened = true;
            }
            
            files::writeFile("./logs/release_logs.txt", result, true);
        }
    }
}

void logger::setOutLogFile(bool outFile) {
    outLogFile = outFile;
}

void logger::_logPoint(const char* file, int line) {
    std::string point = "Point logged on: " + std::string(file) + ":" + std::to_string(line);

    parseLogWithoutFileLine(point);
}

void logger::_logError(const char* file, int line, const std::string& error, ErrorCode code) {
    std::string _error;

    if (code != 0)
        _error = "Error: " + error + ":" + std::to_string((int)code);
    else if (code == 0)
         _error = "Error: " + error;

    parseLogWithFileLine(_error, file, line);
}

void logger::_logInfo(const std::string& info) {
    std::string _info = "Info: " + info;

    parseLogWithoutFileLine(_info);
}

void logger::printHelp() {
    std::cerr <<  std::endl << "Command line arguments: " << std::endl;
    std::cerr << "  -h, --help: Prints help(this) message." << std::endl;
    std::cerr << "  -v, --version: Prints version info." << std::endl;
    std::cerr << "  -d, --debug: Enables debug mode." << std::endl;
}

void logger::printVersion(const char* name, const char* version, const char* license) {
    std::cerr << std::endl << name << " ver. "<< version << std::endl << license << std::endl;
}

int logger::enterBeforeClose() {
    std::cerr << "\nPress enter to close the application...";
    std::cin.get();

    return 0;
}