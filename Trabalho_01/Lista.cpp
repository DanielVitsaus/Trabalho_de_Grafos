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

    if (n==0) return;

    // Vai deletar o ultimo item
    if (this->nitems==1) this->pri = this->ult = 0;

    // Vai deletar o penultimo item
    else if (this->nitems==2) {
        if (n==this->pri) {
            this->pri = this->ult;
            this->pri->setaAnt(0);
            this->pri->setaProx(0);
        }
        else {
            this->ult = this->pri;
            this->ult->setaAnt(0);
            this->ult->setaProx(0);
        }
    }

    // Vai deletar qualquer outro item
    else if (n==this->it) {
        if (n->pegaProx()) it = n->pegaProx();
        else if (n->pegaAnt()) it = n->pegaAnt();
        else it = pri;
    }

    Item *a = n->pegaAnt();  // Anterior a N
    Item *p = n->pegaProx(); // Sucesso de N

    if (a) a->setaProx( p );
    if (p) p->setaAnt( a );

    this->nitems--; // Contador de items

    delete n;


}



