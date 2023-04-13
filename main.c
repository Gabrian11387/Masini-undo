#include <stdio.h>
#include <stdlib.h>
#include "masina.h"
#include "repo.h"
#include "service.h"

void meniu(){
    printf("0) Exit \n");
    printf("1) Adauga\n");
    printf("2) Afiseaza toate\n");
    printf("3) Sterge masina\n");
    printf("4) Modifica masina\n");
    printf("5) Undo\n");
    printf("Comanda:");
}

void Afis(Listele* lists) {
    if(lists->allCars->lg == 0)
        printf("Nu exista nicio masina in aplicatie!\n");
    for (int i = 0; i < lists->allCars->lg; i++) {
        Car *A = get(lists->allCars, i);
        printf("Masina %d)", i + 1);
        printf("Numarul:%s, ", A->numar);
        printf("Modelul:%s, ", A->model);
        printf("Categoria:%s", A->categorie);
        printf("\n");
    }
}


void run_ui()
{
    Listele lists = createCarStore();
    int ruleaza = 1;
    while(ruleaza)
    {
        meniu();
        char aux[30];
        int cmd;
        printf(">>>");
        scanf("%s", aux);
        cmd = strtol(aux, NULL, 10);
        switch (cmd)
        {
            case 1:
                printf("Numar inmatriculare:");
                char numar[30];
                scanf("%s", numar);

                printf("Model:");
                char model[30];
                scanf("%s", model);

                printf("Categorie:");
                char categorie[30];
                scanf("%s", categorie);
                int ok = addCar(&lists, numar, model, categorie);
                if(ok == -1)
                    printf("Masina nu este valida!\n");
                else
                    printf("Masina a fost adaugata!\n");
                break;
            case 2:
                Afis(&lists);
                break;
            case 3:
                printf("Numarul de ordine al masinii:\n");
                int poz;
                char aux1[30];
                scanf("%s", aux1);
                poz = strtol(aux1, NULL, 25);
                int ok1 = deleteCar(&lists, poz - 1);
                if(ok1 == -1)
                    printf("Numarul de ordine al masinii este invalid!\n");
                else
                    printf("Masina a fost stearsa!\n");

                break;
            case 4:
                printf("Numarul de ordine al masinii:\n");
                int poz1;
                char aux2[30];
                scanf("%s", aux2);
                poz1 = strtol(aux2, NULL, 25);
                printf("Plate:");
                char numar1[30];
                scanf("%s", numar1);

                printf("Model:");
                char model1[30];
                scanf("%s", model1);

                printf("Type:");
                char categorie1[30];
                scanf("%s", categorie1);

                if(modifyCar(&lists, poz1-1, numar1, model1, categorie1) == -1)
                    printf("Numar de ordine invalid!\n");
                else
                    printf("Masina a fost modificata cu succes!\n");
                ;
                break;
            case 5:
                if(undo(&lists) == -1)
                    printf("Nu mai puteti face undo!\n");
                else
                    printf("Undo-ul a fost realizat cu succes!\n");
                break;
            case 0:
                ruleaza = 0;
                break;
            default:
                printf("Comanda invalida! Incercati din nou\n");
        }
    }
    destroyStore(&lists);
}

int main()
{
    testeListaMasini();
    testListeDeListe();
    TesteService();
    TesteCar();
    run_ui();
    return 0;
}