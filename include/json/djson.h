#ifndef DJSON_H
#define DJSON_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "master.h"
#include "json.h"
#include "../makers/makers.h"
#include "../encrypt/encrypt.h"

	ServerKeys deserializeServerKeys(const char *json_string);
	Carrier *deserializeNetworkCarrier(
		KeyStore *keystore,
		ServerKeys *server_keys,
		const char *json_string);

#ifdef __cplusplus
}
#endif

#endif
