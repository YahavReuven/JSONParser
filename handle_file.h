#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "errors.h"

/* saves a file in memory and alow access to its content via paramater s. */
Error handle_file(char** s, char* file_path);

/* calculates the file (fp) size and sets the argument len to that size. */
Error get_file_size(FILE* fp, int* len);

/* allocates the file content in memory. can be accesible via s. */
Error save_file_to_mem(FILE* fp, int len, char** s);

