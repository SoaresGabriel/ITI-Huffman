//
// Created by gabriel on 23/03/18.
//

#ifndef HUFFMAN_BITWRITER_H
#define HUFFMAN_BITWRITER_H

#include <iostream>
#include <fstream>

using namespace std;

class HuffmanWriter {
private:
    unsigned char buffer;
    short bitCount;
    ofstream file;
public:
    HuffmanWriter(const string& fileName, unsigned long (&frequencies)[256], unsigned long long bytesPerTree);

    void writeBit(bool bit);

    void close();
};


#endif //HUFFMAN_BITWRITER_H
