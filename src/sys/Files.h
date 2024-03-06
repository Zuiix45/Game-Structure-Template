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
     * @brief Write data to a text file.
     * 
     * @param mPath The path of the file to be written.
     * @param data The data to be written to the file.
     * @param append Whether to append to the file (default: false).
     */
    void writeFile(const std::string& mPath, const std::string& data, bool append = false);

    /**
     * @brief Read data from a text file.
     *
     * @param mPath The path of the file to be read.
     * @return The data read from the file as a string.
     */
    std::string readFile(const std::string& mPath);

    /**
     * @brief Normalizes the given path.
     *
     * @param messyPath original path
     * @return normalized path
     */
    std::string normalizePath(const std::string& messyPath);

    /**
     * @brief Get path of root folder.
     *
     * @return Path of root folder.
     */
    std::string getRootPath();
    
    /**
     * @brief Get all file names inside a directory.
     *
     * @param directory the path of directory
     * @return list of all files
     */
    std::vector<std::string> getFileNames(const std::string& directory);

    /**
     * @brief Get all folder names inside a directory.
     *
     * @param directory the path of directory
     * @return list of all folders
     */
    std::vector<std::string> getFolderNames(const std::string& directory);

    std::vector<std::string> getAllFilePaths(const std::string& directory);

    std::string extractFileName(const std::string& path);

    /**
     * @brief Erase all whitespaces at the start and end of a string
     *
     * @param str the original string
     */
    std::string trim(const std::string& str);

    /**
     * @brief Split a string with delimiter
     *
     * @param str the original string
     * @param delimiter char to split
     */
    std::vector<std::string> split(const std::string& str, char delimiter);

    /**
     * @brief Check if a directory exists
     *
     * @param path the path of directory
     * @return true if directory exists
     */
    bool isDirExist(const std::string& path);
    
    /**
     * Checks if a file exists at the specified path.
     * 
     * @param path The path of the file to check.
     * @return True if the file exists, false otherwise.
     */
    bool isFileExist(const std::string& path);

    /**
     * @brief Create directory
     *
     * @param path the path of folder
     */
    void createDir(const std::string& path);

    /**
     * Loads an image from the specified path.
     *
     * @param path The path to the image file.
     * @param flip Whether to flip the image vertically (default: true).
     * @return The loaded image.
     */
    Image loadImage(const std::string& path, bool flip = true);

    char* loadBinaryFile(const std::string& path);
}
