#ifndef CALLBACK_H
#define CALLBACK_H

#include <fstream>

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::ofstream* file);

#endif
