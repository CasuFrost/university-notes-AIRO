#pragma once
using namespace std;
struct Node
{
    int value;
    Node *parent;
    Node *left;
    Node *right;

    Node();
    Node(int v);
    Node(int v, Node *l, Node *r);
    ~Node();

    bool haveLeft();
    bool haveRight();

    void addLeft(Node *n);
    void addRight(Node *n);
};

bool exists(int v, Node *n);