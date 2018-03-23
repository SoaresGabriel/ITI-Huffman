//
// Created by gabriel on 23/03/18.
//

#ifndef HUFFMAN_BITWRITER_H
#define HUFFMAN_BITWRITER_H

#include <iostream>
#include <fstream>

using namespace std;

class BitWriter {
private:
    char buffer;
    short bitCount;
    ofstream file;
public:
    explicit BitWriter(string fileName);

    void writeBit(bool bit);

    void writeCode(string& code);

    void close();
};


#endif //HUFFMAN_BITWRITER_H
