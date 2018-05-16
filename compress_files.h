#pragma once
#include "filesystem_header.h"
#include "mosaico.h"
#include "compresor.h"
#include "allegro_init.h"
#include "show_mosaicos.h"
#include <vector>
#include <string>

bool compress_files(const char * path, unsigned int threshold);