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

typedef int ErrorCode;

namespace logger {
    // use logPoint() instead
    void _logPoint(const char* file, int line);

    // use logError(error, code) instead
    void _logError(const char* file, int line, const std::string& error, ErrorCode code = NO_ERROR_CODE);

    // use logInfo(info) instead
    void _logInfo(const std::string& info);

    void printHelp();
    void printVersion(const char* name, const char* version, const char* license);

    int enterBeforeClose();

    /**
     * @brief set logger for logging into a file. Useful on debug mode
     * 
     * @param outFile set false to prevent logger logging into a file
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
