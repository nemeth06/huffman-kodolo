#ifndef LISTAKEZELES_H_INCLUDED
#define LISTAKEZELES_H_INCLUDED
#include "fakezeles.h"
#include <stdio.h>
#include "fileszerkezetek.h"
#include "debugmalloc.h"

Lista *filebollista(FILE *f);
void felszlista(Lista *l);
#endif // LISTAKEZELES_H_INCLUDED
