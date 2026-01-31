/***********************************************************************
 *  File Name   : validate.c
 *  Description : Implements all validation-related operations for the
 *                Inverted Search System. This includes:
 *                  - Validating input file arguments
 *                  - Checking file extensions and sizes
 *                  - Detecting duplicate filenames
 *                  - Building the file list structure
 *
 *                Functions:
 *                  - read_and_validate_input_arguments()
 *                  - validate_file_extension()
 *                  - validate_file_size()
 *                  - validate_duplicate_file()
 *                  - insert_at_last()
 *
 *  Author      : Omkar Ashok Sawant
 *  Batch ID    : 25021C_309
 *  Date        : 07/12/2025
 ***********************************************************************/

#include "inverted_search.h"

/***********************************************************************
 * Function     : read_and_validate_input_arguments
 * Description  : Validates each input file provided via command-line.
 *                Checks:
 *                  - Valid .txt extension
 *                  - File accessibility
 *                  - Non-empty file size
 *                  - Duplicate file names
 *                Valid files are added to File_list.
 *
 * Arguments    : argc  - Count of command-line arguments
 *                argv  - Argument vector
 *                file  - Pointer to file list head
 *
 * Returns      : SUCCESS if at least one valid file is found,
 *                otherwise FAILURE.
 ***********************************************************************/
Status read_and_validate_input_arguments(int argc, char *argv[], File_list **file)
{
    printf("=====================================================\n");
    printf("               Validating Input Files              \n");
    printf("=====================================================\n\n");

    int count = 0;

    for (int i = 1; i < argc; i++)
    {
        /* 1. Validate extension */
        if (validate_file_extension(argv[i]) == FAILURE)
        {
            fprintf(stderr, "Error: '%s' has invalid extension. Only .txt allowed.\n", argv[i]);
            continue;
        }

        /* 2. Validate file accessibility */
        FILE *fptr = fopen(argv[i], "r");
        if (!fptr)
        {
            fprintf(stderr, "Error: File '%s' not found or cannot be opened.\n", argv[i]);
            continue;
        }

        /* 3. Validate non-empty size */
        if (validate_file_size(fptr) == 0)
        {
            fprintf(stderr, "Error: File '%s' is empty.\n", argv[i]);
            fclose(fptr);
            continue;
        }
        fclose(fptr);

        /* 4. Check for duplicate file names */
        if (validate_duplicate_file(argv[i], file) == DUPLICATE)
        {
            fprintf(stderr, "Error: Duplicate file '%s' ignored.\n", argv[i]);
            continue;
        }

        /* 5. Insert file into linked list */
        if (insert_at_last(file, argv[i]) == FAILURE)
        {
            fprintf(stderr, "Error: Failed to insert '%s' into file list.\n", argv[i]);
            continue;
        }

        printf("Info : File '%s' added successfully.\n", argv[i]);
        count++;
    }

    printf("\n-----------------------------------------------------\n");
    printf("  Total Valid Files : %d\n", count);
    printf("=====================================================\n");
    print_file_list(file);

    return (count > 0 ? SUCCESS : FAILURE);
}

/***********************************************************************
 * Function     : validate_file_extension
 * Description  : Checks if the file name ends with ".txt".
 *
 * Arguments    : argv - File name
 *
 * Returns      : SUCCESS if valid, FAILURE otherwise.
 ***********************************************************************/
Status validate_file_extension(char *argv)
{
    char *dot = strrchr(argv, '.');
    if (!dot)
        return FAILURE;

    return (strcmp(dot, ".txt") == 0) ? SUCCESS : FAILURE;
}

/***********************************************************************
 * Function     : validate_file_size
 * Description  : Returns the size of a file in bytes. Used to detect empty files.
 *
 * Arguments    : fptr - File pointer
 *
 * Returns      : Size of file in bytes, or 0 if empty.
 ***********************************************************************/
long validate_file_size(FILE *fptr)
{
    fseek(fptr, 0, SEEK_END);
    long size = ftell(fptr);

    if (size < 1)
        return 0;

    fseek(fptr, 0, SEEK_SET);
    return size;
}

/***********************************************************************
 * Function     : validate_duplicate_file
 * Description  : Checks whether the filename is already present in list.
 *
 * Arguments    : argv - File name string
 *                file - Pointer to file list head
 *
 * Returns      : DUPLICATE if found, SUCCESS otherwise.
 ***********************************************************************/
Status validate_duplicate_file(char *argv, File_list **file)
{
    File_list *temp = *file;

    while (temp)
    {
        if (strcmp(temp->file_name, argv) == 0)
            return DUPLICATE;

        temp = temp->next;
    }

    return SUCCESS;
}

/***********************************************************************
 * Function     : insert_at_last
 * Description  : Inserts a file name at the end of the File_list.
 *
 * Arguments    : head - Pointer to list head
 *                argv - File name
 *
 * Returns      : SUCCESS on success, FAILURE if memory allocation fails.
 ***********************************************************************/
Status insert_at_last(File_list **head, char *argv)
{
    File_list *newnode = malloc(sizeof(File_list));
    if (!newnode)
        return FAILURE;

    strcpy(newnode->file_name, argv);
    newnode->next = NULL;

    if (*head == NULL)
    {
        *head = newnode;
        return SUCCESS;
    }

    File_list *temp = *head;
    while (temp->next)
    {
        temp = temp->next;
    }

    temp->next = newnode;
    return SUCCESS;
}
