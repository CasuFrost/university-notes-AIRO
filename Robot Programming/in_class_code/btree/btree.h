#pragma once
using namespace std;
#include "node.h"

struct BTree
{
    BTree(int v);
    BTree();

    Node *root;
    bool insert(int v);
    void print();
    void print(Node *curr, int depth);
};

bool rescursive_insert(int v, Node *curr);
