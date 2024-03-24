#include "Files.h"

#include "Logger.h"

#include <fstream>
#include <sstream>
#include <filesystem>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

void Image::free() {
    stbi_image_free(data);
}

/////////////

namespace {
    // Helper function to split a string by a delimiter
    void splitTwice(std::vector<std::string>& vect, std::string data, char delimiter) {
        std::string parsed = data.substr(0, data.find(delimiter));

        vect.push_back(files::trim(parsed));

        data.erase(data.begin(), data.begin()+data.find(delimiter)+1);

        if (data.find(delimiter) != std::string::npos) splitTwice(vect, data, delimiter);
    }
}

// Write data to a text file
void files::writeFile(const std::string& mPath, const std::string& data, bool append) {
    std::ofstream file;

    std::string path = files::normalizePath(mPath);

    // Create required directories if not exists
    std::string dirPath = path.substr(0, path.find_last_of('\\'));
    std::filesystem::create_directories(dirPath);

    if (append) file.open(path, std::ios::app);
    else file.open(path, std::ios::out);

    // Write data to the file
    std::istringstream iss(data);
    std::string line;

    while (std::getline(iss, line)) {
        file << line << std::endl;
    }

    file.close();
}

// Read data from a text file
std::string files::readFile(const std::string& mPath) {
    std::ifstream file;

    std::string path = files::normalizePath(mPath);

    try {
        // Open the file for reading
        file.open(path.c_str());

        if (!file.is_open()) logError("Failed to open file: " + path, FILE_NOT_FOUND);

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
    std::string totalPath = messyPath;
    std::string rootPath = getRootPath();

    // includes "./" or ".\", does not include ".." and the root contains "src" folder
    if ((messyPath.find("./")  != std::string::npos || messyPath.find(".\\") != std::string::npos) && 
         messyPath.find("..") == std::string::npos &&
         rootPath.find("src") != std::string::npos) {

        std::string projectRoot = rootPath.substr(0, getRootPath().find("src"));

        totalPath = projectRoot + messyPath;
    }

    std::filesystem::path path(totalPath);
    std::filesystem::path canonicalPath = std::filesystem::weakly_canonical(path);
    std::string nPath = canonicalPath.make_preferred().string();

    return nPath;
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

std::vector<std::string> files::getAllFilePaths(const std::string& directory) {
    std::vector<std::string> result;

    std::string nDirectory = normalizePath(directory);

    if (!isDirExist(nDirectory)) {
        logError("Directory does not exist: " + nDirectory, FILE_NOT_FOUND);
        return result;
    }

    for(auto& path : std::filesystem::recursive_directory_iterator(normalizePath(nDirectory)))
        if (path.is_regular_file())
            result.push_back(path.path().string());

    return result;
}

std::string files::extractFileName(const std::string& path) {
    std::filesystem::path p = path;
    return p.filename().string();
}

std::string files::trim(const std::string& str) {
    const char* ws = " \t\n\r\f\v";

    std::string result = str;
    
    result.erase(result.find_last_not_of(ws) + 1);
    result.erase(0, result.find_first_not_of(ws));

    return result;
}

std::vector<std::string> files::split(const std::string& str, char delimiter) {
    std::vector<std::string> result;

    splitTwice(result, str+delimiter, delimiter);

    return result;
}

bool files::isDirExist(const std::string& path) {
    return std::filesystem::is_directory(normalizePath(path));
}

bool files::isFileExist(const std::string& path) {
    return std::filesystem::is_regular_file(normalizePath(path));
}

void files::createDir(const std::string& path) {
    std::filesystem::create_directories(normalizePath(path));
}

Image files::loadImage(const std::string& path, bool flip) {
    Image image;

    // Load image from file
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(flip);

    std::string normalizedPath = files::normalizePath(path);
    
    unsigned char *data = stbi_load(normalizedPath.c_str(), &width, &height, &nrChannels, 0);

    if (data) {
        image.data = data;
        image.width = width;
        image.height = height;
        image.nrChannels = nrChannels;
        image.isLoaded = true;
    }
    
    else {
        logError("Failed to load image: " + normalizedPath, FILE_NOT_FOUND);
        image.isLoaded = false;
    }

    image.path = normalizedPath;

    return image;
}

char* files::loadBinaryFile(const std::string& path) {
    std::string nPath = normalizePath(path);

    std::ifstream file(nPath, std::ios::binary);

    if (!file.is_open()) {
        logError("Failed to open file: " + nPath, FILE_NOT_FOUND);
        return nullptr;
    }

    file.seekg(0, std::ios::end);
    int size = file.tellg();
    char* data = new char[size];
    file.seekg(0, std::ios::beg);
    file.read(data, size);
    file.close();

    return data;
}

std::vector<Image> loadSpriteSheet(const std::string& path, int spriteWidth, int spriteHeight, int spriteCount, bool flip = true) {
    std::vector<Image> sprites;

    Image spriteSheet = files::loadImage(path, flip);

    if (!spriteSheet.isLoaded) return sprites;

    for (int i = 0; i < spriteCount; i++) {
        Image sprite;
        sprite.width = spriteWidth;
        sprite.height = spriteHeight;
        sprite.nrChannels = spriteSheet.nrChannels;
        sprite.data = new unsigned char[spriteWidth * spriteHeight * spriteSheet.nrChannels];

        for (int y = 0; y < spriteHeight; y++) {
            for (int x = 0; x < spriteWidth; x++) {
                int index = (i * spriteWidth * spriteHeight + y * spriteWidth + x) * spriteSheet.nrChannels;
                int spriteIndex = (y * spriteSheet.width + x + i * spriteWidth) * spriteSheet.nrChannels;

                for (int c = 0; c < spriteSheet.nrChannels; c++) {
                    sprite.data[index + c] = spriteSheet.data[spriteIndex + c];
                }
            }
        }

        sprites.push_back(sprite);
    }

    return sprites;
}