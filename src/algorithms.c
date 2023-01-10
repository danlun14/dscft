#include <stdio.h>
#include <malloc.h>

#include "algorithms.h"
#include "defines.h"
#include "sortings.h"

/* Next Fit Decreasing High */
void NFDH_algorithm(schedules_t *sch)
{
    if (!sch || !sch->schedules || sch->task_count <= 0)
    {
        return;
    }
    int t_level = 0;
    int cnt_free = 0;
    sort_step_one(sch);
    sort_step_two(sch);
    for (int i = 0; i < sch->task_count; i++)
    {
        if (sch->schedules[i].task.node_count > cnt_free)
        {
            t_level = sch->time_max;
            sch->time_max += sch->schedules[i].task.time_limit;
            cnt_free = N;
        }
        int start_rang = N - cnt_free;
        cnt_free -= sch->schedules[i].task.node_count;
        int end_rang = N - cnt_free - 1;
        sch->schedules[i].start_time = t_level;
        sch->schedules[i].end_time = t_level + sch->schedules[i].task.time_limit;
        sprintf(sch->schedules[i].node_range, "%d-%d", start_rang, end_rang);
    }
}

/* First Fit Decreasing High */
void FFDH_algorithm(schedules_t *sch)
{
    if (!sch || !sch->schedules || sch->task_count <= 0)
    {
        return;
    }
    level_t *levels = malloc(sizeof(level_t));
    level_t *current_level;
    levels->time = 0;
    levels->cnt_free = N;
    levels->next = NULL;
    sort_step_one(sch);
    sort_step_two(sch);
    sch->time_max = sch->schedules[0].task.time_limit;
    for (int i = 0; i < sch->task_count; i++)
    {
        current_level = levels;
        while (sch->schedules[i].task.node_count > current_level->cnt_free)
        {
            if (current_level->next)
            {
                current_level = current_level->next;
            }
            else
            {
                current_level->next = malloc(sizeof(level_t));
                current_level = current_level->next;
                current_level->time = sch->time_max;
                current_level->cnt_free = N;
                current_level->next = NULL;
                sch->time_max += sch->schedules[i].task.time_limit;
            }
        }
        int start_rang = N - current_level->cnt_free;
        current_level->cnt_free -= sch->schedules[i].task.node_count;
        int end_rang = N - current_level->cnt_free - 1;
        sch->schedules[i].start_time = current_level->time;
        sch->schedules[i].end_time = current_level->time + sch->schedules[i].task.time_limit;
        sprintf(sch->schedules[i].node_range, "%d-%d", start_rang, end_rang);
    }
    while (levels)
    {
        current_level = levels;
        levels = levels->next;
        free(current_level);
    }
}