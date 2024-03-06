#include "keys/keys.h"

unsigned char *sign(KeyStore keystore)
{
	unsigned char *signature = (unsigned char *)malloc(crypto_sign_BYTES);
	crypto_sign(signature, NULL, keystore.public_key, crypto_kx_PUBLICKEYBYTES, keystore.secret_key);
	return signature;
}

void base64(KeyStore *keystore)
{
	keystore->public_key_base64 = base64Encode(keystore->public_key, crypto_box_PUBLICKEYBYTES);

	keystore->secret_key_base64 = base64Encode(keystore->secret_key, crypto_box_SECRETKEYBYTES);

	keystore->sign_public_key_base64 = base64Encode(keystore->sign_public_key, crypto_sign_PUBLICKEYBYTES);

	keystore->sign_secret_key_base64 = base64Encode(keystore->sign_secret_key, crypto_sign_SECRETKEYBYTES);
}

KeyStore genKeyStore()
{
	KeyStore keystore;

	crypto_box_keypair(keystore.public_key, keystore.secret_key);
	crypto_sign_keypair(keystore.sign_public_key, keystore.sign_secret_key);

	base64(&keystore);

	return keystore;
}

void genSharedKey(KeyStore *keystore, ServerKeys server_keys)
{
	if (crypto_box_beforenm(keystore->shared_key, server_keys.public_key, keystore->secret_key) != 0)
	{
		// printf("Error deriving shared key\n");
		return;
	}

	size_t base64_sharedkey_size = sodium_base64_ENCODED_LEN(crypto_box_BEFORENMBYTES, sodium_base64_VARIANT_ORIGINAL) + 1;
	keystore->shared_key_base64 = (char *)malloc(base64_sharedkey_size);
	sodium_bin2base64(keystore->shared_key_base64, base64_sharedkey_size, keystore->shared_key, crypto_box_BEFORENMBYTES, sodium_base64_VARIANT_ORIGINAL);
}