#include <iostream>
#include "Lista.h"
#include "Grafo.h"

using namespace std;

/*

    Listas são compostas de Items.
    Listas são representações de grafos, Logo Grafos são Listas.  --> Herança simples
    Vertices são Listas de Arestas, e Items dos Grafos.  --> Herança multipla
    Arestas são Items dos Vertices.  --> Herança simples

*/

int main()
{

    /*
            --------       TESTE DAS FUNÇÕES DE LISTA   ----------
    */

    Lista *l1 = new Lista();
    Item *i1;
    Grafo *g1;
    int i;

    // Adiciona 5 milhões de items na lista
    for (i=0; i<10123123; i++) {
        i1 = new Item();
        i1->setaInfo(i+1);
        l1->adicionaItem(i1);
        //cout << i << endl;  // Contagem
    }

    // Percorre lista de tras pra frente deletando items
    l1->fimLista();
    i = 0;
    do {
        //cout << l1->noIterator()->pegaInfo() << endl; // Contagem regressiva
        l1->deletaItem(l1->noIterator());
    } while (l1->retornaLista());

    /*
                -----  TESTE DAS FUNÇÕES DE GRAFO -----
    */

    g1 = new Grafo();

    // Cria 10 mil nós
    for (i=0;i<10000;i++) {
        g1->adicionaNo(i+1);
    }

    // Percorre do 1 até o 9999, criando uma Aresta do atual, com o anterior
    for (i=1;i<10000;i++) {
        g1->adicionaAresta(i, i-1);
    }

    // Percorre deletando todos os nós... (AINDA ESTOU COM PROBLEMAS AQUI...)
    /**
    i=0;
    for (i=0;i<10000;i++) {
        cout << i << endl;
        g1->removeNo(i);
    }**/

    return 0;
}





