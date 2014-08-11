#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct charList 
{
    char *chChar;

    char *pinyin;
    char *def;
    struct charList *next;
};

void iterateFile(FILE *dictFile, FILE *outputFile)
{
    int c;


    while((c = fgetc(dictFile)) != EOF && c == '#')
    {
        // Skip first few comment lines
        while((c = fgetc(dictFile)) != '\n')
        {
            
        }
    }
    
    struct charList *head, *curr;
    head = NULL;
    int strSize;
    int i;
    // Start iterating dictionary
    for(i = 0; i < 10; i++)
    {    
        curr = (struct charList*)malloc(sizeof(struct charList));

        strSize = 0;
        curr->chChar = (char*)malloc(sizeof(char));
        while((c = fgetc(dictFile)) != ' ')
        {
            strSize++;
            curr->chChar = (char*)realloc(curr->chChar, sizeof(char) * strSize);
            curr->chChar[strSize - 1] = (char)c;
        }
        curr->chChar = (char*)realloc(curr->chChar, sizeof(char) *(strSize + 1));
        curr->chChar[strSize] = '\0';
        
        // Simplified
        while((c = fgetc(dictFile)) != ' ')
        {
            
        }
        

        // Pinyin
        curr->pinyin = (char*)malloc(sizeof(char));
        strSize = 0;
        while((c = fgetc(dictFile)) != ']')
        {
            if(c == '[' || c == ']')
            {
                continue;
            }
            strSize++;
            curr->pinyin = (char*)realloc(curr->pinyin, sizeof(char) * strSize);
            curr->pinyin[strSize - 1] = (char)c;
        }
        curr->pinyin = (char*)realloc(curr->pinyin, sizeof(char) * (strSize + 1));
        curr->pinyin[strSize] = '\0';
        
        // Def
        curr->def = (char*)malloc(sizeof(char));
        strSize = 0;
        while((c = fgetc(dictFile)) != '\n')
        {
            strSize++;
            curr->def = (char*)realloc(curr->def, sizeof(char) * strSize);
            curr->def[strSize - 1] = (char)c;
        }
        curr->def = (char*)realloc(curr->def, sizeof(char) * (strSize + 1));
        curr->def[strSize] = '\0';
            

        fprintf(outputFile, "Character: %s\nPinyin: %s\nDef: %s\n", curr->chChar, curr->pinyin, curr->def);
        fprintf(outputFile, "\n\n-----------------\n\n");
        head = curr;

        free(curr->chChar);
        free(curr->pinyin);
        free(curr->def);

        free(curr);

        
    }
    curr = head;
}


int main()
{
    FILE *dictFile = fopen("cedict_1_0_ts_utf-8_mdbg.txt", "r");
    FILE *outputFile = fopen("output.txt", "w");
    
    iterateFile(dictFile, outputFile);
    
    close(dictFile);
    close(outputFile);
    fprintf(stderr, "Done\n");
    return 0;
}
