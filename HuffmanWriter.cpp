//
// Created by gabriel on 23/03/18.
//

#include "HuffmanWriter.h"

HuffmanWriter::HuffmanWriter(const string &fileName, unsigned long (&frequencies)[256], unsigned long long bytesPerTree) :
        file(fileName, ofstream::binary), buffer(0), bitCount(0) {

    file.write((char*) &frequencies, sizeof(unsigned long) * 256);
    file.write((char*) &bytesPerTree, sizeof(unsigned long long));

}

void HuffmanWriter::writeBit(bool bit) {
    buffer = ((buffer << 1) | bit);
    bitCount++;

    if(bitCount == 8){
        file.put(buffer);
        bitCount = 0;
    }
}

void HuffmanWriter::close() {
    if(bitCount > 0) {
        buffer = (buffer << 8 - bitCount);
        file.put(buffer);
    }
    file.close();
}
