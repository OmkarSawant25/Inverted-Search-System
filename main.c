/***********************************************************************
 *  File Name      : main.c
 *  Project Title  : Inverted Search System
 *  Author         : Omkar Ashok Sawant
 *  Batch ID       : 25021C_309
 *  Date           : 07/12/2025
 *  Language       : C Programming & Data Structures
 *
 *  --------------------------------------------------------------------
 *  Description
 *  --------------------------------------------------------------------
 *  This file serves as the entry point of the Inverted Search System.
 *  It handles:
 *      • Command-line argument validation
 *      • File list creation and preprocessing
 *      • Hash table initialization
 *      • Menu-driven interaction with the user
 *      • Execution of all major operations on the inverted index
 *
 *  The Inverted Search System builds an index of words from multiple
 *  text files. For every unique word, the system stores:
 *      - The word itself
 *      - The number of files in which it appears
 *      - A list of files along with occurrence counts
 *
 *  --------------------------------------------------------------------
 *  Features
 *  --------------------------------------------------------------------
 *  • Validate and register input text files
 *  • Build the inverted index (hash-based database)
 *  • Display the complete indexed data
 *  • Search for a particular word across files
 *  • Save the database to a backup file
 *  • Load an existing database from a backup
 *  • Organized and user-friendly menu system
 *
 *  --------------------------------------------------------------------
 *  Working Principle
 *  --------------------------------------------------------------------
 *  1. Input files are validated and added to a linked list.
 *  2. Hash table (size 27) is initialized for indexing words (a–z) & special characters.
 *  3. Each word extracted from the files is hashed and added to the table.
 *  4. Each main node stores the word and a sublist of file occurrences.
 *  5. User operations (display, search, save, update) are performed via menu.
 *
 *  --------------------------------------------------------------------
 *  Error Handling
 *  --------------------------------------------------------------------
 *  • Improper command-line arguments
 *  • Invalid or unreadable text files
 *  • Incorrect backup file format
 *  • Selecting menu options without creating/loading a database
 *  • Invalid numeric input in the menu
 *
 *  --------------------------------------------------------------------
 *  Menu Options
 *  --------------------------------------------------------------------
 *      1. Create Database
 *      2. Display Database
 *      3. Search Database
 *      4. Save Database (Backup)
 *      5. Update Database (Load Backup)
 *      6. Exit
 *
 *  --------------------------------------------------------------------
 *  Functions Included
 *  --------------------------------------------------------------------
 *  - main()
 *  - print_startup_banner()
 *  - print_menu()
 *  - read_and_validate_input_arguments()
 *  - initialise_hash()
 *  - create_database()
 *  - display_database()
 *  - search_database()
 *  - save_database()
 *  - update_database()
 *
 *  --------------------------------------------------------------------
 *  Future Enhancements
 *  --------------------------------------------------------------------
 *  • Dynamic hash table resizing based on input volume
 *  • Stop-word filtering for cleaner indexing
 *  • Export database in JSON/CSV format
 *  • Full-text search features (prefix/suffix matching)
 *  • GUI-based version for user-friendly access
 *
 ***********************************************************************/

#include "inverted_search.h"

void print_startup_banner()
{
    printf("\n");
    printf("-----------------------------------------------------\n");
    printf("          <<>> INVERTED SEARCH SYSTEM <<>>            \n");
    printf("-----------------------------------------------------\n\n");
}

/* ------------------ MAIN MENU ------------------ */
void print_menu()
{
    printf("\n");
    printf("┌────────────────────── MENU ───────────────────────┐\n");
    printf("│  1. Create Database                               │\n");
    printf("│  2. Display Database                              │\n");
    printf("│  3. Search Database                               │\n");
    printf("│  4. Save Database (Backup)                        │\n");
    printf("│  5. Update Database (Load Backup)                 │\n");
    printf("│  6. Exit                                          │\n");
    printf("└───────────────────────────────────────────────────┘\n");
    printf(">> Enter your choice : ");
}

int main(int argc, char *argv[])
{
    print_startup_banner();

    if (argc < 2)
    {
        fprintf(stderr, "[ERROR] Invalid Arguments! \nUsage: ./a.out <file1> <file2> ...\n\n");
        printf("-----------------------------------------------------\n\n");

        return FAILURE;
    }

    File_list *head = NULL;

    /* Validate input files */
    if (read_and_validate_input_arguments(argc, argv, &head) == FAILURE)
    {
        fprintf(stderr, "\n[ERROR] File validation failed.\n");
        return FAILURE;
    }

    Hash_t hash_array[HASH_SIZE];

    /* Initialise Hash Table */
    if (initialise_hash(hash_array) == FAILURE)
    {
        fprintf(stderr, "[ERROR] Hash Table initialization failed.\n");
        return FAILURE;
    }

    int choice;
    char backupfilename[WORD_SIZE];
    char search[WORD_SIZE];
    bool create_flag = false;
    bool update_flag = false;

    /* ===================== MAIN LOOP ===================== */
    while (1)
    {
        print_menu();

        if (scanf("%d", &choice) != 1)
        {
            fprintf(stderr, "\n[ERROR] Invalid Input! Enter a number between 1–6.\n");
            while (getchar() != '\n'); // clear buffer
            continue;
        }

        switch (choice)
        {
        /* -------- CREATE DATABASE -------- */
        case 1:
            if (create_flag)
            {
                fprintf(stderr, "\n[INFO] Database already created.\n");
            }
            else
            {
                printf("\n[PROCESS] Creating Database...\n");
                if (create_database(hash_array, head) == SUCCESS)
                {
                    printf("[SUCCESS] Database created.\n");
                    create_flag = true;
                }
                else
                {
                    printf("[ERROR] Failed to create database.\n");
                }
            }
            break;

        /* -------- DISPLAY DATABASE -------- */
        case 2:
            if (create_flag)
            {
                printf("\n[DISPLAY] Displaying Database...\n");
                display_database(hash_array);
            }
            else
            {
                fprintf(stderr, "\n[ERROR] Database not created yet.\n");
                fprintf(stderr, "[INFO] Choose option 1 to create or option 5 to load backup.\n");
            }
            break;

        /* -------- SEARCH DATABASE -------- */
        case 3:
            if (create_flag)
            {
                printf("\nEnter word to search: ");
                scanf("%49s", search);

                printf("\n[PROCESS] Searching for '%s'...\n", search);
                search_database(hash_array, search);
            }
            else
            {
                fprintf(stderr, "\n[ERROR] Cannot search. Database not created.\n");
                fprintf(stderr, "[INFO] Choose option 1 to create or option 5 to load backup.\n");
            }
            break;

        /* -------- SAVE DATABASE -------- */
        case 4:
            if (create_flag)
            {
                printf("\nEnter backup filename: ");
                scanf("%49s", backupfilename);

                printf("\n[PROCESS] Saving database to '%s'...\n", backupfilename);
                save_database(hash_array, backupfilename);
            }
            else
            {
                fprintf(stderr, "\n[ERROR] Cannot save. No database available.\n");
                fprintf(stderr, "[INFO] Create DB first or load backup.\n");
            }
            break;

        /* -------- UPDATE DATABASE -------- */
        case 5:
            if (create_flag)
            {
                fprintf(stderr, "\n[INFO] Cannot load backup while database is active.\n");
                fprintf(stderr, "[INFO] Restart the application to load backup.\n");
            }
            else if (!update_flag)
            {
                printf("\nEnter backup file to load: ");
                scanf("%49s", backupfilename);

                printf("\n[PROCESS] Loading backup from '%s'...\n\n", backupfilename);

                if (update_database(hash_array, backupfilename, &head) == SUCCESS)
                {
                    printf("\n[SUCCESS] Database loaded from backup.\n");
                    create_flag = true;
                    update_flag = true;
                }
                else
                {
                    printf("[ERROR] Backup loading failed.\n");
                }
            }
            else
            {
                printf("[ERROR] Database already loaded from backup.\n");
            }
            break;

        /* -------- EXIT -------- */
        case 6:
            delete_list(&head);
            printf("\n[EXIT] Program terminated.\n");
            return 0;

        /* -------- INVALID OPTION -------- */
        default:
            fprintf(stderr, "\n[ERROR] Invalid Option! Enter between 1-6.\n");
        }
    }
}

