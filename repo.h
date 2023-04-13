#pragma once
#include "masina.h"

typedef void* ElemType;

typedef void(*DestroyFunction) (ElemType);

typedef ElemType (*CopyFunction) (ElemType);

typedef struct
{
    ElemType* elems;
    int lg, cap;
    DestroyFunction destf;
}MyList;

MyList * createEmpty(DestroyFunction destf);

void add(MyList * l, ElemType el);

void delete(MyList* l, int poz);

void modify(MyList* l, int poz, char* numar1, char* model1, char* categorie1);

void destroy(MyList * l);

void ensureCapacity(MyList * l);

MyList * copyList(MyList * l, CopyFunction cp);

ElemType removeLast(MyList * l);
//pentru a sterge ultimul element din lista de undo

int size(MyList * l);

ElemType get(MyList* l, int poz);

ElemType set(MyList* l, int poz, Car* c);

void testeListaMasini();

void testListeDeListe();