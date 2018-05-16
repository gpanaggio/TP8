#include <iostream>
#include "parsecmd.h"
#include "parsecallback.h"
#include "compress_files.h"
#include "decompressor.h"

using namespace std;

int main(int argc, char *argv[]) 
{

	pCallback p = parseCallback;
	userData myinfo;

	myinfo.key[0] = (char*)"PATH";//habria que ubicarlo en un class
	myinfo.key[1] = (char*)"MODE";
	myinfo.key[2] = (char*)"THRESHOLD";


	int result = parseCmdLine(argc, argv, p, &myinfo);

	if (result == ERROR1)
		cout << "Error tipo 1, se ha ingresado una opcion sin valor" << endl << "se espera el siguiente fomato por linea de comando:\n  -path Direccion -mode com -threshold 37" << endl << "presione ENTER para salir" << endl;
	else if (result == ERROR2)
		cout << "Error tipo 2, se ha ingresado una opcion sin clave" << endl << "se espera el siguiente fomato por linea de comando:\n -path Direccion -mode com -threshold 37" << endl << "presione ENTER para salir" << endl;
	else if (result == ERROR3)
	{
		cout << "Error tipo 3, los datos ingresados no son validos. Porfavor verifique que las claves sean correctas y que el valor del threshold sea entre 0 y 765, de la siguente manera:" << endl;
		cout << "-p Direccion -m com -t 376" << endl;
	}
	else
	{
		cout << "path:" << myinfo.value[0] << endl;

		if (myinfo.act)
		{
			cout << "Empieza a comprimir" << endl;
			cout << "threshold:" << myinfo.value[1] << endl;

			bool error;

			error = compress_files(myinfo.value[0], atoi(myinfo.value[1]));

			if (error)
			{
				cout << "ERROR" << endl;
				getchar();
			}

		}
		else
		{
			cout << "Empieza a descomprimir" << endl;
			decompress_file(myinfo.value[0]);
		}
	}

	getchar();
	return 0;
}