#include "callback.h"

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::ofstream* file) {
    size_t totalSize = size * nmemb;
    file->write(static_cast<char*>(contents), totalSize);
    return totalSize;
}
