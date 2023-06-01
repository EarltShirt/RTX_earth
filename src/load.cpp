#include <fstream>
#include <curl.h>
#include <vector>

// Function prototype
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::ofstream* file);

int main() {
    CURL* curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        // List of URLs to download
        std::vector<std::string> urls = {
            "https://example.com/file1.zip",
            "https://example.com/file2.zip",
            "https://example.com/file3.zip"
            // Add more URLs as needed
        };

        for (const auto& url : urls) {
            std::string filename = url.substr(url.find_last_of('/') + 1);
            std::ofstream file(filename, std::ios::binary);

            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &file);

            res = curl_easy_perform(curl);

            if (res != CURLE_OK)
                fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

            file.close();
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return 0;
}

// Callback function
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::ofstream* file) {
    size_t totalSize = size * nmemb;
    file->write(static_cast<char*>(contents), totalSize);
    return totalSize;
}
