#include "Grafo.h"
#include "util.h"
#include "Alfa.h"

#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <limits>
#include <algorithm>
#include <string.h>
#include <list>
#include <queue>
#include <functional>
#include <sys/time.h>
#include <iomanip>
#include <cmath>
#include <limits>

#define INFINITO 999999

using namespace std;


//// 3 PARTE ///////

/** \brief Metodo contrutivo guloso ou ramdomizado. Para determinar o metodo guloso, basta passa como parametro o valor 0.0,
            e para determinar o metodo randomizado(sem o numero determinado de iterações), basta passar como parametro um valor entre
            0.1 ate 1.0.
 *
 * \param alfa valor de ponto flutuante entre 0.0 e 1.0.
 * \return retorna um vetor de Vertice com a solução.
 */
 vector<Vertice*> Grafo::ContrutivoCoberturaPonderada(float alfaGuloso, float &tempoGuloso){

    vector<Vertice*> solu; // solução
    cout << "bele1" << endl;
    vector<Vertice*> lista = this->ordenaVertice(); // cria a lista ordenada


    int i = 0;
    timeval tempo_inicio,tempo_fim; // variaveis para medir o tempo

    gettimeofday(&tempo_inicio,NULL); // tempo inicial

    while(!lista.empty()){

        i = xrandomRange(0 , ( (int)( lista.size() * alfaGuloso) ) ) ; //define o indice i.
        Vertice * v = lista[i];

        for (Aresta *u = v->primeiraAresta(); u != NULL; u = v->proximaAresta()){
            this->decrementaGrau(lista, u->pegaIdDestino()); // decrementa o grau do adjacente de v
        }
        solu.push_back(lista[i]);
        lista = this->atualizaLista(lista, i);
        sort(lista.begin(), lista.end(), Vertice::ordenaVerticeRazao); //ordena a lista
    }

    gettimeofday(&tempo_fim,NULL); //tempo final.

    //tempo gostos ára execulção da função em segundos
    tempoGuloso = (float) (1000 * (tempo_fim.tv_sec - tempo_inicio.tv_sec) + (tempo_fim.tv_usec - tempo_inicio.tv_usec) / 1000);

    return solu;
}

/** \brief Metodo construtivo guloso randomizado com um numero determinado de iterações.
 *
 * \param valor de ponto flutuante entre 0.1 e 1.0.
 * \param inteiro que determina o numero de iteraçes.
 * \return retorna um vetor de Vertice com a solução.
 */
vector<Vertice*> Grafo::CoberturaRamdomizado(float alfaRand, int numIteracao, float &tempoRand){

    vector<Vertice*> solu; //solução
    vector<Vertice*> soluParcial; // solução parcial
    float melhorCusto = INFINITO;
    float somaValor = 0.0;

    timeval tempo_inicio,tempo_fim;

    gettimeofday(&tempo_inicio,NULL);

    for (int i = 0; i < numIteracao; i++){

        soluParcial.clear();

        if (solu.empty()){
            soluParcial = this->ContrutivoCoberturaPonderada(alfaRand,tempoRand);
            solu = soluParcial;
        }else{
            soluParcial = this->ContrutivoCoberturaPonderada(alfaRand,tempoRand);
        }

        solu = melhorSolu(melhorCusto, somaValor, alfaRand, alfaRand, solu, soluParcial);
    }

    gettimeofday(&tempo_fim,NULL);

    tempoRand = (float) (1000 * (tempo_fim.tv_sec - tempo_inicio.tv_sec) + (tempo_fim.tv_usec - tempo_inicio.tv_usec) / 1000);

    return solu;
}


/** \brief Metodo contrutivo goluso randomizado reativo. Utiliza um vetoer de alfas para determinar a melhor soulçao possivel dentro de um
            numero finito de iterações.
 *
 * \param Um array de alfas.
 * \param Valor que determina a quantidade de iterações pro bloco.
 * \param Valor que determina o numero de iterações.
 * \return retorna um vetor de Vertice com a solução.
 *
 */
vector<Vertice*> Grafo::CoberturaReativo( vector<Alfa*> alfa, float &alfaReativo, int numIteracaoBloco, int numIteracao, float &tempoReativo){

    int indexAlfa = 0;
    float valorAlfa = 0.0;
    float melhorCusto = 0.0;
    float somaValor = 0.0;
    float somaQ = 0.0;
    vector<Vertice*> solu;
    vector<Vertice*> soluParcial;

    timeval tempo_inicio,tempo_fim;

    /*
    for (int i = 0; i < (int) alfa.size(); i++){
        float p = 1 / alfa.size();
        alfa[i]->setProbabilidade( p );
    }
    */
    //solu.clear();
    gettimeofday(&tempo_inicio,NULL);

    while (numIteracao != 0){

        for (int i = 0; i < numIteracaoBloco; i++){
            cout << "bele0" << endl;
            indexAlfa = escolheAlfa(alfa);
            valorAlfa = alfa[indexAlfa]->getAlfa();
            alfa[indexAlfa]->setQuantVezesUsado(1);

            if (solu.empty()){
                soluParcial = this->ContrutivoCoberturaPonderada(valorAlfa, tempoReativo);
                cout << "bele2" << endl;
                solu = soluParcial;
            }else{
                soluParcial = this->ContrutivoCoberturaPonderada(valorAlfa, tempoReativo);
            }
            cout << "bele3" << endl;
             solu = melhorSolu(melhorCusto, somaValor, alfaReativo, valorAlfa, solu, soluParcial);
             alfa[indexAlfa]->setSomaTotalCusto(somaValor);
             somaValor = 0.0;
             soluParcial.clear();
        }

        for (int j  = 0; j < (int)alfa.size(); j++){
            alfa[j]->setQ(melhorCusto/ ( alfa[j]->getMedia() == 0 ? 1 : alfa[j]->getMedia() ) );
            somaQ += alfa[j]->getQ();
        }

        for (int i = 0; i < (int)alfa.size(); i++){
            alfa[i]->setProbabilidade(alfa[i]->getQ() / (somaQ == 0 ? 1 : somaQ) );
        }
        somaQ = 0.0;
        numIteracao--;
    }

    gettimeofday(&tempo_fim,NULL);

    tempoReativo = (float) (1000 * (tempo_fim.tv_sec - tempo_inicio.tv_sec) + (tempo_fim.tv_usec - tempo_inicio.tv_usec) / 1000);

    return  solu;
}

/** \brief Metodo que cria e ordena um array de vertices.
 *
 * \return Um array ordemado de vertice.
 */
vector<Vertice*> Grafo::ordenaVertice(){
    vector<Vertice*> listaVertice;
    for (Vertice* v = this->primeiroNo(); v != NULL; v = this->proximoNo()){
        v->setRazao(v->getPesoV()/ v->pegaGrau());
        v->iniciaNumItemDecre();
        listaVertice.push_back(v);
    }
    sort(listaVertice.begin(), listaVertice.end(), Vertice::ordenaVerticeRazao);

    return listaVertice;
}

/** \brief Decremente o grau do vertice de id passado por parametro de uma lista.
 *
 * \param Um array de Vertices(vector<Vertice*>).
 * \param Um intteiro que repesenta o ID no vertice.
 * \return Um array de Vertices(vector<Vertice*>).
 */
void Grafo::decrementaGrau(vector<Vertice*> lista, int no){

    for(int i = 0; i < (int)lista.size(); i++){
        if (lista[i]->pegaId() == no){
            lista[i]->decreGrau();
        }
    }
}

/** \brief Atualiza uma array de Vertice removendo o vertice de ID informado por paramentro
            e remove todos os vertices com o grau 0.
 *
 * \param Um array de Vertices(vector<Vertice*>).
 * \param Um intteiro que repesenta o ID no vertice.
 * \return Um array de Vertices(vector<Vertice*>).
 */
vector<Vertice*> Grafo::atualizaLista(vector<Vertice*> lista, int id){

    lista.erase(lista.begin() + id);

    for (int i = 0; i < (int)lista.size(); i++){
        if (lista[i]->pegaGrauDecre() == 0){
            lista.erase(lista.begin() + i);
        }
    }
    return lista;
}

/** \brief Metodo que retorna a melhor solução entre a solução corrente e a solução atual.
            Encontra o menor custo  enter as soluções e o custo da solução corrente.
 *
 * \param float que armazena o menor custo.
 * \param float que armazena o custo da solução corrente.
 * \param array com a solução atual(vector<Vertice*>).
 * \param array com a solução corrente(vector<Vertice*>).
 * \return Um array de Vertices(vector<Vertice*>).
 */
vector<Vertice*> Grafo::melhorSolu(float &melhorCusto, float &somaValor, float &alfa, float alfa2,vector<Vertice*> solu, vector<Vertice*> soluParcial){

    int i = (int)solu.size();
    int j = (int)soluParcial.size();
    float soluCusto = 0.0 , soluParcialCusto = 0.0;

    while(true){

        i--;
        j--;

        if (i < 0 && j < 0){
            break;
        }

        if (i >= 0){
            soluCusto += solu[i]->pesoV;
        }
        if (j >= 0 ){
            soluParcialCusto += soluParcial[j]->pesoV;
            somaValor = soluParcialCusto;
        }
    }
    if (soluCusto < soluParcialCusto){
        melhorCusto = soluCusto ;
        return solu;
    }
    melhorCusto = soluParcialCusto;
    alfa = alfa2;
    return soluParcial;
}

/** \brief Metodo que retorna o indice aleatorio de um alfa em um array de Alfa.
 *
 * \param Um array de alfas(vector<Alfa*>).
 * \return indice do array.
 */
int Grafo::escolheAlfa(vector<Alfa*> alfa){

    int i = 0;
    float p = 0;
    int index = xrandomRange(0, 100);

    for(i = 0; i < (int)alfa.size(); i++){
        p += alfa[i]->getProbabilidade() ;

        if ( (p * 100) >= index  ){
            return i;
        }
    }

    return 0;
}


/** \brief Construtor para grafo nao direcionado.
 */
Grafo::Grafo() {
    this->direcionado = false;
}

/** \brief Construto para grafo direcionado (digrafo).
*
* \param dir -> booleano que define se o grafo é direcionado.
*
*/
Grafo::Grafo(bool dir) {
    this->direcionado = dir;
}

/** \brief  Destrutor.  */
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

/** \brief Adiciona um Vertice com a id dada caso não exista, caso exista retorna ponteiro para o Vertice.
 *
 * \param id -> Identificador do vertice.
 * \return v -> Retorna um vertice.
 */
Vertice* Grafo::adicionaNo(int id) {

    Vertice *v = this->encontraNo(id);

    if (!v)
    {
        v = new Vertice(id);
        this->adicionaItem(v);
    }
    return v;
}

/** \brief Adiciona uma aresta em id_origem, apontando (quando pertinente) para id_destino.
 *
 * \param int origem -> Origem da aresta.
 * \param int destino -> Destino da aresta.
 */
void Grafo::adicionaAresta(int id_origem, int id_destino){
    Vertice *vd = this->adicionaNo(id_destino);
    Vertice *vo = this->adicionaNo(id_origem);

    vo->adicionaAresta(id_destino);

    if (!this->direcionado)
        vd->adicionaAresta(id_origem);

}

/** \brief Adiciona uma aresta com PESO, em id_origem apontando (quando pertinente) para id_destino.
 *
 * \param id_origem -> Origem da aresta.
 * \param id_destino -> Destino da aresta.
 * \param peso -> Peso da aresta.
 */
void Grafo::adicionaAresta(int id_origem, int id_destino, float peso){
    Vertice *vd = this->adicionaNo(id_destino);
    Vertice *vo = this->adicionaNo(id_origem);

    vo->adicionaAresta(id_destino, peso);
    if (!this->direcionado) vd->adicionaAresta(id_origem, peso);

}

/** \brief Procura o Vertice que possui a id dada, e deleta caso encontre.
 *
 * \param id -> Identificador do vertice.
 */
void Grafo::removeNo(int id){
    Vertice *v = this->encontraNo(id);
    if (v == NULL)
    {
       return;
    }

    Vertice *v2 = this->primeiroNo();

    while (v2) {
        if (v2->removeAresta(id)) {
            v->removeAresta(v2->pegaId());
        }
        v2 = this->proximoNo();
    }
    Lista::deletaItem(v);
    delete v;
}

/** \brief Remove uma aresta entre dois vertices.
 *
 * \param id_no1 -> Vertice origem.
 * \param id_no2 -> Vertice destino.
 */
void Grafo::removeAresta(int id_no1, int id_no2){
    Vertice *v1 = this->encontraNo(id_no1);
    Vertice *v2 = this->encontraNo(id_no2);

    if (!(v1 &&  v2)) return ;

    v1->removeAresta(id_no2);
    v2->removeAresta(id_no1);

}

/** \brief  Retorna o grau do vertice (no) passando como parametro o id no vertice(no),
 *
 * \param id -> Identificador do vertice.
 * \return grau -> Grau do no.
 */
int Grafo::grauNo(int id){

    Vertice *v = this->encontraNo(id);

    if (v)
        return v->pegaGrau();
    else
        return -1;

}




/** \brief Vetifica se a aresta existe
 *
 * \param Vertice *v
 * \param int id
 * \return bool
 */
bool Grafo::encontraAresta(Vertice *v, int id){
    return v->existeAresta(id);
}



/** \brief Encontra um Vertice com a id e retona o vertice v se encontra. Caso nao encontre, retorna NULL
 *
 * \param int id
 * \return Vertice *v
 *
 */
Vertice* Grafo::encontraNo(int id) {

    Vertice *v = this->primeiroNo();

    while (v)
    {
        if (v->pegaId()==id)
        {
            return v;
        }
        else
        {
            v = this->proximoNo();
        }
    }
    return NULL;
}

/** \brief Encontra um Vertice com a id e retona o vertice v se encontra. Caso nao encontre, retorna NULL
 *
 * \param Grafo *g
 * \param int id
 * \return Vertice *v
 *
 */
Vertice* Grafo::encontraNo(Grafo*g,int id){
    Vertice *v = g->primeiroNo();

    while (v)
    {
        if (v->pegaId()==id)
        {
            return v;
        }
        else
        {
            v = g->proximoNo();
        }
    }
    return NULL;
}

/** \brief Imprime cada vertice (no) com os nos adjacentes
 *
 * \param Grafo* g
 */
void Grafo::imprimeGrafo(Grafo* g){
    Vertice *v;
//    Aresta *a;

    for (v = g->primeiroNo() ; v != NULL; v = g->proximoNo())
    {
        cout << v->pegaId() << " (G -> " << v->pegaGrau() <<") "<<" (P-V -> " << v->pesoV <<") "<<" -> ";
        /*
        for (a = v->primeiraAresta() ; a != NULL; a = v->proximaAresta())
        {
            cout << a->pegaIdDestino() << " (P-A -> " << a->pegaPeso() << ") ";
        }
        */
        cout << endl;
    }
    delete(v);
    //delete(a);
}

/** \brief Retorna o ordem do Grafo.
 *
 * \return inteiro que repesenta a ordem do grafo.
 */
int Grafo::ordemGrafo(){
    return this->contaNos();
}

/** \brief Destrutor
 *
 */
 Vertice::~Vertice() {

    Item *i;

    this->inicioLista();
    do {
        i = this->noIterator();
        this->deletaItem(i);
        delete i;
    } while (this->noIterator());

}

/** \brief Verifica se a aresta com id esxite
 *
 * \param int id
 * \return bool
 */
bool Vertice::existeAresta(int id){
    Aresta *a = this->encontraAresta(id);
    if (a != NULL)
        return true;
    else
        return false;

}

/** \brief Encontra uma Aresta para id no Vertice v
 *
 * \param int id
 * \return Aresta*
 */
Aresta* Vertice::encontraAresta(int id) {

    Aresta *a = this->primeiraAresta();

    while (a) {
        if (a->pegaIdDestino()==id) return a;
        else a = this->proximaAresta();
    }

    return NULL;
}

/** \brief Retorna o peso da aresta passado por parametro
 *
 * \param int id
 * \return float
 */
float Vertice::pegaPesoAresta(int id) {

    Aresta *a = this->encontraAresta(id);

    if (a) {
        return a->pegaPeso();
    }
    return 0.0f;
}

/** \brief Remove aresta do Vertice se encontra-la
 *
 * \param int id
 * \return bool
 *
 */
bool Vertice::removeAresta(int id) {

    Aresta *a = this->encontraAresta(id);

    if(a == NULL){
        return false;
    }
    while (a != NULL) {
        Lista::deletaItem(a);
        a = this->encontraAresta(id);
    }
    return true;
}

bool Vertice::ordenaVerticeRazao(const Vertice* v1, const Vertice* v2){
    return (v1->razao < v2->razao);
};

bool Aresta::ordenaArestaPeso(const Aresta* a1, const Aresta* a2){
    return (a1->peso < a2->peso);
};




