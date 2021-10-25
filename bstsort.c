#include "bstsort.h"
#include "mainbst.h"

void copyWord(char *original, char *add)
{
    memset(original, 0, strlen(original));

    int j = 0;
    // while((isLetter(add[j]) || add[j] == '-') && j < strlen(add))
    // {
    //     printf("strlen(original)while: %ld\n", strlen(original));
    //     printf("Add[j]: (%c)\n", add[j]);
    //     original[j] = add[j];
    //     j++;
    // }
    strcpy(original, add);
}
bool isGreater(char *a, char *b)
{
    int i = 0;
    int wordSize = (strlen(a) <= strlen(b)) ? strlen(a) : strlen(b);

    for(; i < wordSize; i++)
    {

        if(a[i] > b[i])
            return true;
            
        if((int)a[i] < (int)b[i])
            return false;
    }
    return (strlen(a) >= strlen(b) ? true: false);
}
bool isEqual(char *a, char *b)
{
    bool is_Equal = false;
    int i = 0;
    if(!a || !b)
        return is_Equal;
    if(strlen(a) != strlen(b))
        return is_Equal;
    for (; i < strlen(a); i++)
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

struct node* newNode(char *item)
{
    struct node* inputNode = NULL;
    inputNode = (struct node*)malloc(sizeof(struct node));
    inputNode->keySize = strlen(item); 
    inputNode->key = (char*)malloc(sizeof(char*) * inputNode->keySize);
    
    strcpy(inputNode->key, item);
    //printf("(newNode) Item is: (%s)\ninputNode->key is: (%s)\n", item, inputNode->key);
    inputNode->Case = checkCase(item);
    inputNode->left = inputNode->right = NULL;
    return inputNode;
};

void printOrder(struct node* root)
{
    if(root != NULL)
    { 
        // printf("node: %s\t L: %s\t R: %s\n", root->key,\
        //     (root->left) ? root->left->key : "NULL",\
        //     (root->right) ? root->right->key : "NULL");
        printOrder(root->left);
        printNode(root->key);
        printOrder(root->right);
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

struct node* insert(struct node* node, char* add)
{
    
    if(node == NULL)
    {
        printf("node is null\t inserting %s\n", add);
        return newNode(add);
    }
   
    //printf("%s : %s", (add->key == NULL) ? "Add->key is NULL" : "", (node->key == NULL) ? "Node->key is NULL\n" : "");
    // printf("node: %s\t L: %s\t R: %s\n", node->key,\
    //     (node->left) ? node->left->key : "NULL",\
    //     (node->right) ? node->right->key : "NULL");
    if(isEqual(add, node->key))
    {
        printf("%s == %s\n", add, node->key);
        return NULL;
    } //if they are equal
    printf("checking !isGreater(%s,%s)\n", add, node->key);
    if (!(isGreater(add, node->key)))
    {
        printf("Add is not greater than nodekey\t");
        printf("Node: %s\tL: %s\t Add: %s\n", node->key, (node->left) ? node->left->key : "NULL", add);
        node->left = insert(node->left,add);
    }  
    else// if(isGreater(add->key, node->key))
    {
        printf("add is greater than nodekey\t");
        //printf("Node: %s\tR: %s\t Add: %s", node->key, node->right->key, add);
        node->right = insert(node->right,add);
    }   
    return node;
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
void transfer(struct node* root, FILE* fp)
{
    if(root)
    {
        printf("check Root: %s\n", root->key);
        transfer(root->left, fp);
        fprintf(fp, "%s\n", root->key);
        transfer(root->right, fp);
    }
}
void transferCapitals(struct node* root, FILE* fp)
{
    if(root)
    {
        printf("check Root: %s\n", root->key);
        transferCapitals(root->left, fp);
        if(root->Case == 1)
            fprintf(fp, "%s\n", root->key);
        transferCapitals(root->right, fp);
    }
}
void transferLower(struct node* root, FILE* fp)
{
    if(root)
    {
        printf("check Root: %s\n", root->key);
        transferLower(root->left, fp);
        if(root->Case == -1)
            fprintf(fp, "%s\n", root->key);
        transferLower(root->right, fp);
    }
}

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
        return -1;
    }
    else if (isCapital)
    {
        return 1;
    }
    return 0;
}

struct node* populateTree(char *userInput, bool isUserinput)
{
    struct node* root = NULL;
    int wordSize = 20;
    char *temp = (char*)malloc(sizeof(char*) * wordSize);
    bool isRoot = true;
    int i = 0;
    //printArray(userInput);
    
    while(i < strlen(userInput)) //infinite loop to break out of 
    {
        int j = 0;
        memset(temp, 0, wordSize);
        while(isLetter(userInput[i]) && userInput[i] != 0) //get word until \n or \0 in userInput
        {
            temp[j] = userInput[i];
            j++;
            i++;
        }
        if(isUserinput)
            i++; //skip over \n
        else
            i +=2;
        if(isLetter(temp[0]) )
        {
            printf("Adding: (%s)\n", temp);

            //struct node* newWord = newNode(temp);
            //printf("Root: %s\tnewWord: %s\n", (root) ? root->key : "NULL", newWord->key);
            if(isRoot)
            {
                
                isRoot = false;
                printf("check\n");
                printf("Root is: %p", root);
                root = insert(root, temp);//newWord);
            }
            else
            {
                insert(root, temp);
            }
        }
    } 
    printf("ROOT IS: %s\n", root->key);
    return root;
}