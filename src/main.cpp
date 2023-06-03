#include <fstream>
#include <curl/curl.h>
#include "../include/callback.h"
#include <iostream>
#include <string>
#include "../include/unzip.h"
#include "../include/HeightMap.h"

int CurlRoutine(){
        CURL* curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        std::ifstream inputFile("../data/NASA_DEM.txt");
        std::string url;

        // Get the total number of URLs
        int totalUrls = 1015;

        int currentUrl = 0;

        while (std::getline(inputFile, url)) {
            // Extract latitude and longitude values from the URL
            std::string latitudeStr = url.substr(url.find_last_of('/') + 1, 3);
            std::string longitudeStr = url.substr(url.find_last_of('/') + 4, 4);

            // Convert latitude and longitude strings to numeric values
            int latitude = std::stoi(latitudeStr.substr(1));
            int longitude = std::stoi(longitudeStr.substr(1));

            // Check if the URL is within the desired latitude and longitude range
            // if (latitude == 36 && longitude >= 31 && longitude <= 54) If you want to download only some files
            if (latitude >= 36 && latitude <= 71 && longitude >= 31 && longitude <= 60) {
                std::string filename = "../data/loaded/" + url.substr(url.find_last_of('/') + 1);
                std::ofstream file(filename, std::ios::binary);

                curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, &file);

                res = curl_easy_perform(curl);
                
                currentUrl++;
                double progress = static_cast<double>(currentUrl) / totalUrls * 100;
                std::cout << "Progress: " << progress << "%" << std::endl;

                if (res != CURLE_OK) {
                    fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
                    std::cout << "Failed to download URL: " << url << std::endl;
                }
                file.close();
            }
        }

        inputFile.close();
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return 0;
}


int main() {
    // If the files need to be downloaded, uncomment the following line
    // CurlRoutine();

    // std::cout << "Unzipping files..." << std::endl;
    // unzipAll();
    // std::cout << "All files were unzipped" << std::endl;
    HeightMap heightMap("../data/unzipped/N02W063.hgt");
    
    try {
        cout << "Height at (10, 10): " << heightMap.getHeight(100, 100) << endl;
    } catch (const out_of_range& e) {
        cerr << "Error: " << e.what() << endl;
    }
    return 0;
}
