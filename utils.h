#define _CRT_SECURE_NO_WARNINGS

#pragma once
#include <string.h>

#include "errors.h"


void replace_char(char* str, char find, char replace);

/*mallocs and copies malloc_len chars from the content and returnes it via allocated_str*/
Error copy_str_set_end_zero(char* content, int malloc_len, char* allocated_str);
