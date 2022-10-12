#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char *name;
    struct node *next;
    struct node *prev;
} Node;

typedef struct linkedList{
    char *key;
    Node *friend;
    struct linkedList * prev;
    struct linkedList * next;
} LinkedList;

typedef struct
{
    int size;
    LinkedList **entries;
} hashTable;

hashTable *initHashTable(int size);
int createUser(hashTable *hTable, char *name);
int h(char *name, int size);
int checkExist(hashTable *hTable, char *name);
LinkedList *createLinkedList(char *user);
Node *createNode(char *user);
int insertFriend(hashTable *hTable, char *userName, Node *friend);
int addFriends(hashTable *hTable, char *friend1, char *friend2);
int listFriends(hashTable *hTable, char *name);
int queryFriends(hashTable *hTable, char *name1, char *name2);
int unfriend(hashTable *hTable, char *name1, char *name2);
void freeTable(hashTable *hTable, int size);
void freeLinkedList(LinkedList *list);
void freeNode(Node *node);

int chooseCommand(hashTable *hTable, char** commands);
void checkEmptyStrings(char** commands);