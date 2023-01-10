#include "sortings.h"

/* Сортируем по убыванию времени */
void sort_step_one(schedules_t *sch)
{
    if (!sch || !sch->schedules || sch->task_count <= 0)
    {
        return;
    }
    double factor = 1.247;
    int step = sch->task_count - 1;
    task_schedule_t temp;
    while (step >= 1)
    {
        for (int i = 0; i < sch->task_count - step; i++)
        {
            if (sch->schedules[i].task.time_limit < sch->schedules[i + step].task.time_limit)
            {
                temp = sch->schedules[i];
                sch->schedules[i] = sch->schedules[i + step];
                sch->schedules[i + step] = temp;
            }
        }
        step /= factor;
    }
}

/* Уже отсортированный набор досортируем по рангам, если одинаковое время у элементов*/
void sort_step_two(schedules_t *sch)
{
    if (!sch || !sch->schedules || sch->task_count <= 0)
    {
        return;
    }
    double factor = 1.247;
    int step = sch->task_count - 1;
    task_schedule_t temp;
    while (step >= 1)
    {
        for (int i = 0; i < sch->task_count - step; i++)
        {
            if (sch->schedules[i].task.time_limit == sch->schedules[i + step].task.time_limit &&
                sch->schedules[i].task.node_count < sch->schedules[i + step].task.node_count)
            {
                temp = sch->schedules[i];
                sch->schedules[i] = sch->schedules[i + step];
                sch->schedules[i + step] = temp;
            }
        }
        step /= factor;
    }
}