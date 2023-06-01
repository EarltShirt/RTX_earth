#include <fstream>
#include <curl.h>
#include "callback.h"
#include <iostream>
#include <string>
#include "unzip.h"

int main() {
    CURL* curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        std::ifstream inputFile("../data/NASA_DEM.txt");
        std::string url;

        // Get the total number of URLs
        int totalUrls = 0;
        std::ifstream countFile("../data/NASA_DEM.txt");
        std::string line;
        while (std::getline(countFile, line)) {
            totalUrls++;
        }
        countFile.close();

        int currentUrl = 0;
        int maxUrls = 1000;

        while (std::getline(inputFile, url) && currentUrl < maxUrls) {
            currentUrl++;

            std::string filename = "../data/loaded/" + url.substr(url.find_last_of('/') + 1);
            std::ofstream file(filename, std::ios::binary);

            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &file);

            res = curl_easy_perform(curl);

            if (res != CURLE_OK) {
                fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
                std::cout << "Failed to download URL: " << url << std::endl;
            } else {
                double progress = static_cast<double>(currentUrl) / totalUrls * 100;
                std::cout << "Progress: " << progress << "%" << std::endl;
            }

            file.close();
        }

        inputFile.close();
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();

    std::string zipDirectory = "../data/loaded";
    std::string extractDirectory = "../data/unzipped";

    std::cout << "Unzipping files..." << std::endl;
    unzipAll();
    std::cout << "All files were unzipped" << std::endl;

    return 0;
}
