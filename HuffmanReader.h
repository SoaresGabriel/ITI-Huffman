//
// Created by gabriel on 23/03/18.
//

#ifndef HUFFMAN_HUFFMANREADER_H
#define HUFFMAN_HUFFMANREADER_H

#include <fstream>

using namespace std;

class HuffmanReader {
private:
    unsigned char buffer;
    short bitCount;
    ifstream file;

public:
    unsigned long frequencies[256];
    unsigned long long bytesPerTree;

    explicit HuffmanReader(string fileName);

    bool getBit();

    void close();
};


#endif //HUFFMAN_HUFFMANREADER_H
