#include "encrypt/encrypt.h"

char *fXOR(char *data, char key)
{
	int dataLen = strlen(data);
	char *output = (char *)malloc(sizeof(char) * dataLen);

	for (int i = 0; i < dataLen; ++i)
	{
		output[i] = data[i] ^ key;
	}

	output[dataLen] = '\0';

	return output;
}

char *fheXOR(char *hex, char *key)
{
	size_t ciphertext_len = strlen(hex) / 2;
	unsigned char *ciphertext = (unsigned char *)malloc(ciphertext_len);
	for (size_t i = 0; i < ciphertext_len; ++i)
	{
		sscanf(hex + 2 * i, "%2hhx", &ciphertext[i]);
	}

	int key_len = strlen(key);
	char *decrypted = (char *)malloc(ciphertext_len + 1);

	for (size_t i = 0; i < ciphertext_len; ++i)
	{
		decrypted[i] = ciphertext[i] ^ key[i % key_len];
	}

	decrypted[ciphertext_len] = '\0';

	free(ciphertext);

	return decrypted;
}

int fhash(const char *s, const int n)
{
	long long p = 31, m = 1e9 + 7;
	long long hash = 0;
	long long p_pow = 1;
	for (int i = 0; i < n; i++)
	{
		hash = (hash + (s[i] - 'a' + 1) * p_pow) % m;
		p_pow = (p_pow * p) % m;
	}
	return hash;
}

char *boxEncrypt(KeyStore keystore, Dict *dict)
{
	char *enc_str = stitch(dict);
	int len = strlen(enc_str);

	unsigned char nonce[crypto_box_NONCEBYTES];
	randombytes_buf(nonce, sizeof(nonce));

	unsigned char ciphertext[crypto_box_MACBYTES + len];

	if (crypto_box_easy_afternm(ciphertext, (const unsigned char *)enc_str, len, nonce, keystore.shared_key) != 0)
	{
		return NULL;
	}

	unsigned char hash[crypto_generichash_BYTES];

	crypto_generichash(hash, sizeof(hash), (const unsigned char *)enc_str, len, NULL, 0);

	unsigned char sig[crypto_sign_BYTES];

	crypto_sign_detached(sig, NULL, hash, crypto_sign_BYTES, keystore.secret_key);

	Dict dict2[] = {
		{"type", "text/plain"},
		{"nonce", base64Encode(nonce, crypto_box_NONCEBYTES)},
		{"body", base64Encode(ciphertext, crypto_box_MACBYTES + len)},
		{"signature", base64Encode(sig, crypto_sign_BYTES)},
		{NULL, NULL}};

	char *delimeters[] = {"$", ">"};

	return stitchEx(dict2, delimeters);
}