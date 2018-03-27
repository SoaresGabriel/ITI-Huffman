//
// Created by gabriel on 23/03/18.
//

#include <iostream>
#include "HuffmanReader.h"

HuffmanReader::HuffmanReader(string fileName) :
    buffer(0), bitCount(0), file(fileName, ifstream::binary) {

    if(!file.good()) {
        cout << "Problema ao abrir o arquivo!!" << endl;
        exit(1);
    }

    file.read((char*) &frequencies, sizeof(unsigned long) * 256);
    file.read((char*) &bytesPerTree, sizeof(int));
}

bool HuffmanReader::getBit() {
    if(bitCount == 0) {
        buffer = (unsigned char) file.get();
        bitCount = 7;
    } else {
        bitCount--;
    }

    return (bool) ((buffer >> bitCount) & 1);
}

void HuffmanReader::close() {
    file.close();
}
