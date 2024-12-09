#include "wiJSON.h"
#include "wiAssert.h"
#include <stdio.h>

/* Forward declarations */
void dump_array(const wiArrayEl* value, FILE* file);

void dump_JSON_to_string(const wiValue* root, char* string) {

}

void dump_JSON_to_file(const wiValue* root, const char* file_name) {
	FILE* file = fopen(file_name, "w");
	wiAssert(file != NULL, "Failed to open file to dump JSON to");
	fclose(file);
}

void dump_JSON_to_file_append(const wiValue* root, const char* file_name) {
	FILE* file = fopen(file_name, "a");
	wiAssert(file != NULL, "Failed to open file to dump JSON to");
	fclose(file);
}


void dump_int(const long value, FILE* file) {
	wiAssert(
		fprintf(file, "%ld", value) >= 0,
		"Failed to write integer value to file."
	);
}

void dump_double(const double value, FILE* file) {
	wiAssert(
		fprintf(file, "%f", value) >= 0,
		"Failed to write float value to file."
	);
}

void dump_string(const char* value, FILE* file) {
	wiAssert(
		fprintf(file, "%s", value) >= 0,
		"Failed to write string value to file."
	);
}

void dump_bool(const bool value, FILE* file) {
	wiAssert(
		fprintf(
			file,
			"%s",
			value ? "true" : "false"
		) >= 0,
		"Failed to write bool value to file."
	);
}

void dump_null(FILE* file) {
	wiAssert(
		fprintf(file, "null") >= 0,
		"Failed to write string value to file."
	);
}

void dump_wiValue(const wiValue* value, FILE* file) {
	switch (value->_type) {
		case WIARRAY:
			dump_array(value->contents.arrayVal, file);
			break;
		case WIBOOL:
			dump_bool(value->contents.boolVal, file);
			break;
		case WIFLOAT:
			dump_double(value->contents.floatVal, file);
			break;
		case WIINT:
			dump_int(value->contents.intVal, file);
			break;
		case WINULL:
			dump_null(file);
			break;
		case WIPAIR:
		case WISTRING:
			dump_string(value->contents.stringVal, file);
			break;
	}
}

void dump_array(const wiArrayEl* value, FILE* file) {
	if (value->elementVal == NULL) {
		return;
	}
	fprintf(file, "[");
	const wiArrayEl* current_value = value;
	while (current_value != NULL) {
		dump_wiValue(current_value->elementVal, file);
		current_value = current_value->nextElement;
		if (current_value != NULL) {
			fprintf(file, ",");
		}
	}
	fprintf(file, "]");
}
