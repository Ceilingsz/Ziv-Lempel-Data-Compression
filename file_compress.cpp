#include <fstream>
#include <iostream>
#include <bitset>
#include "zl_compress.hpp"
using namespace std;

string readBinary(ifstream& inFile) {
    string rawData((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());

    string binaryData;
    for (unsigned char c : rawData) {
        binaryData += bitset<8>(c).to_string();
    }

    return binaryData;
}

int main(int argc, char** argv) {
    ifstream inFile(argv[1], ios::binary);

    string binaryData = readBinary(inFile);
    inFile.close();

    ZivLempelCompression comp(binaryData);

    ofstream outFile(argv[2], ios::binary);

    outFile.write(comp.compressedData.data(), comp.compressedData.size());
    outFile.close();

    return 0;
}
