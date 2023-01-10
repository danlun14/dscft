
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "algorithms.h"
#include "defines.h"
#include "parser.h"
#include "types.h"
#include "wtime.h"

int main(int argc, char *argv[])
{
    FILE *file1 = fopen(argv[1], "w");
    int i = -1;
    if (strcmp(argv[2], "FFDH") == 0)
    {
        i = 0;
    }
    else if (strcmp(argv[2], "NFDH") == 0)
    {
        i = 1;
    }
    fprintf(file1, "%10s\t%10s\t%10s\t%10s\t%10s\n", "cnt_tasks", "t_packing", "t_low_bnd", "eps", "alg_time");
    int num_tasks = atoi(argv[3]);
    double alg_time;
    schedules_t sch = {.schedules = NULL, .task_count = 0, .time_max = 0};
    sch.task_count = num_tasks;
    sch.schedules = malloc(sizeof(task_schedule_t) * num_tasks);
    memset(sch.schedules, 0, sizeof(task_schedule_t) * num_tasks);
    double t_low_bound = 0; // сколько времени бы потребовалось, если бы был идеальный случай
                            // (площадь всех прямоугольников делим на число узлов)
    double eps;
    srand(num_tasks);
    for (int j = 0; j < num_tasks; j++)
    {
        sch.schedules[j].task.time_limit = rand() % MAX_TIME + 1;
        sch.schedules[j].task.node_count = rand() % MAX_NODES + 1;
        sch.schedules[j].task.id = j + 1;
    }
    alg_time = wtime();
    switch (i)
    {
    case 0:
        NFDH_algorithm(&sch);
        break;
    case 1:
        FFDH_algorithm(&sch);
        break;
    }
    alg_time = wtime() - alg_time;
    for (int j = 0; j < num_tasks; j++)
    {
        t_low_bound += sch.schedules[j].task.node_count * sch.schedules[j].task.time_limit;
    }
    t_low_bound /= N;
    eps = (sch.time_max - t_low_bound) / t_low_bound;

    fprintf(file1, "%10d\t", num_tasks);
    fprintf(file1, "%10d\t", sch.time_max);
    fprintf(file1, "%10.0lf\t", t_low_bound);
    fprintf(file1, "%10lf\t", eps);
    fprintf(file1, "%10lf\n", alg_time);

    free(sch.schedules);

    fclose(file1);
    return 0;
}