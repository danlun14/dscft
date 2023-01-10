#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "parser.h"

#define SUBSTR_TIME_LIMIT "TimeLimit="
#define SUBSTR_NODE_CNT "NodeCnt="

int deserialize_log_file(FILE *input_file, schedules_t * output_schedules, int count_records)
{
    char buffer[1024];
    int task_count = 0;
    while (fgets(buffer, sizeof(buffer), input_file))
    {   
        char *ptr_substr = NULL;
        int time_limit = 0;
        int node_cnt = 0;

        ptr_substr = strstr(buffer, SUBSTR_TIME_LIMIT);
        if (!ptr_substr)
        {
            continue;
        }
        ptr_substr += strlen(SUBSTR_TIME_LIMIT);
        time_limit = atoi(ptr_substr);
        if (time_limit <= 0 || time_limit > 4096)
        {
            continue;
        }

        ptr_substr = strstr(buffer, SUBSTR_NODE_CNT);
        if (!ptr_substr)
        {
            continue;
        }
        ptr_substr += strlen(SUBSTR_NODE_CNT);
        node_cnt = atoi(ptr_substr);
        if (node_cnt <= 0 || node_cnt > 1152)
        {
            continue;
        }

        output_schedules->schedules[task_count].task.time_limit = time_limit;
        output_schedules->schedules[task_count].task.node_count = node_cnt;
        output_schedules->schedules[task_count].task.id = task_count;
        task_count++;

        if (task_count == count_records)
        {
            break;
        }
    }
    
    output_schedules->task_count = task_count;
    
    return 0;
}