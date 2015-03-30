#include "Lista.h"
#include <iostream>
using namespace std;

void Lista::adicionaItem(Item *n) {

    // Primeiro item
    if (this->nitems==0) {
        this->pri = n;
        n->setaAnt(0);
        n->setaProx(0);
        this->ult = n;
    }

    // Segundo item
    else if (this->nitems==1) {
        n->setaAnt(this->pri);
        n->setaProx(0);
        this->pri->setaProx(n);
        this->ult = n;
    }

    // Qualquer outro item
    else {
        this->ult->setaProx(n);
        n->setaAnt(this->ult);
        this->ult = n;
    }

    this->nitems++;  // Contador de items
}

void Lista::deletaItem(Item *n) {

    // Condições de saída imediata
    if (!n) return;
    if (!this->nitems) return;

    // Tem apenas 1 elemento
    if (this->nitems==1) {
        this->pri = this->ult = 0;
    }

    // Tem apenas 2 elementos
    else if (this->nitems==2) {
        if (n==this->pri) {            // É o primeiro da lista
            this->pri = this->ult;
            this->pri->setaAnt(0);
            this->pri->setaProx(0);
        }
        else {                         // É o ultimo da lista
            this->ult = this->pri;
            this->ult->setaAnt(0);
            this->ult->setaProx(0);
        }
    }

    // Para qualquer outra quantidade de elementos
    else {
        Item *a = n->pegaAnt();  // Anterior a N
        Item *p = n->pegaProx(); // Sucessor de N
        if (a) a->setaProx( p );
        if (p) p->setaAnt( a );
        if (n==this->ult) this->ult = n->pegaAnt();
        if (n==this->pri) this->pri = n->pegaProx();
    }

    // Relocar o iterator caso estejamos deletando o ponteiro para o qual ele aponta
    if (n==this->it) {
        if (n->pegaAnt()) this->it = n->pegaAnt();
            else if (n->pegaProx()) this->it = n->pegaProx();
                else this->it=0;
    }

    this->nitems--; // Contador de items

    //delete n;

}



