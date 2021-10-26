#include "bstsort.h"

void getUserInput(char *userInput)
{
    char *word;
    char newline = '\n';
    printf("Enter word. Enter 'n' to stop\n");
    scanf("%s", word);                      //scan for word
    while(!stopInput(word))
    {
        printf("You entered: (%s)\n", word);
        word[findIndex('\0', word)] = '\n'; //appends \n to word
        word[findIndex('\0', word)] = '\0'; //appends \n to word
        strcat(userInput, word);       //add word to userInput
        
        scanf("%s", word);                  //scan for another word
    }
    printArray(userInput);
}


bool stopInput(char *word)
{
    return (word[0] == '\n' || (word[0] == 'n' && word[1] == '\0')) ? true : false;
}


int main (int argc, char **argv)
{
    int input; 
    int cflag = 0;
    int lflag = 0;
    int oflag = 0;
    int lineCount = 1;
    int SIZE = 50;
    
    char outputFile[SIZE];
    char temp[SIZE];
    char userInput[SIZE];
    extern char *optarg;
    bool inputFileIncluded = false;
    struct node* root = NULL;
    char argument[SIZE];
    int keySize;
    
    char *userInputContents = malloc( sizeof(char) * (500));
    char *inputContents = malloc( sizeof(char) * (500));
    char *outputContents = malloc( sizeof(char) * (500));
    while((input = getopt(argc, argv, "clo::")) != -1){
        switch(input){
            case 'c': 
                cflag=1;
                break;
            case 'l':
                lflag=1;
                break;
            case 'o':
                oflag=1;
                break;
            case '?':
                if(optopt == 'o') //supposed to check if o has arguement
                    {
                        fprintf(stderr, "Option -%c needs arguement\n", optopt);
                        print_usage();
                        exit(3);
                    }
                print_usage();
        }
    }
    
    //if c and l are both included print error
    if(cflag > 0 && lflag > 0) 
    {
        fprintf(stderr, "Arguement c and l cannot be included together.\n");
        print_usage();
        exit(4);
    }

    // finds and sets the output file name to outputFile
    if(oflag > 0) 
    {
        char *p;
        for(int i = 1; i < 6; i++)
        {
            p = argv[argc-i];
            if(*(p) == '-' && *(p+1) == 'o')
            {
                strcpy(outputFile, argv[argc-i+1]);
                strcpy(temp, outputFile);
                strcat(outputFile, ".txt");
                break;
            }
        }
    }
    
    //if an input file has been included
    strcpy(argument, argv[argc-1]);
    if(!(isEqual(argument, temp)) && !(isEqual(argument, "-c")) && !(isEqual(argument, "-l")))
    {
        //assign the name of the input file to inputFile
        FILE* fp;
        char inputFile[SIZE];
        memset(inputFile, 0, SIZE);
        strcpy(inputFile, argv[argc-1]); 
        strcat(inputFile, ".txt"); //append .txt to inputfile

        fp = fopen(inputFile, "r");
        if (fp == NULL)
        {
            printf("Error! opening file\n");
            // Program exits if the file pointer returns NULL.
            exit(1);
        }
        char c;
        int i = 0;
        while((c = fgetc(fp)) != EOF)
        {
            if(c != 0)
            {
                inputContents[i] = c;   
                i++;
            }
            else
            {
                break;
            }
        }
        fclose(fp);
        //printArray(inputContents);
        root = populateTree(inputContents, false); //NEW
    }
    else
    {
        printf("Getting standard input\n");
        getUserInput(userInput);
        root = populateTree(userInput, true);
    }
    //if the outputFile is present in the command line
    if(oflag > 0)
    {
        FILE* fp;
        fp = fopen(outputFile, "w");
        if (fp == NULL)
        {
            fprintf(stderr, "%s", "File not found in transfer capitals\n");
            print_usage();
            exit(5);
        }
        if(cflag == 0 && lflag == 0) //if there is no -c or -l in the command line print all BST words into the output file
        {
            transfer(root, fp);
        }
        else
        {
            if(cflag > 0) //if the -c argument was present in the comnmand line then print all Capital words from the BST into the output file
            {
                transferCapitals(root, fp);
                //deleteTree
            }
            else if(lflag > 0) //if the -l argument was present in the comnmand line then print all lowercase words from the BST into the output file
            {   
                transferLower(root, fp);
            }
        }
        fclose(fp);
    }
    else //there is no outputfile 
    {
        if(cflag == 0 && lflag == 0)
        {
            printOrder(root); //print all words from the bst to the standard output
        }
        else
        {
            if(cflag > 0) //print all Capital words to the standard output
            {
                printCapitals(root);
            }
            else if(lflag > 0) //print all lowercase words to the standard output
            {   
                printLower(root);
            }
        }
    }
} //main


/**
 * UTILITY FUNCTIONS
 */


bool isGreater(char *a, char *b)
{
    int i = 0;
    int wordSize = (strlen(a) <= strlen(b)) ? strlen(a) : strlen(b); //sets wordSize to be equal to the word with the smallest length

    for(; i < wordSize; i++) //loops through the letters of both words to detect at any point if *a is not greater than *b
    {
        if(a[i] > b[i])
            return true;
            
        if(a[i] < b[i])
            return false;
    }   //if the for loops ends without returning then the words are equal so far
    return (strlen(a) >= strlen(b) ? true: false); //final check to see if *a is greater or equal to the length of *b
}


bool isEqual(char *a, char *b)
{
    bool is_Equal = false; //set bool to false
    int i = 0;
    if(!a || !b) //if a or b is NULL
        return is_Equal;
    if(strlen(a) != strlen(b)) //if they are different length then they are not equal
        return is_Equal;
    for (; i < strlen(a); i++) //loops through the words to check at any point if they are not equal
    {
        if(a[i] != b[i])
            return is_Equal;
    }
    is_Equal = (a[i] == b[i]);
    return is_Equal;
}


void printNode(char *key) //used to print the key of a node
{
    int i = 0;
    while(key[i] != 0)
    {
        printf("%c", key[i]);
        i++;
    }
    printf("\n");
}


bool isLetter(char ch) //check if inputted character is a letter from A - Z or a - z
{
    if(ch >= CAPITALA && ch <= CAPITALZ)
        return true;
        
    if(ch >= LOWERA && ch <= LOWERZ)
        return true;
    return false;
}

struct node* newNode(char *item) //creates a new node for the inputted word
{
    struct node* inputNode = NULL;
    inputNode = (struct node*)malloc(sizeof(struct node)); //malloc the node
    inputNode->keySize = strlen(item); //set keySize to be the length of said word
    inputNode->key = (char*)malloc(sizeof(char*) * inputNode->keySize); //malloc the word to go inside the node
    
    strcpy(inputNode->key, item); //set the key of the node to be the item
    inputNode->Case = checkCase(item); //checks the case of the word and returns it to inputNode->Case
    inputNode->left = inputNode->right = NULL;
    return inputNode;
};

void printOrder(struct node* root) //print the Nodes in order recursivley
{
    if(root != NULL)
    { 
        printOrder(root->left);
        printNode(root->key);
        printOrder(root->right);
    }
}


struct node* insert(struct node* node, char* add) //insert the node into the BST at the correct position
{
    
    if(node == NULL) //if the root is NULL then set the add to be the new root
    {
        return newNode(add);
    }
   
    if(isEqual(add, node->key)) //first check to see if there are any duplicate words. if so they are ignored
    {
        return NULL;
    } 
    if (!(isGreater(add, node->key)))   //checking if the word to be inserted is greater than the key of the root node
    {
        node->left = insert(node->left,add);
    }  
    else// if(isGreater(add->key, node->key))
    {
        node->right = insert(node->right,add);
    }   
    return node;
}
void printCapitals(struct node* root) //print only the capital words in the BST recursivley
{
    
    if(root != NULL)
    {
        printCapitals(root->left);
        if(root->Case == 1) //check the case of the selected node
            printNode(root->key);
        printCapitals(root->right);
    }
    
}
void printLower(struct node* root) //print only the lower case words in the BST recursivley
{
    if(root != NULL)
    {
        printLower(root->left);
        if((root->Case) == -1) //Check the case of the selected node
            printNode(root->key);
        printLower(root->right);
    }
}
void transfer(struct node* root, FILE* fp) //transfer all words from BST to outputfile
{
    if(root)
    {
        transfer(root->left, fp);
        fprintf(fp, "%s\n", root->key);
        transfer(root->right, fp);
    }
}
void transferCapitals(struct node* root, FILE* fp) //transfer all capital Words from bst to outputfile
{
    if(root)
    {
        transferCapitals(root->left, fp);
        if(root->Case == 1)
            fprintf(fp, "%s\n", root->key);
        transferCapitals(root->right, fp);
    }
}
void transferLower(struct node* root, FILE* fp) //transfer all the lower case words from bst to outfile
{
    if(root)
    {
        transferLower(root->left, fp);
        if(root->Case == -1)
            fprintf(fp, "%s\n", root->key);
        transferLower(root->right, fp);
    }
}

int checkCase(char *word) //check the inputted word case and returns -1,1 or 0 depending on the case of the word
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

struct node* populateTree(char *userInput, bool isUserinput) //populate the BST using the userInput char array that is obtained from standard input or inputfile
{
    struct node* root = NULL;
    int wordSize = 20;
    char *temp = (char*)malloc(sizeof(char*) * wordSize);
    bool isRoot = true;
    int i = 0;
    
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

            //struct node* newWord = newNode(temp);
            //printf("Root: %s\tnewWord: %s\n", (root) ? root->key : "NULL", newWord->key);
            if(isRoot)
            {
                
                isRoot = false;
                root = insert(root, temp);//newWord);
            }
            else
            {
                insert(root, temp);
            }
        }
    } 
    return root;
}

int findIndex(char index, char *word)
{
    int i = 0;
    for(; word[i] != index; i++);
    return i;
}
void print_usage(){
    printf("Usage: bstsort [-c] [-l] [-o output_file_name] [input_file_name].\n");
}
void printArray(char *arr) //print given array to the standard output
{
    for(int i = 0; i < strlen(arr); i++)
    {
        printf("%c", arr[i]);
    }   
}

