#include "prog1.h"

// Initializes a hash table with a declared size and returns a pointer to that table
hashTable *initHashTable(int size)
{
    hashTable *hTable = NULL;
    int i;

    if(size < 1) return NULL;

    if( ( hTable = malloc(sizeof(hashTable))) == NULL) return NULL;

    if( ( hTable->entries = malloc(sizeof(LinkedList*) * size)) == NULL) return NULL;

    for(int i = 0; i < size; i++)
    {
        hTable->entries[i] = NULL;
    }

    hTable->size = size;

    return hTable;
}

// Creates a user profile in the specified hash table with the given name using chaining for the collision method.  The new entry will be at the head of the linked list
// Returns a 0 if successful, 1 if not
int createUser(hashTable *hTable, char *name)
{
    LinkedList *user = createLinkedList(name);
    int index;

    if(user)
    {
        index = h(user->key, hTable->size);
        if(hTable->entries[index] == NULL)
        {
            hTable->entries[index] = user;
        }
        else
        {
            hTable->entries[index]->prev = user;
            user->next = hTable->entries[index];
            hTable->entries[index] = user;
        }

        if(strcmp(name, hTable->entries[index]->key) == 0)
        {
            return 0;
        }
    }
    return 1;
}

// takes the names of two users and creates a new Node in each users friends list with the other users name
// returns 0 if successful and 1 if not
int addFriends(hashTable *hTable, char *friend1, char *friend2)
{
    // checks to see if the users are already friends and that they exist
    if(queryFriends(hTable, friend1, friend2) == 0)
    {
        printf("These users are already friends\n");
        return 1;
    }

    Node *n1;
    Node *n2;

    // creates a node with each users name for the other users friend list
    n1 = createNode(friend1);
    n2 = createNode(friend2);

    // inserts each user into the other users friends list and returns 0 if successful
    if(insertFriend(hTable, friend1, n2) == 0)
    {
        if(insertFriend(hTable, friend2, n1) == 0)
        {
            return 0;
        }
    }
    
    return 1;
}

// takes the name of two users and checks to see if the users exist and are friends and if they do not it removes them from each others friends list
int unfriend(hashTable *hTable, char *name1, char *name2)
{
    if(queryFriends(hTable, name1, name2) == 1)
    {
        return 1;
    }

    // removes the first friend
    LinkedList *user;
    int index = h(name1, 53);
    user = hTable->entries[index];
    Node *friend = user->friend;

    while(strcmp(name2, friend->name) != 0)
    {
        friend = friend->next;
    }

    if(friend->next == NULL && friend->prev == NULL)
    {
        user->friend = NULL;
        free(friend);
    }
    else if (friend->next != NULL && friend->prev == NULL)
    {
        user->friend = friend->next;
        user->friend->prev = NULL;
        free(friend);
    }
    else if(friend->next == NULL && friend->prev != NULL)
    {
        friend->prev->next = NULL;
        free(friend);
    }
    else
    {
        friend->next->prev = friend->prev;
        friend->prev->next = friend->next;
        free(friend);
    }

    // removes the second friend
    index = h(name2, 53);
    user = hTable->entries[index];
    friend = user->friend;

    while(strcmp(name1, friend->name) != 0)
    {
        friend = friend->next;
    }

    if(friend->next == NULL && friend->prev == NULL)
    {
        user->friend = NULL;
        free(friend);
    }
    else if (friend->next != NULL && friend->prev == NULL)
    {
        user->friend = friend->next;
        user->friend->prev = NULL;
        free(friend);
    }
    else if(friend->next == NULL && friend->prev != NULL)
    {
        friend->prev->next = NULL;
        free(friend);
    }
    else
    {
        friend->next->prev = friend->prev;
        friend->prev->next = friend->next;
        free(friend);
    }

    // checks to make sure they are successfully removed
    if(queryFriends(hTable, name1, name2) == 1)
    {
        return 0;
    }
    else{
        return 1;
    }
}

// takes a users name and lists all of his friends
// returns 0 if successful and 1 if not
int listFriends(hashTable *hTable, char *name)
{
    if(checkExist(hTable, name) == 1)
    {
        printf("This user does not exist\n");
        return 1;
    }
    LinkedList *user;
    int index = h(name, 53);
    user = hTable->entries[index];
    Node *f;

    if(user != NULL)
    {
        f = user->friend;

        if(f == NULL)
        {
            printf("This user has no friends\n");
        }
        else
        {
            while(f != NULL)
            {
                printf("%s ", f->name);
                f = f->next;
            }
            printf("\n");
            return 0;
        }
    }
    return 1;
}

// checks if two users are friends and returns 0 if they are and 1 if they aren't or do not exist
int queryFriends(hashTable *hTable, char *name1, char *name2)
{
    if(checkExist(hTable, name1) == 1 || checkExist(hTable, name2) == 1)
    {
        printf("Please enter real users!\n");
        return 1;
    }

    LinkedList *user;
    int index = h(name1, 53);
    user = hTable->entries[index];
    Node *friend = user->friend;

    while(friend != NULL)
    {
        if(strcmp(name2, friend->name) == 0)
        {
            return 0;
        }

        friend = friend->next;
    }

    return 1;
}

// inserts a friend into a users friend list
int insertFriend(hashTable *hTable, char *userName, Node *friend)
{
    LinkedList *person;
    int index = h(userName, 53);
    
    person = hTable->entries[index];

    if(person == NULL)
    {
        return 1;
    }
    else
    {
        if(person->friend == NULL)
        {
            person->friend = friend;
        }
        else
        {
            person->friend->prev = friend;
            friend->next = person->friend;
            person->friend = friend;
        }
        return 0;
    }
    
    return 1;
}

// hash function
int h(char *name, int size)
{
    int i = 0;
    int hash = 0;
    while (i < 100 && name[i] != '\0')
    {
        hash = (hash * 128) % size;
        hash = (hash + (name[i] % 128)) % size;
        i++;
    }
    return hash;
}

// checks to see if a given name exists in the hash table
// returns a 0 if the person exists and a 1 if they do not
int checkExist(hashTable *hTable, char *name)
{
    LinkedList *user;
    int index;

    index = h(name, hTable->size);
    user = hTable->entries[index];

    while(user != NULL)
    {
        if(strcmp(name, user->key) == 0)
        {
            return 0;
        }
        else{
            user = user->next;
        }
    }

    return 1;
}

// initializes a linked list for each index in the hash table
LinkedList *createLinkedList(char *user)
{
    LinkedList *list = malloc(sizeof(LinkedList));

    if(list)
    {
        list->key = strdup(user);
        list->friend = NULL;
        list->next = NULL;
        list->prev = NULL;

        return list;
    }

    return NULL;
}

// creates a node to be entered into a friend list
Node *createNode(char *user)
{
    Node *n = malloc(sizeof(Node));

    if(n)
    {
        n->name = strdup(user);
        n->next = NULL;
        n->prev = NULL;

        return n;
    }

    return NULL;
}

void freeTable(hashTable *hTable, int size)
{
    for(int i = 0; i < size; i++)
    {
        if(hTable->entries[i] != NULL)
        {
            freeLinkedList(hTable->entries[i]);
        }
    }
    free(hTable);
}

void freeLinkedList(LinkedList *list)
{
    Node *node;
    Node *tempNode;
    LinkedList *tempList;

    while(list != NULL)
    {
        node = list->friend;
        while(node != NULL)
        {
            tempNode = node->next;
            freeNode(node);
            node = tempNode;
        }

        tempList = list->next;
        list->next = NULL;
        list->prev = NULL;
        free(list->key);
        free(list);
        list = tempList;
    }
}

void freeNode(Node *node)
{
    node->next = NULL;
    node->prev = NULL;
    free(node->name);
    free(node);
}