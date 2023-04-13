#include "masina.h"
#include "stdlib.h"
#include "string.h"
#include "assert.h"

Car* createCar(char* numar, char* model, char* categorie)
{
    Car* rez = malloc(sizeof(Car));

    size_t nrC = strlen(numar) + 1;
    rez->numar = malloc(sizeof(char) * nrC);
    strcpy(rez->numar, numar);

    nrC = strlen(model) + 1;
    rez->model = malloc(sizeof(char) * nrC);
    strcpy(rez->model, model);

    nrC = strlen(categorie) + 1;
    rez->categorie = malloc(sizeof(char) * nrC);
    strcpy(rez->categorie, categorie);

    return rez;
}

void DestroyCar(Car* A)
{
    free(A->numar);
    free(A->model);
    free(A->categorie);
    free(A);
}

Car* copyCar(Car* A)
{
    return createCar(A->numar, A->model, A->categorie);
}

int valid(Car* A)
{
    if(strlen(A->numar) == 0)
        return -1;
    if(strlen(A->categorie) == 0)
        return -1;
    if(strlen(A->model) == 0)
        return -1;
    if(strcmp(A->categorie, "mini") !=0 && strcmp(A->categorie, "sport") != 0 && strcmp(A->categorie, "suv") != 0)
        return -1;
    return 0;
}

void TesteCar()
{
    Car* A = createCar("BN GAB 10", "BMW", "mini");
    assert(strcmp(A->numar, "BN GAB 10") == 0);
    assert(strcmp(A->model, "BMW") == 0);
    assert(strcmp(A->categorie, "mini") == 0);
    Car* C = createCar("BN GAB 10", "BMW", "Mini");
    assert(valid(C) == -1);
    Car* B = copyCar(A);
    DestroyCar(A);
    DestroyCar(B);
    DestroyCar(C);
}


