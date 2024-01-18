#pragma once

#include <string>

namespace logger {
    // use logPoint() instead
    void _logPoint(const char* file, int line);

    // use logError(error, code) instead
    void _logError(const char* file, int line, std::string error, int code);

    // use logInfo(info) instead
    void _logInfo(std::string info);

    // use logSDLError() instead
    void _logSDLError(const char* file, int line);

    /**
     * @brief set logger for logging into a file. Useful on debug mode
     * 
     * @param outFile set false to prevent logger logging into a file
     */
    void setOutLogFile(bool outFile);
}

using namespace logger;

/** 
 * @brief Log a point on the given line
 */
#define logPoint() _logPoint(__FILE__, __LINE__)

/** 
 * @brief Log error with code, timestamp and line location
 * 
 * @param code set 0 to log without error code
 */ 
#define logError(error, code) _logError(__FILE__, __LINE__, error, code)

/** 
 * @brief Log given info with timestamp
 */ 
#define logInfo(info) _logInfo(info)

/** 
 * @brief Log sdl error with timestamp and line location
 */
#define logSDLError() _logSDLError(__FILE__, __LINE__)