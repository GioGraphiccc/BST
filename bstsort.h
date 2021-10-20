#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
struct Node
{
    Node *parent;
    Node *left;
    Node *right;
    char value;
};
struct BST
{
    Node.node;
    void populateBST(char* ch);
    void addLetter(char* ch);
};


