#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"
#include "debugmalloc.h"

int muvelet(char *infile, char *outfile, int (*tomorit)(FILE *in, FILE *out)){
    FILE *in=fopen(infile,"rb");
    if(in==NULL){       //van e file
        perror("hiba:");
        return 2;
    }
    FILE *out=fopen(outfile,"wb");
    int var=tomorit(in,out);        //compress/extract
    if(fclose(in)==EOF||fclose(out)==EOF){
        perror("hiba:");
        return 2;
    }
    return var;
}
int main(int argc, char *argv[])
{
    if(argc!=4){
        printf("hasznalat: ./huffman_kodolo <(be||ki)> <bemenet> <kimenet>\n");
        return 1;
    }
    if(strcmp("be",argv[1])==0){
        int ok=muvelet(argv[2],argv[3],betomorit);
        if(ok!=0)
            return ok;
    }
    else if(strcmp("ki",argv[1])==0){
        int ok=muvelet(argv[2],argv[3],kitomorit);
        if(ok!=0)
            return ok;
    }
    else{
        printf("hasznalat: ./huffman_kodolo <(be||ki)> <bemenet> <kimenet>\n");
        return 1;       //ha nem be/ki az argumentum
    }
    return 0;
}
