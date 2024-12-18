#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "wiJSON.h"
#include "wiTest.h"

const char* enumToString(wiType type) {
	switch (type) {
        case WIARRAY: return "WIARRAY";
        case WIBOOL: return "WIBOOL";
        case WIFLOAT: return "WIFLOAT";
        case WIINT: return "WIINT";
        case WINULL: return "WINULL";
        case WIPAIR: return "WIPAIR";
        case WISTRING: return "WISTRING";
		default: return "WI_UNKNOWN";
    }
}

void testSimpleArray(void) {
	// Path because so the executables link correctly
	FILE* jsonFile = fopen("core/file/files/testArray.json", "r");
	assert(jsonFile != NULL);
	wiValue* testArray = parseJSONFile(jsonFile);
	fclose(jsonFile);

	wiTestEnum(WIARRAY, testArray->_type, enumToString);
	assert(testArray->contents.arrayVal != NULL);
	assert(testArray->contents.arrayVal->elementVal != NULL);

	wiArrayEl* currentElement = testArray->contents.arrayVal;

	assert(currentElement != NULL);
	wiTestEnum(WIINT, currentElement->elementVal->_type, enumToString);
	wiTestInt(1, currentElement->elementVal->contents.intVal);

	currentElement = currentElement->nextElement;

	assert(currentElement != NULL);
	wiTestEnum(WIFLOAT, currentElement->elementVal->_type, enumToString);
	wiTestFloat(-32.4, currentElement->elementVal->contents.floatVal);

	currentElement = currentElement->nextElement;

	assert(currentElement != NULL);
	wiTestEnum(WISTRING, currentElement->elementVal->_type, enumToString);
	wiTestString("Hello, World!", currentElement->elementVal->contents.stringVal);

	currentElement = currentElement->nextElement;

	assert(currentElement != NULL);
	wiTestEnum(WIBOOL, currentElement->elementVal->_type, enumToString);
	wiTestBool(true, currentElement->elementVal->contents.boolVal);

	currentElement = currentElement->nextElement;

	assert(currentElement != NULL);
	wiTestEnum(WIBOOL, currentElement->elementVal->_type, enumToString);
	wiTestBool(false, currentElement->elementVal->contents.boolVal);

	currentElement = currentElement->nextElement;

	assert(currentElement != NULL);
	wiTestEnum(WIFLOAT, currentElement->elementVal->_type, enumToString);
	wiTestFloat(-32e4, currentElement->elementVal->contents.floatVal);

	currentElement = currentElement->nextElement;

	assert(currentElement != NULL);
	assert(currentElement->elementVal->_type == WINULL);

	freeEverything(testArray);
}

int main(void) {
	printf("Testing simple array...\n");

	testSimpleArray();

	wiPrintResult("simple array");
}

