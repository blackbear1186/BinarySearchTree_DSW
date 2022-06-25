#include <fstream>
#include <math.h>
#include <iomanip>
#include "Johnson_assign2.h"
#include "customErrorClass.h"

using namespace std;

/*
**    Author: Berlin Johnson
**    Function Purpose: 
**        To initialize the root node and the node count.
**    Function Output: Nothing.
**    Side Effects: Nothing
*/
C_bst::C_bst(void)
{
    this->root = NULL;
    this->nodeCount = 0;
}
/*
**    Author: Berlin Johnson
**    Function Purpose: 
**        To deallocate memory, call the deleteTree function, and do cleanup of the tree.
**    Function Output: Nothing.
**    Side Effects: Nothing.
*/
C_bst::~C_bst(void)
{
    deleteTree();
}
/*
**    Author: Berlin Johnson
**    Function Purpose: 
**        To call the p_deleteTree function.
**    Function Output: Nothing.
**    Side Effects: Throw an error if the tree is empty.
*/

void C_bst::deleteTree()
{
    if (0 == this->nodeCount)
    {
        throw MyException("ERROR: Cannot delete an empty tree.");
    }
    this->p_deleteTree(this->root);
}
/*
**    Author: Berlin Johnson
**    Function Purpose: 
**        To call the p_findNode function.
**    Function Output: Nothing.
**    Side Effects: To pass an integer value into the p_findNode function and return the node. Throw an error is the tree is empty.
*/
B_NODE *C_bst::findNode(int value)
{
    if (value < 0)
    {
        throw MyException("ERROR: Cannot enter negative values to find.");
    }
    B_NODE *temp = this->p_findNode(this->root, value);
    return temp;
}

/*
**    Author: Berlin Johnson
**    Function Purpose: 
**        To call the p_getHeight function.
**    Function Output:
**    Side Effects: To pass the root into the p_getHeight function and return the height as an integer. 
**                  Throw an error if the tree is empty.
*/
int C_bst::getHeight(void)
{
    if (0 == this->nodeCount)
    {
        throw MyException("ERROR: Cannot get height of empty tree.");
    }
    return this->p_getHeight(this->root);
    
}

/*
**    Author: Berlin Johnson
**    Function Purpose: 
**           To call the p_insertValue function.
**    Function Output: Nothing.
**    Side Effects: 
**           Create a new node and pass the integer value into the p_insertValue function.
**           If the root is NULL, then the node equals this->root. Increase the node count by one each time a node is inserted.
*/

void C_bst::insertValue(int value)
{

    B_NODE *node = this->p_createNode(value);
    if (this->p_contains(value))
    {
        cout << value << " is a duplicate value." << endl;
    }
    
    if (NULL == this->root)
    {
        this->root = node;
    }
    else
    {
        this->p_insertValue(this->root, node);
        this->nodeCount++;
    }
}
/*
**    Author: Berlin Johnson
**    Function Purpose: 
**        To call the p_printTree function.
**    Function Output: Nothing.
**    Side Effects: Throw an error if the tree is empty.
*/

void C_bst::printTree()
{

    if (0 == this->nodeCount)
    {
        throw MyException("ERROR: Cannot print from an empty Linked List.");
    }
    else
    {
        this->p_printTree(this->root);
    }
}

/*
**    Author: Berlin Johnson
**    Function Purpose: 
**        To call the p_sortTree function.
**    Function Output:
**    Side Effects: Throw an error if the tree is empty.
*/

void C_bst::sortTree()
{
    if (0 == this->nodeCount)
    {
        throw MyException("ERROR: Cannot sort an empty tree.");
    }
    this->p_sortTree();
}
/*
**    Author: Berlin Johnson
**    Function Purpose: 
**        To determine if a node exist or not.
**    Function Output:
**    Side Effects: Return true if the node exist, return false if it does not exist.
**                  Throw an error if the tree is empty.
*/
bool C_bst::p_contains(int value)
{
    if (value < 0)
    {
        throw MyException("ERROR: Cannot enter negative values.");
    }
    if (findNode(value) != NULL)
    {
        return true;
    }
    return false;
}
/*
**    Author: Berlin Johnson
**    Function Purpose: 
**          To create a balanced binary search Tree implementing the DSW algorithm.
**    Function Output: Nothing.
**    Side Effects: 
**          Calculate the perfectly balanced tree, perform an intial left rotation on every second node to take care of excess,
**          perform a left rotation on every second node based on the number rotations need to perfectly balance the tree. 
**          Throw an exception error if the number of nodes in the tree is less than 3.
**
**    I used https://www.programmersought.com/article/28476322215/ as a reference to p_createTree function.
**    I followed the same structure: Initialize the three nodes. Iterate n - m, rotate left, update the grandParent and parent
**    nodes. If parent is NULL set child equal to parent->right for initials rotations. The second set of rotations: I iterated
**    through m rotations needed with the same code structure as the first for loop.
*/
void C_bst::p_createTree()
{

    int n = this->nodeCount;
    if (n < 3)
    {
        throw MyException("ERROR: Must have at least 3 nodes to balance.");
    }

    int m = (1 << (int)log2(n + 1)) - 1;

    B_NODE *grandParent = NULL;
    B_NODE *parent = this->root;
    B_NODE *child = this->root->right;

    for (int i = 0; i < n - m; i++)
    {
        this->p_rotateLeft(grandParent, parent, child);
        grandParent = child;
        parent = grandParent->right;

        if (NULL != parent)
        {
            child = parent->right;
        }
        else
        {
            break;
        }
    }

    while (m > 1)
    {
        B_NODE *grandParent = NULL;
        B_NODE *parent = this->root;
        B_NODE *child = this->root->right;
        m = m / 2;

        for (int j = 0; j < m; ++j)
        {
            this->p_rotateLeft(grandParent, parent, child);
            grandParent = child;
            parent = grandParent->right;

            if (NULL != parent)
            {
                child = parent->right;
            }
            else
            {
                break;
            }
        }
    }
}
/*
**    Author: Berlin Johnson
**    Function Purpose: 
**          To create new nodes.
**    Function Output: Nothing.
**    Side Effects: 
**          Create a new node that is dynamically store, set the left and right pointer to NULL, and return newly create node. 
**          Throw an exception error if a negative value is entered by user. 
*/
B_NODE *C_bst::p_createNode(int value)
{
    if (value < 0)
    {
        throw MyException("ERROR: Cannot enter negative values.");
    }
    B_NODE *temp = new B_NODE;

    temp->value = value;
    temp->left = NULL;
    temp->right = NULL;

    return temp;
}

/*
**    Author: Berlin Johnson
**    Function Purpose: 
**          To take an binary search tree and form it into a linked list like tree.
**    Function Output: Nothing.
**    Side Effects: 
**          All nodes to left children are rotated to the right. Throw an exception error if less than 2 nodes are in the tree. 
**
**    I used https://www.programmersought.com/article/28476322215/ as a reference to p_createVine function.
**    I used the same structure: Initialize the three nodes grandParent, parent, and child. If Child doesn't equal to NULL 
**    rotate right, update parent and child pointer. Else, grandParent equals parent, parent equals to parent->right. 
**    
*/

void C_bst::p_createVine()
{
    B_NODE *grandParent = NULL;
    B_NODE *parent = this->root;
    B_NODE *child = NULL;
    if (this->nodeCount < 2)
    {
        throw MyException("ERROR: Must have at least 2 nodes to create a vine.");
    }
    while (NULL != parent)
    {
        child = parent->left;
        if (NULL != child)
        {
            this->p_rotateRight(grandParent, parent, child);
            parent = child;
        }
        else
        {
            grandParent = parent;
            parent = parent->right;
        }
    }
}
/*
**    Author: Berlin Johnson
**    Function Purpose: 
**        To delete the entire binary Tree.
**    Function Output:
**    Side Effects: To traverse through binary Search Tree and delete every node. Throw an exception error if the tree is empty.
*/

void C_bst::p_deleteTree(B_NODE *node)
{
    if (0 == this->nodeCount)
    {
        throw MyException("ERROR: Cannot delete an empty tree.");
    }
    if (NULL != node)
    {
        this->p_deleteTree(node->left);
        this->p_deleteTree(node->right);
        delete node;
    }
}
/*
**    Author: Berlin Johnson
**    Function Purpose: 
**          To traverse the tree and return the node if it is found, otherwise return NULL.
**    Function Output:
**    Side Effects: 
**          Create new node and pass the value into it. Check if the value enter matches a node in the tree.
**          Traverse both sides of the tree and return the node if found. Throw an exception error is the tree is empty.
**
**          I used https://www.tutorialspoint.com/binary-search-tree-search-and-insertion-operations-in-cplusplus
**          as a reference to build this function. I followed the same format of: if node
**          equals to NULL or node value equals to value entered return the node.
*/

B_NODE *C_bst::p_findNode(B_NODE *node, int value)
{
    if (value < 0)
    {
        throw MyException("ERROR: Cannot enter negative values to find.");
    }
    if (NULL == node || node->value == value)
    {
        return node;
    }
    else
    {
        if (value < node->value)
        {

            return this->p_findNode(node->left, value);
        }
        else if (value > node->value)
        {

            return this->p_findNode(node->right, value);
        }
    }
    return node;
}
/*
**    Author: Berlin Johnson
**    Function Purpose: 
**          Display the binary search tree in a format.
**    Function Output: Nothing.
**    Side Effects: 
**          Perform inorder traversal and print the nodes to the screen. Throw an exception error is the tree is empty.
*/

void C_bst::p_formattedPrint(B_NODE *node, int indent)
{

    if (NULL != node)
    {
        if (0 == this->nodeCount)
        {
            throw MyException("ERROR: Cannot print in format from an empty tree.");
        }
        this->p_formattedPrint(node->left, indent + 4);
        if (indent)
        {
            cout << setw(indent) << " ";
        }
        cout << node->value << endl;
        this->p_formattedPrint(node->right, indent + 4);
    }
}
/*
**    Author: Berlin Johnson
**    Function Purpose: 
**           To traverse the tree and get height of the tree.
**    Function Output: Nothing.
**    Side Effects: 
**          Return zero if the tree is empty. Traverse through the tree and store the height on boths sides. 
**          Compare the height on both sides and return the highest height. Throw an exception error if the height is less than zero.
*/
int C_bst::p_getHeight(B_NODE *node)
{
    if (NULL == node)
    {
        return 0;
    }
    else
    {
        int lHeight = 0;
        int rHeight = 0;

        lHeight = this->p_getHeight(node->left);
        rHeight = this->p_getHeight(node->right);

        if (lHeight < 0 || rHeight < 0)
        {
            throw MyException("ERROR: Height of tree cannot be less than zero.");
        }
        if (lHeight > rHeight)
        {
            return lHeight + 1;
        }
        else
        {
            return rHeight + 1;
        }
    }
}
/*
**    Author: Berlin Johnson
**    Function Purpose: 
**           Insert a node into the binary search tree.
**    Function Output: Nothing.
**    Side Effects: 
**           Traverse the tree insert the node on the left side if less than parent value, store on the right side if greater
**           than parent node, return the parent node.      
*/

B_NODE *C_bst::p_insertValue(B_NODE *parent, B_NODE *currentNode)
{
    if(NULL == currentNode){
        throw MyException("ERROR: The node entered is empty.");
    }
    
    if (NULL == parent)
    {
        return currentNode;
    }
    else
    {
        if (currentNode->value < parent->value)
        {
            parent->left = this->p_insertValue(parent->left, currentNode);
        }
        else if (currentNode->value > parent->value)
        {
            parent->right = this->p_insertValue(parent->right, currentNode);
        }
    }
    return parent;
}

/*
**    Author: Berlin Johnson
**    Function Purpose: 
**        Print the binary search tree.
**    Function Output: Nothing.
**    Side Effects: Traverse the tree and print by inorder traversal. Throw an error is the tree is empty.
*/

void C_bst::p_printTree(B_NODE *node)
{

    if (0 == this->nodeCount)
    {
        throw MyException("ERROR: Cannot print nodes from an empty tree.");
    }
    this->p_printTree(node->left);
    cout << node->value << endl;
    this->p_printTree(node->right);
}

/*
**    Author: Berlin Johnson
**    Function Purpose: 
**        Rotate a node to the left.
**    Function Output: Nothing.
**    Side Effects: Rotate the node to the left. Throw an exception error if the parent has no children.
**
**    I used http://www.geekviewpoint.com/java/bst/dsw_algorithm as a reference to build p_rotateLeft function.
**    I used the same structure: Set grandParent->right equal to child, if grandParent is NULL set this->root equal to child.
**    Set parent->right equal to child->left and child->left equal to parent.
*/
void C_bst::p_rotateLeft(B_NODE *grandParent, B_NODE *parent, B_NODE *child)
{

    if (NULL != grandParent)
    {
        grandParent->right = child;
    }
    else
    {
        this->root = child;
    }

    if (parent->right == NULL && parent->left == NULL)
    {
        throw MyException("ERROR: There are no children to rotate right.");
    }
    parent->right = child->left;
    child->left = parent;
}
/*
**    Author: Berlin Johnson
**    Function Purpose: 
**        Rotate a node to the right.
**    Function Output: Nothing.
**    Side Effects: Rotate the node to the right. Throw an exception error if the parent has no children.
**
**    I used http://www.geekviewpoint.com/java/bst/dsw_algorithm as a reference to build p_rotateRight function.
**    I used the same structure: Set grandParent->right equal to child, if grandParent is NULL set this->root equal to child.
**    Set parent->left equal to child->right and child->right equal to parent.
*/
void C_bst::p_rotateRight(B_NODE *grandParent, B_NODE *parent, B_NODE *child)
{

    if (NULL != grandParent)
    {
        grandParent->right = child;
    }
    else
    {
        this->root = child;
    }
    if (parent->left == NULL && parent->right == NULL)
    {
        throw MyException("ERROR: There are no children to rotate right.");
    }
    parent->left = child->right;
    child->right = parent;
}

/*
**    Author: Berlin Johnson
**    Function Purpose: 
**           Print the binary search tree, create a vine and balance the tree.
**    Function Output: Nothing.
**    Side Effects: 
**           Print the formatted version of the tree, create a vine from the tree, balanced the tree, then print the formatted version of the 
**           tree again. Throw an error is the tree is empty.
*/
void C_bst::p_sortTree()
{

    if (0 == this->nodeCount)
    {
        throw MyException("ERROR: Cannot sort an empty tree.");
    }
    this->p_formattedPrint(this->root, this->nodeCount);
    this->p_createVine();
    this->p_createTree();
    cout << "--------------------------------------------------------------------" << endl;
    this->p_formattedPrint(this->root, this->nodeCount);
}
