#include "../include/HeightMap.h"

HeightMap::HeightMap(const string& filename) {
    ifstream file(filename, ios::in | ios::binary | ios::ate);
    if (file.is_open()) {
        const int SRTM_version = 1201;
        height.resize(SRTM_version, vector<int>(SRTM_version));

        unsigned char memblock[2];

        for (int r = 0; r < SRTM_version; r++) {
            for (int c = 0; c < SRTM_version; c++) {
                file.read(reinterpret_cast<char*>(memblock), 2);
                height[r][c] = (memblock[0] << 8) | memblock[1];
            }
        }
        file.close();
    } else {
        throw std::runtime_error("Cannot open file");
    }
}




int HeightMap::getHeight(int r, int c) {
    if (r >= 0 && r < height.size() && c >= 0 && c < height[0].size()) {
        return height[r][c];
    } else {
        throw out_of_range("Indices out of range");
    }
}
