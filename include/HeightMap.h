#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class HeightMap {
private:
    vector<vector<int>> height;

public:
    HeightMap(const string& filename);
    int getHeight(int r, int c);
};
