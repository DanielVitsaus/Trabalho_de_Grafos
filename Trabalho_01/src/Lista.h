#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include "Vertice.h"

class No {

    protected:
        No *ant, *prox;

    public:
        No() { this->ant = this->prox = 0; } ;
        //~No() {  }
        void setaProx(No *prox) { this->prox = prox; };
        void setaAnt(No *ant) { this->ant = ant; };
        No* pegaProx() { return this->prox; };
        No* pegaAnt() { return this->ant; };

};

class Lista {

    protected:
        No *pri, *ult, *it;
        int nitems;

    public:
        Lista() { this->pri = this->ult = 0; this->nitems = 0; } ;
        ~Lista();
        void adcNo();
        void delNo(No *n);
        No *primeiroNo() { it = pri; return this->pri; };
        No *ultimoNo() { it = ult; return this->ult; };
        No *proximoNo() { if (it!=0) it = it->pegaProx(); return it; }
        No *noAnterior() { if (it!=0) it = it->pegaAnt(); return it; }
        int contaNos() { return this->nitems; }


};

#endif
