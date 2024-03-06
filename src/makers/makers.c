#include "makers/makers.h"

ServerKeys makeServerKeys(const char *public_key, const char *sign_public_key)
{
	ServerKeys server_keys;
	server_keys.public_key_base64 = public_key;
	server_keys.sign_public_key_base64 = sign_public_key;

	size_t pkey, spkey;
	base64DecodeEx(server_keys.public_key, crypto_box_PUBLICKEYBYTES, public_key, &pkey);
	base64DecodeEx(server_keys.sign_public_key, crypto_sign_PUBLICKEYBYTES, sign_public_key, &spkey);

	return server_keys;
}

Carrier makeCarrier(KeyStore keystore, ServerKeys server_keys, const char *nonce, const char *type, const char *signature, const char *body)
{
	Carrier carrier;
	carrier.type = type;

	size_t body_len, signature_len, nonce_len;
	unsigned char *body_bin = base64Decode(body, &body_len);
	unsigned char *signature_bin = base64Decode(signature, &signature_len);
	unsigned char *nonce_bin = base64Decode(nonce, &nonce_len);

	int len = body_len - crypto_box_MACBYTES;

	unsigned char *decrypted = (unsigned char *)malloc(len + 1);
	if (decrypted == NULL)
	{
		free(decrypted);
		carrier.body = NULL;
	}

	if (crypto_box_open_easy_afternm(decrypted, body_bin, crypto_box_MACBYTES + len, nonce_bin, keystore.shared_key) != 0)
	{
		free(decrypted);
		free(nonce_bin);
		free(body_bin);
		carrier.body = NULL;
	}

	decrypted[len] = '\0';

	unsigned char hash[crypto_generichash_BYTES];

	crypto_generichash(hash, sizeof(hash), decrypted, len, NULL, 0);

	if (crypto_sign_verify_detached(signature_bin, hash, crypto_generichash_BYTES, server_keys.sign_public_key) != 0)
	{
		carrier.body = NULL;
	}

	carrier.body = (char *)decrypted;

	free(body_bin);
	free(decrypted);
	free(nonce_bin);
	free(signature_bin);

	return carrier;
}