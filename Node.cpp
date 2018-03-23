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
    destroy(this);
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

void Node::destroy(Node *node) {
    if(!node->isLeaf()) {
        destroy(node->leftChild);
        destroy(node->rightChild);
    }
    delete node;
}
