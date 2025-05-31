#ifndef ZL_COMPRESS_H
#define ZL_COMPRESS_H

#include "naive_suffixtrees.hpp"
#include <iostream>
using namespace std;

class ZivLempelCompression {
    public:
    string give;
    string compressedData;
    ZivLempelCompression(string& s);

    string compress(string& data);
    string decompress(string& data);

    private:
    pair<int,int> findPrior(string& s, int pos, Node* node, int length, int i);
    pair<int,int> parse(string& s);
};

#endif