#include <stdio.h>
#include "huffman.h"
#include "listakezeles.h"
#include "fakezeles.h"
#include "filekezeles.h"
#include "debugmalloc.h"
#include "fileszerkezetek.h"
#include <time.h>
int betomorit(FILE *in, FILE *out){
    clock_t tStart = clock();
    printf("start\n");
    Lista *karakterlista=filebollista(in);      //RENDEZETT lista epitese
    printf("ok\n");
    printf("lista: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    BiFa *karakterfa=faepit(karakterlista);     //a lista fel lesz szabaditva
    printf("fa: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    filebafa(out,karakterfa);
    printf("fakodol: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    bekodol(karakterfa,in,out);
    printf("bekodol: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    felszfa(karakterfa);
    printf("felszfa: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    return 0;
}
