#ifndef MAKERS_H
#define MAKERS_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "master.h"
#include "../base64/base64.h"

	ServerKeys makeServerKeys(const char *public_key, const char *sign_public_key);
	Carrier makeCarrier(
		KeyStore keystore,
		ServerKeys server_keys,
		const char *nonce,
		const char *type,
		const char *signature,
		const char *body);

#ifdef __cplusplus
}
#endif

#endif
