#include <stdlib.h>

#include "value_type.h"
#include "handle_file.h"
#include "parser.h"
#include "errors.h"

#define MAX_FILE_PATH 200



int main() {
	char* file_content = NULL;
	char file_path[MAX_FILE_PATH] = { 0 };


	printf("please enter the file path: ");
	fgets(file_path, MAX_FILE_PATH, stdin);
	if (!file_path) {
		printf("couldn't get input.\n");
		return ERROR_FILE;
	}
	replace_char(file_path, '\n', '\0');


	int res = handle_file(&file_content, file_path);
	if (res != ERROR_SUCCESS) {
		return res;
	}

	Value json = { 0 };
	handle_json(file_content, &json);

	return ERROR_SUCCESS;


}