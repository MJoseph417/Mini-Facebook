#include "prog1.h"

int chooseCommand(hashTable *hTable, char** commands)
{
    if(strlen(commands[0]) == 2 || (*commands)[1] == '\0')
    {
        switch((*commands)[0])
        {
            case 'P':
                if(commands[1] == NULL || commands[2] != NULL)
                {
                    return -1;
                }
                else
                {
                    *(commands[1] + strcspn(commands[1], "\r\n")) = 0;
                    createUser(hTable, commands[1]);
                }

                break;

            case 'F':
                if(commands[2] == NULL)
                {
                    return -1;
                }
                else
                {
                    *(commands[2] + strcspn(commands[2], "\r\n")) = 0;
                    if(addFriends(hTable, commands[1], commands[2]) == 1)
                    {
                        printf("Could not add friends\n");
                    }
                }
                break;

            case 'U':
                if(commands[2] == NULL)
                {
                    return -1;
                }
                else
                {
                    *(commands[2] + strcspn(commands[2], "\r\n")) = 0;
                    if(unfriend(hTable, commands[1], commands[2]) == 0)
                    {
                        printf("%s and %s are no longer friends\n", commands[1], commands[2]);
                    }
                }
                break;

            case 'L':
                if(commands[1] == NULL || commands[2] != NULL)
                {
                    return -1;
                }
                else
                {
                    *(commands[1] + strcspn(commands[1], "\r\n")) = 0;
                    listFriends(hTable, commands[1]);
                }
                break;

            case 'Q':
                if(commands[2] == NULL)
                {
                    return -1;
                }
                else
                {
                    *(commands[2] + strcspn(commands[2], "\r\n")) = 0;
                    if(queryFriends(hTable, commands[1], commands[2]) == 0)
                    {
                        printf("Yes\n");
                    }
                    else
                    {
                        printf("No\n");
                    }
                }

                break;

            case 'X':
                printf("X was chosen\n");
                return 0;
                break;

            case '\n':
                break;

            default:
                return -1;
        }
    }
    else{
        return -1;
    }
    
    return 1;
}

void checkEmptyStrings(char** commands)
{
    for(int i = 0; i<3; i++)
    {
        if(commands[i])
        {
            if((*(commands + i))[0] == '\n')
            {
                commands[i] = NULL;
            }
        }
    }
}