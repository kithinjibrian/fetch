#ifndef HTTP_H
#define HTTP_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "master.h"
#include "../encrypt/encrypt.h"
	char *makeHttpPostRequest(
		const char *host,
		int port,
		const char *endpoint,
		const char *postData);

#ifdef __cplusplus
}
#endif

#endif
