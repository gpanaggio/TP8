#pragma once
#include <allegro5/allegro.h> 
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_color.h>
#include <string>
#include <iostream>

using namespace std;

class mosaico
{
public:
	mosaico(string path, string name);	//se inicializa cada mosaico con su respectivo path
	~mosaico();

	string path;	//tengo que guardar el path para cuando cree el scalated bitmap
	bool selected;	//uso este bool para saber si fue seleccionado el coso
	ALLEGRO_BITMAP  *mosaicoBitmap = NULL;
	string name;

	void setBitmap();
	void select();
};

