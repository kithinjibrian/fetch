#ifndef FETCH_H
#define FETCH_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "master.h"
#include "keys/keys.h"
#include "http/http.h"
#include "json/djson.h"
#include "strings/strings.h"
#include "encrypt/encrypt.h"
#include "base64/base64.h"
#include "makers/makers.h"

	char *fetch(Data data, int pinned_public_key);

#ifdef __cplusplus
}
#endif

#endif