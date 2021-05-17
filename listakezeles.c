#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fakezeles.h"
#include "listakezeles.h"
#include "debugmalloc.h"
#include "fileszerkezetek.h"

void kiir(Lista *l){
    for(StatLista *i=l->elso;i!=NULL;i=i->kov)
        printf("%c %d\n",i->karakter,i->elofordulas);
    printf("\n");
}
void felszlista(Lista *l){
    StatLista *prev;        //csak a teljesseg kedveert, a programban a faepito fg felsz. a listat
    for(StatLista *i=l->elso;i!=NULL;i=i->kov){
        prev=i;
        i=i->kov;
        free(prev);
    }
    free(l);        //a Lista strukturat is fel kell szabaditani!
}
//2 kiBi tarhely, ide tarolodnak a listaelemekre mutato pointerek a konnyebb megtalalas erdekeben
StatLista* listaelemek[256];
Lista *listaepit(FILE *f){
    Lista *l=(Lista *)malloc(sizeof(Lista));
    l->elso=l->utolso=NULL;
    unsigned char puf;
    while(fread(&puf,sizeof(unsigned char),1,f)==1){
        if(listaelemek[puf]==NULL){     //ha nincs benn a tombben akkor letre kell hozni, a vegere fuzni es letre kell hozni egy pointert a tombbe
            StatLista *uj=(StatLista *)malloc(sizeof(StatLista));
            uj->karakter=puf;
            uj->elofordulas=1;
            uj->fa=NULL;
            uj->kov=NULL;
            listaelemek[puf]=uj;
            if(l->elso==NULL)
                l->elso=l->utolso=uj;
            else{
                l->utolso->kov=uj;
                l->utolso=uj;
            }
        }
        else
            listaelemek[puf]->elofordulas++;     //ha benne van akkor pedig eggyel novelni az elofordulasokat
    }
    return l;
}
bool azonoselemek(Lista *l){            //csak egyfajta elemekbol all a lista?(csak azert nezi meg az utolsot is, hogy mas helyeken is fel lehessen hasznalni)
    for(StatLista *i=l->elso;i!=NULL;i=i->kov)
        if(i->elofordulas!=l->elso->elofordulas)
            return false;
    return true;
}
Lista *beszurquick(Lista *l,StatLista *e){      //utolso helyre szur be
    if(l->elso==NULL){
        l->elso=e;
        l->utolso=e;
    }
    else{
        l->utolso->kov=e;
        l->utolso=e;
    }
    l->utolso->kov=NULL;
    return l;
}
Lista *quicksort(Lista *l){
    //akkor kell visszaterni, ha egy elemu a lista es ha az osszes elem megegyezek(ha nem egyezik meg az 1. es az utolso, el se kezdi
    if(l->elso==l->utolso||(l->elso->elofordulas==l->utolso->elofordulas&&azonoselemek(l)))
            return l;
    //median elem
    StatLista *median=l->elso;
    //allistak
    Lista *kicsik=(Lista *)malloc(sizeof(Lista));
    Lista *nagyok=(Lista *)malloc(sizeof(Lista));
    kicsik->elso=nagyok->elso=kicsik->utolso=nagyok->utolso=NULL;
    StatLista *next;
    for(StatLista *i=l->elso->kov;i!=NULL;i=next){
        next=i->kov;
        //atlancolas
        if(i->elofordulas<median->elofordulas)
            kicsik=beszurquick(kicsik,i);
        else
            nagyok=beszurquick(nagyok,i);
    }
    //a median mindig a nagyokba kerul
    nagyok=beszurquick(nagyok,median);
    //allistak rendezese
    kicsik=quicksort(kicsik);
    nagyok=quicksort(nagyok);
    //kivetelkezeles ha az egyik ures(magyaran NULL)
    l->elso= kicsik->elso==NULL ? nagyok->elso: kicsik->elso;       //osszefuzes
    if(kicsik->elso!=NULL)
        kicsik->utolso->kov=nagyok->elso;
    l->utolso=nagyok->utolso==NULL ? kicsik->utolso: nagyok->utolso;
    free(kicsik);
    free(nagyok);
    return l;
}
Lista *filebollista(FILE *f){       //egyben a ketto hogy csak egy fuggvenyt kelljen kezelni
    Lista *l=listaepit(f);
    l=quicksort(l);
    fseek(f,0,SEEK_SET);        //visszaugrunk a file elejere
    return l;
}
