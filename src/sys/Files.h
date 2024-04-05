#pragma once

#include <string>
#include <vector>
#include <map>

struct Image {
    unsigned char* data;
    int width;
    int height;
    int nrChannels;
    bool isLoaded;
    std::string path;

    void free();
};

/**
 * @brief Declarations for file operations.
 */
namespace files {
    /**
     * @brief Provides functions for file operations such as reading, writing, and manipulating file paths.
     */
    void writeFile(const std::string& mPath, const std::string& data, bool append = false);

    /**
     * @brief Reads data from a text file.
     *
     * @param mPath The path of the file to be read.
     * @return The data read from the file as a string.
     */
    std::string readFile(const std::string& mPath);

    /**
     * @brief Normalizes the given path.
     *
     * @param messyPath The original path.
     * @return The normalized path.
     */
    std::string normalizePath(const std::string& messyPath);

    /**
     * @brief Gets the path of the root folder.
     *
     * @return The path of the root folder.
     */
    std::string getRootPath();
    
    /**
     * @brief Gets all file names inside a directory.
     *
     * @param directory The path of the directory.
     * @return A list of all file names.
     */
    std::vector<std::string> getFileNames(const std::string& directory);

    /**
     * @brief Gets all folder names inside a directory.
     *
     * @param directory The path of the directory.
     * @return A list of all folder names.
     */
    std::vector<std::string> getFolderNames(const std::string& directory);

    /**
     * @brief Gets all file paths inside a directory.
     *
     * @param directory The path of the directory.
     * @return A list of all file paths.
     */
    std::vector<std::string> getAllFilePaths(const std::string& directory);

    /**
     * @brief Extracts the file name from a path.
     *
     * @param path The original path.
     * @return The extracted file name.
     */
    std::string extractFileName(const std::string& path);

    /**
     * @brief Erases all whitespaces at the start and end of a string.
     *
     * @param str The original string.
     * @return The trimmed string.
     */
    std::string trim(const std::string& str);

    /**
     * @brief Splits a string with a delimiter.
     *
     * @param str The original string.
     * @param delimiter The character to split the string.
     * @return A vector of substrings.
     */
    std::vector<std::string> split(const std::string& str, char delimiter);

    /**
     * @brief Checks if a directory exists.
     *
     * @param path The path of the directory.
     * @return True if the directory exists, false otherwise.
     */
    bool isDirExist(const std::string& path);
    
    /**
     * @brief Checks if a file exists at the specified path.
     * 
     * @param path The path of the file to check.
     * @return True if the file exists, false otherwise.
     */
    bool isFileExist(const std::string& path);

    /**
     * @brief Creates a directory.
     *
     * @param path The path of the folder to create.
     */
    void createDir(const std::string& path);

    /**
     * @brief Loads an image from the specified path.
     *
     * @param path The path to the image file.
     * @param flip Whether to flip the image vertically (default: true).
     * @return The loaded image.
     */
    Image loadImage(const std::string& path, bool flip = true);

    /**
     * @brief Loads a binary file from the specified path.
     *
     * @param path The path to the binary file.
     * @return A pointer to the loaded binary data.
     */
    char* loadBinaryFile(const std::string& path);
}
