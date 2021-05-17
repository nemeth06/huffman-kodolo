#ifndef FILESZERKEZETEK_H_INCLUDED
#define FILESZERKEZETEK_H_INCLUDED
#include "debugmalloc.h"

typedef struct StatLista{
    unsigned char karakter;
    long int elofordulas;       //max 2GiBi meretu file
    struct BiFa *fa;
    struct StatLista *kov;
}StatLista;
typedef struct Lista{
    StatLista *elso;
    StatLista *utolso;
}Lista;
typedef struct BiFa{
    bool jelzobit;
    unsigned char karakter;
    struct BiFa *bal, *jobb, *szulo;
}BiFa;
#endif // FILESZERKEZETEK_H_INCLUDED
