#include "Grafo.h"
#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <limits>
#include "rnd.h"
using namespace std;

///* -------------------------------------------- CLASSE GRAFO ------------------------------------------ *///
//#define DEBUG

/** \brief Solução gulosa randomizada reativa
 * \param int idbase
 * \param int iter
 * \param double maxpct
 * \return vector<int> *melhor
 */
vector<int>* Grafo::GRASP(int idbase, int iter, double maxpct) {

    vector <int> *solucao, *melhor = NULL;
    double atual, melhor_custo, pct = maxpct;
    unsigned int i, melhor_nos = 0xFFFFFFFF;
    melhor_custo =  std::numeric_limits<double>::max();

    while (pct>0) {
        i = iter;
        while (i--) {
            solucao = this->Guloso(idbase, pct);
            if (solucao->size()<melhor_nos) melhor_nos = solucao->size();
            atual = this->CustoTotal(solucao);
            if (atual<melhor_custo) {
                melhor_custo = atual;
                if (melhor) delete melhor;
                melhor = solucao;
            }
        }
        pct -= 0.5;
    }

    return melhor;
}

/** \brief Solução gulosa (e randomizada, para pct>0) para o problema
 * \param int idbase
 * \param double pct
 * \return vector<int> *resposta
 */
vector<int>* Grafo::Guloso(int idbase, double pct) {

    vector <int> *resposta = new vector <int>;
    vector <int> visitados;
    int posicao, i;
    double bateria;
    Rnd *rand = new Rnd();

    if (this->contaNos()<=2) return NULL;

    // Pega lista de ID's, e seta nos como nao visitados
    i = 0;
    int *id = new int [this->contaNos()];
    for (Vertice *v=this->primeiroNo(); v; v=this->proximoNo()) {
        id[i++] = v->pegaId();
        v->setaVisitado(false);
    }

    // Inicializa robo na base com maximo de bateria
    posicao = idbase;
    bateria = max_bateria;

    while (true) {

        #ifdef DEBUG
        cout << " --------- " << endl;
        #endif

        // Encontra ponteiro para o nó atual
        Vertice *v = this->encontraNo(posicao);
        v->setaVisitado(true);
        resposta->push_back(posicao);
        #ifdef DEBUG
        cout << "Estou em " << posicao << " (" << v << ")" << endl;
        #endif

        // Se estamos na base, carrega bateria
        if (posicao==idbase) {
            bateria = max_bateria;
            #ifdef DEBUG
            cout << "Bateria recarregada !!!" << endl;
            #endif // DEBUG
        }

        // Checa se todos os nós ja foram visitados
        if (this->visitouTodosNos()) {
            if (posicao!=idbase) {
                #ifdef DEBUG
                cout << "Terminei todos os nós, voltando para a base." << endl;
                #endif // DEBUG
                bateria -= v->encontraAresta(idbase)->pegaPeso();
                resposta->push_back(idbase);
                break;
            }
        }

        // Encontra primeira aresta cujo nó não tenha sido visitado e não seja base
        #ifdef DEBUG
        cout << "Encontrando aresta nao visitada ";
        #endif // DEBUG
        Aresta *menor = v->primeiraAresta();
        while (std::find(resposta->begin(), resposta->end(), menor->pegaIdDestino()) != resposta->end()) {
            menor = v->proximaAresta();
            #ifdef DEBUG
            cout << "." << flush;
            #endif // DEBUG
        }
        #ifdef DEBUG
        cout << endl;
        #endif // DEBUG

        // Encontra MENOR aresta cujo no não tenha sido visitado e nao seja base
        #ifdef DEBUG
        cout << "Procurando menor aresta... " << endl;
        #endif // DEBUG
        double fatorAleatorio = 0;      // Caso o fator aleatorio esteja ligado, calcula uma media dos valores das arestas
        double media = 0;               // e aceita também um valor "menor", um percentual (PCT) da media dos valores.
        if (pct) {
            for (Aresta *a = v->primeiraAresta(); a; a = v->proximaAresta()) media += a->pegaPeso();
            media /= v->pegaGrau();
            media *= pct/100;
            #ifdef DEBUG
            cout << "Randomização ligada, aceitando valores ate " << pct << "% maiores. (" << media << " unidades). " << endl;
            #endif // DEBUG
        }
        for (Aresta *a = v->primeiraAresta(); a; a = v->proximaAresta()) {
            if (pct) {
                fatorAleatorio = rand->meurand(0, media);
            }
            if ( (a->pegaPeso() - fatorAleatorio) < menor->pegaPeso()) {
                if (std::find(resposta->begin(), resposta->end(), a->pegaIdDestino()) == resposta->end()) {
                    menor = a;
                }
            }
        }
        #ifdef DEBUG
        cout << "Menor aresta nao visitada e para (" << menor->pegaIdDestino() << ") = " << menor->pegaPeso() << endl;
        #endif // DEBUG

        // Verifica se terei bateria suficiente para ir até lá e voltar se necessario
        if (posicao!=idbase) {

            int volta = v->encontraAresta(idbase)->pegaPeso();

            // Se dá pra ir, já decrementa bateria e altera posicao.
            if ( (bateria - menor->pegaPeso()) > volta+sobra_bateria ) {
                bateria -= menor->pegaPeso();
                posicao = menor->pegaIdDestino();
            } else {
                // Senão, volta para a base.
                posicao = idbase;
                bateria -= volta;
            }
        } else {
            #ifdef DEBUG
            cout << "Nao preciso checar bateria, estou na base." << endl;
            #endif // DEBUG
            bateria -= menor->pegaPeso();
            posicao = menor->pegaIdDestino();
        }
        #ifdef DEBUG
        cout << "Nova carga = " << bateria << endl;
        cout << "Viajando..." << endl;
        #endif // DEBUG
    }

    delete [] id;
    delete rand;

    return resposta;
}

/** \brief Verifica se todos os nós foram visitados
  * \return bool
 */
bool Grafo::visitouTodosNos() {
    for (Vertice *v=this->primeiroNo(); v; v=this->proximoNo())
        if (v->foiVisitado()==false) return false;
    return true;
}

/** \brief Calcula custo total de uma sequência de nós
 * \param vector<int> *ids
 * \return double soma
 */
double Grafo::CustoTotal(vector<int> *ids) {

    double soma = 0;
    unsigned int i = 0;
    Vertice *v;
    Aresta *a;

    while (i<ids->size()) {
        v = this->encontraNo(ids->at(i++));
        if (i<ids->size()) {
            a = v->encontraAresta(ids->at(i++));
            soma += a->pegaPeso();
        }
    };

    return soma;
}

/// Destructor
Grafo::~Grafo() {

    Item *i;
    Vertice *v;

    this->inicioLista();
    do {
        i = this->noIterator();
        v = (Vertice*)i;
        this->deletaItem(i);
        delete v;
    } while (this->noIterator());

}

/** \brief Verifica se o grafo é completo
 *
 * \return bool
 */
bool Grafo::completo(){
    int aux;
    int numVertices = this->contaNos(); ///armazena a quantidade de nós existentes
    int grauCompleto =  numVertices - 1;
    Vertice *v = this->primeiroNo();

    while(v)
    {
        aux = grauNo(v->pegaId());
        if(grauCompleto != aux)
        {
            cout << v->pegaId() << " tem grau " << aux << endl;
            return false;
        }
        v = this->proximoNo();
    }
    return true;
}

/** \brief Verifica se a aresta existe
 *
 * \param Vertice *v
 * \param int id
 * \return bool
 */
bool Grafo::encontraAresta(Vertice *v, int id)
{
    return v->existeAresta(id);
}

/** \brief Encontra no grafo, o vértice correspondente ao id informado
 *
 * \param int id
 * \return Vertice *v
 */
Vertice* Grafo::encontraNo(int id) {

        Vertice *v = this->primeiroNo();

        while (v) {
            if (v->pegaId()==id) return v;
            else v = this->proximoNo();
        }

        return v;
}

/** \brief Adiciona ao grafo, um vértice com o id informado. Caso já exista algum vértice com este id, a função retorna o ponteiro p/ o vértice existente
 *
 * \param int id
 * \return Vertice *v
 */
Vertice* Grafo::adicionaNo(int id) {

    Vertice *v = this->encontraNo(id); /// Tenta encontrar Vertice com essa id

    if (!v) {  /// Se não encontrou, cria...
        v = new Vertice(id);
        this->adicionaItem(v);
    }

    return v;
}

/** \brief Adiciona um Vertice com a id dada caso não exista, caso exista retorna ponteiro para o Vertice
 *
 * \param int x
 * \param int y
 * \param int t
 * \return Vertice *v
 */
Vertice* Grafo::adicionaNo(int x, int y, int t int i) {

    Vertice *v = this->encontraNo(coordToId(x,y)); /// Tenta encontrar Vertice com essa id

    if (!v) {  /// Se não encontrou, cria...
        v = new Vertice(x, y, t);
        this->adicionaItem(v);

    }

    return v;
}

/** \brief Adiciona uma aresta entre os ids informados
 *
 * \param int id_origem
 * \param int id_destino
 */
void Grafo::adicionaAresta(int id_origem, int id_destino) {

    /// Procura nós destino e origem, se não existirem, cria!
    Vertice *vo = this->encontraNo(id_origem);
    Vertice *vd = this->encontraNo(id_destino);

    if (!vo) return;
    if (!vd) return;

    double dx = idToX(id_origem) - idToX(id_destino);
    double dy = idToY(id_origem) - idToY(id_destino);
    double dist;
    dist = pow(dx,2)+pow(dy,2);
    dist = sqrt(dist);

    //cout << "Aresta " << vo->pegaId() << ", " << vd->pegaId() << " = " << dist << endl;

    vo->adicionaAresta(id_destino, dist);
    vd->adicionaAresta(id_origem, dist);

}

/** \brief Remove o vértice correspondente ao id fornecido, caso exista no grafo.
 *
 * \param int id
 * \return bool
 */
void Grafo::removeNo(int id) {

    /// encontra nó com vertice id, se não encontrar retorna
    Vertice *v = this->encontraNo(id);
    if (!v) return;

    Vertice *v2 = this->primeiroNo();

    /// Percorre todos os vertices...
    while (v2) {
        /// O Vertice tem alguma Aresta para o Vertice a ser deletado? Remove Aresta, e pula para o proximo Vertice !
        if (v2->removeAresta(id)) {
            v->removeAresta(v2->pegaId());
        }
        /// Senão, pula para o proximo Vertice
        v2 = this->proximoNo();
    }
    Lista::deletaItem(v);
    delete v;
}

/** \brief Remove a aresta existente entre os ids fornecidos, caso essa aresta exista no grafo
 *
 * \param int id_no1
 * \param int id_no2
 * \return bool
 */
void Grafo::removeAresta(int id_no1, int id_no2) {

    ///  Encontra os Vertices com as id's dadas, no grafo
    Vertice *v1 = this->encontraNo(id_no1);
    Vertice *v2 = this->encontraNo(id_no2);

    if (!(v1&&v2)) return ;

    v1->removeAresta(id_no2);
    v2->removeAresta(id_no1);

}

/** \brief Informa o grau do vértice correspondente ao id informado
 *
 * \param int id
 * \return int -> -1 caso o id informado não pertença ao grafo
 */
int Grafo::grauNo(int id) {

    Vertice *v = this->encontraNo(id);

    if (v) return v->pegaGrau();
    else return -1;

}


///* ---------------------------------------- CLASSE VERTICE --------------------------------------- *///

Vertice::~Vertice() {

    Item *i;

    this->inicioLista();
    do {
        i = this->noIterator();
        this->deletaItem(i);
        delete i;
    } while (this->noIterator());

}

/** \brief Verifica se existe aresta
 *
 * \param int id
 * \return bool
 */
bool Vertice::existeAresta(int id)
{
    Aresta *a = this->encontraAresta(id);
    if (a)
        return true;
    else
        return false;

}

/** \brief Encontra uma aresta associada ao vértice correspondente ao id informado
 *
 * \param int id
 * \return 0
 */
Aresta* Vertice::encontraAresta(int id) {

    Aresta *a = this->primeiraAresta();

    while (a) {
        if (a->pegaIdDestino()==id) return a;
        else a = this->proximaAresta();
    }

    return 0;
}

/** \brief Remove a aresta do vértice, se encontrá-la
 *
 * \param int id
 * \return bool
 */
bool Vertice::removeAresta(int id) {

    Aresta *a = this->encontraAresta(id);
    if (a) {
        Lista::deletaItem(a);
        delete a;
        return true;
    }
    else
        return false;

};

///* ---------------------------------------- CLASSE ARESTA ---------------------------------------- *///


