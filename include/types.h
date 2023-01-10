#pragma once

#include <inttypes.h>

/* Задача */
typedef struct
{
    uint32_t id;         // номер задачи
    uint32_t time_limit; // время на задачу
    uint32_t node_count; // число необходимых узлов
} task_t;

/* Расписание одной задачи */
typedef struct
{
    task_t task;
    uint32_t start_time;
    uint32_t end_time;
    char node_range[64];
} task_schedule_t;

/* Обертка под массив задач */
typedef struct
{
    task_schedule_t *schedules;
    uint32_t task_count;
    uint32_t time_max;
} schedules_t;

/* Вспомогательная структура для алгоритма FFDH */
typedef struct level_t
{
    uint32_t time;
    uint32_t cnt_free;
    struct level_t *next;
} level_t;