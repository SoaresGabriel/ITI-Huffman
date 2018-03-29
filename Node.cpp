//
// Created by gabriel on 21/03/18.
//

#include "Node.h"

Node::Node(Node* leftChild, Node* rightChild) :
        parent(nullptr),
        leftChild(leftChild),
        rightChild(rightChild),
        character(0) {

    leftChild->parent = this;
    rightChild->parent = this;

}

Node::Node(unsigned char character) :
        parent(nullptr),
        leftChild(nullptr),
        rightChild(nullptr),
        character(character) {}

Node::~Node() {
    delete leftChild;
    delete rightChild;
}

bool Node::isLeaf() {
    return leftChild == nullptr;
}

bool Node::isRoot() {
    return parent == nullptr;
}

void Node::writeCodeIn(HuffmanWriter &writer) {
    if (this->isRoot()) return;

    this->parent->writeCodeIn(writer);

    writer.writeBit(this->parent->leftChild == this);
}

Node *Node::getChild(bool witch) {
    return witch ? this->leftChild : this->rightChild;
}
