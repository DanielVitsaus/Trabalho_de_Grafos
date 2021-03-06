#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

class Item {

    protected:
        Item *ant; ///< Item anterior
        Item *prox; ///< Proximo item
        int info; ///< Representecao do vertice

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
        Item *pri; ///< Primeiro elemento da lista
        Item *ult; ///< Ultimo elemento da lista
        Item *it; ///< Interador
        int nitems; ///< Numeros de Itens
        int nunitemsDecre; ///< Numeros de Itens

    public:
        Lista() { this->pri = this->ult = 0; this->nitems = 0; this->nunitemsDecre = 0;} ;
        void adicionaItem(Item *n);
        void deletaItem(Item *n);
        void iniciaNumItemDecre(){ this->nunitemsDecre = this->nitems; };
        void decrementaItem() { this->nunitemsDecre > 0 ? this->nunitemsDecre-- : this->nunitemsDecre = 0;}; //if (this->nunitemsDecre > 0){this->nunitemsDecre--;}else{this->nunitemsDecre = 0;} };
        Item *inicioLista() { it = pri; return it; };
        Item *fimLista() { it = ult; return it; };
        Item *noIterator() { return it; };
        Item *caminhaLista() { if (it) it = it->pegaProx(); return it; };
        Item *retornaLista() { if (it) it = it->pegaAnt(); return it; }
        int contaItems() { return this->nitems; };
        int contaItemsDecre() { return this->nunitemsDecre; };

};

#endif
