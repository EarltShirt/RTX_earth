#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <zip.h>

namespace fs = std::filesystem;

bool unzipFile(const std::string& zipFilePath, const std::string& extractPath) {
    zip* archive = zip_open(zipFilePath.c_str(), 0, nullptr);
    if (!archive) {
        std::cerr << "Failed to open zip archive: " << zipFilePath << std::endl;
        return false;
    }

    int entriesCount = zip_get_num_entries(archive, 0);
    for (int i = 0; i < entriesCount; ++i) {
        zip_stat_t stat;
        if (zip_stat_index(archive, i, 0, &stat) != 0) {
            std::cerr << "Failed to retrieve zip entry information for index: " << i << std::endl;
            zip_close(archive);
            return false;
        }

        std::string entryName = stat.name;
        std::string entryPath = extractPath + "/" + entryName;

        // Check if entry is a directory based on the presence of a trailing slash in the name
        bool isDirectory = entryName.back() == '/';

        if (isDirectory) {
            if (!fs::create_directories(entryPath)) {
                std::cerr << "Failed to create directory: " << entryPath << std::endl;
                zip_close(archive);
                return false;
            }
        } else {
            zip_file* file = zip_fopen_index(archive, i, 0);
            if (!file) {
                std::cerr << "Failed to open file in zip archive: " << entryPath << std::endl;
                zip_close(archive);
                return false;
            }

            std::ofstream outputFile(entryPath, std::ios::binary);
            if (!outputFile) {
                std::cerr << "Failed to create output file: " << entryPath << std::endl;
                zip_fclose(file);
                zip_close(archive);
                return false;
            }

            char buffer[8192];
            zip_int64_t bytesRead;
            while ((bytesRead = zip_fread(file, buffer, sizeof(buffer))) > 0) {
                outputFile.write(buffer, bytesRead);
            }

            outputFile.close();
            zip_fclose(file);
        }
    }

    zip_close(archive);
    return true;
}

void unzipDirectory(const std::string& zipDirectory, const std::string& extractDirectory) {
    for (const auto& entry : fs::directory_iterator(zipDirectory)) {
        std::string entryPath = entry.path().string();
        std::string entryName = entry.path().filename().string();

        if (entryName != "." && entryName != "..") {
            std::string zipFilePath = zipDirectory + "/" + entryName;
            std::cout << "Extracting file: " << zipFilePath << std::endl;
            std::string extractPath = extractDirectory + "/" + entryName.substr(0, entryName.find_last_of('.'));
            if (!unzipFile(zipFilePath, extractPath)) {
                std::cerr << "Failed to extract file: " << zipFilePath << std::endl;
            }
        }
    }
}

int unzipAll() {
    std::string zipDirectory = "../data/loaded";
    std::string extractDirectory = "../data/unzipped";

    unzipDirectory(zipDirectory, extractDirectory);

    return 0;
}
