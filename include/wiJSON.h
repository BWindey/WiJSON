#ifndef WIJSON_HEADER_GUARD
#define WIJSON_HEADER_GUARD

#include <stdbool.h>	/* Required for the boolean value */
#include <stdio.h>

/* Forward declaration needed for cyclic uses */
typedef struct wiArrayEl wiArrayEl;
typedef struct wiValue 	 wiValue;
typedef struct wiPair 	 wiPair;

typedef union wiValueContents {
	long intVal;
	bool boolVal;
	char* stringVal;
	double floatVal;
	wiPair* pairVal;
	wiArrayEl* arrayVal;
} wiValueContents;

typedef enum wiType {
	WIARRAY, WIBOOL, WIFLOAT, WIINT, WINULL, WIPAIR, WISTRING
} wiType;

/* Represent value's from key-value-pairs */
typedef struct wiValue {
	wiType _type;
	wiValueContents contents;
} wiValue;

/* Represent arrays by elements pointing to eachother */
typedef struct wiArrayEl {
	wiValue* elementVal;
	wiArrayEl* nextElement;
} wiArrayEl;

/* Represent key-value pairs pointing to the next for iteration */
typedef struct wiPair {
	char* key;
	wiValue* value;
	wiPair* nextPair;
} wiPair;


wiValue* parseJSONString(const char*);
wiValue* parseJSONFile(FILE*);

void dump_JSON_to_string(const wiValue* root, char* string);
void dump_JSON_to_file(const wiValue* root, const char* file_name);
void dump_JSON_to_file_append(const wiValue* root, const char* file_name);

void freeEverything(wiValue* root);

#endif /* !WIJSON_HEADER_GUARD */
