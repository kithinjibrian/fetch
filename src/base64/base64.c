#include "base64/base64.h"

char *base64Encode(unsigned char *bin, size_t t)
{
	size_t base64_size = sodium_base64_ENCODED_LEN(t, sodium_base64_VARIANT_ORIGINAL) + 1;
	char *b64 = (char *)malloc(base64_size);
	sodium_bin2base64(b64, base64_size, bin, t, sodium_base64_VARIANT_ORIGINAL);
	return b64;
}

unsigned char *base64Decode(const char *base64_encoded_string, size_t *binary_data_len)
{

	size_t max_bin_size = sodium_base64_encoded_len(strlen(base64_encoded_string), sodium_base64_VARIANT_ORIGINAL);

	unsigned char *binary_data = (unsigned char *)malloc(max_bin_size);
	if (binary_data == NULL)
	{
		return NULL;
	}

	int result = sodium_base642bin(binary_data, max_bin_size,
								   base64_encoded_string, strlen(base64_encoded_string),
								   NULL, binary_data_len, NULL, sodium_base64_VARIANT_ORIGINAL);

	if (result != 0)
	{
		free(binary_data);
		return NULL;
	}

	return binary_data;
}

void base64DecodeEx(unsigned char *key,
					size_t key_maxlen,
					const char *base64_encoded_string,
					size_t *binary_data_len)
{
	sodium_base642bin(key, key_maxlen,
					  base64_encoded_string, strlen(base64_encoded_string),
					  NULL, binary_data_len, NULL, sodium_base64_VARIANT_ORIGINAL);
}