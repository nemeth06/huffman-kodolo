#ifndef FAKEZELES_H_INCLUDED
#define FAKEZELES_H_INCLUDED
#include <stdbool.h>
#include "listakezeles.h"
#include "fileszerkezetek.h"
#include "debugmalloc.h"

extern BiFa *elemek[256];
void felszfa(BiFa *root);
BiFa *faepit(Lista *l);
#endif // FAKEZELES_H_INCLUDED
