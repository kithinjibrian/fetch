#ifndef ENCRYPT_H
#define ENCRYPT_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "master.h"
#include "../strings/strings.h"
#include "../base64/base64.h"

	char *fXOR(char *data, char key);
	char *fheXOR(char *hex, char *key);
	int fhash(const char *s, const int n);
	char *boxEncrypt(KeyStore keystore, Dict *dict);

#ifdef __cplusplus
}
#endif

#endif