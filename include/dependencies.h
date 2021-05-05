#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

#include "lib.h"
#include "help.h"
#include "primitivas.h"
#include "derivadas.h"
#include "filtros.h"
#include "fromfile.h"
#include "compress.h"

#ifndef DEPENDENCIES_H
#define DEPENDENCIES_H

#ifdef _WIN32
#define CLS system ("cls")
#elif unix
#define CLS system ("clear")
#else
#define CLS printf ("Essa função não possui suporte para o sistema operacional atual.\n")
#endif

#endif