#include "mainbst.h"
#include "bstsort.h"

void print_usage(){
    printf("Usage: bstsort [-c] [-l] [-o output_file_name] [input_file_name].\n");
}
void printArray(char *arr, int size)
{
    printf("Printing...\n");
    for(int i = 0; i < size; i++)
    {
        printf("%c", arr[i]);
    }
    printf("\n");   
}
void populateArray(char *filename, char *array)
{
    char ch;
    FILE *spData;
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
        while ((ch = fgetc(spData)) != EOF)
            { 
                array[i] = ch;
                i++;
            }
            printf("\n");
        fclose(spData);
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
        for(int i = 1; i < 6; i++)
        {
            if(strcmp(argv[argc-i], "-o") == 0)
            {
                strcpy(outputFile, argv[argc-i+1]);
                strcat(outputFile, ".txt");
                break;
            }
        }
    }

    //if an input file has been included
    if(strcmp(argv[argc-1],outputFile) != 0 && strcmp(argv[argc-1],"-c") != 0 && strcmp(argv[argc-1],"-l") != 0)
    {
        //assign the name of the input file to inputFile
        strcpy(inputFile, argv[argc-1]); 
        strcat(inputFile, ".txt");
        populateArray(inputFile, inputContents);
        printArray(inputContents, SIZE);
        inputFileIncluded = true;
    }
    else
    {
        char word[20];
        bool isCapital;
        printf("Enter word. Enter 'n' to stop\n");
        scanf("%s", word);
        printf("Checking %s if capital.\n", word);
        isCapital = checkWordCapital(word);
        if(word[0] != 'n' && word[1] != '\0')
        {
            
            printf("Inserting %s as root.\n", word);
            root = insert(root, word, isCapital); //insert first word as root
            scanf("%s", word);
            while (word[0] != 'n' && word[1] != '\0')
            {
                printf("Checking %s if capital.\n", word);
                isCapital = checkWordCapital(word);
                printf("Inserting word %s\n", word);
                insert(root, word, isCapital);
                scanf("%s", word);
            }
        }
        printf("printing BST: \n");
        printOrder(root);
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