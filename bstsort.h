#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#define LOWERA 97
#define LOWERZ 122
#define CAPITALA 65
#define CAPITALZ 90


void copyWord(char *original, char *add);
bool isGreater(char *a, char *b);
bool isEqual(char *a, char *b);
void printNode(char key[]);
bool isLetter(char ch);

//NODE STRUCT
struct node
{
    int keySize;
    char *key;
    //bool isCapital; //ADDED
    int Case;
    struct node *left;
    struct node *right;
};
struct node* newNode(char *item);
void printOrder(struct node* root);
struct node* insert(struct node* node, char* add);
void transfer(struct node* root, FILE* fp);
void transferCapitals(struct node* root, FILE* fp);
void transferLower(struct node* root, FILE* fp);
//bool checkWordCapital(char word[]);
int checkCase(char *word);
void printCapitals(struct node* root);
void printLower(struct node* root);
struct node* populateTree(char *userInput, bool isUserInput);