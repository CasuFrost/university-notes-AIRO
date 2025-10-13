using namespace std;
#include "node.h"
bool Node::haveLeft()
{
    return left != nullptr;
}
bool Node::haveRight()
{
    return right != nullptr;
}
Node::Node()
{
    value = 0;
    left = nullptr;
    right = nullptr;
}
Node::Node(int v)
{
    value = v;
    left = nullptr;
    right = nullptr;
}
Node::Node(int v, Node *l, Node *r)
{
    left = l;
    right = r;
    value = v;
}
Node::~Node()
{
    delete[] left;
    delete[] right;
}

bool exists(int v, Node *n)
{
    if (n->value == v)
        return 1;
    int res = 0;
    if (n->haveLeft())
        res += exists(v, (n->left));
    if (n->haveRight())
        res += exists(v, (n->right));
    return res > 0;
}

void Node::addLeft(Node *n)
{
    n->parent = this;
    left = n;
}
void Node::addRight(Node *n)
{
    n->parent = this;
    right = n;
}