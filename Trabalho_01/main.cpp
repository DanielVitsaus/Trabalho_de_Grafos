#include <iostream>
#include "Lista.h"
#include "Grafo.h"
#include "Arquivo.h"

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
    //Item *i1;
    Arquivo *ar = new Arquivo();
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

    g1 = ar->lerArquivo();
    ar->gravaArquivo();

    // Cria 5 mil nós
    /*
    for (i=0;i<10;i++) {
        g1->adicionaNo(i);
        cout << "CRIEI NO " << i;
        if (i>0) {
            g1->adicionaAresta(i, i-1);
            cout << ", COM ARESTA " << i << " - " << i-1 << endl;
        } else cout << endl;
    }
    */
    //g1->adicionaAresta(9 , 0);
    /*
    g1->adicionaAresta(0 , 2);
    g1->adicionaAresta(0 , 3);
    g1->adicionaAresta(1 , 3);
*/
/////////////////////////////////////////////////////////////////////////////////
/*
    g1->adicionaNo(10);
    g1->adicionaNo(11);
    g1->adicionaNo(12);
    g1->adicionaNo(13);
    //g1->adicionaNo(14);

    g1->adicionaAresta(12, 13);
    g1->adicionaAresta(10, 11);
    g1->adicionaAresta(10, 12);
    g1->adicionaAresta(13, 11);
*/
/////////////////////////////////////////////////////////////////////////////////////////////

    if(g1->conexo())
    {
        cout << "\n eh conexo\n" << endl;
    }
    else
        cout << "\nnao eh conexo" << endl;

/////////////////////////////////////////////////////////////////////////////////

    if (g1->mesmaComponenteConexa(11,13))
    {
        cout << "\n Mesma componente!! \n" << endl;
    }
    else
    {
        cout << "\n Não esta na mesma componente!! \n" << endl;
    }

////////////////////////////////////////////////////////////////////////////
    /* ok
    if (g1->completo())
    {
        cout << "\n eh completo \n" << endl;
    }
    else
    {
        cout << "\n nao eh completo \n "<< endl;
    }
    */
////////////////////////////////////////////////////////////////////////////
    /* ok
    if (g1->arestaPonte(9, 13))
    {
        cout << "\n A aresta eh ponte \n" << endl;
    }
    else
    {
        cout << "\n nao eh ponte \n "<< endl;
    }
    */
////////////////////////////////////////////////////////////////////////////
    /*ok
    if (g1->noArticulacao(12))
        cout << "\n O no eh articulação\n" << endl;
    else
        cout << "\n O no nao eh articulação\n" << endl;
        */

////////////////////////////////////////////////////////////////////////
    /* ok
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
        cout << "\n são ad \n" << endl;
    }
    else
    {
        cout << "\n não é ad\n" << endl;
    }
    */
//////////////////////////////////////////////////////////////////////////////////
    cout << g1->contaNos() << endl;

//////////////////////////////////////////////////////////////////////////////////
    i=0;
    for (i=0;i<g1->contaNos();i++) {
        g1->removeNo(i);
    }

    delete g1;

    return 0;
}





