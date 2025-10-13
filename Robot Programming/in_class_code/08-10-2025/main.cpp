using namespace std;
#include <iostream>
#include "node.h"
#include "btree.h"
int main()
{

    BTree *tree = new BTree;
    tree->root->value = 100;
    tree->insert(10);
    tree->insert(30);
    tree->insert(150);
    tree->insert(110);

    cout << tree->root->value << "\n";
    cout << tree->root->left->value << "\n";
    cout << tree->root->left->left->value << "\n";
    cout << tree->root->right->value << "\n";
}