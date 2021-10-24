#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

void getUserInput();
void print_usage();
int findIndex(char index, char *word);
void printArray(char *arr);
bool stopInput(char *word);
void appendArray(char *original, char *add);

