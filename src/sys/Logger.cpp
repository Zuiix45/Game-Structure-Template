#include "Logger.h"

#include <iostream>
#include <string>
#include <sstream>

#include "Files.h"

#include "../Application.h"

namespace {
    bool outLogFile = true;
    bool newSessionOpened = false;

    // Helper function to parse log messages with file and line information
    void parseLogWithFileLine(std::string log, const char* file, int line) {
        std::ostringstream oss;

        /** example: Thu 28 Sep 23:06:49 2023 - Error: error message:1533 
        *             path/to/file:15*/
        oss << __TIMESTAMP__ << " - " << log << std::endl << "  " << file << ":" << line << std::endl;

        std::string result = oss.str();

        if (Application::isDebugging()) {
            std::cout << result << std::endl;

            if (outLogFile) {
                if (!newSessionOpened) {
                    result = "\n\n-----------------New Session-----------------\n\n" + result;
                    newSessionOpened = true;
                }

                files::writeFile("./bin/logs/debug_logs.txt", result);
            }
        }

        else {
            if (!newSessionOpened) {
                result = "\n\n-----------------New Session-----------------\n\n" + result;
                newSessionOpened = true;
            }

            files::writeFile("./logs/release_logs.txt", result);
        }
    }

    // Helper function to parse log messages without file and line information
    void parseLogWithoutFileLine(std::string log) {
        std::ostringstream oss;

        /** example: Thu 28 Sep 23:06:49 2023 - Info: info message */
        oss << __TIMESTAMP__ << " - " << log << std::endl;

        std::string result = oss.str();

        if (Application::isDebugging()) {
            std::cout << result << std::endl;

            if (outLogFile) {
                if (!newSessionOpened) {
                    result = "\n\n-----------------New Session-----------------\n\n" + result;
                    newSessionOpened = true;
                }

                files::writeFile("./bin/logs/debug_logs.txt", result);
            }
        }

        else {
            if (!newSessionOpened) {
                result = "\n\n-----------------New Session-----------------\n\n" + result;
                newSessionOpened = true;
            }
            
            files::writeFile("./logs/release_logs.txt", result);
        }
    }
}

void logger::setOutLogFile(bool outFile) {
    outLogFile = outFile;
}

void logger::_logPoint(const char* file, int line) {
    std::ostringstream oss;
    oss << "Point logged on: " << file << ":" << line;

    parseLogWithoutFileLine(oss.str());
}

void logger::_logError(const char* file, int line, std::string error, int code) {
    std::ostringstream oss;

    if (code != 0)
        oss << "Error: " << error << ":" << code;
    else if (code == 0)
        oss << "Error: " << error;

    parseLogWithFileLine(oss.str(), file, line);
}

void logger::_logInfo(std::string info) {
    std::ostringstream oss;
    oss << "Info: " << info;

    parseLogWithoutFileLine(oss.str());
}

void logger::_logSDLError(const char* file, int line) {
    std::ostringstream oss;

    const char* error = SDL_GetError();
    if (error == "") return;
    
    oss << "SDL ERROR: " << error << " - "<< file << ":" << line;

    parseLogWithoutFileLine(oss.str());
}
