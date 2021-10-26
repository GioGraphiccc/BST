#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#define LOWERA 97
#define LOWERZ 122
#define CAPITALA 65
#define CAPITALZ 90
/**
 *  checks if the character is in between A and Z or a and z
 */
bool isLetter(char ch);

/**
 *  checks if char *a is greater than char *b
 */
bool isGreater(char *a, char *b);

/**
 *  checks if char *a is equal to char *b
 */
bool isEqual(char *a, char *b);

/**
 *  prints the Node to standard output
 */
void printNode(char key[]);


//NODE STRUCT
struct node
{
    int keySize; //Size of key
    char *key;  //word
    int Case;   //Case type of word (-1 = word is lower case.) (0 = word is mixed) (1 = word is all capital) 
    struct node *left;
    struct node *right;
};
/**
 * create a new node with word as parameter
 */
struct node* newNode(char *item);

/**
 * Print out the nodes in order recursivley
 */
void printOrder(struct node* root);

/**
 *  insert node into bst
 */
struct node* insert(struct node* node, char* add);

/**
 * transfer all words from bst to output file
 */
void transfer(struct node* root, FILE* fp);

/**
 *  transfer only all capital words to output file
 */
void transferCapitals(struct node* root, FILE* fp);

/**
 *  transfer all lowercase words to output file
 */
void transferLower(struct node* root, FILE* fp);

/**
 *  check the case for word. returns -1,0 or 1 depending on case of word
 * Ex.  APPLE will return 1
 *      Apple will return 0
 *      apple will return -1
 */
int checkCase(char *word);

/**
 *  print all capital words from BST onto standard output
 */
void printCapitals(struct node* root);

/**
 *  print all lowercase words from bst onto standard output
 */
void printLower(struct node* root);

/**
 *  will create and insert nodes for the BST from the char array UserInput
 */
struct node* populateTree(char *userInput, bool isUserInput);

//Utility

void print_usage();
int findIndex(char index, char *word);
void printArray(char *arr);
bool stopInput(char *word);