#include "masina.h"
#include "repo.h"
#include <stdlib.h>
#include <assert.h>

MyList* createEmpty(DestroyFunction destf)
{
    MyList * rez = malloc(sizeof(MyList));
    rez->cap = 2;
    rez->lg = 0;
    rez->elems = malloc(sizeof(ElemType)*rez->cap);
    rez->destf = destf;
    return rez;
}

void destroy(MyList * l)
{
    for(int i = 0; i < l->lg; i ++)
        l->destf(l->elems[i]);

    free(l->elems);
    free(l);
}

void add(MyList * l, ElemType el)
{
    ensureCapacity(l);
    l->elems[l->lg] = el;
    l->lg++;
}

void delete(MyList* l, int poz)
{
    DestroyCar(l->elems[poz]);
    for(int i = poz; i < l->lg - 1; i ++)
        l->elems[i] = l->elems[i+1];
    l->lg--;
}

void modify(MyList* l, int poz, char* numar1, char* model1, char* categorie1)
{
    DestroyCar(l->elems[poz]);
    (l->elems[poz]) = createCar(numar1, model1, categorie1);
}

int size(MyList * l)
{
    return l->lg;
}

ElemType get(MyList * l, int poz){
    return l->elems[poz];
}

void ensureCapacity(MyList * l)
{
    if (l->lg < l->cap)
        return;

    ElemType* nElems = malloc(sizeof(ElemType) * (l->cap + 2));

    for (int i = 0; i < l->lg; i++)
        nElems[i] = l->elems[i];

    free(l->elems);
    l->elems = nElems;
    l->cap += 2;
}

MyList* copyList(MyList * l, CopyFunction cp)
{
    MyList * rez = createEmpty(l->destf);
    for(int i = 0; i < l->lg; i ++)
    {
        ElemType c = get(l, i);
        add(rez, cp(c));
    }
    return rez;
}

ElemType removeLast(MyList * l)
{
    //grija la dealocare - se face la undo din service
    ElemType rez = l->elems[l->lg - 1];
    l->lg--;
    return rez;
}

void testeListaMasini()
{
    MyList* List = createEmpty((DestroyFunction) DestroyCar);
    assert(size(List) == 0);
    add(List, createCar("BN HUG 10", "Audi","SPORT"));
    assert(size(List) == 1);
    delete(List, 0);
    assert(size(List) == 0);
    destroy(List);
}

void testListeDeListe()
{
    MyList* masini1 = createEmpty((DestroyFunction) DestroyCar);
    add(masini1, createCar("BN HUG 10", "Audi", "sport"));
    add(masini1, createCar("TM DAV 50", "Toyata", "mini"));

    MyList* masini2 = createEmpty((DestroyFunction) DestroyCar);
    add(masini2, createCar("BN CAS 20", "Lambo", "suv"));

    MyList* undoL = createEmpty((DestroyFunction) destroy);
    add(undoL, masini1);
    assert(size(undoL) == 1);

    add(undoL, masini2);
    assert(size(undoL) == 2);

    destroy(masini1);
    destroy(masini2);
}