#include "strings/strings.h"

char *stitch(Dict *dict)
{
	size_t len = 1;
	for (int i = 0; dict[i].key != NULL; i++)
	{

		len += strlen(dict[i].key) + strlen(dict[i].value) + 2;
	}

	char *query_string = malloc(len);
	if (query_string == NULL)
	{
		// perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}

	query_string[0] = '\0';
	for (int i = 0; dict[i].key != NULL; i++)
	{
		if (i > 0)
		{
			strcat(query_string, "&");
		}
		strcat(query_string, dict[i].key);
		strcat(query_string, "=");
		strcat(query_string, dict[i].value);
	}

	return query_string;
}

char *stitchEx(Dict *dict, char **delimeters)
{

	size_t len = 1;
	for (int i = 0; dict[i].key != NULL; i++)
	{

		len += strlen(dict[i].key) + strlen(dict[i].value) + 2;
	}

	char *query_string = malloc(len);
	if (query_string == NULL)
	{

		// perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}

	query_string[0] = '\0';
	for (int i = 0; dict[i].key != NULL; i++)
	{
		if (i > 0)
		{
			strcat(query_string, delimeters[0]);
		}
		strcat(query_string, dict[i].key);
		strcat(query_string, delimeters[1]);
		strcat(query_string, dict[i].value);
	}

	return query_string;
}