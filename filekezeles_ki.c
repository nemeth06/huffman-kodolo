#include <stdio.h>
#include <stdlib.h>
#include "filekezeles.h"
#include "fakezeles.h"
#include "debugmalloc.h"
#include "fileszerkezetek.h"

BiFa kov;
BiFa *idemegkell=&kov;
unsigned char fbuf=0;
int offset=-1;
BiFa *uj(FILE *f){
    BiFa *elem=(BiFa *)malloc(sizeof(BiFa));
    if(offset==-1){
        fread(&fbuf,1,1,f);
        offset=7;
    }
    if((fbuf>>(offset--)&1)==1){
        elem->bal=idemegkell;
        elem->jobb=idemegkell;
    }
    else{
        elem->bal=NULL;
        elem->jobb=NULL;
        elem->karakter=fbuf<<(7-offset);
        fread(&fbuf,1,1,f);
        elem->karakter|=fbuf>>(offset+1);
    }
    return elem;
}
BiFa *legbaloldalibb(BiFa *fa){
    if(fa->bal==idemegkell)
        return fa;
    if(fa->bal==NULL)
        return NULL;
    BiFa *bal=legbaloldalibb(fa->bal);
    if(bal!=NULL)
        return bal;
    if(fa->jobb==idemegkell)
        return fa;
    if(fa->jobb==NULL)
        return NULL;
    BiFa *jobb=legbaloldalibb(fa->jobb);
    if(jobb!=NULL)
        return jobb;
}
BiFa *farekonstrual(FILE *in){
    BiFa *fa=uj(in);
    while(1){
        BiFa *ide=legbaloldalibb(fa);
        if(ide==NULL)
            break;
        if(ide->bal==idemegkell)
            ide->bal=uj(in);
        else
            ide->jobb=uj(in);
    }
    return fa;
}
BiFa *root=NULL;
void kifejt(unsigned char buf,char hossz, BiFa *fa,FILE *f){
    if(root==NULL)
        root=fa;
    while(offset>=8-hossz){
        while(offset>=8-hossz&&root->bal!=NULL){
            if((buf>>(offset--))&1==1)
                root=root->jobb;
            else
                root=root->bal;
        }
        if(root->bal==NULL){
            fwrite(&root->karakter,1,1,f);
            root=fa;
        }
    }
}

void visszakodol(BiFa *fa,FILE *in,FILE *out){
    long int mostani=ftell(in);
    fseek(in,-1,SEEK_END);
    long int vege=ftell(in);
    char eddig;
    fread(&eddig,1,1,in);
    fseek(in,mostani,SEEK_SET);
    while(ftell(in)<vege-1){
        fread(&fbuf,1,1,in);
        offset=7;
        kifejt(fbuf,8,fa,out);
    }
    fread(&fbuf,1,1,in);
    offset=7;
    kifejt(fbuf,eddig,fa,out);
}
