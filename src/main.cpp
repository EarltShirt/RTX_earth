#include <fstream>
#include <curl.h>
#include "callback.h"

int main() {
    CURL* curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        std::ofstream file;
        file.open("output.hgt.zip", std::ios::binary);

        curl_easy_setopt(curl, CURLOPT_URL, "https://e4ftl01.cr.usgs.gov//DP133/SRTM/SRTMGL3.003/2000.02.11/N00E109.SRTMGL3.hgt.zip");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &file);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return 0;
}
