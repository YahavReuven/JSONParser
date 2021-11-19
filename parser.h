#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "value_type.h"
#include "errors.h"
#include "utils.h"

#define JSON_STRING_ENDING '"'
#define DECIMAL_POINT '.'
#define JSON_OBJECT_KEY_VALUE_SEPERATION ':'
#define	JSON_OBJECT_ENDING '}'
#define JSON_OBJECT_PAIRS_SEPERATION ','
#define JSON_ARRAY_ENDING ']'
#define JSON_ARRAY_ITEMS_SEPERATION ','



typedef struct _JsonItem JsonItem;
typedef struct _JsonPair JsonPair;
typedef struct _Value Value;

/*
{
	"fruit": "Apple",
	"size": 12,
	"color": 145.76,
	"dict" : {"a": 123,
		"b": "bbb"},
	"list" : ["a", 321, 17.5]
}
*/

typedef enum {
	INT,
	FLOAT,
	BOOL,
	STR,
	ARRAY,
	OBJECT
} ValueType;


typedef struct _JsonItem {
	Value* value;
	JsonItem* next;
} JsonItem;

// TODO: not sure if to put key as Value or string 
typedef struct _JsonPair {
	Value* key;
	Value* value;
	JsonPair* next;
} JsonPair;


typedef struct _Value {
	ValueType type;
	union
	{
		int integer;
		double float_val;
		int bool;
		char* str;
		JsonItem* array;
		JsonPair* object;
	} u_value;
} Value;



/// <summary>
/// Deserialize a json object.
/// </summary>
/// <param name="json_content">A pointer to the content of the json as data.</param>
/// <param name="mapped_json">A value struct in which the results will be stored. </param>
/// <returns></returns>
Error handle_json(char* json_content, Value* mapped_json);

/// <summary>
/// 
/// </summary>
/// <param name="json_content"></param>
/// <param name="mapped_json"></param>
/// <returns></returns>
Error handle_value(char** json_content, Value* mapped_json);

Error handle_json_object(char** json_content, JsonPair** mapped_json);

Error handle_json_object_pair(char** json_content, JsonPair* mapped_json);

Error handle_json_array(char** json_content, JsonItem** mapped_json);

Error handle_json_array_item(char** json_content, JsonItem* mapped_json);

Error handle_string(char** p_json_content, Value* mapped_json);

Error handle_num(char** p_json_content, Value* mapped_json);

Error handle_integer(char** p_json_content, Value* mapped_json, int integer_len);

Error handle_float(char** p_json_content, Value* mapped_json, int len_before_d_point);



//Error handle_json_object(char* json_content, JsonPair** mapped_json);
//
//Error handle_string(char** p_json_content, Value* mapped_json);
//
//Error handle_num(char** p_json_content, Value* mapped_json);
//
//Error handle_float(char** p_json_content, Value* mapped_json, int len_before_d_point);

