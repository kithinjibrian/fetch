#ifndef MASTER_H
#define MASTER_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <sodium.h>
#include <stdio.h>
#include <loader.h>
#include <tchar.h>

#define BUFFER_SIZE 4096
#define INTERNET_SERVICE_HTTP 3
#define INTERNET_OPEN_TYPE_DIRECT 1

	typedef struct
	{
		const char *type;
		const char *body;
	} Carrier;

	typedef struct
	{
		const char *key;
		const char *value;
	} Dict;

	typedef struct
	{
		Dict *alpha;
		Dict *beta;
		Dict *omega;
	} Post;

	typedef struct
	{
		const char *host;
		const char *endpoint;
		int port;
		Post post;
	} Data;

	typedef struct
	{
		const char *public_key_base64;
		const char *sign_public_key_base64;
		unsigned char public_key[crypto_box_PUBLICKEYBYTES];
		unsigned char sign_public_key[crypto_sign_PUBLICKEYBYTES];
	} ServerKeys;

	typedef struct
	{
		char *public_key_base64;
		char *secret_key_base64;
		char *shared_key_base64;
		char *sign_public_key_base64;
		char *sign_secret_key_base64;
		unsigned char public_key[crypto_box_PUBLICKEYBYTES];
		unsigned char secret_key[crypto_box_SECRETKEYBYTES];
		unsigned char shared_key[crypto_box_BEFORENMBYTES];
		unsigned char sign_public_key[crypto_sign_PUBLICKEYBYTES];
		unsigned char sign_secret_key[crypto_sign_SECRETKEYBYTES];
	} KeyStore;

#ifdef __cplusplus
}
#endif

#endif
