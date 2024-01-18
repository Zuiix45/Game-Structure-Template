#include "Files.h"

#include "Logger.h"

#include <fstream>
#include <filesystem>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>

namespace {
    void splitTwice(std::vector<std::string> &vect, std::string data, char delimiter) {
        std::string parsed = data.substr(0, data.find(delimiter));

        vect.push_back(files::trim(parsed));

        data.erase(data.begin(), data.begin()+data.find(delimiter)+1);

        if (data.find(delimiter) != std::string::npos) splitTwice(vect, data, delimiter);
    }
}

// Write data to a text file
void files::writeTxt(std::string path, std::string data, bool addExtension) {
    std::ofstream file;

    path = files::normalizePath(path.c_str());

    // Add '.txt' extension if not present
    if (path.find(".txt") == std::string::npos && addExtension) {
        path = path + ".txt";
    }

    // Create required directories if not exists
    std::string dirPath = path.substr(0, path.find_last_of('\\'));
    std::filesystem::create_directories(dirPath);

    // Open the file for writing
    file.open(path, std::ios::out);

    // Write data to the file
    std::istringstream iss(data);
    std::string line;

    while (std::getline(iss, line)) {
        file << line << std::endl;
    }

    file.close();
}

// Read data from a text file
std::string files::readTxt(std::string path, bool addExtension) {
    std::ifstream file;

    path = files::normalizePath(path.c_str());

    // Add '.txt' extension if not present
    if (path.find(".txt") == std::string::npos && addExtension) {
        path = path + ".txt";
    }

    try {
        // Open the file for reading
        file.open(path.c_str());

        std::string errorMsg  = "Unable to open " + path;
        if (!file.is_open()) throw std::ios_base::failure("Unable to open " + errorMsg);

        std::string data;
        std::string line;

        // Read data from the file
        while (std::getline(file, line)) {
            data += line + "\n";
        }

        file.close();

        return data + "\0";

    } catch (const std::ios_base::failure& e) {
        // Log error in case of failure
        std::string error = e.what();
        logError(error, e.code().value());

        file.close();

        return "";
    }
}

std::string files::normalizePath(const std::string& messyPath) {
    std::filesystem::path path(messyPath);
    std::filesystem::path canonicalPath = std::filesystem::weakly_canonical(path);
    std::string npath = canonicalPath.make_preferred().string();

    return npath;
}

std::string files::getRootPath() {
    return std::filesystem::current_path().generic_string();
}

std::vector<std::string> files::getFileNames(const std::string& directory) {
    std::vector<std::string> fileList;

    for (const auto & entry : std::filesystem::directory_iterator(normalizePath(directory)))
        fileList.push_back(entry.path().generic_string());

    return fileList;
}

std::vector<std::string> files::getFolderNames(const std::string& directory) {
    std::vector<std::string> result;

    for(auto& path : std::filesystem::recursive_directory_iterator(normalizePath(directory)))
        if (path.is_directory())
            result.push_back(path.path().string());

    return result;
}

std::string files::trim(std::string& str) {
    const char* ws = " \t\n\r\f\v";
    
    str.erase(str.find_last_not_of(ws) + 1);
    str.erase(0, str.find_first_not_of(ws));

    return str;
}

std::vector<std::string> files::split(const std::string& str, char delimiter) {
    std::vector<std::string> result;

    splitTwice(result, str+delimiter, delimiter);

    return result;
}

bool files::isDirExist(const std::string& path) {
    return std::filesystem::is_directory(path);
}

void files::createDir(const std::string& path) {
    std::filesystem::create_directories(path);
}