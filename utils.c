#include "utils.h"

void replace_char(char* str, char find, char replace) {
    char* current_pos = strchr(str, find);
    while (current_pos) {
        *current_pos = replace;
        current_pos = strchr(current_pos, find);
    }
    return;
}


Error copy_str_set_end_zero(char* content, int str_len, char* allocated_str) {
	strncpy(allocated_str, content, str_len);
	*(allocated_str + str_len) = 0;
	return ERROR_SUCCESS;
}