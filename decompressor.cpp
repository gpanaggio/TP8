#include <fstream>
#include "decompressor.h"

bool decompress_file(char* path_to_compressed_image)
{
	bool return_bool = 1;
	path p(path_to_compressed_image); //Constructor de path. lleva un const char.
	if (exists(p) && is_regular_file(p))
	{
		if (decompress(path_to_compressed_image, (char *)((p.filename().string() + ".png").c_str())) == 0)
		{
			return_bool = 0;
		}
	}
	else
	{
		cout << "File not found" << endl;
	}
	return return_bool;
}

bool decompress(char* path_to_compressed_image, char* filename)
{
	bool return_bool = 1;

	unsigned char* raw_data;
	unsigned char* png;
	string compressed_image;
	size_t pngsize;
	std::ifstream file;
	string buffer;

	file.open(path_to_compressed_image, std::ifstream::binary);
	getline(file, buffer);
	unsigned int w = atoi(buffer.c_str());
	buffer.clear();
	getline(file, buffer);
	unsigned int h = atoi(buffer.c_str());
	buffer.clear();
	char c = 'A';
	bool run = 1;
	while (run)
	{
		if (file.peek() == EOF)
		{
			run = 0;
		}
		else
		{
			file.get(c);
			compressed_image.append(1, c);
		}
	}

	raw_data = new unsigned char[w*h * 4];


	unsigned int counter = 0;
	unsigned int* counter_pointer = &counter;
	turn_compressed_into_raw_data(compressed_image.c_str(), raw_data, w, h, counter_pointer, 0, 0, w);

	if (lodepng_encode32(&png, &pngsize, raw_data, w, h) == 0)
	{
		if (lodepng_save_file(png, pngsize, filename) == 0)
		{
			cout << "File decompressed and saved" << endl;
			return_bool = 0;
		}
		else
		{
			cout << "Error while saving file" << endl;
		}
	}
	else
	{
		cout << "Error while encoding file" << endl;
	}
	delete[] raw_data;
	free(png);
	file.close();
	return return_bool;
}

void turn_compressed_into_raw_data(const char* compressed_image, unsigned char* raw_data, unsigned int w, unsigned int h, unsigned int* counter, unsigned int top_left_corner_x, unsigned int top_left_corner_y, unsigned int coloring_size)
{
	if (compressed_image[*counter] == 'N')
	{
		(*counter)++;
		for (unsigned int j = 0; j < coloring_size; j++)
		{
			for (unsigned int i = 0; i < coloring_size; i++)
			{
				raw_data[(top_left_corner_x * 4 + (4 * i)) + (top_left_corner_y * 4 * w + (w * 4 * j))] = compressed_image[*counter];
				raw_data[(top_left_corner_x * 4 + (4 * i) + 1) + (top_left_corner_y * 4 * w + (w * 4 * j))] = compressed_image[(*counter) + 1];
				raw_data[(top_left_corner_x * 4 + (4 * i) + 2) + (top_left_corner_y * 4 * w + (w * 4 * j))] = compressed_image[(*counter) + 2];
				raw_data[(top_left_corner_x * 4 + (4 * i) + 3) + (top_left_corner_y * 4 * w + (w * 4 * j))] = 0xff;
			}
		}
		(*counter) = (*counter) + 3;
	}
	else if (compressed_image[*counter] == 'B')
	{
		(*counter)++;
		turn_compressed_into_raw_data(compressed_image, raw_data, w, h, counter, top_left_corner_x, top_left_corner_y, coloring_size / 2);
		turn_compressed_into_raw_data(compressed_image, raw_data, w, h, counter, top_left_corner_x + coloring_size / 2, top_left_corner_y, coloring_size / 2);
		turn_compressed_into_raw_data(compressed_image, raw_data, w, h, counter, top_left_corner_x, top_left_corner_y + coloring_size / 2, coloring_size / 2);
		turn_compressed_into_raw_data(compressed_image, raw_data, w, h, counter, top_left_corner_x + coloring_size / 2, top_left_corner_y + coloring_size / 2, coloring_size / 2);

	}
}