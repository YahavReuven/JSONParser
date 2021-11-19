#pragma once

typedef enum Errors {
	ERROR_SUCCESS,  //the function executed without errors
	ERROR_FILE,  //a problem handling a file
	ERROR_MEM,  //a problem handling memory
	ERROR_JSON  //the json is not valid
} Error;
