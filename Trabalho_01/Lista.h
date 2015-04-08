#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

class Item {

    protected:
        Item *ant, *prox;
        int info;

    public:
        Item() { this->ant = this->prox = 0; } ;
        void setaProx(Item *prox) { this->prox = prox; };
        void setaAnt(Item *ant) { this->ant = ant; };
        void setaInfo(int info) { this->info = info; };
        Item* pegaProx() { return this->prox; };
        Item* pegaAnt() { return this->ant; };
        int pegaInfo() { return this->info; };

};

class Lista {

    protected:
        Item *pri, *ult, *it;
        int nitems;

    public:
        Lista() { this->pri = this->ult = 0; this->nitems = 0; } ;
        void adicionaItem(Item *n);
        void deletaItem(Item *n);
        Item *inicioLista() { it = pri; return it; };
        Item *fimLista() { it = ult; return it; };
        Item *noIterator() { return it; }
        Item *caminhaLista() { if (it) it = it->pegaProx(); return it; }
        Item *retornaLista() { if (it) it = it->pegaAnt(); return it; }
        int contaItems() { return this->nitems; }

};

#endif
