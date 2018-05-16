#pragma once
#include "allegro_init.h"
#include "mosaico.h"
#include <vector>

#define SCREEN_W 1000
#define SCREEN_H 600

#define FIRST_COLUMN 150	//coordenadas dentro del display
#define SECOND_COLUMN 450
#define THIRD_COLUMN 750
#define FIRST_ROW 100
#define SECOND_ROW 250
#define THIRD_ROW 400

#define MOSAICO_SIZE 100	//largo y ancho del mosaico

bool show_mosaicos(vector<mosaico>&);