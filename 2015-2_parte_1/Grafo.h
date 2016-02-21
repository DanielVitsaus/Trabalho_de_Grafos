#ifndef VERTICE_H_INCLUDED
#define VERTICE_H_INCLUDED
#include "Lista.h"
#include <iostream>
#include <vector>

using namespace std;

class Aresta: public Item {

    private:
        int id_ori;        ///< ID do vertice de origem
        int id_dst;        ///< ID do vertice de destino

    public:
        float peso;
        Aresta(int id_vert_dst) { this->id_dst = id_vert_dst; this->peso = 0; };
        Aresta(int id_vert_dst, float peso) { this->id_dst = id_vert_dst; this->peso = peso; };
        Aresta(int id_vert_ori, int id_vert_dst, float peso) { this->id_ori = id_vert_ori; this->id_dst = id_vert_dst; this->peso = peso; };
        int pegaIdDestino() { return this->id_dst; };
        int pegaIdOrigem() { return this->id_ori; };
        float pegaPeso() { return this->peso; };
        static bool ordenaArestaPeso(const Aresta* a1, const Aresta* a2);

};

class Vertice: public Lista, public Item {

    private:
        int id;         ///< ID do Vertice.
        bool visitado;  ///< verifica se o vertice foi visitado.
        int particao; ///< verificar em qual particao o vertice pertence.


    public:
        Vertice(int Id) { this->id=Id; this->visitado = false; particao = 0; };
        ~Vertice();
        bool foiVisitado() { return this->visitado; };
        void setaVisitado(bool vi) { this->visitado = vi; };
        int pegaId() { return this->id; };
        int pegaGrau() { return Lista::contaItems(); };
        void adicionaAresta(int id_destino) { Lista::adicionaItem(new Aresta(id_destino)); };
        void adicionaAresta(int id_destino, float peso) { Lista::adicionaItem(new Aresta(id_destino, peso)); };
        void removeAresta() { Lista::deletaItem(Lista::it); };
        void setParticao(int part){ this->particao = part; };
        int getParticao() { return this->particao; };
        bool removeAresta(int id);
        bool existeAresta(int id);
        Aresta* primeiraAresta() { return (Aresta*)Lista::inicioLista(); };
        Aresta* proximaAresta() { return (Aresta*)Lista::caminhaLista(); };
        Aresta* arestaAnterior() { return (Aresta*)Lista::retornaLista(); };
        Aresta* ultimaAresta() { return (Aresta*)Lista::fimLista(); };
        Aresta* encontraAresta(int id);
        float pegaPesoAresta(int id);

};

class Grafo: private Lista {

    private:
        int buscaEmProfConexo(Vertice *v ,int contaVisi);
        bool encontraAresta(Vertice *v, int id);
        bool direcionado;
        void imprimirFecho(vector<int> c);
        Vertice* menorPesoA(Vertice* v, float *va, float *maiorPeso);
        Vertice* encontraNo(Grafo*g,int id);
        vector<int> buscaMesmaCompConexo(Vertice *v, vector<int> c);
        vector<int> buscaCompForteConexas(Grafo *g,Vertice *v, vector<int> compForteConexas);


    public:
        int quantNos;
        Grafo();
        Grafo(bool dir);
        ~Grafo();

        void imprimeGrafo(Grafo* g);
        void unir(int subset[], int v1, int v2);
        int contaNos() { return Lista::contaItems(); }
        int buscar(int subset[], int i);
        bool ehADJ(int v, int subset[]);
        bool existeCamonho(Grafo *g,int orin,int dest);
        Grafo * setNaoVisitado(Grafo *g);
        Grafo* geraGrafoTransposto();
        vector<int> ordenaFreBusca(vector<int> ordemC,vector<int>freqNos);
        vector<int> buscaFreqNoConexas(Vertice *v, int *calFre, vector<int> freqNos);

        //static bool ordenaAresta(const Aresta* a1, const Aresta* a2);

        Vertice* encontraNo(int id);
        Vertice* primeiroNo() { return (Vertice*)Lista::inicioLista(); };
        Vertice* proximoNo() { return (Vertice*)Lista::caminhaLista(); };
        Vertice* noAnterior() { return (Vertice*)Lista::retornaLista(); };
        Vertice* ultimoNo() { return (Vertice*)Lista::fimLista(); };

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ////  Parte 1 ////
        Vertice* adicionaNo(int id); //OK
        void adicionaAresta(int id_origem, int id_destino); //OK
        void adicionaAresta(int id_origem, int id_destino, float peso); //OK
        void removeNo(int id); //OK
        void removeAresta(int id_no1, int id_no2); //OK
        int grauNo(int id); //OK
        int grauGrafo(); //OK
        int ordemGrafo(); //OK
        bool ehTrivial(); //OK
        bool ehNulo(); //OK
        bool kRegular(int id); //OK
        bool completo(); //OK
        bool ehMultigrafo(); //OK
        bool ehBipartido(Vertice* v, bool mudaPart); //OK
        Grafo* vizinhacaAberta(int id); //OK
        Grafo* vizinhacaFechada(int id); //OK
        pair<Grafo*, float> menorCaminho(int id_origem, int id_destino); //OK

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //// Parte 2 ////

        bool buscaLargura(int id); //OK
        bool buscaProfundidade(Vertice *v, int id); //OK
        void floyd();// OK
        Grafo* Prim(vector<int> verGafo);// OK
        Grafo* Kruskal(vector<Aresta*> are); //OK


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //// Outros ////
        void fechoTransitivoDireto(int id);
        void fechoTransitivoIndireto(int id);
        bool ehMultiDigrafo();
        bool conexo();
        bool nosSaoAdjacentes(int id1, int id2);
        bool mesmaComponenteConexa(int id1, int id2);
        bool noArticulacao(int id);
        bool arestaPonte(int id1, int id2);
        vector< vector<int> > quantCompConexo();
        vector< vector<int> > quantCompForteConexos();

};


#endif
