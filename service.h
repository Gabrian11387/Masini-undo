#pragma once
#include "repo.h"

typedef struct{
    MyList* allCars;
    MyList* undoList;
}Listele;

Listele createCarStore();

void destroyStore(Listele* lists);

int addCar(Listele* lists, char* numar, char* model, char* categorie);

int deleteCar(Listele* lists, int poz);

int modifyCar(Listele* , int poz,char* numar1, char* model1, char* categorie1);

int undo(Listele* lists);

int updateCar(Listele* lists, char* numar, char* model, char* categorie);

void TesteService();

void testUndo();
