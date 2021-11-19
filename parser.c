#include "parser.h"


// from the beginning of the json file
Error handle_json(char* json_content, Value* mapped_json) {
	Error res = ERROR_SUCCESS;

	while (is_ignore(json_content)) {
		json_content++;
	}
	res = handle_value(&json_content, mapped_json);
	if (res != ERROR_SUCCESS) {
		return res;
	}
	return res;
}

// from the beginning of the value
Error handle_value(char** json_content, Value* mapped_json) {
	Error res = ERROR_SUCCESS;

	if (is_object(*json_content)) {
		mapped_json->type = OBJECT;
		res = handle_json_object(json_content, &(mapped_json->u_value.object));
		if (res != ERROR_SUCCESS) {
			return res;
		}
		(*json_content)++;
	}
	else if (is_array(*json_content)) {
		mapped_json->type = ARRAY;
		res = handle_json_array(json_content, &(mapped_json->u_value.array));
		if (res != ERROR_SUCCESS) {
			return res;
		}
		(*json_content)++;
	}
	else if (is_string(*json_content)) {
		res = handle_string(json_content, mapped_json);
	}
	else if (is_number(*json_content)) {
		res = handle_num(json_content, mapped_json);
	}
	return res;
}


// from the opening {
Error handle_json_object(char** json_content, JsonPair** mapped_json) {
	Error res = ERROR_SUCCESS;
	JsonPair* pair = NULL;
	JsonPair* prev = NULL;

	while (**json_content != JSON_OBJECT_ENDING) {
		pair = (JsonPair*)malloc(sizeof(JsonPair));
		if (!pair) {
			printf("malloc failed.\n");
			return ERROR_MEM;
		}

		if (!prev) {
			*mapped_json = pair; //point to the first pair in the object----------------   
		}
		else {
			prev->next = pair;
		}
		
		res = handle_json_object_pair(json_content, pair);
		if (res != ERROR_SUCCESS) {
			return res;
		}
		while (is_ignore(*json_content)) {
			(*json_content)++;
		}
		if (**json_content != JSON_OBJECT_PAIRS_SEPERATION 
			&& **json_content != JSON_OBJECT_ENDING) {
			return ERROR_JSON;
		}
		prev = pair;
	}

	return ERROR_SUCCESS;
}

// from the beginning of the object ({) or the seperation (,)
Error handle_json_object_pair(char** json_content, JsonPair* mapped_json) {
	Error res = ERROR_SUCCESS;
	Value* key = NULL;
	Value* val = NULL;

	//----------------------HNADLE KEY----------------------------------

	key = (Value*)malloc(sizeof(Value));
	if (!key) {
		printf("malloc failed.\n");
		return ERROR_MEM;
	}

	(*json_content)++; // to pass the opening { or the ,

	while (is_ignore(*json_content)) {
		(*json_content)++;
	}

	if (!is_string(*json_content)) {
		return ERROR_JSON;
	}
	res = handle_string(json_content, key);
	if (res != ERROR_SUCCESS) {
		return res;
	}

	//----------------------HNADLE VAL----------------------------------

	val = (Value*)malloc(sizeof(Value));
	if (!val) {
		printf("malloc failed.\n");
		return ERROR_MEM;
	}

	while (is_ignore(*json_content) || **json_content == JSON_OBJECT_KEY_VALUE_SEPERATION) {
		(*json_content)++;
	}

	res = handle_value(json_content, val);
	if (res != ERROR_SUCCESS) {
		return res;
	}

	mapped_json->key = key;
	mapped_json->value = val;
	mapped_json->next = NULL;

	return ERROR_SUCCESS;
}


// from the opening [
Error handle_json_array(char** json_content, JsonItem** mapped_json) {
	Error res = ERROR_SUCCESS;
	JsonItem* item = NULL;
	JsonItem* prev = NULL;

	while (**json_content != JSON_ARRAY_ENDING) {
		item = (JsonItem*)malloc(sizeof(JsonItem));
		if (!item) {
			printf("malloc failed.\n");
			return ERROR_MEM;
		}

		if (!prev) {
			*mapped_json = item; //point to the first pair in the object----------------   
		}
		else {
			prev->next = item;
		}

		res = handle_json_array_item(json_content, item);
		while (is_ignore(*json_content)) {
			(*json_content)++;
		}
		if (**json_content != JSON_ARRAY_ITEMS_SEPERATION
			&& **json_content != JSON_ARRAY_ENDING) {
			return ERROR_JSON;
		}


		////pair->next = NULL;
		prev = item;
		//pair = pair->next;
	}

	return ERROR_SUCCESS;
}


Error handle_json_array_item(char** json_content, JsonItem* mapped_json) {
	Error res = ERROR_SUCCESS;
	Value* val = NULL;

	(*json_content)++; // to pass the opening [ or the ,

	val = (Value*)malloc(sizeof(Value));
	if (!val) {
		printf("malloc failed.\n");
		return ERROR_MEM;
	}

	while (is_ignore(*json_content)) {
		(*json_content)++;
	}

	res = handle_value(json_content, val);
	if (res != ERROR_SUCCESS) {
		return res;
	}

	mapped_json->value = val;
	mapped_json->next = NULL;

	return ERROR_SUCCESS;
}


// TODO: check support for \"
// including first "
Error handle_string(char** p_json_content, Value* mapped_json) {
	int str_len = 0;
	char* string = NULL;
	Error res = ERROR_SUCCESS;

	(*p_json_content)++; // to pass the opening "
	while (*(*p_json_content + str_len) != JSON_STRING_ENDING) {
		str_len++;
	}

	string = (char*)malloc(str_len * sizeof(char) + 1);
	if (!string) {
		printf("malloc failed.\n");
		return ERROR_MEM;
	}
	res = copy_str_set_end_zero(*p_json_content, str_len, string);
	if (res != ERROR_SUCCESS) {
		return res;
	}

	mapped_json->type = STR;
	mapped_json->u_value.str = string;

	//printf("type: %d", mapped_json->type);
	//printf("value: %s", mapped_json->u_value.str);

	*p_json_content += str_len + 1; // to pass the closing "

	return ERROR_SUCCESS;
}


// from the first number
Error handle_num(char** p_json_content, Value* mapped_json) {
	char* string_num = NULL;
	int val = 0;
	int str_len = 0;
	Error res = ERROR_SUCCESS;

	while (isdigit(*(*p_json_content + str_len))) {
		str_len++;
	}

	if (*(*p_json_content + str_len) ==	DECIMAL_POINT) {
		//check
		res = handle_float(p_json_content, mapped_json, str_len);
		if (res != ERROR_SUCCESS) {
			return res;
		}
	}
	else {
		res = handle_integer(p_json_content, mapped_json, str_len);
		if (res != ERROR_SUCCESS) {
			return res;
		}
	}

	return ERROR_SUCCESS;
}


Error handle_integer(char** p_json_content, Value* mapped_json, int integer_len) {
	char* string_integer = NULL;
	int val = 0;
	Error res = ERROR_SUCCESS;

	// check +1
	string_integer = (char*)malloc(integer_len * sizeof(char) + 1);
	if (!string_integer) {
		printf("malloc failed.\n");
		return ERROR_MEM;
	}

	res = copy_str_set_end_zero(*p_json_content, integer_len, string_integer);
	if (res != ERROR_SUCCESS) {
		return res;
	}

	val = atoi(string_integer);

	free(string_integer);

	mapped_json->type = INT;
	mapped_json->u_value.integer = val;

	*p_json_content += integer_len;

	return ERROR_SUCCESS;


}


Error handle_float(char** p_json_content, Value* mapped_json, int len_before_d_point) {
	int str_len = 0;
	char* string_float = NULL;
	double val = 0;
	Error res = ERROR_SUCCESS;

	str_len = len_before_d_point;
	str_len++; //for the decimal point

	while (isdigit(*(*p_json_content + str_len))) {
		str_len++;
	}

	string_float = (char*)malloc(str_len * sizeof(char) + 1);
	if (!string_float) {
		printf("malloc failed.\n");
		return ERROR_MEM;
	}
	res = copy_str_set_end_zero(*p_json_content, str_len, string_float);
	if (res != ERROR_SUCCESS) {
		return res;
	}

	val = atof(string_float);

	free(string_float);

	mapped_json->type = FLOAT;
	mapped_json->u_value.float_val = val;

	*p_json_content += str_len;

	return ERROR_SUCCESS;
}



















//int handle_object(char* s) {
//
//	while (is_ignore(s)) {
//		s++;
//	}
//
//
//
//}
//
//
//int handle_pair(char* s) {
//	if (!is_string(s)) {
//		// TODO: add logic
//		printf("dict key is not string!");
//	}
//
//	Value key;
//	s++;
//	handle_string(s, &key);
//}
//
//int handle_key(char* s) {
//
//}
//
//
//int handle_value(char *s){}


//int handle_string(char** s, Value* result) {
//	int str_size = 0;
//	char* pos = *s;
//
//	while (**s != '"') {
//		str_size++;
//		*s++;
//	}
//
//	ValueType value_type = STR;
//	 result->type = value_type;
//	strncpy(result->u_value.str, pos, str_size);
//}
