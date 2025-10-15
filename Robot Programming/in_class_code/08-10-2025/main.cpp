using namespace std;
#include <iostream>
#include "node.h"
#include "btree.h"
int main()
{

    BTree *tree = new BTree;
    tree->root->value = 100;
    tree->insert(40);
    tree->insert(50);
    tree->insert(110);
    tree->insert(20);
    tree->insert(25);

    cout << endl
         << tree->root->value << endl;
    cout << tree->root->left->value << endl;
    cout << tree->root->left->left->value << endl;
    cout << tree->root->left->left->left->value << endl;
    cout << tree->root->left->left->left->left->value << endl;
}