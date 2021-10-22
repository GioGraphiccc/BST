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
        if(a[i] == 0 && b[i] == 0)
            break;
        if(a[i] != b[i])
        {
            printf("%s and %s are not Equal\n", a,b);
            return false;
        }
    }
    printf("%s and %s are Equal!\n", a,b);
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
void printCapitals(struct node* root)
{
    if(root != NULL)
    {
        printCapitals(root->left);
        if(root->isCapital)
            printNode(root->key);
        printCapitals(root->right);
    }
}

bool checkWordCapital(char *word)
{
    int i = 0;
    bool isCapital = true;
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

void populateArray(char *filename, char *array, struct node* root)
{
    char ch;
    char *word = malloc( sizeof(char) * (20));
    FILE *spData;
    bool isRoot = true;
    bool isCapital;
    bool newWord = true;
    printf("Word before: %s\n", word);
    //check if file exists
        spData = fopen(filename, "r");
        if (spData == NULL)
        {
            fprintf(stderr, "%s", "File not found");
            print_usage();
            exit(5);
        }
        //contents of the input file is set to inputContents[]
        int i = 0;
        int nullIndex;
        while ((ch = fgetc(spData)) != EOF)
            {
                if(isLetter(ch) && ch != '\0' && ch != '\n')
                {
                    nullIndex = findIndex('\0', word);
                    word[nullIndex] = ch;
                    printf("%d\n",ch);
                    printf("Added letter %c.\n", ch);
                }
                else
                {
                    if(isRoot)
                    {
                        printf("Word is %s\n", word);
                        isRoot = false;
                        isCapital = checkWordCapital(word);
                        printf("Inserting %s as root.\n", word);
                        root = insert(root, word, isCapital);
                        memset(word, 0, 20);
                    }
                    else
                    {
                        printf("Word is %s\n", word);
                        isCapital = checkWordCapital(word);
                        printf("Inserting %s.\n", word);
                        insert(root, word, isCapital);
                        memset(word,0,20);
                    }
                }
                    
                array[i] = ch;
                i++;
            }
            printf("\n");
        fclose(spData);
}