#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALLOCATIONS 100

/* Structure to store allocation information */
typedef struct
{
    void *address;
    size_t size;
    char variable[50];
    int is_freed;
} Allocation;

/* Allocation tracking table */
Allocation allocations[MAX_ALLOCATIONS];

int allocation_count = 0;


/* =========================================
   ALLOCATION TRACKER
   ========================================= */

void track_allocation(void *address, size_t size, const char *variable)
{
    if (allocation_count >= MAX_ALLOCATIONS)
    {
        printf("Allocation tracking limit reached!\n");
        return;
    }

    allocations[allocation_count].address = address;
    allocations[allocation_count].size = size;

    strcpy(allocations[allocation_count].variable, variable);

    allocations[allocation_count].is_freed = 0;

    allocation_count++;

    printf("[ALLOCATED] %s -> %zu bytes\n",
           variable, size);
}


/* =========================================
   DEALLOCATION TRACKER
   ========================================= */

void track_deallocation(void *address)
{
    for (int i = 0; i < allocation_count; i++)
    {
        if (allocations[i].address == address)
        {
            allocations[i].is_freed = 1;

            printf("[FREED] %s -> %zu bytes\n",
                   allocations[i].variable,
                   allocations[i].size);

            return;
        }
    }

    printf("[WARNING] Address not found!\n");
}


/* =========================================
   MEMORY MONITOR
   ========================================= */

void memory_monitor()
{
    size_t total_memory = 0;
    size_t freed_memory = 0;
    size_t used_memory = 0;

    for (int i = 0; i < allocation_count; i++)
    {
        total_memory += allocations[i].size;

        if (allocations[i].is_freed)
        {
            freed_memory += allocations[i].size;
        }
    }

    used_memory = total_memory - freed_memory;

    printf("\n====================================\n");
    printf("          MEMORY MONITOR\n");
    printf("====================================\n");

    printf("Total Allocated : %zu bytes\n", total_memory);
    printf("Freed Memory    : %zu bytes\n", freed_memory);
    printf("Currently Used  : %zu bytes\n", used_memory);
}


/* =========================================
   LEAK DETECTION
   ========================================= */

void detect_leaks()
{
    int leak_count = 0;
    size_t total_leaked_memory = 0;

    printf("\n====================================\n");
    printf("        MEMORY LEAK REPORT\n");
    printf("====================================\n");

    for (int i = 0; i < allocation_count; i++)
    {
        if (allocations[i].is_freed == 0)
        {
            leak_count++;

            total_leaked_memory += allocations[i].size;

            printf("\n[LEAK DETECTED]\n");
            printf("Variable : %s\n",
                   allocations[i].variable);

            printf("Address  : %p\n",
                   allocations[i].address);

            printf("Size     : %zu bytes\n",
                   allocations[i].size);
        }
    }

    printf("\n------------------------------------\n");

    printf("Total Allocations : %d\n",
           allocation_count);

    printf("Leak Count        : %d\n",
           leak_count);

    printf("Leaked Memory     : %zu bytes\n",
           total_leaked_memory);

    printf("------------------------------------\n");

    if (leak_count == 0)
    {
        printf("No memory leaks detected!\n");
    }
    else
    {
        printf("WARNING: Memory leaks detected!\n");
    }
}


/* =========================================
   ANALYSIS MODULE
   ========================================= */

void analyze_memory()
{
    int freed_count = 0;
    int leaked_count = 0;

    for (int i = 0; i < allocation_count; i++)
    {
        if (allocations[i].is_freed)
        {
            freed_count++;
        }
        else
        {
            leaked_count++;
        }
    }

    printf("\n====================================\n");
    printf("        MEMORY ANALYSIS\n");
    printf("====================================\n");

    printf("Total Allocations : %d\n",
           allocation_count);

    printf("Freed Blocks      : %d\n",
           freed_count);

    printf("Unreleased Blocks : %d\n",
           leaked_count);

    if (leaked_count > 0)
    {
        printf("Status            : POTENTIAL LEAKS\n");
    }
    else
    {
        printf("Status            : NO LEAKS\n");
    }
}


/* =========================================
   MAIN TEST PROGRAM
   ========================================= */

int main()
{
    printf("====================================\n");
    printf("       MEMORY LEAK DETECTOR\n");
    printf("====================================\n");

    printf("\nStarting memory monitoring...\n");


    /* =================================
       MEMORY ALLOCATION
       ================================= */

    int *a = malloc(5 * sizeof(int));

    if (a == NULL)
    {
        printf("Memory allocation failed for a!\n");
        return 1;
    }

    track_allocation(
        a,
        5 * sizeof(int),
        "a"
    );


    int *b = malloc(10 * sizeof(int));

    if (b == NULL)
    {
        printf("Memory allocation failed for b!\n");

        free(a);

        return 1;
    }

    track_allocation(
        b,
        10 * sizeof(int),
        "b"
    );


    int *c = malloc(20 * sizeof(int));

    if (c == NULL)
    {
        printf("Memory allocation failed for c!\n");

        free(a);
        free(b);

        return 1;
    }

    track_allocation(
        c,
        20 * sizeof(int),
        "c"
    );


    /* =================================
       DEALLOCATION
       ================================= */

    free(a);

    track_deallocation(a);


    /*
     * b and c are intentionally not
     * deallocated here.
     *
     * Therefore they will be detected
     * as memory leaks.
     */


    /* =================================
       MEMORY MONITOR
       ================================= */

    memory_monitor();


    /* =================================
       MEMORY ANALYSIS
       ================================= */

    analyze_memory();


    /* =================================
       LEAK DETECTION & REPORT
       ================================= */

    detect_leaks();


    /* =================================
       CLEANUP
       ================================= */

    /*
     * Freeing the remaining memory after
     * the detector has generated the report.
     */

    free(b);
    free(c);

    printf("\nProgram completed.\n");

    return 0;
}
