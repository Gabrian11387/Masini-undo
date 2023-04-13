#pragma once

typedef struct{
    char* numar;
    char* model;
    char* categorie;
}Car;

int valid(Car* A);

Car* createCar(char*, char*, char*);

void DestroyCar(Car* A);

Car* copyCar(Car* A);

void TesteCar();