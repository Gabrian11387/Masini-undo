#include "service.h"
#include "repo.h"
#include "assert.h"
#include "string.h"
#include "masina.h"
#include "stdio.h"

Listele createCarStore()
{
    Listele rez;
    rez.allCars = createEmpty((DestroyFunction) DestroyCar);
    rez.undoList = createEmpty((DestroyFunction) destroy);
    return rez;
}

void destroyStore(Listele* lists)
{
    destroy(lists->allCars);
    destroy(lists->undoList);
}

int addCar(Listele* lists, char* numar, char* model, char* categorie)
{
    Car* A = createCar(numar, model, categorie);
    if(valid(A) == -1)
        return -1;

    MyList* copieListaMasini = copyList(lists->allCars, (CopyFunction) copyCar);
    add(lists->allCars, A);
    add(lists->undoList, copieListaMasini);

    return 0;
}

int deleteCar(Listele* lists, int poz)
{
    if(poz >= lists->allCars->lg)
        return -1;

    MyList* copieListaMasini = copyList(lists->allCars, (CopyFunction) copyCar);
    delete(lists->allCars, poz);
    add(lists->undoList, copieListaMasini);

    return 0;
}

int modifyCar(Listele* lists, int poz, char* numar1, char* model1, char* categorie1)
{
    if(poz >= lists->allCars->lg)
        return -1;

    MyList* copieListaMasini = copyList(lists->allCars, (CopyFunction) copyCar);
    modify(lists->allCars, poz, numar1, model1, categorie1);
    add(lists->undoList, copieListaMasini);

    return 0;
}

int undo(Listele* lists)
{
    if(size(lists->undoList) == 0)
        return -1;

    MyList* ultimaLista = removeLast(lists->undoList);
    destroy(lists->allCars);
    lists->allCars = ultimaLista;
    return 0;
}

void TesteService()
{
    Listele list = createCarStore();
    assert(addCar(&list, "", "Ferrari", "sport") == -1);
    assert(addCar(&list, "CJ01AAA", "", "sport") == -1);
    assert(addCar(&list, "CJ01AAA", "Ferrari", "") == -1);
    assert(addCar(&list, "CJ01AAA", "Ferrari", "sport") == 0);
    assert(size(list.allCars) == 1);
    assert(size(list.undoList) == 1);
    assert(deleteCar(&list, 5) == -1);
    deleteCar(&list, 0);
    assert(size(list.allCars) == 0);
    assert(size(list.undoList) == 2);
    addCar(&list, "CJ01AAA", "Ferrari", "sport");
    assert(size(list.undoList) == 3);
    assert(modifyCar(&list, 5, "", "", "") == -1);
    modifyCar(&list, 0, "BN091AAA", "BMW", "mini");
    assert(size(list.undoList) == 4);
    undo(&list);
    assert(size(list.undoList) == 3);

    undo(&list);
    assert(size(list.undoList) == 2);

    undo(&list);
    assert(size(list.undoList) == 1);

    undo(&list);
    assert(size(list.undoList) == 0);
    assert(undo(&list) == -1);

    destroyStore(&list);
}