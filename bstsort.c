#include "bstsort.h"
#include "mainbst.h"

bool isGreater(char *a, char *b)
{
    for(int i = 0; i < 20; i++)
    {
        if(a[i] > b[i])
            return true;
        else if(a[i] < b[i])
            return false;
    }
}
bool isEqual(char *a, char *b)
{
    for (int i = 0; i < 20; i++)
    {
        if(a[i] != b[i])
            return false;
    }
    return true;
}
void printNode(char key[])
{
    int i = 0;
    while(key[i] != '\0')
    {
        printf("%c", key[i]);
        i++;
    }
    printf("\n");
}
bool isLetter(char ch)
{
    if(ch >= 'A' && ch <= 'Z')
        return true;
        
    if(ch >= 'a' && ch <= 'z')
        return true;
    return false;
}
//NODE STRUCT
struct node
{
    char key[20];
    bool isCapital; //ADDED
    struct node *left;
    struct node *right;
};
struct node* newNode(char item[], bool capital)
{
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    for(int i = 0; i < 20; i++)
    {
        temp->key[i] = item[i];
    }
    temp->isCapital = capital;
    
    temp->left = temp ->right = NULL;
    return temp;
};

void printOrder(struct node* root)
{
    if(root != NULL)
    {
        printOrder(root->left);
        printNode(root->key);
        printOrder(root->right);
    }
}
struct node* insert(struct node* node, char key[], bool isCapital)
{
    if(node == NULL)
        return newNode(key, isCapital);
    if(isEqual(key, node->key) == false)
    {
        if (!(isGreater(key, node->key)))
            node->left = insert(node->left, key, isCapital);
        else if(isGreater(key, node->key))
            node->right = insert(node->right, key, isCapital);
        return node;
    }    
}

bool checkWordCapital(char word[])
{
    int i = 0;
    bool isCapital = true;

    printf("Test\n");
    printf("%s\n", word);
    while(!(stopInput(word)) && isCapital)
    {
        if(word[i] == '\0')
            break;
        printf("checking letter %c if capital.\n", word[i]);
        if(word[i] >= 'A' && word[i] <= 'Z')
            i++;
        else
            isCapital = false;
    }
    if(isCapital)
        printf("%s is capital!\n", word);
    else
    {
        printf("%s is not capital!\n", word);
    } 
    return isCapital;
}