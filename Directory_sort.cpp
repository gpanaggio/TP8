#include "filesystem_header.h"

bool isPNG(string);

int not_sort_directories(const char* dir, vector<string>& vec)
{
	path p(dir);   // p se crea a partir de un const char
		if (exists(p))
		{
			if (is_regular_file(p)) 
				cout << p << " es un archivo de size " << file_size(p) << '\n';
			else if (is_directory(p))   
			{
				cout << p << " es un directorio que contiene los siguientes archivos .png:\n";

				for (directory_iterator itr(p); itr != directory_iterator(); itr++)
				{
					if (isPNG(itr->path().filename().string()))
					{
						cout << itr->path().filename() << endl;
						vec.push_back(itr->path().filename().string());
					}
				}
				cout << "presione ENTER para continuar" << endl;
			}
		}
		else
			cout << p << "No existe\n";
		getchar();
	return 0;
}

bool isPNG(string str)
{

	if (str.length() < 4)
		return 0;

	string png;

	png.push_back(str[str.length() - 4]);
	png.push_back(str[str.length() - 3]);
	png.push_back(str[str.length() - 2]);
	png.push_back(str[str.length() - 1]);

	return png == ".png";
}