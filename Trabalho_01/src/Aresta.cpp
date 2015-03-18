#include "Lista.h"
#include "Vertice.h"
#include "Aresta.h"

class Aresta: public No {

    private:
        Vertice *origem;

    public:
        Aresta(Vertice *origem);

};

// Constroi nó da aresta e seta sua origem
Aresta::Aresta(Vertice *origem):No() {

    this->origem = origem;

}
