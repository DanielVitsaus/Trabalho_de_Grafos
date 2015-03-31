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

    //Lista *l1 = new Lista();
    Item *i1;
    Grafo *g1;
    int i;
/*
    // Adiciona 5 milhões de items na lista
    for (i=0; i<50000; i++) {
        i1 = new Item();
        i1->setaInfo(i);
        l1->adicionaItem(i1);
        //cout << i+1 << endl;  // Contagem
    }
    cout << "." << endl;

    // Percorre lista de tras pra frente deletando items
    l1->fimLista();
    do {
        //cout << l1->noIterator()->pegaInfo() << endl; // Contagem regressiva
        l1->deletaItem(l1->noIterator());
    } while (l1->contaItems());

    delete l1; */


    /*
                -----  TESTE DAS FUNÇÕES DE GRAFO -----

    */

    g1 = new Grafo();

    // Cria 5 mil nós
    for (i=0;i<10;i++) {
        g1->adicionaNo(i);
        cout << "CRIEI NO " << i;
        if (i>0) {
            g1->adicionaAresta(i, i-1);
            cout << ", COM ARESTA " << i << " - " << i-1 << endl;
        } else cout << endl;
    }
    g1->adicionaAresta(9, 0);

    // Percorre deletando todos os nós...

    bool te,te2;
    te = g1->kRegular();
    te2 = g1->nosSaoAdjacentes(1 , 0);

    if (te)
    {
        cout << "\né k-regular" << endl;
    }
    else
    {
        cout << "não é k-regular" << endl;
    }

    if (te2)
    {
        cout << "\nsão ad" << endl;
    }
    else
    {
        cout << "\nnão é ad\n" << endl;
    }

    cout << g1->contaNos();

    i=0;
    for (i=0;i<5000;i++) {
        g1->removeNo(i);
    }

    delete g1;

    return 0;
}





