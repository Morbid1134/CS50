// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26 * 27;

// Hash table
node *table[N];

int linked_list_len(node *ptr);
bool linked_list_unload(node *ptr);
bool in_linked_list(const char *word, node *ptr);

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // hash word to get position in table
    int hash_index = hash(word);

    // check if word is in linked list
    return in_linked_list(word, table[hash_index]);
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // give index AA - ZZ (base 26)
    // 26(0) + 1(0)  - 26(25) + 1(25)
    // 26(x) + 1(y)
    // if string is 1 characters
    if (strlen(word) == 1)
    {
        // return only first letter hash
        int x = toupper(word[0]) - 'A';
        return x;
    }
    else
    {
        // get hash of both and convert it like base 26
        // also add 26 so AA is 26 since single Z is 25
        int x = toupper(word[0]) - 'A';
        int y = toupper(word[1]) - 'A';

        return (26 * x) + y + 26;
    }
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }
    // initialize current word
    char *current_word = malloc(sizeof(char) * (LENGTH + 2));
    // if error, return false
    if (current_word == NULL)
    {
        return false;
    }
    // set every address to hash table to be NULL
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    // loop over every line (er, word) in dictionary
    while (fgets(current_word, (LENGTH + 2), dict) != NULL)
    {
        // replace \n with \0 to clean the word and get it back to LENGTH + 1
        current_word[strcspn(current_word, "\n")] = '\0';

        // hash our word with the hash function
        // save returned index corresponding to location in table our word is to be saved
        int hash_index = hash(current_word);

        // then prepend the word to linked list at that arrays pointer location
        // create a node containing current word
        node *current_node = malloc(sizeof(node));
        // if error, return false
        if (current_node == NULL)
        {
            return false;
        }
        // copy word in current node
        strcpy(current_node->word, current_word);

        // if hash index of table is NULL then this is first item in link list
        if (table[hash_index] == NULL)
        {
            // have table point to current node
            table[hash_index] = current_node;
            // have current node point to NULL
            current_node->next = NULL;
        }
        else
        {
            // set current node point to that the table is pointing to at the current hash_index
            current_node->next = table[hash_index];

            // set table at hash_index to point to current node
            table[hash_index] = current_node;
        }
    }
    free(current_word);
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    unsigned int total_words = 0;
    // for every pointer in hash table
    for (int i = 0; i < N; i++)
    {
        // if pointer != NULL
        if (table[i] != NULL)
        {
            // get the length of the linked list
            int length = linked_list_len(table[i]);

            // add length to total number of words
            total_words += length;
        }
    }
    return total_words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // for every pointer in hash table
    for (int i = 0; i < N; i++)
    {
        // if pointer != NULL
        if (table[i] != NULL)
        {
            // get the length of the linked list
            bool success = linked_list_unload(table[i]);
            // return false if failed
            if (!success)
            {
                return false;
            }
        }
    }
    // if no early exits then it must have been successful for every pointer
    return true;
}

int linked_list_len(node *ptr)
{
    if (ptr == NULL)
    {
        return 0;
    }
    else
    {
        int length = linked_list_len(ptr->next);
        return length + 1;
    }
}

bool linked_list_unload(node *ptr)
{
    // if pointer is not pointing to anything
    if (ptr == NULL)
    {
        // return true because the memory allocate at nothing is technically free
        // we just don't need to free it
        return true;
    }
    // otherwise, free linked list we are pointing too
    bool success = linked_list_unload(ptr->next);
    // if we weren't successful, return false
    if (!success)
    {
        return false;
    }
    // otherwise, free ptr node and return true
    free(ptr);
    return true;
}

bool in_linked_list(const char *word, node *ptr)
{
    // if ptr is pointing to a non-existent node, word isn't there
    if (ptr == NULL)
    {
        return false;
    }
    // if word is the word in node we are pointing at then it is there
    if (strcasecmp(word, ptr->word) == 0)
    {
        return true;
    }
    // otherwise, if word is in linked list we are pointing at, word is there
    else if (in_linked_list(word, ptr->next))
    {
        return true;
    }
    // if word is not in linked list pointing at or the word in node we are point at, no word
    else
    {
        return false;
    }
}
