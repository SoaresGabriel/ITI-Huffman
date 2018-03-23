//
// Created by gabriel on 23/03/18.
//

#ifndef HUFFMAN_HUFFMANREADER_H
#define HUFFMAN_HUFFMANREADER_H

#include <fstream>

using namespace std;

class HuffmanReader {
private:
    char buffer;
    short bitCount;
    ifstream file;

public:
    long frequencies[256];

    explicit HuffmanReader(string fileName);

    bool getBit();

    bool hasBit();

    void close();
};


#endif //HUFFMAN_HUFFMANREADER_H
