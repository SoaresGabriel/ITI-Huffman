//
// Created by gabriel on 21/03/18.
//

#include <queue>
#include "HuffmanTree.h"

typedef struct NodeFrequency {
    Node* node;
    long frequency;

    NodeFrequency(Node* node, long frequency): node(node), frequency(frequency) {}
};

struct compare {
    bool operator()(const NodeFrequency* l, const NodeFrequency* r) {
        return l->frequency > r->frequency;
    }
};

Node* buildHuffmanTree(vector<long> frequencies) {
    priority_queue<NodeFrequency*, vector<NodeFrequency*>, compare> priorityQueue;

    for(int i = 0; i < 256; i++) {
        if(frequencies[i] > 0) {
            auto node = new Node((unsigned char)i);
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

    Node* tree = last->node;

    delete last;

    return tree;
}