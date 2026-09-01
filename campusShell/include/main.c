#include <stdio.h>
#include "../include/login.h"
#include "../include/file.h"
#include "../include/directory.h"
#include "../include/process.h"
#include "../include/report.h"

int main()
{
    int choice;

    printf("=====================================\n");
    printf(" Welcome to CampusShell\n");
    printf(" Smart University Lab Management\n");
    printf("=====================================\n");

    while (1)
    {
        printf("\n===== CampusShell Main Menu =====\n");
        printf("1. Login Information\n");
        printf("2. File Management\n");
        printf("3. Directory Management\n");
        printf("4. Execute Linux Command\n");
        printf("5. Process Management\n");
        printf("6. Generate Report\n");
        printf("7. Exit\n");
        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1: showLoginInfo(); break;
            case 2: fileMenu(); break;
            case 3: directoryMenu(); break;
            case 4: executeCommand(); break;
            case 5: processMenu(); break;
            case 6: generateReport(); break;
            case 7:
                printf("Exiting CampusShell. Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice, try again.\n");
        }
    }

    return 0;
}
