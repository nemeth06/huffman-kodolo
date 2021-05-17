#include "fakezeles.h"
#include "listakezeles.h"
#include <stdbool.h>
#include <stdio.h>
#include "debugmalloc.h"

void felszfa(BiFa *root){
    if(root==NULL)
        return;
    felszfa(root->bal);
    felszfa(root->jobb);
    free(root);
}
BiFa *ujelem(BiFa *bal, BiFa *jobb, unsigned char karakter){
    BiFa *uj=(BiFa *)malloc(sizeof(BiFa));
    uj->bal=bal;
    uj->jobb=jobb;
    if(bal==jobb&&jobb==NULL){       //ha level akkor kell a karakter
        uj->karakter=karakter;
        uj->szulo=NULL;
    }
    else{
        bal->szulo=uj;
        jobb->szulo=uj;
    }
    uj->jelzobit=false;
    return uj;
}
Lista *rendez(Lista *l){
    StatLista *elso=l->elso;
    StatLista *kov=l->elso;
    while(kov->kov!=NULL&&l->elso->elofordulas>=kov->kov->elofordulas)  //csak azert van az elso allitas h univerzalis legyan a fg
        kov=kov->kov;
    if(kov==l->elso)
        return l;
    l->elso=l->elso->kov;       //leptetjuk a lista elejet
    elso->kov=kov->kov;
    kov->kov=elso;
    if(kov==l->utolso)      //ha kell leptejuk a veget is
        l->utolso=elso;
    return l;
}
BiFa *elemek[256]={NULL};       //ide kerulnek a levelek a konnyebb kereses erdekeben
BiFa *faepit(struct Lista *l){
    while(l->elso->kov!=NULL){      //a listabol epitjuk fel a fat
        if(l->elso->fa==NULL){      //ha az elso elemhez nem tartozik fa, akkor level lesz
            l->elso->fa=ujelem(NULL,NULL,l->elso->karakter);
            elemek[l->elso->karakter]=l->elso->fa;
        }
        if(l->elso->kov->fa==NULL){ //ha a masodik elemhez nem tartozik fa, akkor level lesz
            l->elso->kov->fa=ujelem(NULL,NULL,l->elso->kov->karakter);
            elemek[l->elso->kov->karakter]=l->elso->kov->fa;
        }
        l->elso->kov->elofordulas+=l->elso->elofordulas;    //osszevonjuk a ket legkisebbet
        l->elso->kov->fa=ujelem(l->elso->fa,l->elso->kov->fa,0);    //atpointerezzuk az elso elem fajat
        StatLista *kov=l->elso->kov;
        free(l->elso);      //toroljuk a nem szukseges elemet
        l->elso=kov;
        if(l->elso!=l->utolso&&l->elso->elofordulas>=l->utolso->elofordulas){       //ha nagyobb a vegenel akkor nem keresunk
            StatLista *utolso=l->elso;
            l->elso=l->elso->kov;
            l->utolso->kov=utolso;
            utolso->kov=NULL;
            l->utolso=l->utolso->kov;
        }
        else        //ha kisebb akkor pedig keresessel rendezzuk
            l=rendez(l);
    }
    if(l->elso->fa==NULL){
        l->elso->fa=ujelem(NULL,NULL,l->elso->karakter);
        elemek[l->elso->karakter]=l->elso->fa;
    }
    l->elso->fa->szulo=NULL;
    BiFa *ptr=l->elso->fa;
    free(l->elso);      //nincs szukseg a lista kezdetere
    free(l);
    return ptr;
}
