#include "parsecmd.h"
#include <string.h>
#include "parsecallback.h"

int parseCmdLine(int argc, char *argv[], pCallback p, void *userData) {
	int result = 0, error = false;

	for (int i = 1; i<argc;)
	{
		if (argv[i][0] == '-')
		{
			if (argv[i][1] == 0) //- unico valor
			{
				error = ERROR2;
				i = argc;
			}
			else if ((i + 1) >= argc)
			{
				error = ERROR1;
				i++;
			}

			else
			{
				if (argv[i + 1][0] == '-')
				{
					error = ERROR1;
					i = argc;
				}
				else
				{
					result = p(&(argv[i][1]), argv[i + 1], userData);
					if (result == 1)
					{
						i += 2;
					}
					else
					{
						error = ERROR3;
						i = argc;
					}
				}
			}
		}
		else
		{
			error = ERROR2;
			i = argc;
		}
	}
	if (error == ERROR1)
		result = ERROR1;
	else if (error == ERROR2)
		result = ERROR2;
	else if (error == ERROR3)
		result = ERROR3;
	return result;

}