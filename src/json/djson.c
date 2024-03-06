#include "json/djson.h"

ServerKeys deserializeServerKeys(const char *json_string)
{
	cJSON *root = cJSON_Parse(json_string);
	ServerKeys server_keys;

	if (root == NULL)
	{
		const char *error_ptr = cJSON_GetErrorPtr();
		if (error_ptr != NULL)
		{
			// fprintf(stderr, "Error before: %s\n", error_ptr);
			server_keys.public_key_base64 = NULL;
			return server_keys;
		}
	}

	cJSON *public_key = cJSON_GetObjectItemCaseSensitive(root, fheXOR("1610160f01053a1f0611", fXOR("56'0;", 'S')));
	cJSON *sign_public_key = cJSON_GetObjectItemCaseSensitive(root, fheXOR("150c130d371610160f01053a1f0611", fXOR("56'0;", 'S')));

	if (!(public_key && cJSON_IsString(public_key) &&
		  sign_public_key && cJSON_IsString(sign_public_key)))
	{
		// fprintf(stderr, "Error: Unable to extract values from JSON\n");
		cJSON_Delete(root);
		server_keys.public_key_base64 = NULL;
		return server_keys;
	}

	server_keys = makeServerKeys(strdup(public_key->valuestring), strdup(sign_public_key->valuestring));

	cJSON_Delete(root);

	return server_keys;
}

Carrier *deserializeNetworkCarrier(KeyStore *keystore, ServerKeys *server_keys, const char *json_string)
{
	Carrier *carrier = (Carrier *)malloc(sizeof(Carrier));
	carrier->body = NULL;

	// Parse JSON
	cJSON *json = cJSON_Parse(json_string);
	if (json == NULL)
	{
		return carrier;
	}

	// Accessing parsed values
	cJSON *type = cJSON_GetObjectItemCaseSensitive(json, "type");
	cJSON *nonce = cJSON_GetObjectItemCaseSensitive(json, "nonce");
	cJSON *body = cJSON_GetObjectItemCaseSensitive(json, "body");
	cJSON *signature = cJSON_GetObjectItemCaseSensitive(json, "signature");

	// Free memory
	// cJSON_Delete(json);

	*carrier = makeCarrier(*keystore, *server_keys, strdup(nonce->valuestring), strdup(type->valuestring), strdup(signature->valuestring), strdup(body->valuestring));

	return carrier;
}
