//
// Created by gabriel on 21/03/18.
//

#ifndef HUFFMAN_NODE_H
#define HUFFMAN_NODE_H

#include <iostream>
#include <list>

using namespace std;

class Node {
public:
    Node(Node* leftChild, Node* rightChild);
    explicit Node(unsigned char character); // leaf
    ~Node();

    Node* parent;
    Node* leftChild;
    Node* rightChild;
    unsigned char character;

    bool isRoot();
    bool isLeaf();

    Node* getChild(bool witch);

    string getCode();
};


#endif //HUFFMAN_NODE_H
