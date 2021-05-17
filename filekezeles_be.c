#include "fakezeles.h"
#include "filekezeles.h"
#include <stdio.h>
#include <stdbool.h>
#include "debugmalloc.h"
#include "fileszerkezetek.h"

unsigned char buf=0;
int eltolas=8;
void told(unsigned char toldando, int hossz, FILE *f){
    if(eltolas-hossz>0){
        buf|=toldando<<(eltolas-hossz);
        eltolas-=hossz;
    }
    else{
        buf|=toldando>>(abs(eltolas-hossz));
        fwrite(&buf,1,1,f);
        eltolas=8+eltolas-hossz;
        buf=toldando<<eltolas;
    }
}
void filebafa2(FILE *out, BiFa *fa){
    if(fa->bal==NULL){   //huffman faban lehetetlen hogy csak egy iranyba menjen tovabb a fa
        told(0,1,out);
        told((unsigned char)fa->karakter,8,out);
        return;
    }
    told(1,1,out);
    filebafa2(out,fa->bal);
    filebafa2(out,fa->jobb);
}
void filebafa(FILE *out, BiFa *fa){     //ideigelenes, lehet nem kell
    filebafa2(out,fa);
    fwrite(&buf,1,1,out);
    buf=0;
    eltolas=8;
}
void beallit(BiFa *level){      //truera allitja a jelzobitet egeszen a gyokerig
    level->jelzobit=true;
    if(level->szulo!=NULL)
        beallit(level->szulo);
}
void beir(BiFa *root, FILE *out){
    root->jelzobit=false;
    if(root->bal==NULL&&root->szulo!=NULL)     //ha level visszaterunk
        return;
    if((root->szulo==NULL&&root->bal==NULL)||root->bal->jelzobit){
        told(0,1,out);      //ha balra megy tovabb akkor 0t kell hozzafuzni
        if(root->bal->jelzobit)
            beir(root->bal,out);
    }
    else if(root->jobb->jelzobit){
        told(1,1,out);      //ha jobbra, akkor pedig 1et
        beir(root->jobb,out);
    }
}
void bekodol(BiFa *fa, FILE *in, FILE *out){
    unsigned char k;
    while(fread(&k,1,1,in)==1){
        beallit(elemek[k]);
        beir(fa,out);
    }
    fwrite(&buf,1,1,out);       //beirjuk a maradekot
    if(eltolas!=8){
        buf=8-eltolas;
        fwrite(&buf,1,1,out);
    }
}
