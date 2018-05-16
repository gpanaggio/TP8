#include "parsecallback.h"
#include <string.h>
#include <iostream>

int parseCallback(char *key, char *value, void *userinfo)
{
	int i = 0, equal = -1;
	char * ke = key;
	char * val = value;

	while (key[i])
	{
		ke[i] = toupper(ke[i]);
		i++;
	}

	for (i = 0; i < KEYS; i++)
	{
		equal = strcmp(ke, ((userData*)userinfo)->key[i]);
		if (equal == 0)
			i = KEYS;
	}

	if (equal == 0)
	{
		i = 0;

		if (!(strcmp(key, "PATH")))
		{

			((userData*)userinfo)->value[0] = value;
		}



		if (!(strcmp(ke, "MODE")))
		{
			int i = 0;
			while (val[i])
			{
				val[i] = toupper(val[i]);
				i++;
			}

			if (!(strcmp(val, "COM")))
			{
				((userData*)userinfo)->act = 1;
			}
			else if (!(strcmp(val, "DES")))
			{
				((userData*)userinfo)->act = 0;
			}
			else
				equal = 1;
		}

		if (((userData*)userinfo)->act)
		{
			if (!(strcmp(ke, "THRESHOLD")))
			{
				((userData*)userinfo)->value[1] = value;
				int j = atoi(value);
				if ((j < 0) || (j > 765))
					equal = 1;
			}
		}

	}

	if (equal != 0)
		equal = -1;
	else
		equal = 1;
	return equal;
}