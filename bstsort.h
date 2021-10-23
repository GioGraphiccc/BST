#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

bool isGreater(char *a, char *b);
bool isEqual(char *a, char *b);
void printNode(char key[]);
bool isLetter(char ch);

//NODE STRUCT
struct node;
struct node* newNode(char item[]);//, bool isCapital);
void printOrder(struct node* root);
struct node* insert(struct node* node, struct node* add);
void transfer(struct node* root, char* filename);
void transferCapitals(struct node* root, char* filename);
void transferLower(struct node* root, char* filename);
//bool checkWordCapital(char word[]);
int checkCase(char *word);
void printCapitals(struct node* root);
void printLower(struct node* root);
void populateTree(char *filename, char *array, struct node* root);