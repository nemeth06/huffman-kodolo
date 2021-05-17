#ifndef FILEKEZELES_H_INCLUDED
#define FILEKEZELES_H_INCLUDED
#include <stdio.h>
#include "fakezeles.h"
#include "debugmalloc.h"

void filebafa(FILE *out, BiFa *fa);
void bekodol(BiFa *fa, FILE *in, FILE *out);
BiFa *farekonstrual(FILE *in);
void visszakodol(BiFa *fa,FILE *in,FILE *out);
#endif // FILEKEZELES_H_INCLUDED
