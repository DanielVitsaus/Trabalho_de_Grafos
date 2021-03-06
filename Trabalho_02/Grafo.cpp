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

using namespace std;

/** \brief função que busca o subconjunto de um elemento "i"
 *
 * \param int subset[]
 * \param int i
 * \return int i
 *
 */
int Grafo::buscar(int subset[], int i)
{
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
void Grafo::unir(int subset[], int v1, int v2)
{
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
Grafo* Grafo::Kruskal(vector<Aresta*> are)
{
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
bool Grafo::ehADJ(int v, int subset[])
{
    if (subset[v] == v)
        return true;

    return false;
}
/** \brief Funcao Prim para encontrar a arvore gerado minima
 *
 * \return Grafo* g
 */
 Grafo* Grafo::Prim(vector<int> verGafo)
 {
     srand (time(NULL));
     Grafo* ar = new Grafo();
     int tamV, indiceRandom, dest;
     tamV = this->quantNos;
     Vertice* v;
     Aresta* a;
     Aresta* are;
     vector<int> vertGM;
     vector<Aresta*> arestaGM;
     vector<Aresta*> arestaP;
     indiceRandom = rand() % tamV;
      //dest = retornaIndice(verGafo, a->pegaIdDestino());
     v = this->encontraNo(verGafo[indiceRandom]);
     cout << "Foiiiii 111\n"<< endl;
     vertGM.push_back(verGafo[0]);
     verGafo.erase(verGafo.begin() + indiceRandom);

     for (Aresta*  ares1 = v->primeiraAresta(); ares1 != NULL; ares1 = v->proximaAresta())
     {
         are = new Aresta(v->pegaId(),ares1->pegaIdDestino(), ares1->pegaPeso());
         arestaP.push_back(are);
     }
     cout << "Foiiiii 2222\n"<< endl;
     int k = 1;
     bool sai = false;
     while (!verGafo.empty())
     {
         if (arestaP.size()>1)
         {
             sort(arestaP.begin(), arestaP.end(), Aresta::ordenaArestaPeso);
         }
        //if (!arestaP.empty())
       // {
            a = arestaP[0];

            arestaGM.push_back(a);

            arestaP.erase(arestaP.begin());
        //}
        dest = retornaIndice(verGafo, a->pegaIdDestino());

        //cout << dest <<"\n"<< endl;

        v = this->encontraNo(verGafo[dest]);

        cout << dest <<"\n"<< endl;

        vertGM.push_back(verGafo[dest]);

        verGafo.erase(verGafo.begin()+dest);

        //cout << dest <<"\n"<< endl;
        cout << dest <<"\n"<< endl;
        for (Aresta* ares = v->primeiraAresta(); ares != NULL; ares = v->proximaAresta())
        {
            if (!tanaLista(ares->pegaIdDestino(),vertGM))
            {
                cout << "Foiiiii 3333\n"<< endl;
                are = new Aresta(v->pegaId(),ares->pegaIdDestino(), ares->pegaPeso());
                arestaP.push_back(are);
            }
        }

        cout << "Foiiiii 4444\n"<< endl;
        if(k == (int)verGafo.size()-1)
        {
            sai = true;
        }

     }
    cout << "Foiiiii 5555\n"<< endl;

     for (int i = 0; i< (int)arestaGM.size(); i++)
     {
         ar->adicionaAresta(arestaGM[i]->pegaIdOrigem(), arestaGM[i]->pegaIdDestino(), arestaGM[i]->pegaPeso());
     }
     cout << "Foiiiii 6666\n"<< endl;

    return ar;
 }

int Grafo::retornaIndice(vector<int> verGafo, int id)
{
    int i = 0;
    for(i = 0; i < (int) verGafo.size(); i++)
    {
        if (verGafo[i] == id)
        {
            return i;
        }
    }
    //return false;
}

bool Grafo::tanaLista(int id, vector<int> v)
{
    for (int i = 0; i < (int)v.size(); i++)
    {
        if (id == v[i])
	{
	    return true;
	}
    }

    return false;
}


/** \brief A função gera o fecho transitivo indireto dado um id de um vertice.
 *
 * \param  int id
 *
 */
void Grafo::fechoTransitivoIndireto(int id)
{
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
void Grafo::fechoTransitivoDireto(int id)
{
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
void Grafo::imprimirFecho(vector<int> fecho)
{
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
vector<int> Grafo::ordenaFreBusca(vector<int> ordemC, vector<int>freqNos)
{
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
 Grafo * Grafo::setNaoVisitado(Grafo *g)
 {
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
Grafo* Grafo::geraGrafoTransposto()
{
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
 vector< vector<int> > Grafo::quantCompForteConexos()
 {
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
vector<int> Grafo::buscaCompForteConexas(Grafo* g ,Vertice *v, vector<int> compForteConexas)
{
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
vector<int> Grafo::buscaFreqNoConexas(Vertice *v, int *calFre, vector<int> freqNos)
{
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


/** \brief Construtor para grafo nao direcionado
 */
Grafo::Grafo() {
    this->direcionado = false;
}

/** \brief Construto para grafo direcionado (digrafo)
*    \ parametor dir que define se o grafo é direcionado
*
* \param bool dir
*
*/
Grafo::Grafo(bool dir) {
    this->direcionado = dir;
}

/** \brief  Destrutor  */
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

/** \brief Retorna a quantidade de componentes conexas do grafo em uma matrix de vector
 *
 * \return vector < vector<int> >
 */
vector< vector<int> > Grafo::quantCompConexo()
{
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
vector<int> Grafo::buscaMesmaCompConexo(Vertice *v, vector<int> c)
{
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
bool Grafo::mesmaComponenteConexa(int id1, int id2)
{
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
int Grafo::buscaEmProfConexo(Vertice *v ,int contaVisi)
{
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
bool Grafo::conexo()
{
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

/** \brief Verifica se o grafo eh completo
 *
 * \return bool
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

/** \brief Vetifica se a aresta existe
 *
 * \param Vertice *v
 * \param int id
 * \return bool
 */
bool Grafo::encontraAresta(Vertice *v, int id)
{
    return v->existeAresta(id);
}

/** \brief verifica se a aresta é ponte
 *
 * \param int id1
 * \param int id2
 * \return bool
 */
bool Grafo::arestaPonte(int id1, int id2)
{
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
bool Grafo::noArticulacao(int id)
{
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

/** \brief Verifica se o grafo é K-Regular
 *
 * \return bool
 */

bool Grafo::kRegular()
{
    int grau1;
    Vertice *v = this->primeiroNo();
    int grau = grauNo(v->pegaId());

    while(v)
    {
        grau1 = grauNo(v->pegaId());
        if(grau1!=grau)
        {
            return false;
        }
        v = this->proximoNo();
    }
    return true;
}

/** \brief Verifica se o nos sao adjacentes
 *
 * \param int id1
 * \param int id2
 * \return bool
 */
bool Grafo::nosSaoAdjacentes(int id1, int id2)
{
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
Vertice* Grafo::encontraNo(Grafo*g,int id)
{
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

/** \brief Adiciona um Vertice com a id dada caso não exista, caso exista retorna ponteiro para o Vertice
 *
 * \param int id
 * \return Vertice *v
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

/** \brief Adiciona uma aresta em id_origem, apontando (quando pertinente) para id_destino
 *
 * \param int id_origem
 * \param int id_destino
 */
void Grafo::adicionaAresta(int id_origem, int id_destino)
{
    Vertice *vd = this->adicionaNo(id_destino);
    Vertice *vo = this->adicionaNo(id_origem);

    vo->adicionaAresta(id_destino);

    if (!this->direcionado) vd->adicionaAresta(id_origem);

}

/** \brief Adiciona uma aresta com PESO, em id_origem apontando (quando pertinente) para id_destino
 *
 * \param int id_origem
 * \param int id_destino
 * \param float peso
 */
void Grafo::adicionaAresta(int id_origem, int id_destino, float peso)
{
    Vertice *vd = this->adicionaNo(id_destino);
    Vertice *vo = this->adicionaNo(id_origem);

    vo->adicionaAresta(id_destino, peso);
    if (!this->direcionado) vd->adicionaAresta(id_origem, peso);

}

/** \brief Procura o Vertice que possui a id dada, e deleta caso encontre
 *
 * \param int id
 */
void Grafo::removeNo(int id)
{
    Vertice *v = this->encontraNo(id);
    if (!v) return;

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

/** \brief Remove uma aresta entre dois vertices
 *
 * \param int id_no1
 * \param int id_no2
 *
 */
void Grafo::removeAresta(int id_no1, int id_no2)
{
    Vertice *v1 = this->encontraNo(id_no1);
    Vertice *v2 = this->encontraNo(id_no2);

    if (!(v1 &&  v2)) return ;

    v1->removeAresta(id_no2);
    v2->removeAresta(id_no1);

}

/** \brief  Retorna o grau do vertice (no) passando como parametro o id no vertice(no)
 *
 * \param int id
 * \return int grau
 */
int Grafo::grauNo(int id) {

    Vertice *v = this->encontraNo(id);

    if (v) return v->pegaGrau();
    else return -1;

}

/** \brief Imprime cada vertice (no) com os nos adjacentes
 *
 * \param Grafo* g
 */
void Grafo::imprimeGrafo(Grafo* g)
{
    Vertice *v;
    Aresta *a;

    for (v = g->primeiroNo() ; v != NULL; v = g->proximoNo())
    {
        cout << v->pegaId() << " -> ";
        for (a = v->primeiraAresta() ; a != NULL; a = v->proximaAresta())
        {
            cout << a->pegaIdDestino() << " ";
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
bool Vertice::existeAresta(int id)
{
    Aresta *a = this->encontraAresta(id);
    if (a)
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

    return 0;
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

    if (a) {
        Lista::deletaItem(a);
        delete a;
        return true;
    }
    else
        return false;

}

bool Aresta::ordenaArestaPeso(const Aresta* a1, const Aresta* a2)
{
    return (a1->peso < a2->peso);
};


