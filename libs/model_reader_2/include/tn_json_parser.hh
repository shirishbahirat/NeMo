#ifndef MODEL_READER_2_LIBRARY_H
#define MODEL_READER_2_LIBRARY_H

#ifdef BUILDJSON
#include "lib/json.h"
#include "lib/forwards.h"
#else
#include <json/forwards.h>
#include <json/json.h>
#endif

void hello();

#endif