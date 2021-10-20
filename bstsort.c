#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

bool isCapital(char ch)
{
    return (ch <= 'Z') && (ch >= 'A');
}
bool isLower(char ch)
{
    return (ch <= 'z') && (ch >= 'a');
}
bool isLetter(char ch)
{
    return (ch <= 'z') && (ch >= 'A');
}
