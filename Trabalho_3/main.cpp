#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <time.h>
#include "rnd.h"
#include "Grafo.h"
#include "Arquivo.h"

using namespace std;

#define INI_CRONO() ti = time(NULL);

#define FIM_CRONO()             \
        tf = time(NULL);        \
        sec = difftime(tf, ti);

int main(int argc, char** argv)
{
    Arquivo *arq = new Arquivo();
    Grafo *mapa;
    int idbase = coordToId(0, 0);
    time_t ti, tf;
    double sec;
    vector <int> *solucao, *melhor;
    unsigned int melhor_nos;
    double melhor_custo, atual;
    char melhor_algo;

    // Sem argumentos le default.map
    if (argc==1) {
        mapa = arq->lerArquivo("default.map");
    // Com um argumento, le arquivo no argumento
    } else if (argc==2) {
        mapa = arq->lerArquivo(argv[1]);
    // Qualquer outra coisa, exibe sintaxe e sai
    } else {
        cout << "Sintaxe: Trabalho3 nome_do_arquivo.map" << endl;
        return -1;
    }

    Vertice *v, *u = mapa->adicionaNo(idbase);
    int j, i = 0, *id = new int[mapa->contaNos()];

    // Após ler instancia, lista todas as ID
    cout << "Coletando ids..." << endl;
    for (v=mapa->ultimoNo(); v; v=mapa->noAnterior()) {
        id[i++] = v->pegaId();
    }

    // Torna o grafo completo criando arestas entre todos os nós, sendo os pesos das arestas as distâncias (em unidades de tempo)
    cout << "Inserindo arestas..." << endl;
    for (j=0; j<mapa->contaNos(); j++)
        for (i=0; i<mapa->contaNos(); i++)
                if (i>j) {
                mapa->adicionaAresta(id[j], id[i]);
                }
    delete [] id;
    cout << "Grafo completo ? "<< mapa->completo() << endl;

    // Remove nós inalcançaveis
    cout << "Removendo nos inalcançaveis... " << flush;
    int nos_removidos = 0;
    for (Aresta *a=u->primeiraAresta(); a; a=u->proximaAresta()) {
        if ( a->pegaPeso() > ((max_bateria/2)+sobra_bateria) ) {
            nos_removidos++;
            mapa->removeNo(a->pegaIdDestino());
        }
    }
    cout << nos_removidos << " removidos. " << endl;

    // Mostra base
    cout << "Base em (" << idToX(idbase) << "," << idToY(idbase) << ")" << endl << endl;

    // Solução 1 - Algoritmo guloso
    cout << "Aplicando solucao por algoritmo guloso..." << endl;
    INI_CRONO();
    melhor = solucao = mapa->Guloso(idbase, 0);
    FIM_CRONO();
    cout << "Guloso concluído em " << sec << " segundos. " << endl;
    melhor_nos = solucao->size();
    cout << "A solução contém " <<  melhor_nos << " nos, " << melhor_nos-mapa->contaNos() << " recargas. " << endl;
    melhor_custo =  mapa->CustoTotal(solucao);
    cout << "Custo total da solução " << melhor_custo << endl << endl;
    melhor_algo = 'G';

    // Solução 2 - Algoritmo guloso randomizado, alfa = 0.5%
    cout << "Aplicando solucao por algoritmo guloso randomizado, alfa = 0.6%" << endl;
    INI_CRONO();
    solucao = mapa->Guloso(idbase, 0.6);
    FIM_CRONO();
    cout << "Guloso Randomizado concluído em " << sec << " segundos. " << endl;
    if (solucao->size()<melhor_nos) melhor_nos = solucao->size();
    cout << "A solução contém " << solucao->size() << " nos, " << solucao->size()-mapa->contaNos() << " recargas. " << endl;
    atual = mapa->CustoTotal(solucao);
    if (atual<melhor_custo) {
        melhor_custo = atual;
        delete melhor;
        melhor = solucao;
        melhor_algo = 'R';
    }
    cout << "Custo total da solução " << melhor_custo << endl << endl;

    // Solução 3 - Algoritmo guloso randomizado (iter = 100, maxpct = 2); (em intervalos de 0.5 com 100 interações cada)
    cout << "Aplicando solucao por GRASP (iteracoes = 50, [0.5% < alfa < 2%])" << endl;
    INI_CRONO();
    solucao = mapa->GRASP(idbase, 50, 2);
    FIM_CRONO();
    cout << "GRASP concluído em " << sec << " segundos. " << endl;
    if (solucao->size()<melhor_nos) melhor_nos = solucao->size();
    cout << "A solução contém " << solucao->size() << " nos, " << solucao->size()-mapa->contaNos() << " recargas. " << endl;
    atual = mapa->CustoTotal(solucao);
    if (atual<melhor_custo) {
        melhor_custo = atual;
        delete melhor;
        melhor = solucao;
        melhor_algo = 'A';
    }
    cout << "Custo total da solução " << melhor_custo << endl << endl;

    // Responde qual algoritmo teve melhor solução
    cout << "Melhor solução apresentada pelo algoritmo ";
    switch (melhor_algo) {
        case 'A':
            cout << "GRASP" << endl;
            break;

        case 'R':
            cout << "Guloso Randomizado" << endl;
            break;

        case 'G':
            cout << "Guloso" << endl;
            break;
    }

    // Libera memória para finalizar programa
    delete melhor;
    delete mapa;
    delete arq;
    return 0;
}

