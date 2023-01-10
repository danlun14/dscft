#pragma once

#include <stdio.h>

#include "types.h"

int deserialize_log_file(FILE *input_file, schedules_t * output_schedules, int count_records);