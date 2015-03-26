#include "Grafo.h"

/* -------------------------------------------- CLASSE GRAFO ------------------------------------------ */

// Encontra um Vertice com a id dada
Vertice* Grafo::encontraNo(int id) {

        Vertice *v = (Vertice*)this->inicioLista();

        while (v) {
            if (v->pegaInfo()==id) break;
            else v = (Vertice*)this->caminhaLista();
        }

        return v;
}

// Adiciona um Vertice com a id dada caso não exista
Vertice* Grafo::adicionaNo(int id) {

    Vertice *v = this->encontraNo(id); // Tenta encontrar Vertice com essa id

    if (v==0) {  // Se não encontrou, cria...
        v = new Vertice(id);
        this->adicionaItem(v);
    }

    return v;

}

// Adiciona uma aresta em id_origem, apontando para id_destino
void Grafo::adicionaAresta(int id_origem, int id_destino) {

    Aresta *a;
    Vertice *vd, *vo = this->encontraNo(id_origem);  // Procura nó com id id_orgiem
    if (vo) vd = this->encontraNo(id_destino);      //    ...     ...    id_destino

    if (vd&&vo) { // Se encontrar, adiciona arestas nos dois vertices

        a = new Aresta(id_destino);
        vo->adicionaItem(a);
        vo->incGrau();

        a = new Aresta(id_origem);
        vd->adicionaItem(a);
        vd->incGrau();

    }

}

// Procura o Vertice que possui a id dada, e deleta caso encontre
void Grafo::removeNo(int id) {

    // encontra nó com vertice id
    Vertice *v = this->encontraNo(id), *v2;
    Aresta *a, *a2;


    // Se existir, remove todas as Arestas dos Vertices ligados a ele...
    if (v) {


        a = (Aresta*)v->inicioLista();

        while (a) {

            // Pega ID do Vertice que contem essa Aresta, e localiza o Vertice
            v2 = this->encontraNo(a->pegaIdDestino());

            if (v2) {

                // Percorre o Vertice em busca da Aresta, e exclui
                a2 = (Aresta*)v2->inicioLista();

                while (a2) {
                    if (a2->pegaIdDestino()==id) {
                        v2->deletaItem(a2);
                        v2->decGrau();
                        break;
                    }
                    else a2 = (Aresta*)v2->caminhaLista();
                }
            }

            // Proxima Aresta...
            a = (Aresta*)v->caminhaLista();

        }


        /**----------------------------------------------------------------------------------------------------------
        // CÓDIGO ALTERNATIVO...

        v2 = (Vertice*)this->inicioLista();

        // Percorre o Grafo em busca de algum Vertice com Aresta que aponte para o nó que está sendo removido

        while (v2) {

            // Percorre Vertice em busca de Arestas apontando para esse nó
            a = (Aresta*)v2->inicioLista();
            while (a) {
                // Se id for a do Vertice sendo deletado, deleta Aresta
                if (a->pegaIdDestino()==id) {
                    v2->deletaItem(a);
                    break;
                }
                // Senão for o id... proxima aresta!
                else a = (Aresta*)v2->caminhaLista();
            };

            // Proximo Vertice !
            v2 = (Vertice*)this->caminhaLista();
        };

        --------------------------------------------------------------------------------------------------------------------**/

        // Finalmente... deleta Vertice do Grafo
        this->deletaItem((Item*)v);
    }

}

// Remove uma aresta entre dois vertices
void Grafo::removeAresta(int id_no1, int id_no2) {

    //  Encontra os Vertices com as id's dadas, no grafo
    Vertice *v1 = this->encontraNo(id_no1);
    Vertice *v2 = this->encontraNo(id_no2);

    // Percorre primeiro Vertice em busca da Aresta
    v1->inicioLista();
    while (v1->noIterator()) {
        if (v1->noIterator()->pegaInfo()==id_no2) break;
        v1->caminhaLista();
    }
    if (v1->noIterator()) {
        v1->decGrau();
        v1->deletaItem(v1->noIterator());  // se encontrar, deleta
    }

    // Percorre segundo Vertice em busca da Aresta
    v2->inicioLista();
    while (v2->noIterator()) {
        if (v2->noIterator()->pegaInfo()==id_no1) break;
        v2->caminhaLista();
    }
    if (v2->noIterator()) {
        v2->decGrau();
        v2->deletaItem(v2->noIterator()); // se encontrar, deleta
    }

}

// Grau de um nó
int Grafo::grauNo(int id) {

    Vertice *v = this->encontraNo(id);

    if (v!=0) {
        return v->pegaGrau();
    }

    return 0;
}

/* ---------------------------------------- CLASSE VERTICE --------------------------------------- */



/* ---------------------------------------- CLASSE ARESTA ---------------------------------------- */


