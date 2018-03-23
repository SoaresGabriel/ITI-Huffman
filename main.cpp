#include <iostream>
#include <vector>
#include "HuffmanTree.h"

using namespace std;

int main() {

    vector<long> frequencies(256);

    frequencies[0] = 3;
    frequencies[1] = 1;
    frequencies[2] = 6;

    Node* tree = buildHuffmanTree(frequencies);

    return 0;
}
