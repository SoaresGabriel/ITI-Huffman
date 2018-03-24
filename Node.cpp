//
// Created by gabriel on 21/03/18.
//

#include <utility>
#include <vector>
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

string Node::getCode() {
    if(this->isRoot()) return "";
    string thisCode = parent->leftChild == this ? "1" : "0";
    return parent->getCode() + thisCode;
}

Node *Node::getChild(bool witch) {
    return witch ? this->leftChild : this->rightChild;
}
