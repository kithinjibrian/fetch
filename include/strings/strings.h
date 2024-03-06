#ifndef STRINGS_H
#define STRINGS_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "master.h"

	char *stitch(Dict *dict);
	char *stitchEx(Dict *dict, char **delimeters);

#ifdef __cplusplus
}
#endif

#endif
