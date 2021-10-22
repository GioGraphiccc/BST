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
    printf("BEFORE: %s\n", original);
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
    printf("After: %s\n", original);

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
    extern char *optarg;
    bool inputFileIncluded = false;
    struct node* root = NULL;
    char argument[SIZE];
    
    
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
                printf("adding .txt to outputfile name...\n");
                appendArray(outputFile, argv[argc-i+1]);
                appendArray(outputFile, ".txt");
                break;
            }
        }
    }
    
    //if an input file has been included
    copyWord(argument, argv[argc-1]);
    printf("last argument is: %s\n", argument);
    if(!(isEqual(argument, outputFile)) && !(isEqual(argument, "-c")) && !(isEqual(argument, "-l")))
    {
        //assign the name of the input file to inputFile
        printf("Adding .txt to inputfile name\n.");
        copyWord(inputFile, argv[argc-1]); 
        appendArray(inputFile, ".txt");
        populateArray(inputFile, inputContents, root);
        inputFileIncluded = true;
        printOrder(root);
    }
    else
    {
        char word[20];
        bool isCapital;
        printf("Enter word. Enter 'n' to stop\n");
        scanf("%s", word);
        if(!(stopInput(word)))
        {
            printf("Inserting %s as root.\n", word);
            root = insert(root, word, isCapital); //insert first word as root
            scanf("%s", word);
            while (!(stopInput(word)))
            {
                printf("Checking %s if capital.\n", word);
                isCapital = checkWordCapital(word);
                printf("Inserting word %s\n", word);
                insert(root, word, isCapital);
                scanf("%s", word);
            }
        }
        if(stopInput(word))
            printf("Stopped input.\n");
        printf("printing BST: \n");
        printOrder(root);
        printf("Printing only capitals.\n");
        printCapitals(root);
    }
    //Find capital words and output them into the outputContents
    if(cflag > 0)
    {
        if(inputFileIncluded)   //print all capitals from input file
        {
            
        }
        else    //print all capitals from standard input.
        {
            
        }
    }
    if(oflag > 0) 
    {
    //     spData = fopen(outputFile, "w");
    //     printf("Printing inputContents: \n");
    //     for (int i = 0; i < 500; i++)
    //     {
    //         printf("%c", inputContents[i]);
    //         fputc(inputContents[i], spData);
    //     }
    //     printf("\n");
    //     fclose(spData);
    // }
    // else // if no outputfile was mentioned. Print to screen TODO: CHANGE INPUTCONTENTS TO OUTPUTCONTENTS
    // {
    //     printf("No output file detected. Output: \n");
    //     for (int i = 0; i < 500; i++)
    //     {
    //         printf("%c", inputContents[i]);
    //     }
    //     printf("\n");
    }
}