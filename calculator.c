#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void adunare(int *nr1, int *nr2, int *rezultat, int dim, int *dim_rez) {
    int suma = 0, trecere_ordin = 0;
    *dim_rez = dim;
    for(int i = dim - 1; i >= 0; i--) {
        suma = nr1[i] + nr2[i] + trecere_ordin;
        rezultat[i] = suma % 10;
        if(suma > 9) {
            trecere_ordin = 1;
        }
        else trecere_ordin = 0;
    }
    if(trecere_ordin == 1) {
        for(int i = dim; i > 0; i--) rezultat[i] = rezultat[i - 1];
        rezultat[0] = 1;
        *dim_rez++;
    }
}

int comparare(int *nr1, int *nr2, int dim) {
    for(int i = 0; i < dim; i++) {
        if(nr1[i] > nr2[i])return 1;
        if(nr1[i] < nr2[i])return 2;
    }
}

void scadere(int *descazut, int *scazator, int *rezultat, int dim, int *dim_rez) {
    int dif = 0, trecere_ordin = 0;
    *dim_rez = dim;
    for(int i = dim - 1; i >= 0; i--) {
        dif = descazut[i] - scazator[i] - trecere_ordin;
        rezultat[i] = (dif + 10) % 10;
        if(dif < 0) trecere_ordin = 1;
        else trecere_ordin = 0;
    }
}

int main() {
    char sir1[10005] = "\0", sir2[10005] = "\0", *rez;
    char semn_operatie = '\0', semn_nr1 = '\0', semn_nr2 = '\0', semn_rezultat = '\0';
    int *nr1 = NULL,  *nr2 = NULL, *rezultat;
    scanf("%c", &semn_operatie);
    scanf("%s", sir1);
    scanf("%s", sir2);
    int dim1 = 0, dim2 = 0, dim_max = 0, dim_rez = 0;
    dim1 = strlen(sir1);
    dim2 = strlen(sir2);
    
    //am alocat vectorii care reprezinta numerele si rezultatul lor
    if(dim1 > dim2) dim_max = dim1;
    else dim_max = dim2;
    rezultat = calloc(dim_max + 1, sizeof(int *));
    nr1 = calloc(dim_max, sizeof(int *));
    nr2 = calloc(dim_max, sizeof(int *));
    rez = malloc(dim_max * sizeof(char *));

    //aflu semnul primului numar si initializez vectorul cu cifrele numarului
    if(sir1[0] > '0' && sir1[0] <= '9') {
        semn_nr1 = '+';
        int ct = dim_max - 1;
        for(int i = dim1 - 1; i >= 0; i--) {
            nr1[ct] = sir1[i] - '0';
            ct--;
        }
    }
    else {
        semn_nr1 = '-';
        int ct = dim_max - 1;
        for(int i = dim1 - 1; i >= 1; i--) {
            nr1[ct] = sir1[i] - '0';
            ct--;
        }
        dim1--;
    }

    //aflu semnul celui de-al doliea numar si initializez vectorul cu cifrele numarului
    if(sir2[0] > '0' && sir2[0] <= '9') {
        semn_nr2 = '+';
        int ct = dim_max - 1;
        for(int i = dim2 - 1; i >= 0; i--) {
            nr2[ct] = sir2[i] - '0';
            ct--;
        }
    }
    else {
        semn_nr2 = '-';
        int ct = dim_max - 1;
        for(int i = dim2 - 1; i >= 1; i--) {
            nr2[ct] = sir2[i] - '0';
            ct--;
        }
        dim2--;
    }

    //verific ce operatie execut
    if(semn_operatie == '+') {
        if(semn_nr1 == semn_nr2) {   //daca cele 2 numere au acelasi semn, le adun, iar rezultatul va avea semnului primului numar
            semn_rezultat = semn_nr1;
            adunare(nr1, nr2, rezultat, dim_max, &dim_rez);
        }
        else {          //numerele au semne diferite, se compara, se scad si rezultatul are semnul numarului mai mare
            if(comparare(nr1, nr2, dim_max) == 1) {
                semn_rezultat = semn_nr1;
                scadere(nr1, nr2, rezultat, dim_max, &dim_rez);
            }
            if(comparare(nr1, nr2, dim_max) == 2) {
                semn_rezultat = semn_nr2;
                scadere(nr2, nr1, rezultat, dim_max, &dim_rez);
            }
        }
    }
    else {
        if(semn_nr1 == semn_nr2) {   //daca cele 2 numere au acelasi semn, se compara, se scad si rezultatul are semnul numarului mai mare
            if(comparare(nr1, nr2, dim_max) == 1) {
                semn_rezultat = semn_nr1;
                scadere(nr1, nr2, rezultat, dim_max, &dim_rez);
            }
            if(comparare(nr1, nr2, dim_max) == 2) {
                semn_rezultat = semn_nr2;
                scadere(nr2, nr1, rezultat, dim_max, &dim_rez);
            }
        }
        else {          //numerele au semne diferite, le adun, iar rezultatul va avea semnului primului numar
            semn_rezultat = semn_nr1;
            adunare(nr1, nr2, rezultat, dim_max, &dim_rez);   
        }
    }

    //construiesc numarul rezultat
    if(semn_rezultat == '+') {
        int i = 0, j = 0;
        while(i < dim_rez) {
            if(rezultat[i] == 0) i++;
            else break;
        }
        while(i < dim_rez) {
            rez[j] = rezultat[i] + '0';
            j++;
            i++;
        }
        rez[j] = '\0';
    }
    else {
        rez[0] = '-';
        int i = 0, j = 1;
        while(i < dim_rez) {
            if(rezultat[i] == 0) i++;
            else break;
        }
        while(i < dim_rez) {
            rez[j] = rezultat[i] + '0';
            j++;
            i++;
        }
        rez[j] = '\0';
    }
    printf("%s", rez);
}