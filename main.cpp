#include <iostream>
#include <fstream>
#include <cstring>
#include "HuffmanTree.h"
#include "HuffmanReader.h"

using namespace std;

void compress(const string &sourceFile, unsigned long long bytesPerTree);
void decompress(const string &sourceFile);

int main(int argc, char** argv) {

    clock_t initialTime = clock(), finalTime;

    if ((argc < 3 || argc > 4) || (argv[1][1] != 'c' && argv[1][1] != 'd') || (argc == 4 && argv[1][1] != 'c') || (argc == 3 && argv[1][1] != 'd')) {
        cout << "Arguments: [-c N |-d] file" << endl;
        exit(1);
    } else if (argv[1][1] == 'c') {
        unsigned long long bytesPerTree = static_cast<unsigned long long>(stoi(argv[2]));
        bytesPerTree = bytesPerTree == 0 ? UINT64_MAX : bytesPerTree;
        compress(argv[3], bytesPerTree);
    } else if (argv[1][1] == 'd') {
        decompress(argv[2]);
    }

    finalTime = clock();
    long executionTime = ((finalTime - initialTime) / (CLOCKS_PER_SEC / 1000));
    cout << "t: " << executionTime << " ms" << endl;

    return 0;
}

void compress(const string &sourceFile, const unsigned long long bytesPerTree) {

    ifstream inFile(sourceFile, ifstream::in);
    if(!inFile.good()) {
        cout << "Failed to open the file!" << endl;
    }

    // frequency and totalBytes declaration
    unsigned long frequencies[256];
    memset(&frequencies, 0, sizeof(unsigned long) * 256);
    short totalSymbols = 0;

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

    unsigned long long bytesThisTree = 0;

    HuffmanTree* tree = nullptr;

    // file compression
    while(totalSymbols > 1) {

        if(tree == nullptr)
            tree = buildHuffmanTree(frequencies);

        int value = inFile.get(); // get char value from file

        tree->leafPointers[value]->writeCodeIn(writer);

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
        cout << "Invalid compressed file! (not .huff)!" << endl;
        exit(1);
    }

    string outFileName = sourceFile.substr(0, sourceFile.find_last_of('.'));

    HuffmanReader reader(sourceFile);
    ofstream outFile(outFileName, ofstream::binary);

    unsigned long (&frequencies)[256] = reader.frequencies;
    unsigned long long &bytesPerTree = reader.bytesPerTree;

    short totalSymbols = 0;

    // count number of different symbols in the source file
    for(auto& frequency : frequencies) if(frequency > 0) totalSymbols++;

    unsigned long long bytesThisTree = 0;

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
    for (int i = 0; i < 256; i++) {
        if(frequencies[i] > 0) {
            while(frequencies[i]--) {
                outFile.put((unsigned char)i);
            }
        }
    }

    reader.close();
    outFile.close();

}