#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>      // add this line — needed for rmdir()
#include "../include/directory.h"

void createFolder()
{
    char foldername[100];
    printf("Enter folder name to create: ");
    scanf("%s", foldername);

    if (mkdir(foldername, 0755) == 0)
        printf("Folder '%s' created.\n", foldername);
    else
        printf("Error creating folder.\n");
}

void removeFolder()
{
    char foldername[100];
    printf("Enter folder name to remove: ");
    scanf("%s", foldername);

    if (rmdir(foldername) == 0)
        printf("Folder '%s' removed.\n", foldername);
    else
        printf("Error removing folder (must be empty).\n");
}

void listFiles()
{
    struct dirent *entry;
    DIR *dp = opendir(".");

    if (dp == NULL)
    {
        printf("Error opening directory.\n");
        return;
    }

    printf("\n----- Files in Current Directory -----\n");
    while ((entry = readdir(dp)) != NULL)
        printf("%s\n", entry->d_name);

    closedir(dp);
}

void directoryMenu()
{
    int choice;

    printf("\n----- Directory Management -----\n");
    printf("1. Create Folder\n");
    printf("2. Remove Folder\n");
    printf("3. List Files\n");
    printf("4. Back\n");
    printf("Enter Choice: ");
    scanf("%d", &choice);

  switch (choice)
    {
        case 1: createFolder(); break;
        case 2: removeFolder(); break;
        case 3: listFiles(); break;
        case 4: return;
        default: printf("Invalid choice.\n");
    }
}
