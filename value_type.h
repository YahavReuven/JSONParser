#pragma once
#include <ctype.h>


int is_object(char* s);

int is_array(char* s);

int is_string(char* s);

int is_boolean(char* s);

int is_null(char* s);

int is_number(char* s);

int is_ignore(char* s);