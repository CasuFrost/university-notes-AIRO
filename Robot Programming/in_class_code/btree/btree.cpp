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
    rescursive_insert(v, root);
}

void BTree::print()
{
    print(root, 0);
}
void BTree::print(Node *curr, int depth)
{
    cout << curr->value;
    if (curr->haveRight())
    {
        cout << "--";
        print(curr->right, depth + 1);
    }
    if (curr->haveLeft())
    {
        cout << endl;
        for (int i = 0; i <= depth; i++)
        {
            cout << "      ";
        }
        print(curr->left, depth + 1);
    }
}

bool rescursive_insert(int v, Node *curr)
{
    if (v < curr->value && !curr->haveLeft())
    {
        Node *n = new Node(v);
        curr->addLeft(n);
        return 1;
    }
    if (v > curr->value && !curr->haveRight())
    {
        Node *n = new Node(v);
        curr->addRight(n);
        return 1;
    }
    if (v < curr->value)
    {
        if (v > curr->left->value)
        {
            Node *n = new Node(v);
            Node *left_curr = curr->left;
            curr->addLeft(n);
            n->addLeft(left_curr);
            return 1;
        }
        rescursive_insert(v, curr->left);
    }
    if (v > curr->value)
    {
        if (v < curr->right->value)
        {
            Node *n = new Node(v);
            Node *right_curr = curr->right;
            curr->addRight(n);
            n->addRight(right_curr);
            return 1;
        }
        rescursive_insert(v, curr->right);
    }
    return 0;
}