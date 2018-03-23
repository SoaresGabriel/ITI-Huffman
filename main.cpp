#include <iostream>
#include <fstream>
#include "HuffmanTree.h"
#include "HuffmanWriter.h"

using namespace std;

void compress(const string &sourceFile);

int main() {

    clock_t initialTime = clock(), finalTime;

    compress("test.txt");

    finalTime = clock();
    long executionTime = ((finalTime - initialTime) / (CLOCKS_PER_SEC / 1000));
    cout << "t: " << executionTime << " ms" << endl;

    return 0;
}

void compress(const string &sourceFile) {

    // frequency and totalBytes declaration
    long frequencies[256];
    for (long &frequency : frequencies) frequency = 0;
    long totalBytes = 0;

    ifstream inFile(sourceFile, ifstream::in);

    if(!inFile.good()) {
        cout << "Falha ao abrir o arquivo" << endl;
    }

    // read file frequency and total bytes
    while(inFile.good()) {
        frequencies[inFile.get()]++;
        totalBytes++;
    }

    // return to begin of inFile
    inFile.clear();
    inFile.seekg(0, inFile.beg);

    // output file
    HuffmanWriter writer(sourceFile + ".huff", frequencies);

    // file compression
    while(totalBytes-- > 1) {
        HuffmanTree* tree = buildHuffmanTree(frequencies);
        int value = inFile.get(); // get char value from file
        string code = tree->leafPointers[value]->getCode();
        writer.writeCode(code);
        frequencies[value]--;
        delete tree;
    }
    inFile.close();
    writer.close();

}
