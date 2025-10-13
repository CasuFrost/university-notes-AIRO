#pragma once
using namespace std;
#include "node.h"

struct BTree
{
    BTree(int v);
    BTree();

    Node *root;
    bool insert(int v);
};