#include "Lista.h"

Lista::~Lista() {

    this->fimLista();
    do { this->deletaItem(this->it); } while (this->retornaLista());

}

void Lista::adicionaItem(Item *n) {

    // Primeiro item
    if (this->nitems==0) {
        this->pri = n;
        n->setaAnt(0);
        n->setaProx(0);
        this->ult = 0;
    }

    // Segundo item
    else if (this->nitems==1) {
        this->ult = n;
        n->setaAnt(this->pri);
        n->setaProx(0);
        this->pri->setaProx(n);
    }

    // Qualquer outro item
    else {
        n->setaAnt(this->ult);
        n->setaProx(0);
        this->ult->setaProx(n);
        this->ult = n;
    }

    this->nitems++;  // Contador de items

}

void Lista::deletaItem(Item *n) {

    if (n==0) return;

    if (n==this->it) {
        if (n->pegaProx()!=0) it = n->pegaProx();
        else if (n->pegaAnt()!=0) it = n->pegaAnt();
        else it = pri;
    }

    Item *a = n->pegaAnt();  // Anterior a N
    Item *p = n->pegaProx(); // Sucesso de N

    if (a!=0) a->setaProx( p );
    if (p!=0) p->setaAnt( a );

    this->nitems--; // Contador de items

    delete n;

}




