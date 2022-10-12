#include "prog1.h"

int main()
{
    hashTable *hTable;
    hTable = initHashTable(53);

    int terminate = 1;
    char *str = malloc(sizeof(char)*50);
    char **commands = malloc(sizeof(char*)*3);

    while (terminate != 0)
    {
        fgets(str, 50, stdin);
        char *token = strtok(str, " ");
        commands[0] = token;
        int i = 0;
        
        while(token != NULL && i < 2)
        {
            token = strtok(NULL, " ");
            i++;
            commands[i] = token;
        }

        checkEmptyStrings(commands);

        terminate = chooseCommand(hTable, commands);

        if(terminate == -1)
        {
            printf("That is not a valid command!\n");
        }
    }
    return 0;
}