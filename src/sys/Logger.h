#pragma once

#include <string>

#define NO_ERROR_CODE 0
#define FILE_NOT_FOUND 1
#define SPRITE_LOADING_ERROR 2
#define INVALID_CORNER_SPECIFIED 3
#define OPENGL_INITIALIZATION_ERROR 4
#define FREETYPE_INITIALIZATION_FAILED 5
#define FONT_NOT_FOUND 6
#define FONT_LOADING_ERROR 7
#define GLYPH_LOADING_ERROR 8
#define INVALID_UNIFORM_TYPE 9
#define SHADER_COMPILATION_ERROR 10
#define OPENAL_DEVICE_ERROR 11
#define OPENAL_CONTEXT_ACTIVATION_ERROR 12
#define OPENAL_CONTEXT_CREATION_ERROR 13
#define VERTEX_OR_INDEX_NULLPTR 14
#define CHARACTER_NOT_FOUND 15

typedef int ErrorCode;

namespace logger {
    
    /**
     * @brief Logs the point of execution in the code.
     * 
     * @param file The name of the source file where the log point is called.
     * @param line The line number in the source file where the log point is called.
     */
    void _logPoint(const char* file, int line);

    /**
     * @brief Logs an error message with an optional error code.
     * 
     * @param file The name of the source file where the error is logged.
     * @param line The line number in the source file where the error is logged.
     * @param error The error message to be logged.
     * @param code The error code associated with the error (default: NO_ERROR_CODE).
     */
    void _logError(const char* file, int line, const std::string& error, ErrorCode code = NO_ERROR_CODE);

    /**
     * @brief Logs an informational message.
     * 
     * @param info The informational message to be logged.
     */
    void _logInfo(const std::string& info);

    /**
     * @brief Prints the help information.
     */
    void printHelp();

    /**
     * @brief Prints the version information.
     * 
     * @param name The name of the application.
     * @param version The version of the application.
     */
    void printVersion(const char* name, const char* version);

    /**
     * @brief Prompts the user to enter a value before closing the application.
     * 
     * @return The value entered by the user.
     */
    int enterBeforeClose();

    /**
     * @brief Sets the logger to log into a file.
     * 
     * @param outFile Set to false to prevent the logger from logging into a file.
     */
    void setOutLogFile(bool outFile);
}

/** 
 * @brief Log a point on the given line
 */
#define logPoint() logger::_logPoint(__FILE__, __LINE__)

/** 
 * @brief Log error with code, timestamp and line location
 */ 
#define logError(error, code) logger::_logError(__FILE__, __LINE__, error, code)

/** 
 * @brief Log error without code, timestamp and line location
 */ 
#define logErrorWithoutCode(error) logger::_logError(__FILE__, __LINE__, error)

/** 
 * @brief Log given info with timestamp
 */ 
#define logInfo(info) logger::_logInfo(info)
