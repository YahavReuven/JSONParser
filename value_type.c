#include "value_type.h"

int is_object(char* s) {
	if (*s == '{') {
		return 1;
	}
	return 0;
}

int is_array(char* s) {
	if (*s == '[') {
		return 1;
	}
	return 0;
}


int is_string(char* s) {
	if (*s == '"') {
		return 1;
	}
	return 0;
}


int is_boolean(char* s) {
	if (*s == "true" || *s == "false") {
		return 1;
	}
	return 0;
}


int is_null(char* s) {
	if (*s == "null") {
		return 1;
	}
	return 0;
}


int is_number(char* s) {
	if (isdigit(*s)) {
		return 1;
	}
	return 0;
}


int is_ignore(char* s) {
	if (*s == ' ' || *s == '\t' || *s == '\n' || *s == '\r') {
		return 1;
	}
	return 0;
}