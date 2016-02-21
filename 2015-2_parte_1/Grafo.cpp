/**
 *
 * Grafo.cpp
 *
 */

#include "Grafo.h"
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

#define INFINITO 999999

using namespace std;


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
 * \param id_origem -> Origem da aresta.
 * \param id_destino -> Destino da aresta.
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

/** \brief Retorna o grau do Grafo.
 *
 * \return maior -> Grau do grafo .
 */
int Grafo::grauGrafo(){
    int maior = 0;
    Vertice* v;
    for (v = this->primeiroNo(); v != NULL; v = this->proximoNo())
    {
        if (maior < v->pegaGrau())
        {
            maior = v->pegaGrau();
        }
    }

    return maior;
}

/** \brief Retorna o ordem do Grafo.
 *
 * \return inteiro que repesenta a ordem do grafo.
 */
int Grafo::ordemGrafo(){
    return this->contaNos();
}

/** \brief Verifica se o grafo eh trivial.
 *
 * \return True para trivial e false para nao trivial.
 */
bool Grafo::ehTrivial(){
    if (this->contaNos() == 1)
    {
        return true;
    }

    return false;
}

/** \brief  Verifica se o grafo eh nulo.
 *
 * \return True para nulo e false para nao nulo.
 */
bool Grafo::ehNulo(){
    if (this->contaNos() == 0)
    {
        return true;
    }

    return false;
}

/** \brief Verifica se o grafo é K-Regular.
 *
 * \return True para k-regular e false para nao k-regular.
 */
bool Grafo::kRegular(int id){
    int grau1;
    Vertice *v = this->primeiroNo();
    //int grau = grauNo(v->pegaId());

    while(v)
    {
        grau1 = grauNo(v->pegaId());
        if(grau1!=id)
        {
            return false;
        }
        v = this->proximoNo();
    }
    return true;
}

/** \brief Verifica se o grafo eh completo.
 *
 * \return True para completo e false para nao completo.
 */
bool Grafo::completo(){
    int aux;
    int numVertices = this->contaNos();
    int grauCompleto =  numVertices - 1;
    Vertice *v = this->primeiroNo();

    while(v)
    {
        aux = grauNo(v->pegaId());
        if(grauCompleto != aux)
        {
            return false;
        }
        v = this->proximoNo();
    }
    return true;
}

/** \brief Verifica se eh um Multigrafo.
 *
 * \return True para Multigrafo e false para nao Multigrafo.
 */
bool Grafo::ehMultigrafo(){

    vector<int> idAresta;
    bool sai = false;
    for (Vertice * v = this->primeiroNo(); v != NULL; v = this->proximoNo())
    {
        for(Aresta *a = v->primeiraAresta(); a != NULL; a =  v->proximaAresta())
        {

            idAresta.push_back(a->pegaIdDestino());
        }

        for(int i = 0; i < (int)idAresta.size(); i++)
        {
            for(int j = i+1; j < (int)idAresta.size(); j++)
            {
                if (idAresta[i] == idAresta[j])
                {
                    i = (int)idAresta.size();
                    j = (int)idAresta.size();
                    sai = true;
                }
            }
        }

        idAresta.clear();

        if (sai)
        {
            v = NULL;
        }
    }

    if (sai)
    {
        return true;
    }

    return false;
}

/** \brief Verifica se eh um Multidigrafo.
 *
 * \return True para MultiDigrafo e false para nao MultiDigrafo.
 */
bool Grafo::ehMultiDigrafo(){

    vector<int> idAresta;
    bool sai = false;
    for (Vertice * v = this->primeiroNo(); v != NULL; v = this->proximoNo())
    {
        for(Aresta *a = v->primeiraAresta(); a != NULL; a =  v->proximaAresta())
        {
            idAresta.push_back(a->pegaIdDestino());
        }

        for(int i = 0; i < (int)idAresta.size(); i++)
        {

            for(int j = i+1; j < (int)idAresta.size(); j++)
            {
                if (idAresta[i] == idAresta[j])
                {
                    i = (int)idAresta.size();
                    j = (int)idAresta.size();
                    sai = true;
                }
            }

            if (!sai)
            {
                Vertice *v2 = this->encontraNo(idAresta[i]);
                for(Aresta *a = v2->primeiraAresta(); a != NULL; a = v->proximaAresta())
                {
                    if (a->pegaIdDestino() == v2->pegaId())
                    {
                        i = (int)idAresta.size();
                    }
                }
            }
        }

        idAresta.clear();

        if (sai)
        {
            v = NULL;
        }
    }

    if (sai)
    {
        return true;
    }

    return false;
}

/** \brief Verifica se eh um Bipartido.
 *
 * \param v -> primeiro vertice da lista.
 * \param mudaPart -> Booleano que altera a partcao do vertice.
 * \return True para bipartido e false para nao bipartido.
 */
bool Grafo::ehBipartido(Vertice* v, bool mudaPart){

   v->setaVisitado(true);
   if (mudaPart){
      v->setParticao(1);
   }
   else{
      v->setParticao(2);;
   }
   Aresta *aux  = v->primeiraAresta();
   bool eh_bipartido = true;
   for(int i = 0; i < v->contaItems(); i++ )
   {
       Vertice *ve  = this->encontraNo(aux->pegaIdDestino());
       if (ve->foiVisitado() == false)
       {
          if (mudaPart)
          {
              eh_bipartido = ehBipartido(ve, false);
          }
          else
          {
              eh_bipartido = ehBipartido(ve, true);
          }

       }
       else if(ve->getParticao() == v->getParticao() )
       {
           return false;
       }
      aux  = v->proximaAresta();
   }
   return eh_bipartido;
}

/** \brief Retorna um subgrafo com o menor caminho entre dois vertice(no) utilizando o Dijkstra.
 *
 * \return Grafo
 */
pair<Grafo*, float> Grafo::menorCaminho(int id_origem, int id_destino){

        // vetor de distâncias
		float dist[this->contaNos()+1];
		float caminho[this->contaNos()+1];
		Grafo * g = new Grafo();
		int id_caminho = id_destino;
        pair<Grafo*, float> info;

		// fila de prioridades de pair (distancia, vértice) greater< pair<int,int> >
		priority_queue < pair<int, int>,vector< pair<int, int > >, greater< pair<int,int > > > filaPrioridade;

		// inicia o vetor de distâncias e visitados
		for(int i = 0; i <= this->contaNos(); i++)
		{
			dist[i] = INFINITO;
			caminho[i] = -1;
		}

		// a distância de orig para orig é 0
		dist[id_origem] = 0;
		caminho[id_origem] = 0;

		// insere na fila
		filaPrioridade.push(make_pair(dist[id_origem], id_origem));

		while(!filaPrioridade.empty())
		{
			pair<int, int> fp = filaPrioridade.top();
			Vertice *u = this->encontraNo(fp.second);
			filaPrioridade.pop(); // remove da fila

			// verifica se o vértice não foi expandido
			if(u->foiVisitado() == false)
			{
				// marca como visitado
				u->setaVisitado(true);
				// percorre os vértices "v" adjacentes de "u"
				for(Aresta *a = u->primeiraAresta(); a != NULL; a = u->proximaAresta())
				{
					// obtém o vértice adjacente e o custo da aresta
					int v = a->pegaIdDestino();
					float custo_aresta = a->pegaPeso();

					// relaxamento (u, v)
					if(dist[v] > (dist[u->pegaId()] + custo_aresta))
					{
						// atualiza a distância de "v" e insere na fila
						dist[v] = dist[u->pegaId()] + custo_aresta;
						caminho[v] = u->pegaId();
						filaPrioridade.push(make_pair(dist[v], v));
					}
				}
			}
		}

        cout << endl;
        Aresta *ac;
        Vertice *vc = this->encontraNo(caminho[id_caminho]);
        while(id_caminho != id_origem)
        {
            ac = vc->encontraAresta(id_caminho);
            g->adicionaAresta(vc->pegaId(), ac->pegaIdDestino(), ac->pegaPeso() );

            id_caminho = vc->pegaId();
            vc = this->encontraNo(caminho[id_caminho]);
        }

       //g->imprimeGrafo(g);
        cout << endl;
		// retorna a distância mínima até o destino
		//return dist[id_destino];
		info.first = g;
		info.second = dist[id_destino];
		return info;
}

/** \brief Retorna um subgrafo induzido com os vertices adjacentes ao vertice(no) informado.
 *
 * \param int id
 * \return Grafo
 */
Grafo* Grafo::vizinhacaAberta(int id){

    Grafo* subgrafo = new Grafo();
    vector<int> idVizinhos;
    Vertice* v = this->encontraNo(id);
    if(v->contaItems() == 0)
    {
        return NULL;
    }
    Aresta* a = v->primeiraAresta();
    while(a != NULL)
    {
        subgrafo->adicionaNo(a->pegaIdDestino());
        idVizinhos.push_back(a->pegaIdDestino());
        a = v->proximaAresta();
    }

    for(int i = 0; i < (int)idVizinhos.size(); i++)
    {
        Vertice* vz = this->encontraNo(idVizinhos[i]);
        for(Aresta* az = vz->primeiraAresta(); az != NULL; az = vz->proximaAresta())
        {
            for(int j = 0; j < (int)idVizinhos.size(); j++)
            {
                 if (az->pegaIdDestino() == idVizinhos[j])
                 {
                     subgrafo->adicionaAresta(vz->pegaId(), idVizinhos[j]);
                     j = idVizinhos.size();
                 }
            }
        }
    }
    idVizinhos.clear();
    return subgrafo;
}

/** \brief Retorna um subgrafo induzido com os vertices adjacentes ao vertice(no) informado incluindo o proprio vertice.
 *
 * \param int id
 * \return Grafo
 */
Grafo* Grafo::vizinhacaFechada(int id){

    Grafo* subgrafo = new Grafo();
    vector<int> idVizinhos;
    Vertice* v = this->encontraNo(id);
    if(v->contaItems() == 0)
    {
        subgrafo->adicionaNo(v->pegaId());
        return subgrafo;
    }
    Aresta* a = v->primeiraAresta();
    subgrafo->adicionaNo(v->pegaId());
    //this->imprimeGrafo(this);
    //cout << a->pegaInfo() << endl;
    while(a != NULL)
    {
        subgrafo->adicionaAresta(v->pegaId(),a->pegaIdDestino());
        idVizinhos.push_back(a->pegaIdDestino());
        a = v->proximaAresta();
    }

    for(int i = 0; i < (int)idVizinhos.size(); i++)
    {
        Vertice* vz = this->encontraNo(idVizinhos[i]);
        for(Aresta* az = vz->primeiraAresta(); az != NULL; az = vz->proximaAresta())
        {
            for(int j = 0; j < (int)idVizinhos.size(); j++)
            {
                 if (az->pegaIdDestino() == idVizinhos[j])
                 {
                     subgrafo->adicionaAresta(vz->pegaId(), idVizinhos[j]);
                     j = idVizinhos.size();
                 }
            }
        }
    }

    idVizinhos.clear();
    return subgrafo;
}

/** \brief Metodo para buscar um vertice no grafo utilizado a abordagem em largura
 *
 * \param Identificador do vertice
 * \return booleano
 */
bool Grafo::buscaLargura(int id){


    vector<int> pai;
    Vertice *v = this->primeiroNo();
    pai.push_back(v->pegaId());
    v->setaVisitado(true);
    while(!pai.empty()){

        for(Aresta *aux = v->primeiraAresta(); aux != NULL; aux = v->proximaAresta()){
            Vertice *vaux = this->encontraNo(aux->pegaIdDestino());
            if (!vaux->foiVisitado()){
                vaux->setaVisitado(true);
                pai.push_back(vaux->pegaId());
                if (vaux->pegaId() == id){
                    pai.clear();
                    return true;
                }
            }
        }
        pai.erase(pai.begin());
        v = this->encontraNo(pai[0]);
    }
    pai.clear();

    return false;
}

/** \brief Metodo para buscar um vertice no grafo utilizado a abordagem em profundidade.
 *
 * \param
 * \return bool
 */
bool Grafo::buscaProfundidade(Vertice *v, int id){

    v->setaVisitado(true);
    bool resposta = false;
    for (Aresta *a = v->primeiraAresta(); a != NULL; a = v->proximaAresta()){
        Vertice *w = this->encontraNo(a->pegaIdDestino());
        if (!w->foiVisitado()){
            w->setaVisitado(true);
            if (w->pegaId() == id){
                return true;
            }
            else{
                resposta = buscaProfundidade(w,id);
            }
        }
    }

    return resposta;
}

/** \brief Metodo que cria uma matriz que contem o menor caminho do vertice u para cada o vertice v do grafo.
 */
void Grafo::floyd(){

    int tamanho = this->ordemGrafo();
    //
    int **dist = (int**) malloc((tamanho) * sizeof(int*));
    int **caminho = (int**) malloc((tamanho) * sizeof(int*));

    Vertice *v ;//= this->primeiroNo();

    for (int i = 0; i < tamanho; i++){
        v = this->encontraNo(i+1);
        dist[i] = (int*) malloc(tamanho * sizeof(int));
        caminho[i] = (int*) malloc(tamanho * sizeof(int));
        if (v != NULL){
            for(int j = 0; j < tamanho; j++){
                Aresta *a = v->encontraAresta(j+1);
                if (a != NULL){
                    dist[i][j] = a->pegaPeso();
                    caminho[i][j] = i;
                }
                else{
                    dist[i][j] = 0;
                    caminho[i][j] = 0;
                }
            }
        }
    }


    for (int i = 0; i < tamanho; i++){
        cout << endl;
        for(int j = 0; j < tamanho; j++){
            if (dist[i][j] != 0){
                cout << dist[i][j] << " ";
            }
            else{
                cout << "N ";
            }
        }
    }
    cout<< endl;


    for (int k = 0; k < tamanho; k++){
        for (int i = 0; i < tamanho; i++){
            for (int j = 0; j < tamanho; j++){
                if ((dist[i][k] * dist[k][j] != 0) && (i != j))
                {
                    if ((dist[i][k] + dist[k][j] < dist[i][j]) || (dist[i][j] == 0))
                    {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        caminho[i][j] = caminho[k][j];
                    }
                }
            }
        }
    }
    cout << "\nMatriz com os menores valores para cada caminho do vertice u para v";
    for (int i = 0; i < tamanho; i++){
        cout << endl;
        for(int j = 0; j < tamanho; j++){
            if (dist[i][j] != 0){
                cout << dist[i][j] << " ";
            }
            else{
                cout << "N ";
            }
        }
    }
    cout << endl;
    cout << "\nMatriz com os com cada caminho do vertice u para v";
    for (int i = 0; i < tamanho; i++){
        cout << endl;
        for(int j = 0; j < tamanho; j++){
            if (i != j){
                cout << caminho[i][j] << " ";
            }else{
                cout << "N ";
            }
        }
    }
    cout<< "\n" << endl;

    //libera menoria
     for (int i = 0; i < tamanho; i++){
        free(dist[i]);
        free(caminho[i]);
    }
}

/** \brief função que busca o subconjunto de um elemento "i" usada no Kruskal
 *
 * \param int subset[]
 * \param int i
 * \return int i
 *
 */
int Grafo::buscar(int subset[], int i){
	if(subset[i] == -1)
		return i;
	return buscar(subset, subset[i]);
}

/** \brief função para unir dois subconjuntos em um único subconjunto
 *
 * \param int subset[] subconjunto resuntante
 * \param int v1 subconjunto 1
 * \param int v2 subconjunto 2
 * \return
 *
 */
void Grafo::unir(int subset[], int v1, int v2){
    int v1_set = buscar(subset, v1);
    int v2_set = buscar(subset, v2);
    subset[v1_set] = v2_set;
}

/** \brief Funcao kruskal que em contra um arvore geradora minima recebendo como parametro um vector comtendo as arestas
 *   ordemadas de forma crecente em relacao ao peso.
 *
 * \param vector<Aresta*> are
 * \return Grafo* ar;
 *
 */
Grafo* Grafo::Kruskal(vector<Aresta*> are){
    Grafo* ar = new Grafo();

    int size_arestas = are.size();

    // aloca memória para criar "V" subconjuntos
    int * subset = new int[ this->quantNos ];

    // inicializa todos os subconjuntos como conjuntos de um único elemento
    memset(subset, -1, sizeof(int) * this->quantNos);

    for(int i = 0; i < size_arestas; i++)
    {
        int v1 = buscar(subset, are[i]->pegaIdOrigem());
        int v2 = buscar(subset, are[i]->pegaIdDestino());

        if(v1 != v2)
        {
            // se forem diferentes é porque NÃO forma ciclo, insere no vetor
            ar->adicionaAresta(are[i]->pegaIdOrigem(), are[i]->pegaIdDestino(),are[i]->pegaPeso());
            unir(subset, v1, v2); // faz a união
        }
    }
    free(subset);
    return ar;
}

/** \brief Funcoa eu verifica se o vertice v esta no subconjunto de vertice da AGM
 *
 * \param int v -> vertice v
 * \param int subset[] -> subconjunto de vertice da AGM
 * \return bool
 *
 */
bool Grafo::ehADJ(int v, int subset[]){
    if (subset[v] == v)
        return true;

    return false;
}

/** \brief Funcao Prim para encontrar a arvore gerado minima.
 *
 * \return Grafo* g
 */
Grafo* Grafo::Prim(vector<int> verGafo){

     //cout << "Prim 1" << endl;

     Grafo* ar = new Grafo();
     int dest;     Vertice* v;     Aresta* a;     Aresta* areP;     //const int tamanho = this->ordemGrafo();

     vector<int> vertSolu;     vector<Aresta*> arestaSolu;
     vector<Aresta*> possiveisAresta;//( (tamanho* (tamanho-1))/2);

     v = this->encontraNo(verGafo[0]);
     vertSolu.push_back(verGafo[0]);
     verGafo.erase(verGafo.begin());

    //cout << "Prim 2" << endl;
    if (v->contaItems() > 0){
         for (Aresta*  are = v->primeiraAresta(); are != NULL; are = v->proximaAresta())
         {
             areP = new Aresta(v->pegaId(),are->pegaIdDestino(), are->pegaPeso());
             possiveisAresta.push_back(areP);
         }
    }
     //cout << "Prim 3" << endl;

     int k = 0;
     bool tah = false;
     while (!verGafo.empty())
     {
         //cout << "Prim 4" << endl;

         if (possiveisAresta.size()>1)
         {
             //cout << "Prim 4.1" << endl;
             sort(possiveisAresta.begin(), possiveisAresta.end(), Aresta::ordenaArestaPeso);
             //cout << "Prim 4.2" << endl;
        }
        a = possiveisAresta[0];

        //cout << "Prim 5" << endl;

        dest = a->pegaIdDestino();
        while(k < (int)vertSolu.size()){
            if (vertSolu[k] == dest)
            {
                tah = true;
                k = (int)vertSolu.size();
            }
            k++;
        }
        //cout << "Prim 6" << endl;

        if (!tah){
            arestaSolu.push_back(a);
            possiveisAresta.erase(possiveisAresta.begin());
            vertSolu.push_back(dest);
            k = 0;
            //cout << "Prim 7" << endl;
            while (k < (int)verGafo.size()){
                if (verGafo[k] == dest){
                    verGafo.erase(verGafo.begin()+k);
                    k = (int)verGafo.size();
                }
                k++;
            }
            //cout << "Prim 8" << endl;
            v = this->encontraNo(dest);
            if (v->contaItems() > 0){
                 for (Aresta*  are = v->primeiraAresta(); are != NULL; are = v->proximaAresta())
                 {
                     areP = new Aresta(v->pegaId(),are->pegaIdDestino(), are->pegaPeso());
                     possiveisAresta.push_back(areP);
                 }
            }
            //cout << "Prim 9" << endl;
        }
        else{
            possiveisAresta.erase(possiveisAresta.begin());
            tah = false;
        }
        k = 0;
     }
     //cout << "Prim 10" << endl;
     for (int i = 0; i< (int)arestaSolu.size(); i++)
     {
         ar->adicionaAresta(arestaSolu[i]->pegaIdOrigem(), arestaSolu[i]->pegaIdDestino(), arestaSolu[i]->pegaPeso());
     }
    //cout << "Prim 11" << endl;
    return ar;
 }


/** \brief A função gera o fecho transitivo indireto dado um id de um vertice.
 *
 * \param  int id
 *
 */
void Grafo::fechoTransitivoIndireto(int id){
    Grafo *transposto;
    transposto = this->geraGrafoTransposto();
    Vertice *v = transposto->encontraNo(id);
    vector<int> fechoTransitivoIndir;

    fechoTransitivoIndir = buscaCompForteConexas(transposto,v,fechoTransitivoIndir);
    transposto->~Grafo();
    imprimirFecho(fechoTransitivoIndir);
}

/** \brief A função gera o fecho transitivo direto dado um id de um vértice
 *
 * \param int id
 *
 */
void Grafo::fechoTransitivoDireto(int id){
    vector<int> fechoTransitivoDir;
    Vertice *v = encontraNo(id);

    fechoTransitivoDir = buscaMesmaCompConexo(v, fechoTransitivoDir);
    imprimirFecho(fechoTransitivoDir);
}

/** \brief A função imprime o fecho transitivo direto ou indireto
 *
 * \param vector fecho
 *
 */
void Grafo::imprimirFecho(vector<int> fecho){
    int i=0;
    while(i < (int)fecho.size() )
    {
        cout<<fecho[i]<< " " ;
        i++;
    }
}

/** \brief Ordena e frequencia resultante da busca em profundidade de forma decrescente
 *
 * \param int freqNos[]
 * \return vector<int> ordemC
 */
vector<int> Grafo::ordenaFreBusca(vector<int> ordemC, vector<int>freqNos){
    int maior = 0 , indice = 0;
    for(int l = 1; l < this->quantNos +1; l++)
    {
        maior = freqNos[l];
        for(int r = 0; r < this->quantNos ; r++)
        {
            if (maior <= freqNos[r])
            {
                indice = r;
                maior  = freqNos[r];
            }
        }
        freqNos[indice] = 0;
        ordemC.push_back(indice);
    }

    return ordemC;
}

/** \brief Seta todos os vertice do Grafo com nao visitao
 *
 * \param Grafo *g
 * \return Grafo *g
 */
Grafo * Grafo::setNaoVisitado(Grafo *g){
    Vertice* v;
    for (v = g->primeiroNo(); v != NULL; v = g->proximoNo())
    {
        v->setaVisitado(false);
    }
    delete(v);
    return g;
 }

/** @brief Função que gera um gafos transposto invertendo das aresta de um grafo direcionado G
 *   retornando G'
 * @return Grafo* gt
 *
 */
Grafo* Grafo::geraGrafoTransposto(){
    Vertice* v;
    Grafo* gt = new Grafo(true);
    Aresta *aux;
    for (v = this->primeiroNo(); v != NULL; v = this->proximoNo())
    {
        for(aux  = v->primeiraAresta(); aux != NULL; aux = v->proximaAresta() )
        {
            gt->adicionaAresta(aux->pegaIdDestino(),v->pegaId());
        }
    }
    gt->quantNos = this->quantNos;
    return gt;
}

/** \brief Funcao que retona as componentes fortemente conexas criando um array com as ordem dos vertice no retorno
 *   de uma busca em profundidade. Ao encontrar esse numeracao, e criado um grafo transposto( grafo G com as aresta invertidas).
 *   Depois e realizada uma busca em profundidade no grafo G' e as componete conexa de G' sao as componentes fortemente conexas de G
 *
 * \return vector< vector<int> > quantForteConexo
 *
 */
vector< vector<int> > Grafo::quantCompForteConexos(){
    Grafo* gt;
    Vertice* v;
    Vertice* k;
    vector< vector<int> > quantForteConexo;
    vector<int> compForteVisitado;
    vector<int> ordemC;
    vector<int> freqNos;
    int p = 0;

    for(int y = 0; y < this->quantNos+1; y++)
    {
        freqNos.push_back(0);
    }

    gt = this->geraGrafoTransposto();

    for (v = this->primeiroNo(); v != NULL; v = this->proximoNo())
    {
        if (v->foiVisitado() == false)
        {
             freqNos = buscaFreqNoConexas(v, &p, freqNos);
        }
    }

    this->setNaoVisitado(this);

    ordemC = this->ordenaFreBusca(ordemC,freqNos);

    for(int i = 0; i < gt->contaNos(); i++)
    {
        k = gt->encontraNo(ordemC[i]);
        if (k != NULL && k->foiVisitado() == false)
        {
             quantForteConexo.push_back( buscaCompForteConexas(gt,k,compForteVisitado) );
             compForteVisitado.clear();
        }
    }
    freqNos.clear();
    ordemC.clear();
    compForteVisitado.clear();
    gt->~Grafo();
    return quantForteConexo;
}

/** \brief Busca em profundidade das componete fortemente conexas em um grafo transposto
 *
 * \param Grafo *g -> Grafo aonde a busaca vai ser realizada
 * \param Vertice *v -> vertice inicial
 * \param vector<int> compForteConexas -> para armazenar os ID das componentes fortemente conexas
 * \param int calFre -> calcula a numeraçao para atribuir ao vertice
 * \param int freqNos[] -> array para guarda as numeração dos vertice na busca em profundidade
 * \return vector<int> compForteConexas
 *
 */
vector<int> Grafo::buscaCompForteConexas(Grafo* g ,Vertice *v, vector<int> compForteConexas){
    v->setaVisitado(true);
    compForteConexas.push_back(v->pegaId());
    Vertice *w = NULL;
    Aresta *aux = NULL;
    for(aux = v->primeiraAresta(); aux != NULL; aux = v->proximaAresta() )
    {
        w  = g->encontraNo(g,aux->pegaIdDestino());
        if (w->foiVisitado() == false)
        {
            compForteConexas = buscaCompForteConexas(g,w,compForteConexas);
        }
    }

    return compForteConexas;
}

/** \brief Retorna um vector com a ordem de cada vertice na volta da recursao de uma busca em profundidade
 *
 * \param Vertice *v
 * \param int *calFre
 * \param vector<int> freqNos
 * \return vector<int> freqNos
 */
vector<int> Grafo::buscaFreqNoConexas(Vertice *v, int *calFre, vector<int> freqNos){
    v->setaVisitado(true);
    Aresta *aux = NULL;
    for(aux = v->primeiraAresta(); aux != NULL; aux = v->proximaAresta() )
    {
        Vertice *w  = this->encontraNo(aux->pegaIdDestino());
        if (w->foiVisitado() == false)
        {
            freqNos = buscaFreqNoConexas(w, calFre, freqNos);
        }
    }
    *calFre += 1;
    freqNos[v->pegaId()] = *calFre;

    return freqNos;
}

/** \brief Retorna a quantidade de componentes conexas do grafo em uma matrix de vector
 *
 * \return vector < vector<int> >
 */
vector< vector<int> > Grafo::quantCompConexo(){
    Vertice* v;
    vector< vector<int> > quantConexo;
    vector<int> compVisitado;

    for (v = this->primeiroNo(); v != NULL; v = this->proximoNo())
    {
        if (v->foiVisitado() == false)
        {
             quantConexo.push_back( buscaMesmaCompConexo(v,compVisitado) );
             compVisitado.clear();
        }
    }
    this->setNaoVisitado(this);
    return quantConexo;
}

 /** \brief Retorna os ids de uma componente Conexa
  *
  * \param Vertice *v
  * \param vector<int> c
  * \return c
  *
  */
vector<int> Grafo::buscaMesmaCompConexo(Vertice *v, vector<int> c){
    v->setaVisitado(true);
    c.push_back(v->pegaId());
    Aresta *aux  = v->primeiraAresta();
    for(int i = 0; i < v->contaItems(); i++ )
    {
        Vertice *ve  = this->encontraNo(aux->pegaIdDestino());

        if (ve->foiVisitado() == false)
        {
           c = buscaMesmaCompConexo(ve,c);
        }
       aux  = v->proximaAresta();
    }
    return c;
}

/** \brief Verifica se dois vertices estao em uma mesmo conponente conexa
 *
 * \param int id1
 * \param int id2
 * \return bool
 *
 */
bool Grafo::mesmaComponenteConexa(int id1, int id2){
    bool comp = false, idV1 = false, idV2 = false;
    vector<int> compVisitado;
    Vertice* v;
    Vertice* v1 = this->encontraNo(id1);
    Vertice* v2 = this->encontraNo(id2);

    if(! (v1 && v2) )
    {
        return false;
    }
    else if (this->conexo())
    {
        return true;
    }
    else
    {
        for (v = this->primeiroNo(); v != NULL; v = this->proximoNo())
        {
            if (v->foiVisitado() == false)
            {
                compVisitado = buscaMesmaCompConexo(v,compVisitado);
                for(int t = 0 ; t < (int)compVisitado.size(); t++)
                {
                    if (id1 == compVisitado[t])
                    {
                        idV1 = true;
                    }
                    if (id2 == compVisitado[t])
                    {
                        idV2 = true;
                    }
                }
                compVisitado.clear();
                if( (idV1 && idV2 ) )
                {
                    comp = true;
                    break;
                }
                idV1 = false;
                idV2 = false;
            }

        }
    }
    this->setNaoVisitado(this);
    return comp;
}
/** \brief Busca em Profundidade para verificar se o Grafo é conexo
 *
 * \param Vertice *v
 * \param int contaVisi
 * \return int contaVisi
 */
int Grafo::buscaEmProfConexo(Vertice *v ,int contaVisi){
    v->setaVisitado(true);
    Aresta *aux  = v->primeiraAresta();
    for(int i = 0; i < v->contaItems(); i++ )
    {
        Vertice *ve  = this->encontraNo(aux->pegaIdDestino());

        if (ve->foiVisitado() == false)
        {
           contaVisi = buscaEmProfConexo(ve,contaVisi+1) ;
        }
       aux  = v->proximaAresta();
    }
    return contaVisi;
}

 /** \brief Verifica se o grafo eh conexo
  *
  * \return bool
  */
bool Grafo::conexo(){
    int quantVisitados = 0 ,quantVertice = 0;
    Vertice *v = this->primeiroNo();
    quantVertice = this->contaItems(); /// quantidade de vertice no grafo
    if (this->completo())
    {
        return true;
    }
    else
    {
        quantVisitados = this->buscaEmProfConexo(v,1); /// quantidade de vertice visitados
        for (v = this->primeiroNo(); v != NULL; v = this->proximoNo())
        {
            v->setaVisitado(false);
        }
        if (quantVisitados == quantVertice)
        {
            return true;
        }
    }
   return false;
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

/** \brief verifica se a aresta é ponte
 *
 * \param int id1
 * \param int id2
 * \return bool
 */
bool Grafo::arestaPonte(int id1, int id2){
    Vertice * v1 = this->encontraNo(id1);
    Vertice * v2 = this->encontraNo(id1);

    if ( this->encontraAresta(v1,id2) || this->encontraAresta(v2,id1))
    {
        this->removeAresta(id1, id2);

        if(this->conexo())
        {
            this->adicionaAresta(id1, id2);
            return false;
        }
        else
        {
            this->adicionaAresta(id1, id2);
            return true;
        }
    }
    else
        return false;

}

/** \brief verifica se o no eh de articulacao
 *
 * \param int id
 * \return bool
 */
bool Grafo::noArticulacao(int id){
    Vertice *re = this->encontraNo(id);
    if (!re)
    {
        return false;
    }
    vector<int> are;
    for (Aresta *i = re->primeiraAresta() ; i != NULL ; i = re->proximaAresta())
    {
        are.push_back(i->pegaIdDestino());
    }

    this->removeNo(id);

    if(this->conexo())
    {
        this->adicionaNo(re->pegaId());
        for (int i = 0; i < (int)are.size(); i++)
        {
            this->adicionaAresta(id, are[i]);
        }
        are.clear();
        return false;
    }
    else
    {
        this->adicionaNo(id);
        for (int i = 0; i < (int)are.size(); i++)
        {
            this->adicionaAresta(id, are[i]);
        }
        are.clear();
        return true;
    }
}

/** \brief Verifica se o nos sao adjacentes
 *
 * \param int id1
 * \param int id2
 * \return bool
 */
bool Grafo::nosSaoAdjacentes(int id1, int id2){
    Vertice *v1 = this->encontraNo(id1);

    if(!v1){ return false;}

    Aresta *a;
    a = v1->primeiraAresta();
    while (a)
    {
        if (a->pegaIdDestino() == id2)
        {
            return true;
        }
        a = v1->proximaAresta();

    }
    return false;

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
    Aresta *a;

    for (v = g->primeiroNo() ; v != NULL; v = g->proximoNo())
    {
        cout << v->pegaId() << " -> ";
        for (a = v->primeiraAresta() ; a != NULL; a = v->proximaAresta())
        {
            cout << a->pegaIdDestino() << " (P-> " << a->pegaPeso() << ") ";
        }
        cout << endl;
    }
    delete(v);
    delete(a);
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

bool Aresta::ordenaArestaPeso(const Aresta* a1, const Aresta* a2){
    return (a1->peso < a2->peso);
    //return min(a1->peso, a2->peso);
};





