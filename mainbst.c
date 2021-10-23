#include "mainbst.h"
#include "bstsort.h"
int findIndex(char index, char *word)
{
    int i = 0;
    for(; word[i] != index; i++);
    return i;
}
void print_usage(){
    printf("Usage: bstsort [-c] [-l] [-o output_file_name] [input_file_name].\n");
}
void printArray(char *arr)
{
    printf("Printing...\n");
    for(int i = 0; isLetter(i); i++)
    {
        printf("%c", arr[i]);
    }
    printf("Done.\n");   
}
bool stopInput(char *word)
{
    if(word[1] == '\0')
    {
        if(word[0] == 'n')
            return true;
    }
    return false;
}
void appendArray(char *original, char *add)
{
    int i = 0; 
    int j = 0;
    while (isLetter(original[i]))
    {
        i++;
    }
    while(isLetter(add[j]) || add[j] == '.')
    {
        original[i] = add[j];
        i++;
        j++;
    }
}
void copyWord(char *original, char *add)
{
    int i = 0, j = 0;
    while(isLetter(add[j]) || add[j] == '-')
    {
        original[i] = add[j];
        i++;
        j++;
    }
}

int main (int argc, char **argv)
{
    int input; 
    int cflag = 0;
    int lflag = 0;
    int oflag = 0;
    int lineCount = 1;
    int SIZE = 50;
    char inputFile[SIZE];
    char outputFile[SIZE];
    char temp[SIZE];
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
                //printf("Input: %d\n", input);
                //printf("Optarg: %s\n", optarg);
                //strcpy(outputFile, optarg);
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
                copyWord(outputFile, argv[argc-i+1]);
                copyWord(temp, outputFile);
                appendArray(outputFile, ".txt");
                break;
            }
        }
    }
    
    //if an input file has been included
    copyWord(argument, argv[argc-1]);
    if(!(isEqual(argument, temp)) && !(isEqual(argument, "-c")) && !(isEqual(argument, "-l")))
    {
        //assign the name of the input file to inputFile
        printf("Adding .txt to inputfile name.\n");
        copyWord(inputFile, argv[argc-1]); 
        appendArray(inputFile, ".txt");
        populateTree(inputFile, inputContents, root);
        inputFileIncluded = true;
        printf("Print BST.\n");
        printOrder(root);
    }
    else
    {
        char word[20];;
        printf("Enter word. Enter 'n' to stop\n");
        scanf("%s", word);
        if(!(stopInput(word)))
        {
            printf("Inserting %s as root.\n", word);
            struct node* newWord = newNode(word);
            root = insert(root, newWord); //insert first word as root
            scanf("%s", word);
            while (!(stopInput(word)))
            {
                printf("Checking %s if capital.\n", word);
                printf("Inserting word %s\n", word);
                struct node* wordNode = newNode(word);
                root = insert(root, wordNode);
                scanf("%s", word);
            }
        }
        if(stopInput(word))
            printf("Stopped input.\n");
    }
    //Find capital words and output them into the outputContents
    if(oflag > 0)
    {
        if(cflag == 0 && lflag == 0)
        {
            transfer(root, outputFile);
        }
        else
        {
            if(cflag > 0)
            {

                printf("outputFile: %s", outputFile);
                transferCapitals(root, outputFile);
            }
            else if(lflag > 0) 
            {   
                transferLower(root, outputFile);
            }
        }
    }
    else
    {
        if(cflag == 0 && lflag == 0)
        {
            printOrder(root);
        }
        else
        {
            if(cflag > 0)
            {
                printCapitals(root);
            }
            else if(lflag > 0) 
            {   
                printLower(root);
            }
        }
    }
}