//
// Created by gabriel on 21/03/18.
//

#include <queue>
#include "HuffmanTree.h"

HuffmanTree::~HuffmanTree() {
    delete root;
}

struct NodeFrequency {
    Node* node;
    unsigned long frequency;

    NodeFrequency(Node* node, unsigned long frequency): node(node), frequency(frequency) {}
};

struct compare {
    bool operator()(const NodeFrequency* l, const NodeFrequency* r) {
        return l->frequency > r->frequency;
    }
};

HuffmanTree* buildHuffmanTree(unsigned long frequencies[256]) {
    priority_queue<NodeFrequency*, vector<NodeFrequency*>, compare> priorityQueue;

    auto tree = new HuffmanTree();

    for(int i = 0; i < 256; i++) {
        if(frequencies[i] > 0) {
            auto node = new Node((unsigned char)i);

            tree->leafPointers[i] = node;

            auto nodeFrequency = new NodeFrequency(node, frequencies[i]);
            priorityQueue.push(nodeFrequency);
        }
    }

    while(priorityQueue.size() > 1) {
        NodeFrequency* item1 = priorityQueue.top();
        priorityQueue.pop();

        NodeFrequency* item2 = priorityQueue.top();
        priorityQueue.pop();

        auto newNode = new Node(item1->node, item2->node);
        auto nodeFrequency = new NodeFrequency(newNode, (item1->frequency) + (item2->frequency));
        priorityQueue.push(nodeFrequency);

        delete item1;
        delete item2;
    }

    NodeFrequency* last = priorityQueue.top();

    priorityQueue.pop();

    tree->root = last->node;

    delete last;

    return tree;
}
