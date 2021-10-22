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
struct node* newNode(char item[], bool capital);
void printOrder(struct node* root);
struct node* insert(struct node* node, char key[], bool isCapital);
bool checkWordCapital(char word[]);
