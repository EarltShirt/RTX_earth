#ifndef UNZIP_H
#define UNZIP_H

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <zip.h>

namespace fs = std::filesystem;

bool unzipFile(const std::string& zipFilePath, const std::string& extractPath);
void unzipDirectory(const std::string& zipDirectory, const std::string& extractDirectory);
int unzipAll();

#endif  // UNZIP_H
