/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "dictionary.h"

#define APOSTROPHE 39
#define SIZE 26

typedef struct node
{
    bool realword;
    struct node *nextchar[27];
}
Node;

int wordcount;
Node *root;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    Node *current = root;
    int x = *word;
    while (isupper(x) || islower(x) || x == APOSTROPHE)
    {
        if(isupper(x))
        {
            x = tolower(x);
        }
        if (x == APOSTROPHE)
        {
            x = SIZE; //Apostrophe set to last element in array
        }
        else
            x -= 97; //Set alphabet with and a = 0
        
        if(current->nextchar[x] != NULL)
        {
            current = current->nextchar[x];
        }
        else
        {
            return false;
        }
        x = *++word;
    }
    if (x == EOF || x == '\n' || x == 0)
    {
        if (current->realword == true)
        {
            return true;
        }
    }
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    FILE *fp = fopen(dictionary, "r");
    wordcount = 0;
    root = calloc(1, sizeof(Node));
    Node *current = root;
    if (fp == NULL)
    {
        return false;
    }
    
    int x;
    x = fgetc(fp);
    while (x != EOF)
    {
        if (x == '\n')
        {
            wordcount++;
            current->realword = true;
            current = root;
        }
        else
        {
            if(isupper(x))
            {
                x = tolower(x);
            }
            if (x == APOSTROPHE)
            {
                x = SIZE; //Apostrophes are set to last element in array
            }
            else
                x -= 97;
            
            if (current->nextchar[x] != NULL)
            {
                current = current->nextchar[x];
            }
            else
            {
                current->nextchar[x] = calloc(1, sizeof(Node));
                current = current->nextchar[x];
            }
        }
        x = fgetc(fp);
    }
    fclose(fp);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    if (wordcount > 0)
        return wordcount;
    else
        return 0;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    Node *current = root;
    Node **lastnode;
    int count = 0;
    while (count <= SIZE)
    {
        if (current->nextchar[count] != NULL)
        {
            lastnode = &(current->nextchar[count]);
            current = current->nextchar[count];
            count = 0;
        }
        else if (count == 26 && current != root)
        {
            *lastnode = NULL;
            free(current);
            current = root;
            count = 0;
        }
        else
            count++;
    }
    free(current);
    return true;
}