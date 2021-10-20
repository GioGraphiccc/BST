#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
struct node
{
    char key;
    stuct node *left, *right;
};
struct node* newNode(char item)
{
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->key = item;
    temp->left = temp ->right = NULL;
    return temp;
    // Node.node;
    // void populateBST(char* ch);
    // void addLetter(char* ch);
};

void printOrder(struct node* root)
{
    if(root != NULL)
    {
        inorder(root->left);
        printf("%d \n", root->key);
        inorder(root->right);
    }
}
struct node* insert(struct node* node, int key)
{
    if(node == NULL)
        return newNode(key);

    else if(key > node->key)
        node->right = insert(node->right,key);
    
    return node;
}