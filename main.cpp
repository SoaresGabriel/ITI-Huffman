#include <iostream>
#include <fstream>
#include "HuffmanTree.h"
#include "HuffmanWriter.h"
#include "HuffmanReader.h"

using namespace std;

void compress(const string &sourceFile);
void decompress(const string &sourceFile);

int main(int argc, char** argv) {

    clock_t initialTime = clock(), finalTime;

    // calls compress or decompress

    finalTime = clock();
    long executionTime = ((finalTime - initialTime) / (CLOCKS_PER_SEC / 1000));
    cout << "t: " << executionTime << " ms" << endl;

    return 0;
}

void compress(const string &sourceFile) {

    // frequency and totalBytes declaration
    long frequencies[256];
    for (long &frequency : frequencies) frequency = 0;

    long totalSymbols = 0;

    ifstream inFile(sourceFile, ifstream::in);

    if(!inFile.good()) {
        cout << "Falha ao abrir o arquivo" << endl;
    }

    // read file frequency and total bytes
    int symbol;
    while((symbol = inFile.get()) != EOF) {
        if(frequencies[symbol] == 0) totalSymbols++;
        frequencies[symbol]++;
    }

    // return to begin of inFile
    inFile.clear();
    inFile.seekg(0, inFile.beg);

    // output file
    HuffmanWriter writer(sourceFile + ".huff", frequencies);

    // file compression
    while(totalSymbols > 1) {

        HuffmanTree* tree = buildHuffmanTree(frequencies);

        int value = inFile.get(); // get char value from file

        string code = tree->leafPointers[value]->getCode();
        writer.writeCode(code);

        frequencies[value]--;
        if(frequencies[value] == 0) totalSymbols--;

        delete tree;
    }
    inFile.close();
    writer.close();

}

void decompress(const string &sourceFile) {
    string outFileName = sourceFile.substr(0, sourceFile.find_last_of('.')) + "2";

    HuffmanReader reader(sourceFile);
    ofstream outFile(outFileName, ofstream::binary);

    long (&frequencies)[256] = reader.frequencies;
    short totalSymbols = 0;

    // count number of different symbols in the source file
    for(auto& frequency : frequencies) if(frequency > 0) totalSymbols++;

    // decompress file
    while(totalSymbols > 1) {
        HuffmanTree* tree = buildHuffmanTree(frequencies);
        Node* node = tree->root;
        while(!node->isLeaf()) {
            node = node->getChild(reader.getBit());
        }
        unsigned char value = node->character;
        outFile.put(value);
        frequencies[value]--;
        if(frequencies[value] == 0) {
            totalSymbols--;
        }
        delete tree;
    }

    // search and writes the remaining symbol
    for (int i = 0; i < 256; ++i) {
        if(frequencies[i] > 0) {
            while(frequencies[i]--) {
                outFile.put((unsigned char)i);
            }
        }
    }

    reader.close();
    outFile.close();

}