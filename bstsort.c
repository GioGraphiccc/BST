#include "bstsort.h"
#include "mainbst.h"

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
    for (; (a[i] == 0 || b[i] == 0); i++)
    {
        if(a[i] != b[i])
            return is_Equal;
    }
    is_Equal = (a[i] == b[i]);
    return is_Equal;
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
    int keySize;
    char *key;
    //bool isCapital; //ADDED
    int Case;
    struct node *left;
    struct node *right;
};
struct node* newNode(char item[])//, int case)
{
    
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    int i = 0;
    for(; item[i] == 0; i++)
    {
        temp->key[i] = item[i];
    }
    int keySize = i;
    temp->Case = checkCase(item);
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
    if(isEqual(add->key, node->key) == false)
    {
        if (!(isGreater(add->key, node->key)))
            node->left = insert(node->left,add);
        else// if(isGreater(add->key, node->key))
            node->right = insert(node->right,add);
        return node;
    } 
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
        fprintf(stderr, "%s", "File not found\n");
        print_usage();
        exit(5);
    }
    transfer(root->left, filename);
    copyWord(word, root->key);
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
        fprintf(stderr, "%s", "File not found!!!!!!!!!!!!!!!!!!!!!!!\n");
        print_usage();
        exit(5);
    }
    transferCapitals(root, filename);
    if(root->Case == 0)
    {
        copyWord(word,root->key);
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
        fprintf(stderr, "%s", "File not found\n");
        print_usage();
        exit(5);
    }
    transferLower(root, filename);
    if((root->Case) == -1)
    {
        copyWord(word,root->key);
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
            printf("checking letter %c if lower.\n", word[i]);
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
            printf("checking letter %c if capital.\n", word[i]);
            if(word[i] >= 'A' && word[i] <= 'Z')
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
    printf("%s is mixed", word);
    return 0;
}

void populateTree(char *filename, char *array, struct node* root)
{
    char ch;
    char *word = malloc( sizeof(char) * (20));
    FILE *spData;
    bool isRoot = true;
    bool newWord = true;
    //check if file exists
    spData = fopen(filename, "r");
    if (spData == NULL)
    {
        fprintf(stderr, "%s", "File not found\n");
        print_usage();
        exit(5);
    }
    //contents of the input file is set to inputContents[]
    int i = 0;
    int nullIndex;
    while ((ch = fgetc(spData)) != EOF )
    {
        while(isLetter(ch) && ch != '\0' && ch != '\n')
        {
            nullIndex = findIndex('\0', word);
            word[nullIndex] = ch;
            printf("%d\n",ch);
            printf("Added letter %c.\n", ch);
            ch = fgetc(spData);
        }
        printf("\n%d : %c\n", ch, ch);
        printf("(0: (%d:%c))(1: (%d:%c))\n", word[0], word[0], word[1], word[1]);
        if(word[0] == 0)
        {
            printf("detected\n");
            continue;
        }
            
        // else
        // {
            //if(isRoot)
            //{
        printf("Word is %s\n", word);
        struct node* newWord = newNode(word);
        root = insert(root,newWord);
        memset(word, 0, 20);
            //}
            // else
            // {
            //     printf("Word is %s\n", word);
            //     isCapital = checkWordCapital(word);
            //     printf("Inserting %s.\n", word);
            //     struct node* newWord = newNode(word, isCapital);
            //     root = insert(root, newWord);
            //     memset(word,0,20);
            // }
        //}
    }
    printf("\n");
    fclose(spData);
}