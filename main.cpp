#include <iostream>
#include "HuffmanTree.h"

using namespace std;

int main() {

    long frequencies[256];

    frequencies[0] = 3;
    frequencies[1] = 1;
    frequencies[2] = 6;

    HuffmanTree* tree = buildHuffmanTree(frequencies);

    return 0;
}
