#include "bstsort.h"
#include "mainbst.h"

void copyWord(char *original, char *add)
{
    memset(original, 0, strlen(original));

    int j = 0;
    printf("add: (%s)\n", add);
    printf("original: (%s)\n", original);
    printf("strlen(add): %ld\n", strlen(add));
    printf("strlen(original): %ld\n", strlen(original));
    // while((isLetter(add[j]) || add[j] == '-') && j < strlen(add))
    // {
    //     printf("strlen(original)while: %ld\n", strlen(original));
    //     printf("Add[j]: (%c)\n", add[j]);
    //     original[j] = add[j];
    //     j++;
    // }
    strcpy(original, add);
    printf("J: %d.\nstrlen(original): %ld\nORIGINAL(copyword): (%s)\n", j, strlen(original), original);
}
bool isGreater(char *a, char *b)
{
    int i = 0;
    for(;(a[i] == 0 || b[i] == 0); i++)
    {
        if(a[i] > b[i])
            return true;
        else //if(a[i] <= b[i])
            return false;
    }
    return (a[i] > b[i]);
}
bool isEqual(char *a, char *b)
{
    bool is_Equal = false;
    int i = 0;
    if(a == NULL || b == NULL)
        return is_Equal;
    for (; (a[i] == 0 || b[i] == 0); i++)
    {
        if(a[i] != b[i])
            return is_Equal;
    }
    is_Equal = (a[i] == b[i]);
    return is_Equal;
}
void printNode(char *key)
{
    int i = 0;
    while(key[i] != 0)
    {
        printf("%c", key[i]);
        i++;
    }
    printf("\n");
}
bool isLetter(char ch)
{
    if(ch >= CAPITALA && ch <= CAPITALZ)
        return true;
        
    if(ch >= LOWERA && ch <= LOWERZ)
        return true;
    return false;
}

void newNode(struct node* inputNode, char *item)
{
    //inputNode = (struct node*)malloc(sizeof(struct node));
    inputNode->keySize = strlen(item); 
    inputNode->key = (char*)malloc(sizeof(char*) * inputNode->keySize);
    
    strcpy(inputNode->key, item);
    printf("(newNode) Item is: (%s)\ninputNode->key is: (%s)\n", item, inputNode->key);
    inputNode->Case = checkCase(item);
    inputNode->left = inputNode->right = NULL;
};

void printOrder(struct node* root)
{
    
    if(root != NULL)
    { 
        printf("KEY IS: %s", root->key);
        printOrder(root->left);
        printNode(root->key);
        printOrder(root->right);
    }
    else
    {
        printf("root is null.\n");
    }
}
// struct node* insert(struct node* node, char key[], bool isCapital, int keySize)
// {
    // if(node == NULL)
    //     return newNode(key, isCapital, keySize);
//     if(isEqual(key, node->key) == false)
//     {
//         if (!(isGreater(key, node->key)))
//             node->left = insert(node->left, key, isCapital, keySize);
//         else if(isGreater(key, node->key))
//             node->right = insert(node->right, key, isCapital, keySize);
//         return node;
//     }    
// }

struct node* insert(struct node* node, struct node* add)
{
    
    if(node == NULL)
        return add;
    //printf("%s : %s", (add->key == NULL) ? "Add->key is NULL" : "", (node->key == NULL) ? "Node->key is NULL\n" : "");
    if(isEqual(add->key, node->key))
        return NULL;

    if (!(isGreater(add->key, node->key)))
        node->left = insert(node->left,add);
    else// if(isGreater(add->key, node->key))
        node->right = insert(node->right,add);
}
void printCapitals(struct node* root)
{
    
    if(root != NULL)
    {
        printCapitals(root->left);
        if(root->Case == 1)
            printNode(root->key);
        printCapitals(root->right);
    }
    
}
void printLower(struct node* root)
{
    if(root != NULL)
    {
        printLower(root->left);
        if((root->Case) == -1)
            printNode(root->key);
        printLower(root->right);
    }
}
void transfer(struct node* root, char* filename)
{
    FILE *file = fopen(filename, "a");
    char word[20];
    if (file == NULL)
    {
        fprintf(stderr, "%s", "File not found in trasnfer\n");
        print_usage();
        exit(5);
    }
    transfer(root->left, filename);
    strcpy(word, root->key);
    fprintf(file, "%s", word);
    fprintf(file,"\n");
    transfer(root->right, filename);
    fclose(file);
}
void transferCapitals(struct node* root, char* filename)
{
    FILE *file;
    file = fopen(filename, "w");
    char word[20];
    fprintf(file, "%c", 'B');
    fprintf(file, "%c", 'C');
    if (file == NULL)
    {
        fprintf(stderr, "%s", "File not found in transfer capitals\n");
        print_usage();
        exit(5);
    }
    transferCapitals(root, filename);
    if(root->Case == 0)
    {
        strcpy(word,root->key);
        fprintf(file, "%s", word);
        fprintf(file, "\n");
    }
    transferCapitals(root->right, filename);
    fclose(file);
}
void transferLower(struct node* root, char* filename)
{
    FILE *file = fopen(filename, "a");
    char word[20];
    if (file == NULL)
    {
        fprintf(stderr, "%s", "File not found in transferlower\n");
        print_usage();
        exit(5);
    }
    transferLower(root, filename);
    if((root->Case) == -1)
    {
        strcpy(word,root->key);
        fprintf(file, "%s", word);
        fprintf(file, "\n");
    }
    transferLower(root->right, filename);
    fclose(file);
}

// int checkWordCapital(char *word)
// {
//     int i = 0;
//     bool isCapital = true;
//     while(!(stopInput(word)) && isCapital)
//     {
//         if(word[i] == '\0')
//             break;
//         printf("checking letter %c if capital.\n", word[i]);
//         if(word[i] >= 'A' && word[i] <= 'Z')
//             i++;
//         else
//             isCapital = false;
//     }
//     if(isCapital)
//         printf("%s is capital!\n", word);
//     else
//     {
//         printf("%s is not capital!\n", word);
//     } 
//     return isCapital;
// }
int checkCase(char *word)
{
    int i = 0; 
    bool isLower = true;
    bool isCapital = true;
    if(word[0] >= 97 && word[i] <= 122) //if first letter of word is lowercase
    {
        isCapital = false;
        while(isLower)
        {
            if(word[i] == 0)
                break;
            if(word[i] >= 97 && word[i] <= 122)
                i++;
            else   
                isLower = false;
        }
    }
    else //if fist letter of word is capital
    {
        while(isCapital)
        {
            isLower = false;
            if(word[i] == 0)
                break;
            if(word[i] >= 65 && word[i] <= 90)
                i++;
            else
                isCapital = false;
        }
    }
    if(isLower)
    {
        printf("%s is all lowercase!\n", word);
        return -1;
    }
    else if (isCapital)
    {
        printf("%s is all capitals.\n", word);
        return 1;
    }
    printf("%s is mixed\n", word);
    return 0;
}

void populateTree(char *userInput, struct node* root)
{
    int wordSize = 20;
    char *temp = (char*)malloc(sizeof(char*) * wordSize);
    bool isRoot = true;
    int i = 0;
    //printArray(userInput);
    while(true) //infinite loop to break out of 
    {
        int j = 0;
        memset(temp, 0, wordSize);
        while(isLetter(userInput[i]) && userInput[i] != 0) //get word until \n or \0 in userInput
        {
            temp[j] = userInput[i];
            j++;
            i++;
        }
        i++; //skip over \n
        
        if(isLetter(temp[0]))
        {
            printf("Adding: (%s)\n", temp);
            struct node newWord;
            newNode(&newWord, temp);
            
            if(isRoot)
            {
                isRoot = false;
                root = insert(root,&newWord);
            }
            else
            {
                insert(root, &newWord);
            }
        }
        if(userInput[i] == 0) // break out of infinite loop if end of Userinput has been reached
            break;
    } 
}