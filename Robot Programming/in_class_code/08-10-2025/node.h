#pragma once
using namespace std;
struct Node
{
    int value;
    Node *left;
    Node *right;

    Node()
    {
        value = 0;
        left = nullptr;
        right = nullptr;
    }
    Node(int v)
    {
        value = v;
    }
    Node(int v, Node *l, Node *r)
    {
        left = l;
        right = r;
        value = v;
    }
    ~Node()
    {
        delete[] left;
        delete[] right;
    }
};