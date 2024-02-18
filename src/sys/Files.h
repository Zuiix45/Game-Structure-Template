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
     * @param path The path of the file to be written.
     * @param data The data to be written to the file.
     */
    void writeFile(std::string path, std::string data, bool addExtension = true);

    /**
     * @brief Read data from a text file.
     *
     * @param path The path of the file to be read.
     * @return The data read from the file as a string.
     */
    std::string readFile(std::string path, bool addExtension = true);

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
     * @return ath of root folder.
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

    /**
     * @brief Get all file paths inside a root directory. This function includes all files inside subdirectories.
     *
     * @param directory the path of root directory
     * @return list of all file paths
     */
    std::vector<std::string> getAllFilePaths(const std::string& directory);

    /**
     * @brief Returns the file name from the given path.
     * 
     * @param path The path of the file.
     * @return The file name extracted from the path.
     */
    std::string extractFileName(const std::string& path);

    /**
     * @brief Erase all whitespaces at the start and end of a string
     *
     * @param str the original string
     */
    std::string trim(std::string &str);

    /**
     * @brief Split a string with delimiter
     *
     * @param str he original string
     * @param delimiter char to slit
     */
    std::vector<std::string> split(const std::string& str, char delimiter);

    /**
     * @brief Check if a directory exists
     *
     * @param path the path of directory
     * @return rue if directory exists
     */
    bool isDirExist(const std::string& path);
    
    /**
     * Checks if a file existsat the specified path.
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
}
