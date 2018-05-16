#include "mosaico.h"


mosaico::mosaico(string path, string name)
{
	this->path = path;
	this->name = name;

	(this->name).pop_back();
	(this->name).pop_back();
	(this->name).pop_back();
	(this->name).pop_back();		//hacemos esto para el nombre borrarle el ".png"

	selected = false;
}


mosaico::~mosaico()
{
}


void mosaico::setBitmap()
{
	mosaicoBitmap = al_load_bitmap(path.c_str());
}

void mosaico::select()
{
	selected = !selected;
}