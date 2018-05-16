#include "compress_files.h"

bool compress_files(const char * path_, unsigned int threshold)
{
	if (allegro_init_all())
		return 1;					//hubo un error al iniciar Allegro
	string path = path_;
	vector <string> PNGvec;			//este va a ser el vector que contenga el nombre de las imagenes PNG
	vector <mosaico> mosaico_vec;	//vector de mosaicos
	not_sort_directories(path_, PNGvec);	//se guardo en el vector los nombres de los acrivos PNG

	vector<string>::iterator itr;
	for (itr = PNGvec.begin(); itr < PNGvec.end(); itr++)
		mosaico_vec.push_back(mosaico(path + "/" + *itr, *itr));		//tengo mi vector cargado con todos los mosaicos

	for (int i = 0; i < mosaico_vec.size(); i++)
		mosaico_vec[i].setBitmap();		//cargo los bitmaps

	bool error;
	error = show_mosaicos(mosaico_vec);

	if (!error)
		compresor(mosaico_vec, threshold);
	else
		return 1;

	for (int j = 0; j < mosaico_vec.size(); j++)
		al_destroy_bitmap(mosaico_vec[j].mosaicoBitmap);

	return 0;
}