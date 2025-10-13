using namespace std;
#include "btree.h"
#include <iostream>

BTree::BTree(int v)
{
    root = new Node;
    root->value = v;
}
BTree::BTree()
{
    root = new Node;
    root->value = 0;
}

bool BTree::insert(int v)
{
    Node *curr = root;
    while (1)
    {
        if (v < curr->value)
        {
            if (!(curr->haveLeft()))
            {
                Node *child = new Node(v);
                curr->addLeft(child);
                return 1;
            }
            if (v < curr->left->value)
                curr = curr->left;
            else if (v > curr->left->value)
            {
                Node *child = new Node(v);
                Node *left = curr->left;
                curr->addLeft(child);
                child->addLeft(left);
                return 1;
            }
        }
        else if (v > curr->value)
        {
            if (!(curr->haveRight()))
            {
                Node *child = new Node(v);
                curr->addRight(child);
                return 1;
            }
            if (v > curr->right->value)
                curr = curr->right;
            else if (v < curr->right->value)
            {
                Node *child = new Node(v);
                Node *right = curr->right;
                curr->addRight(child);
                child->addRight(right);
                return 1;
            }
        }
        else
        {
            cout << "element already in the btree." << endl;
            return 0;
        }
    }
}