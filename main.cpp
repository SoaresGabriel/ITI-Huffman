#include <iostream>
#include <fstream>
#include "HuffmanTree.h"
#include "HuffmanWriter.h"
#include "HuffmanReader.h"

using namespace std;

void compress(const string &sourceFile, int bytesPerTree);
void decompress(const string &sourceFile);

int main(int argc, char** argv) {

    clock_t initialTime = clock(), finalTime;

    if ((argc < 3 || argc > 4) || (argv[1][1] != 'c' && argv[1][1] != 'd') || (argc == 4 && argv[1][1] != 'c') || (argc == 3 && argv[1][1] != 'd')) {
        cout << "Arguments: [-c N |-d] arquivo" << endl;
        exit(1);
    } else if (argv[1][1] == 'c') {
        compress(argv[3], stoi(argv[2]));
    } else if (argv[1][1] == 'd') {
        decompress(argv[2]);
    }

    finalTime = clock();
    long executionTime = ((finalTime - initialTime) / (CLOCKS_PER_SEC / 1000));
    cout << "t: " << executionTime << " ms" << endl;

    return 0;
}

void compress(const string &sourceFile, const int bytesPerTree) {

    // frequency and totalBytes declaration
    unsigned long frequencies[256];
    for (unsigned long &frequency : frequencies) frequency = 0;

    unsigned long totalSymbols = 0;

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
    HuffmanWriter writer(sourceFile + ".huff", frequencies, bytesPerTree);

    int bytesThisTree = 0;

    HuffmanTree* tree = nullptr;

    // file compression
    while(totalSymbols > 1) {

        if(tree == nullptr)
            tree = buildHuffmanTree(frequencies);

        int value = inFile.get(); // get char value from file

        string code = tree->leafPointers[value]->getCode();
        writer.writeCode(code);

        frequencies[value]--;
        if(frequencies[value] == 0) totalSymbols--;

        bytesThisTree++;
        if(bytesThisTree == bytesPerTree) {
            delete tree;
            tree = nullptr;
            bytesThisTree = 0;
        }
    }
    inFile.close();
    writer.close();

}

void decompress(const string &sourceFile) {
    if(sourceFile.size() <= 5 || sourceFile.substr(sourceFile.find_last_of('.')) != ".huff") {
        cout << "Arquivo comprimido precisa ter a extensão .huff!" << endl;
        exit(1);
    }

    string outFileName = sourceFile.substr(0, sourceFile.find_last_of('.'));

    HuffmanReader reader(sourceFile);
    ofstream outFile(outFileName, ofstream::binary);

    unsigned long (&frequencies)[256] = reader.frequencies;
    int &bytesPerTree = reader.bytesPerTree;

    short totalSymbols = 0;

    // count number of different symbols in the source file
    for(auto& frequency : frequencies) if(frequency > 0) totalSymbols++;

    int bytesThisTree = 0;

    HuffmanTree* tree = nullptr;

    // decompress file
    while(totalSymbols > 1) {
        if(tree == nullptr)
            tree = buildHuffmanTree(frequencies);
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

        bytesThisTree++;
        if(bytesThisTree == bytesPerTree) {
            delete tree;
            tree = nullptr;
            bytesThisTree = 0;
        }

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