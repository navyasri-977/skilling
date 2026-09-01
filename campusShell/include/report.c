#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "../include/report.h"

void generateReport()
{
    FILE *fp = fopen("reports/report.txt", "w");
    char cwd[1024];
    time_t now;

    if (fp == NULL)
    {
        printf("Error creating report.\n");
        return;
    }

    time(&now);
    getcwd(cwd, sizeof(cwd));

    fprintf(fp, "===== CampusShell Report =====\n");
    fprintf(fp, "Date       : %s", ctime(&now));
    fprintf(fp, "User       : %s\n", getlogin());
    fprintf(fp, "Directory  : %s\n", cwd);
    fprintf(fp, "PID        : %d\n", getpid());

    fclose(fp);
    printf("Report generated at reports/report.txt\n");
}
