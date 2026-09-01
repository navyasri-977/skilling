#include <stdio.h>
#include "../include/file.h"

void createFile()
{
    char filename[100];
    printf("Enter filename to create: ");
    scanf("%s", filename);

    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
    {
        printf("Error creating file.\n");
        return;
    }
    fclose(fp);
    printf("File '%s' created successfully.\n", filename);
}

void deleteFile()
{
    char filename[100];
    printf("Enter filename to delete: ");
    scanf("%s", filename);

    if (remove(filename) == 0)
        printf("File '%s' deleted successfully.\n", filename);
    else
        printf("Error deleting file.\n");
}

void renameFile()
{
    char oldname[100], newname[100];
    printf("Enter current filename: ");
    scanf("%s", oldname);
    printf("Enter new filename: ");
    scanf("%s", newname);

    if (rename(oldname, newname) == 0)
        printf("File renamed to '%s'.\n", newname);
    else
        printf("Error renaming file.\n");
}

void fileMenu()
{
    int choice;

    printf("\n----- File Management -----\n");
    printf("1. Create File\n");
    printf("2. Delete File\n");
    printf("3. Rename File\n");
    printf("4. Back\n");
    printf("Enter Choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
        case 1: createFile(); break;
        case 2: deleteFile(); break;
        case 3: renameFile(); break;
        case 4: return;
        default: printf("Invalid choice.\n");
    }
}
