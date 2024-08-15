#include <assert.h>
#include <string.h>

#include "../include/wiJSON.h"
#include "../../WiEnrich/include/enrich.h"

int main() {
	char startMsg[] = "[UNDER]Testing simple array...[/]";
	wiEnrich(startMsg);
	printf("\n%s\n", startMsg);
	const char arrayString[] = "[ 1, -32.4, \"Hello, World!\", true, false, -32e4, null]";
	wiValue* testArray = parseJSONString(arrayString);
	printf(" > Object = '%s'\n", arrayString);

	assert(testArray->_type == WIARRAY);
	assert(testArray->contents.arrayVal != NULL);
	assert(testArray->contents.arrayVal->elementVal != NULL);

	wiArrayEl* currentElement = testArray->contents.arrayVal;

	assert(currentElement != NULL);
	assert(currentElement->elementVal->_type == WIINT);
	assert(currentElement->elementVal->contents.intVal == 1);

	currentElement = currentElement->nextElement;

	assert(currentElement != NULL);
	assert(currentElement->elementVal->_type == WIFLOAT);
	assert(currentElement->elementVal->contents.floatVal == -32.4);

	currentElement = currentElement->nextElement;

	assert(currentElement != NULL);
	assert(currentElement->elementVal->_type == WISTRING);
	assert(strcmp(currentElement->elementVal->contents.stringVal, "Hello, World!") == 0);

	currentElement = currentElement->nextElement;

	assert(currentElement != NULL);
	assert(currentElement->elementVal->_type == WIBOOL);
	assert(currentElement->elementVal->contents.boolVal == true);

	currentElement = currentElement->nextElement;

	assert(currentElement != NULL);
	assert(currentElement->elementVal->_type == WIBOOL);
	assert(currentElement->elementVal->contents.boolVal == false);

	currentElement = currentElement->nextElement;

	assert(currentElement != NULL);
	assert(currentElement->elementVal->_type == WIFLOAT);
	assert(currentElement->elementVal->contents.floatVal == -32e4);

	currentElement = currentElement->nextElement;

	assert(currentElement != NULL);
	assert(currentElement->elementVal->_type == WINULL);

	freeEverything(testArray);

	char message[] = "Simple array tests [BRIGHT-GREEN]succeeded[/].\n\n";
	wiEnrich(message);
	printf("%s", message);
}


