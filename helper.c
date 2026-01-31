/***********************************************************************
 *  File Name   : helpers.c
 *  Description : Contains helper functions for the Inverted Search System,
 *                including:
 *                  - Hash table initialization
 *                  - Word-to-index mapping
 *                  - Main node creation
 *                  - Sub node creation
 *                  - Backup file format validation
 *                  - Duplicate file removal
 *                  - File list printing
 *
 *                Functions:
 *                  - initialise_hash()
 *                  - find_index()
 *                  - create_main_node()
 *                  - create_sub_node()
 *                  - validate_backup_database()
 *                  - delete_duplicate_file()
 *                  - print_file_list()
 *
 *  Author      : Omkar Ashok Sawant
 *  Batch ID    : 25021C_309
 *  Date        : 07/12/2025
 ***********************************************************************/

#include "inverted_search.h"

Status initialise_hash(Hash_t *hash)
{
    for (int i = 0; i < HASH_SIZE; i++) // Initialize each hash index
    {
        hash[i].index = i;     // Store index value
        hash[i].m_link = NULL; // Set main node link to NULL
    }
    return SUCCESS;
}

void find_index(int *index, char *buffer)
{
    if (isupper(buffer[0])) // Uppercase A–Z
    {
        *index = buffer[0] - 'A';
    }
    else if (islower(buffer[0])) // Lowercase a–z
    {
        *index = buffer[0] - 'a';
    }
    else // Digits / special characters
    {
        *index = 26;
    }
}

Main_node *create_main_node(char *word)
{
    Main_node *newnode = (Main_node *)malloc(sizeof(Main_node)); // Allocate main node

    if (newnode == NULL) // Check malloc failure
        return NULL;

    strcpy(newnode->word, word); // Store the word
    newnode->file_count = 1;     // Initialize file count
    newnode->m_link = NULL;      // Next main node = NULL
    newnode->s_link = NULL;      // First subnode = NULL

    return newnode;
}

Sub_node *create_sub_node(char *filename)
{
    Sub_node *newnode = (Sub_node *)malloc(sizeof(Sub_node)); // Allocate subnode

    if (newnode == NULL) // Check malloc failure
        return NULL;

    strcpy(newnode->file_name, filename); // Store filename
    newnode->word_count = 1;              // First occurrence
    newnode->s_link = NULL;               // Next subnode = NULL

    return newnode;
}

Status validate_backup_database(FILE *fptr)
{
    char ch;
    ch = fgetc(fptr); // Read first character
    if (ch != '#')    // Backup must start with '#'
        return FAILURE;

    fseek(fptr, -2, SEEK_END); // Move to second last char
    ch = fgetc(fptr);          // Read character ('#')
    if (ch != '#')             // Backup must end with '#'
        return FAILURE;

    rewind(fptr); // Reset file pointer
    return SUCCESS;
}

Status delete_duplicate_file(File_list **head, char *file_name)
{
    File_list *curr = *head; // Start of file list
    File_list *prev = NULL;

    while (curr) // Traverse file list
    {
        if (strcmp(file_name, curr->file_name) == 0) // Match found
        {
            if (prev == NULL) // Node is at head
            {
                File_list *temp = *head;
                *head = temp->next; // Move head
                free(temp);         // Free removed node
            }
            else // Node is in middle/end
            {
                prev->next = curr->next;
                free(curr); // Free node
            }
            return SUCCESS;
        }
        prev = curr;       // Move prev forward
        curr = curr->next; // Move curr forward
    }
    return FAILURE; // No duplicate found
}

void print_file_list(File_list **file_list)
{
    printf("\n>> FileList: ");
    File_list *temp = *file_list; // Pointer to traverse list
    while (temp)
    {
        printf("-> %s ", temp->file_name); // Print each filename
        temp = temp->next;                 // Move to next
    }
    printf("\n");
}
int delete_list(File_list **head)
{
    File_list *temp = *head; // Temporary pointer to traverse the list

    if (*head == NULL) // If the list is empty
    {
        return FAILURE; // Return failure (nothing to delete)
    }
    else
    {
        while (temp != NULL) // Traverse the entire list
        {
            temp = temp->next; // Move temp to next node
            free(*head);       // Free the current head node
            *head = temp;      // Update head to the next node
        }
    }

    return SUCCESS; // Return success after deleting all nodes
}
