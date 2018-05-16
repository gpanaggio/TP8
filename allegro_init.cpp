#include "allegro_init.h"

bool allegro_init_all()
{
	if (!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return 1;
	}

	if (!al_init_image_addon()) { // ADDON necesario para manejo(no olvidar el freno de mano) de imagenes 
		fprintf(stderr, "failed to initialize image addon !\n");
		return 1;
	}

	if (!al_install_keyboard()) {
		fprintf(stderr, "failed to initialize the keyboard!\n");
		return 1;
	}

	if (!al_init_primitives_addon()) {
		fprintf(stderr, "failed to initialize primitives!\n");
		return 1;
	}

	return 0;
}