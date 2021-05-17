#include <stdio.h>
#include "huffman.h"
#include "fakezeles.h"
#include "filekezeles.h"
#include "debugmalloc.h"
#include "fileszerkezetek.h"

int kitomorit(FILE *in, FILE *out){
    BiFa *fa=farekonstrual(in);
    visszakodol(fa,in,out);
    felszfa(fa);
    return 0;
}
