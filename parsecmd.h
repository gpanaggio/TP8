#pragma once
#include <stdlib.h>
#include <stdio.h>

typedef int(*pCallback) (char *, char*, void *);

int parseCmdLine(int argc, char *argv[], pCallback p, void *userData);

enum { ERROR1 = -4, ERROR2, ERROR3 };//Error 1 es opcion sin valor, Error 2 es opcion sin clave, Error3 es no encontrado
