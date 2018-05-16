#pragma once
#include "lodepng.h"
#include "lodepng_util.h"
#include <iostream>
#include <string>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost::filesystem;
/*
Functions here assume a square image with sides being powers of 2
*/


/*
Checks if the file exists and then decompresses it. Returns 0 on success or 1 on failure
*/
bool decompress_file(char* path_to_compressed_image);


/*
Decompresses and saves the file from our compression format with the required filename
*/
bool decompress(char* path_to_compressed_image, char* filename);

/*
Turns our compressed format into a raw pixel format for the lodepng functions
*/
void turn_compressed_into_raw_data(const char* compressed_image, unsigned char* raw_data, unsigned int w, unsigned int h, unsigned int* counter, unsigned int top_left_corner_x, unsigned int top_left_corner_y, unsigned int coloring_size);
