#include "compresor.h"
#include <fstream>

using namespace std;

unsigned int rgb_maxDiference(const unsigned char * out, unsigned int w, unsigned int h);
void rec_decode(const unsigned char * image, string& code, unsigned int w, unsigned int h, unsigned int threshold);
void set_avg(const unsigned char * quadrant, string& code, unsigned int w, unsigned int h);
void set_quadrants(const unsigned char * image, unsigned int w, unsigned int h, unsigned char * first_q, unsigned char * second_q, unsigned char * third_q, unsigned char * forth_q);

void compresor(vector<mosaico>& vecM, unsigned int threshold)
{
	unsigned char * image;
	unsigned int h, w;

	unsigned int spectrum;		//aca vamos a guardar el valor del espectro de imagen, que luego comparamos con tl threshold
	string code;
	

	for (unsigned int i = 0; i < vecM.size(); i++)
	{
		if (vecM[i].selected)					//si este mosaico esta seleccionado
		{
			lodepng_decode32_file(&image, &w, &h, vecM[i].path.c_str());		//tengo en image toda la informacion de la imagen

			spectrum = rgb_maxDiference(image, w, h);

			if (spectrum > threshold)
			{
				code = 'B';			//brancheo
				rec_decode(image, code, w, h, threshold);
			}
			else
				set_avg(image, code, w, h);

			std::ofstream dest;
			dest.open((vecM[i].name + ".eda").c_str());
			dest << (to_string(w) + '\n').c_str();
			dest << (to_string(h) + '\n').c_str();
			dest.close();
			dest.open((vecM[i].name + ".eda").c_str(), ios::app | ios::binary);
			dest.write(code.c_str(), code.length());
			dest.close();
		}
	}

	cout << "termine :D" << endl << "presione ENTER para continuar" << endl;
}


unsigned int rgb_maxDiference(const unsigned char * out, unsigned int w, unsigned int h)
{
	vector<unsigned char> red;
	vector<unsigned char> green;
	vector<unsigned char> blue;

	unsigned char redMin = 255;		//255 para asegurarnos que vamos a encontrar algo menos
	unsigned char blueMin = 255;
	unsigned char greenMin = 255;

	unsigned char redMax = 0;		//0 para asegurarnos que vamos a encontrar algo major
	unsigned char blueMax = 0;
	unsigned char greenMax = 0;

	for (unsigned int i = 0; i < h*w; i++)
	{
		red.push_back(out[i * 4]);
		green.push_back(out[i * 4 + 1]);
		blue.push_back(out[i * 4 + 2]);				//tengo los valores de los colores
	}

	for (unsigned int i = 0; i < red.size(); i++)			//todos los vectores van a tener igual size
	{
		if (red[i] < redMin)
			redMin = red[i];
		if (red[i] > redMax)
			redMax = red[i];

		if (green[i] < greenMin)
			greenMin = green[i];
		if (green[i] > greenMax)
			greenMax = green[i];

		if (blue[i] < blueMin)
			blueMin = blue[i];
		if (blue[i] > blueMax)
			blueMax = blue[i];
	}

	return (redMax - redMin) + (greenMax - greenMin) + (blueMax - blueMin);
}

void rec_decode(const unsigned char * image, string& code, unsigned int w, unsigned int h, unsigned int threshold)
{
	if (w == 1 == h)	//si estoy trabajando en un pixel...
	{
		code += image[0];
		code += image[1];
		code += image[2];
	}
	else
	{
		unsigned char * first_quadrant = new unsigned char[w*h];	//la cantidad de chars en un cuadrante sera w*h / 4 * (la cantidad de chars en un byte -> 4)  =  w*h
		unsigned char * second_quadrant = new unsigned char[w*h];
		unsigned char * third_quadrant = new unsigned char[w*h];
		unsigned char * forth_quadrant = new unsigned char[w*h];

		set_quadrants(image, w, h, first_quadrant, second_quadrant, third_quadrant, forth_quadrant);	//guarda la info respectiva a cada cuadrante

		if (rgb_maxDiference(first_quadrant, w / 2, h / 2) > threshold)
		{
			code = code + 'B';
			rec_decode(first_quadrant, code, w / 2, h / 2, threshold);
		}
		else
		{
			code = code + 'N';	  //no breancheo
			set_avg(first_quadrant, code, w / 2, h / 2);
		}

		if (rgb_maxDiference(second_quadrant, w / 2, h / 2) > threshold)
		{
			code = code + 'B';
			rec_decode(second_quadrant, code, w / 2, h / 2, threshold);
		}
		else
		{
			code = code + 'N';	  //no breancheo
			set_avg(second_quadrant, code, w / 2, h / 2);
		}

		if (rgb_maxDiference(third_quadrant, w / 2, h / 2) > threshold)
		{
			code = code + 'B';
			rec_decode(third_quadrant, code, w / 2, h / 2, threshold);
		}
		else
		{
			code = code + 'N';	  //no breancheo
			set_avg(third_quadrant, code, w / 2, h / 2);
		}

		if (rgb_maxDiference(forth_quadrant, w / 2, h / 2) > threshold)
		{
			code = code + 'B';
			rec_decode(forth_quadrant, code, w / 2, h / 2, threshold);
		}
		else
		{
			code = code + 'N';	  //no breancheo
			set_avg(forth_quadrant, code, w / 2, h / 2);
		}
		delete[] first_quadrant;
		delete[] second_quadrant;
		delete[] third_quadrant;
		delete[] forth_quadrant;
	}
}

void set_avg(const unsigned char * quadrant, string& code, unsigned int w, unsigned int h)
{
	vector<unsigned int> red;
	vector<unsigned int> green;
	vector<unsigned int> blue;

	long int total = 0;

	for (unsigned int i = 0; i < h*w; i++)
	{
		red.push_back(quadrant[i * 4]);
		green.push_back(quadrant[i * 4 + 1]);
		blue.push_back(quadrant[i * 4 + 2]);				//tengo los valores de los colores
	}

	for (unsigned int i = 0; i < red.size(); i++)			//todos los vectores van a tener igual size
		total += red[i];

	code += (char)(total / red.size());
	total = 0;

	for (unsigned int i = 0; i < green.size(); i++)			//todos los vectores van a tener igual size
		total += green[i];

	code += (char)(total / green.size());
	total = 0;

	for (unsigned int i = 0; i < blue.size(); i++)			//todos los vectores van a tener igual size
		total += blue[i];

	code += (char)(total / blue.size());
	total = 0;
}



void set_quadrants(const unsigned char * image, unsigned int w, unsigned int h, unsigned char * first_q, unsigned char * second_q, unsigned char * third_q, unsigned char * forth_q)
{
	int a = 0;
	int b = 0;
	int c = 0;
	int d = 0;

	for (unsigned int i = 0; i < (w*h) * 4; i++)		//multiplico x 4 porque en cada byte (que es en lo que se miden h y w) tengo 4 chars
	{
		if (i < (w*h) * 2)		//estoy en la mitad de arriba
		{
			if ((i % (w*4)) < ((w*4) / 2))		//estoy en la mitad de la izquierda
			{
				first_q[a] = image[i];
				a++;
			}
			else
			{
				second_q[b] = image[i];	//mitad derecha
				b++;
			}
		}
		else					//estoy en la mitad de abajo
		{
			if ((i % (w*4)) < ((w*4) / 2))		//estoy en la mitad de la izquierda
			{
				third_q[c] = image[i];
				c++;
			}
			else
			{
				forth_q[d] = image[i];	//mitad derecha
				d++;
			}
		}
	}
}