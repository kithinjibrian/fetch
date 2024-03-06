#ifndef BASE64_H
#define BASE64_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "master.h"

	char *base64Encode(unsigned char *bin, size_t t);
	unsigned char *base64Decode(const char *base64_encoded_string, size_t *binary_data_len);
	void base64DecodeEx(unsigned char *key,
						size_t key_maxlen,
						const char *base64_encoded_string,
						size_t *binary_data_len);

#ifdef __cplusplus
}
#endif

#endif