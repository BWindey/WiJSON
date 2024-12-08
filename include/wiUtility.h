#ifndef WIUTILITY_HEADER_GUARD
#define WIUTILITY_HEADER_GUARD

#include <stdbool.h>

#include "wiJSON.h"

int getIntVal(wiPair*);
bool getBoolVal(wiPair*);
char* getStringVal(wiPair*);
double getFloatVal(wiPair*);
wiPair* getPairVal(wiPair*);
wiArrayEl* getArrayVal(wiPair*);

bool isNull(wiPair*);

wiPair* get(wiPair*, const char*);

#endif /* !WIUTILITY_HEADER_GUARD */
