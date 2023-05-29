/**
 * Driver.c
 *
 * Schedule is in the format
 *
 *  [name] [priority] [CPU burst]
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#include "task.h"
#include "list.h"
#include "schedule_rr.h"

#define SIZE    100

static int id = 1;

double time1, timedif;

char* strsep(char** stringp, const char* delim) {
    if (*stringp == NULL) {
        return NULL;
    }

    char* token = *stringp;
    char* delimiter = strstr(token, delim);

    if (delimiter == NULL) {
        *stringp = NULL;
    }
    else {
        *delimiter = '\0';
        *stringp = delimiter + strlen(delim);
    }

    return token;
}


int main(int argc, char* argv[])
{

    srand(time(NULL));

    time1 = (double)clock();
    time1 = time1 / CLOCKS_PER_SEC;

    FILE* in;
    char* temp;
    char task[SIZE];

    in = fopen("rr-schedule.txt", "r");

    //inicializo o nó da lista encadeada aqui e depois passo sempre ele pela função add e schedule.

    struct node* head = NULL;

    while (fgets(task, SIZE, in) != NULL) {
        temp = _strdup(task);

        struct task* task = (struct task*)malloc(sizeof(struct task));
        task->name = strsep(&temp, ", ");
        task->tid = id++;
        task->priority = atoi(strsep(&temp, ", "));
        task->burst = atoi(strsep(&temp, ", "));

        addTask(&head, task);
        free(temp);
    }

    fclose(in);
    // invoke the scheduler
    // Utilizando timeSlice fixo de 2
    schedule(head, 10);

    timedif = (((double)clock()) / CLOCKS_PER_SEC) - time1;
    printf("Tempo Total = %f", timedif);

    return 0;
}
