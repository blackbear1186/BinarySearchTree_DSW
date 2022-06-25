#ifndef __BST__H__
#define __BST__H__

#include <iostream>

using namespace std;

struct B_NODE
{
    int value;
    B_NODE *left;
    B_NODE *right;
};

class C_bst
{

public:
    C_bst();
    ~C_bst();

    void insertValue(int);
    void deleteTree();
    B_NODE *findNode(int);
    void formattedPrint();
    void printTree();
    void sortTree();
    int getHeight();

private:
    B_NODE *root;
    int nodeCount;

    B_NODE *p_createNode(int);
    B_NODE *p_insertValue(B_NODE *, B_NODE *);
    B_NODE *p_findNode(B_NODE *, int);
    void p_formattedPrint(B_NODE *, int);
    void p_printTree(B_NODE *);
    int p_getHeight(B_NODE *);
    void p_sortTree();
    void p_height(B_NODE *);
    void p_deleteTree(B_NODE *);
    void p_createVine();
    void p_rotateRight(B_NODE *, B_NODE *, B_NODE *);
    void p_rotateLeft(B_NODE *, B_NODE *, B_NODE *);
    void p_createTree();
    bool p_contains(int);
};

#endif