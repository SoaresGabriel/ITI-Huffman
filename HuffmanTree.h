//
// Created by gabriel on 21/03/18.
//

#ifndef HUFFMAN_HUFFMANTREE_H
#define HUFFMAN_HUFFMANTREE_H

#include "Node.h"

struct HuffmanTree {
    Node* root;
    Node* leafPointers[256];
    ~HuffmanTree();
};

HuffmanTree* buildHuffmanTree(unsigned long frequencies[256]);

#endif //HUFFMAN_HUFFMANTREE_H
