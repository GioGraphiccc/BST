#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

void print_usage(){
    printf("Usage: bstsort [-c] [-l] [-o output_file_name] [input_file_name].\n");
}
bool isCapital(char ch)
{
    return (ch <= 'Z') && (ch >= 'A');
}
bool isLower(char ch)
{
    return (ch <= 'z') && (ch >= 'a');
}
bool isLetter(char ch)
{
    return (ch <= 'z') && (ch >= 'A');
}
int main (int argc, char **argv)
{
    int input; 
    int cflag = 0;
    int lflag = 0;
    int oflag = 0;
    char ch;
    int lineCount = 1;
    int SIZE = 50;
    char inputFile[SIZE];
    char outputFile[SIZE];
    extern char *optarg;
    FILE *spData;
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

        //check if file exists
        spData = fopen(inputFile, "r");
        if (spData == NULL)
        {
            fprintf(stderr, "%s", "File not found");
            print_usage();
            exit(5);
        }
        int i = 0;
        //contents of the input file is set to inputContents[]
        while ((ch = fgetc(spData)) != EOF)
            { 
                inputContents[i] = ch;
                if(inputContents[i] == '\n')
                   lineCount++;
                i++;
            }
            printf("\n");
        fclose(spData);
    }

    //Find capital words and output them into the outputContents
    if(cflag > 0)
    {
        printf("Entered -C\n");
        int i = 0; //outputContents index
        int wordLength = 0;
        bool CapitalWord = true;

        for(int j = 0; j < SIZE; j++) //loop through inputContents
        {
            wordLength++;
            printf("inputContents[%d] = %c\n", j, inputContents[j]);
            if(inputContents[j] == '\n') //find new line index
            {
                printf("found newline at: %d\n", j);
                printf("K = ((%d)+1) - (%d)\n", j, wordLength);
                for(int k = (j+1) - wordLength; k < j; k++)//start for loop at beginning of word
                {
                    printf("Checking: %c for capital and newline\n", inputContents[k]);
                    if(isLower(inputContents[k])) // if any letter in the word is not capital exit the for loop
                    {
                        printf("letter %c is not capital\n", inputContents[k]);
                        if(inputContents[k] != '\n')
                        {
                            printf("letter %c is not newline or capital\n", inputContents[k]);
                            k = j;
                            CapitalWord = false;
                        }
                        else    
                            printf("letter %c is newline\n", inputContents[k]);
                    }
                }
                if(CapitalWord) //if the word found is all capital letters
                {
                    printf("Found Capital Word\n");
                    for(int g = j - wordLength; g < j; g++)//start for loop at beginning of all capital word and stop at end of word (j). j is currently indexed at \n
                    {
                        outputContents[i] = inputContents[g];
                        i++; //increment outputContents index
                    }
                }
                printf("finished word\n");
                CapitalWord = true;
                wordLength = 0;
            }
        }
        printf("\n");
    }

    //OUTPUT THROUGH OUTPUTFILE OR STANDARD 
    //if an outputfile was mentioned. Write to output file
    if(oflag > 0) 
    {
        spData = fopen(outputFile, "w");
        printf("Printing inputContents: \n");
        for (int i = 0; i < 500; i++)
        {
            printf("%c", inputContents[i]);
            fputc(inputContents[i], spData);
        }
        printf("\n");
        fclose(spData);
    }
    else // if no outputfile was mentioned. Print to screen TODO: CHANGE INPUTCONTENTS TO OUTPUTCONTENTS
    {
        printf("No output file detected. Output: \n");
        for (int i = 0; i < 500; i++)
        {
            printf("%c", inputContents[i]);
        }
        printf("\n");
    }
    printf("lineCount: %d\n", lineCount);
} //end of main