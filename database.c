/***********************************************************************
 *  File Name   : database.c
 *  Description : Contains all major database operations for the
 *                Inverted Search System:
 *                  - Creating the inverted index
 *                  - Displaying the database
 *                  - Searching for words
 *                  - Saving the database to a backup file
 *                  - Loading database from a backup
 *
 *                Functions:
 *                  - create_database()
 *                  - display_database()
 *                  - search_database()
 *                  - save_database()
 *                  - update_database()
 *
 *  Author      : Omkar Ashok Sawant
 *  Batch ID    : 25021C_309
 *  Date        : 07/12/2025
 ***********************************************************************/

#include "inverted_search.h"

Status create_database(Hash_t *hash_array, File_list *head)
{
    while (head != NULL) // Loop through each file in the file list
    {
        FILE *fptr = fopen(head->file_name, "r"); // Open file for reading
        if (fptr == NULL)                         // Check file open failure
        {
            fprintf(stderr, "Error : Failed to open '%s' file\n", head->file_name);
            head = head->next;
            continue;
        }
        char buffer[WORD_SIZE];
        while (fscanf(fptr, "%s", buffer) != EOF) // Read each word from the file
        {
            int index;

            find_index(&index, buffer); // Find hash index for current word

            if (hash_array[index].m_link == NULL) // No main node exists at this index
            {
                Main_node *main_new_node = create_main_node(buffer);       // Create new main node
                Sub_node *sub_new_node = create_sub_node(head->file_name); // Create sub node for file

                main_new_node->s_link = sub_new_node;     // Connect sub node
                main_new_node->file_count = 1;            // First file occurrence
                hash_array[index].m_link = main_new_node; // Insert into hash table
            }
            else
            {
                int flag = 0; // Flag to check if word exists
                Main_node *temp1 = hash_array[index].m_link;
                Main_node *backup_main = NULL;
                Main_node *prev_main = NULL;

                while (temp1) // Traverse all main nodes at this index
                {
                    if (strcmp(buffer, temp1->word) == 0) // Word found
                    {
                        flag = 1;
                        backup_main = temp1;
                        break;
                    }
                    prev_main = temp1;
                    temp1 = temp1->m_link;
                }

                if (flag) // Word already exists in database
                {
                    int flag1 = 0; // Subnode file match flag
                    Sub_node *temp2 = backup_main->s_link;
                    Sub_node *backup_sub = NULL;
                    Sub_node *prev_sub = NULL;

                    while (temp2) // Traverse subnode list to find same file
                    {
                        if (strcmp(temp2->file_name, head->file_name) == 0)
                        {
                            flag1 = 1;
                            backup_sub = temp2;
                            break;
                        }
                        prev_sub = temp2;
                        temp2 = temp2->s_link;
                    }
                    if (flag1) // File exists -> increment count
                    {
                        backup_sub->word_count++;
                    }
                    else // File does not exist -> create new subnode
                    {
                        Sub_node *new = create_sub_node(head->file_name);
                        backup_main->file_count++; // Increase file count

                        if (prev_sub == NULL) // Insert at beginning
                        {
                            backup_main->s_link = new;
                        }
                        else // Insert at end
                        {
                            prev_sub->s_link = new;
                        }
                    }
                }
                else // Word does not exist -> create new main node
                {
                    Main_node *main_new = create_main_node(buffer);
                    Sub_node *sub_new = create_sub_node(head->file_name);

                    main_new->s_link = sub_new;
                    main_new->file_count = 1;

                    if (prev_main == NULL) // Insert at head
                    {
                        // Insert at head
                        hash_array[index].m_link = main_new;
                    }
                    else // Insert at end
                    {
                        // Insert at end
                        prev_main->m_link = main_new;
                    }
                }
            }
        }
        fclose(fptr);      // Close file after reading all words
        head = head->next; // Move to next file
    }
    return SUCCESS;
}

void display_database(Hash_t *hash_array)
{
    printf("\n======================================================================================\n");
    printf("                                DISPLAY DATABASE                                        \n");
    printf("======================================================================================\n\n");

    printf("+--------+----------------------+------------+---------------------------+-----------+\n");
    printf("| %-6s | %-20s | %-10s | %-25s | %-9s |\n",
           "Index", "Word", "FileCount", "FileName", "WordCount");
    printf("+--------+----------------------+------------+---------------------------+-----------+\n");

    for (int i = 0; i < HASH_SIZE; i++) // Loop through all hash indexes
    {
        Main_node *main_temp = hash_array[i].m_link;

        while (main_temp) // Traverse all main nodes
        {
            Sub_node *sub_temp = main_temp->s_link;

            if (!sub_temp) // Skip words with no subnodes
            {
                main_temp = main_temp->m_link;
                continue;
            }

            /* First row for each word */
            printf("| %-6d | %-20s | %-10d | %-25s | %-9d |\n", i, main_temp->word, main_temp->file_count, sub_temp->file_name, sub_temp->word_count);

            sub_temp = sub_temp->s_link;

            /* Additional rows */
            while (sub_temp) // Print remaining file occurrences
            {
                printf("| %-6s | %-20s | %-10s | %-25s | %-9d |\n", " ", " ", " ", sub_temp->file_name, sub_temp->word_count);

                sub_temp = sub_temp->s_link;
            }

            printf("+--------+----------------------+------------+---------------------------+-----------+\n");

            main_temp = main_temp->m_link; // Move to next word
        }
    }
}

Status search_database(Hash_t *hash_arr, char *data)
{
    int index;
    find_index(&index, data); // Compute index for word

    Main_node *main_temp = hash_arr[index].m_link;

    printf("\n=====================================================\n");
    printf("                  SEARCH RESULTS        \n");
    printf("=====================================================\n\n");

    printf("Searching for: \"%s\"\n\n", data);

    while (main_temp) // Traverse main nodes
    {
        if (strcmp(main_temp->word, data) == 0) // Word found
        {
            Sub_node *sub_temp = main_temp->s_link;

            /* Table header */
            printf("+---------------------------+-----------+\n");
            printf("| %-25s | %-9s |\n", "FileName", "WordCount");
            printf("+---------------------------+-----------+\n");

            /* Print all file occurrences */
            while (sub_temp)
            {
                printf("| %-25s | %-9d |\n", sub_temp->file_name, sub_temp->word_count);

                sub_temp = sub_temp->s_link;
            }

            /* Bottom border */
            printf("+---------------------------+-----------+\n");

            printf("\nWord '%s' found in %d file(s).\n", data, main_temp->file_count);

            printf("=====================================================\n");
            return SUCCESS;
        }

        main_temp = main_temp->m_link; // Move to next main node
    }

    /* Not found case */
    printf("No entries found for word '%s'.\n\n", data);
    printf("=====================================================\n");

    return SUCCESS;
}

Status save_database(Hash_t *hash_array, char *file_name)
{
    if (validate_file_extension(file_name) == FAILURE) // Validate extension
    {
        fprintf(stderr, "Error: '%s' has invalid extension. It must be .txt\n", file_name);
        return FAILURE;
    }

    FILE *fptr = fopen(file_name, "w+"); // Open file for writing
    for (int i = 0; i < HASH_SIZE; i++)  // Loop through all indexes
    {
        Main_node *main_temp = hash_array[i].m_link;
        while (main_temp) // Traverse all main nodes
        {
            Sub_node *sub_temp = main_temp->s_link;

            fprintf(fptr, "#%d;%s;%d;", i, main_temp->word, main_temp->file_count);

            while (sub_temp) // Write all subnodes
            {
                fprintf(fptr, "%s;%d;", sub_temp->file_name, sub_temp->word_count);
                sub_temp = sub_temp->s_link;
            }

            fprintf(fptr, "#\n");
            main_temp = main_temp->m_link;
        }
    }

    fclose(fptr); // Close backup file
    printf("INFO: Database saved successfully in file '%s'\n\n", file_name);

    return SUCCESS;
}

Status update_database(Hash_t *hash_array, char *backup, File_list **head)
{
    // Validate file
    if (validate_file_extension(backup) == FAILURE) // Check for .txt extension
    {
        fprintf(stderr, "Error: '%s' has invalid extension. It must be .txt\n", backup);
        return FAILURE;
    }

    // Open & verify database format
    FILE *fptr = fopen(backup, "r");
    if (fptr == NULL) // Unable to open file
    {
        fprintf(stderr, "Error: Unable to open '%s' file\n", backup);
        return FAILURE;
    }

    if (validate_file_size(fptr) == 0) // Check empty file
    {
        fprintf(stderr, " ERROR: %s file is empty\n", backup);
        return FAILURE;
    }

    if (validate_backup_database(fptr) == FAILURE) // Check database format
    {
        fprintf(stderr, " ERROR: %s file is not a DATABASE file\n", backup);
        return FAILURE;
    }
    int index, file_count;
    char word[WORD_SIZE];

    while (fscanf(fptr, "#%d;%[^;];%d;", &index, word, &file_count) == 3) // Read each record
    {
        Main_node *curr_main = hash_array[index].m_link;
        Main_node *prev_main = NULL;

        while (curr_main) // Traverse to last main node
        {
            prev_main = curr_main;
            curr_main = curr_main->m_link;
        }

        Main_node *newNode = create_main_node(word); // Create new main node
        newNode->file_count = file_count;

        if (prev_main)
            prev_main->m_link = newNode; // Insert after existing nodes
        else
            hash_array[index].m_link = newNode; // Insert as first node

        Sub_node *temp_sub = newNode->s_link;

        int word_count;
        char file_name[WORD_SIZE];

        for (int i = 0; i < file_count; i++) // Read subnode data
        {
            fscanf(fptr, "%[^;];%d;", file_name, &word_count);
            Sub_node *newSubNode = create_sub_node(file_name);
            newSubNode->word_count = word_count;

            if (delete_duplicate_file(head, file_name) == SUCCESS) // Remove duplicate file entries
            {
                printf("INFO: Deleting File %s in FileList (already present in the database file %s)\n", file_name, backup);
                // print_file_list(head);
            }

            if (temp_sub == NULL) // First subnode
            {
                newNode->s_link = newSubNode;
            }
            else // Append subnode
            {
                temp_sub->s_link = newSubNode;
            }
            temp_sub = newSubNode;
        }
        fscanf(fptr, "#\n"); // Skip closing '#'
    }
    fclose(fptr);

    // insert_at_last(head,backup);
    return SUCCESS;
}
