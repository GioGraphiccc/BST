#include "mainbst.h"
#include "bstsort.h"
void getUserInput(char *userInput)
{
    char *word;
    char newline = '\n';
    printf("Enter word. Press enter on blank to stop\n");
    scanf("%s", word);                      //scan for word
    while(!stopInput(word))
    {
        printf("adding \\n to (%s)\n", word);
        word[findIndex('\0', word)] = '\n'; //appends \n to word
        word[findIndex('\0', word)] = '\0'; //appends \n to word
        strcat(userInput, word);       //add word to userInput
        printf("You entered: (%s)\n", word);
        scanf("%s", word);                  //scan for another word
    }
    printArray(userInput);
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
void printArray(char *arr)
{
    printf("Printing...\n");
    printf("(");
    for(int i = 0; i < strlen(arr); i++)
    {
        printf("%c", arr[i]);
    }
    printf(")\n");
    printf("Done.\n");   
}
bool stopInput(char *word)
{
    return (word[0] == '\n' || (word[0] == 'n' && word[1] == '\0')) ? true : false;
    //word[0] == 0 || word[0] == 13 || (word[0] == 110 && word[1] == 0))
}
void appendArray(char *original, char *add)
{
    if(strlen(original) == 0)
    {
        strcpy(original, add);
        return;
    }

    int i = 0; 
    int j = 0;    
    i = strlen(original); //start appending up to this
    while(isLetter(add[j]) || add[j] == '.' || add[j] == '\n')
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
        appendArray(inputFile, ".txt"); //append .txt to inputfile

        fp = fopen(inputFile, "r");
        printf("File name is: %s\n", inputFile);
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

    printf("Print BST.\n");
    printOrder(root);
    
    if(oflag > 0)
    {
        if(cflag == 0 && lflag == 0)
        {
            FILE* fp;
            fp = fopen(outputFile, "w");
            if (fp == NULL)
            {
                fprintf(stderr, "%s", "File not found in transfer capitals\n");
                print_usage();
                exit(5);
            }
            transfer(root, fp);
            fclose(fp);
        }
        else
        {
            if(cflag > 0)
            {
                FILE* fp;
                fp = fopen(outputFile, "w");
                if (fp == NULL)
                {
                    fprintf(stderr, "%s", "File not found in transfer capitals\n");
                    print_usage();
                    exit(5);
                }
                transferCapitals(root, fp);
                fclose(fp);
                //deleteTree
            }
            else if(lflag > 0) 
            {   
                FILE* fp;
                fp = fopen(outputFile, "w");
                if (fp == NULL)
                {
                    fprintf(stderr, "%s", "File not found in transfer capitals\n");
                    print_usage();
                    exit(5);
                }
                transferLower(root, fp);
                fclose(fp);
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