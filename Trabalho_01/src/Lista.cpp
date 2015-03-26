#include "Lista.h"

void Lista::adcNo() {

    No *n = new No();

    if (this->pri==0) this->pri=n;
    else {
        n->setaAnt(this->ult);
        this->ult->setaProx(n);
        this->ult = n;
    }

    this->nitems++;

}

void Lista::delNo(No *n) {

    No *a = n->pegaAnt();  // Anterior a N
    No *p = n->pegaProx(); // Sucesso de N

    a->setaProx( p );
    p->setaAnt( a );

    this->nitems--;

    delete n;

}




