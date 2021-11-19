#define _CRT_SECURE_NO_WARNINGS

#include "handle_file.h"


Error handle_file(char** s, char* file_path) {
	FILE* fp = NULL;
	int file_len = 0;
	int res = 0;

	fp = fopen(file_path, "rb");
	if (!fp) {
		printf("couldn't open file %s\n", file_path);
		return ERROR_FILE;
	}

	res = get_file_size(fp, &file_len);
	if (res != ERROR_SUCCESS) {
		return res;
	}

	res = save_file_to_mem(fp, file_len, s);
	if (res != ERROR_SUCCESS) {
		return res;
	}

	printf("%s", *s);

	res = fclose(fp);
	if (res) {
		printf("couldn't close file.\n");
		return ERROR_FILE;
	}

	return ERROR_SUCCESS;
}


Error get_file_size(FILE* fp, int* len) {
	int res = 0;
	long size = 0;
	long offset = 0;

	//offset = ftell(fp);
	//if (size == -1L) {
	//	printf("couldn't get the file's offset.\n");
	//	return ERROR_FILE;
	//}
	res = fseek(fp, offset, SEEK_END);
	if (res) {
		printf("couldn't seek the end of given file.\n");
		return ERROR_FILE;
	}
	size = ftell(fp);
	if (size == -1L) {
		printf("couldn't get the file's size.\n");
		return ERROR_FILE;
	}
	res = fseek(fp, 0L, SEEK_SET);
	if (res) {
		printf("couldn't return to the beginning of the file.\n");
		return ERROR_FILE;
	}
	*len = size / sizeof(char) + 1;
	return ERROR_SUCCESS;
}


Error save_file_to_mem(FILE* fp, int file_len, char** s) {
	int res = 0;

	*s = (char*)malloc(file_len * sizeof(char));
	if (!*s) {
		printf("malloc failed.\n");
		return ERROR_MEM;
	}

	// TODO: error checking.
	fread(*s, sizeof(char), file_len, fp);
	*(*s + file_len - 1) = 0;

	return ERROR_SUCCESS;
}