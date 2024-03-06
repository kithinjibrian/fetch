#ifndef KEYS_H
#define KEYS_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "master.h"
#include "../base64/base64.h"

	KeyStore genKeyStore();
	void freeKeyStore(KeyStore *keystore);
	unsigned char *sign(KeyStore keystore);
	void genSharedKey(KeyStore *keystore, ServerKeys server_keys);

#ifdef __cplusplus
}
#endif

#endif