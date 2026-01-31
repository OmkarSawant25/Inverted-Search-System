/***********************************************************************
 *  File Name   : inverted_search.h
 *  Description : Header file for all operations used in the Inverted
 *                Search System. Contains structure definitions and
 *                function prototypes for file validation, database
 *                creation, display, searching, saving, and updating.
 *
 *  Author      : Omkar Ashok Sawant
 *  Batch ID    : 25021C_309
 *  Date        : 07/12/2025
 ***********************************************************************/

#ifndef INVERTED_SEARCH_H
#define INVERTED_SEARCH_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

/* Size limits */
#define FILE_SIZE 50
#define WORD_SIZE 50
#define HASH_SIZE 27 // a–z + special symbol bucket

/* ------------------ File List Node ------------------ */
typedef struct node
{
    char file_name[FILE_SIZE];
    struct node *next;
} File_list;

/* ------------------ Sub Node (File Occurrences) ------------------ */
typedef struct sub
{
    int word_count;
    char file_name[FILE_SIZE];
    struct sub *s_link;
} Sub_node;

/* ------------------ Main Node (Unique Word Entry) ------------------ */
typedef struct main
{
    int file_count;
    char word[WORD_SIZE];
    Sub_node *s_link;
    struct main *m_link;
} Main_node;

/* ------------------ Hash Table Bucket ------------------ */
typedef struct hash
{
    int index;
    Main_node *m_link;
} Hash_t;

/* Operation status codes */
typedef enum
{
    FAILURE = 0,
    SUCCESS,
    DUPLICATE,
    EXIT
} Status;

/* ------------------ File Validation ------------------ */
Status read_and_validate_input_arguments(int argc, char *argv[], File_list **file);
Status validate_file_extension(char *argv);
long validate_file_size(FILE *fptr);
Status validate_duplicate_file(char *argv, File_list **file);
Status insert_at_last(File_list **head, char *argv);

/* ------------------ Initialization ------------------ */
Status initialise_hash(Hash_t *hash);
Status validate_backup_database(FILE *fptr);

/* ------------------ Database Operations ------------------ */
Status create_database(Hash_t *hash_array, File_list *head);
void display_database(Hash_t *hash_array);
Status search_database(Hash_t *hash_arr, char *data);
Status save_database(Hash_t *hash_array, char *file_name);
Status update_database(Hash_t *hash_array, char *backup, File_list **head);

/* ------------------ Utility Functions ------------------ */
void print_file_list(File_list **fileList);
Status delete_duplicate_file(File_list **head, char *file_name);
void find_index(int *index, char *buffer);
Main_node *create_main_node(char *word);
Sub_node *create_sub_node(char *filename);
int delete_list(File_list **head);

#endif
