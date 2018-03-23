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

    file.read((char*) &frequencies, sizeof(long) * 256);
}

bool HuffmanReader::getBit() {
    if(bitCount == 0) {
        file >> buffer;
        bitCount = 7;
    } else {
        bitCount--;
    }

    return (bool) ((buffer >> bitCount) & 1);
}

bool HuffmanReader::hasBit() {
    return file.good() || bitCount > 0;
}

void HuffmanReader::close() {
    file.close();
}
