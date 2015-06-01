#ifndef VERTICE_H_INCLUDED
#define VERTICE_H_INCLUDED
#include "Lista.h"
#include <iostream>
#include <vector>

using namespace std;

class Aresta: public Item {

    private:
        int id_dst;        // ID do vertice de destino
        float peso;        // Peso da aresta

    public:
        Aresta(int id_vert_dst) { this->id_dst = id_vert_dst; this->peso = 0; };
        Aresta(int id_vert_dst, float peso) { this->id_dst = id_vert_dst; this->peso = peso; };
        int pegaIdDestino() { return this->id_dst; };
        float pegaPeso() { return this->peso; };

};

class Vertice: public Lista, public Item {

    private:
        int id;         // ID do Vertice
        bool visitado;  // verifica se o vertuce foi visitado
        Aresta* encontraAresta(int id);

    public:
        Vertice(int Id) { this->id=Id; this->visitado = false; };
        ~Vertice();
        bool foiVisitado() { return this->visitado; };
        void setaVisitado(bool vi) { this->visitado = vi; };
        int pegaId() { return this->id; };
        int pegaGrau() { return Lista::contaItems(); };
        void adicionaAresta(int id_destino) { Lista::adicionaItem(new Aresta(id_destino)); };
        void adicionaAresta(int id_destino, float peso) { Lista::adicionaItem(new Aresta(id_destino, peso)); };
        void removeAresta() { Lista::deletaItem(Lista::it); };
        bool removeAresta(int id);
        bool existeAresta(int id);
        Aresta* primeiraAresta() { return (Aresta*)Lista::inicioLista(); };
        Aresta* proximaAresta() { return (Aresta*)Lista::caminhaLista(); };
        Aresta* arestaAnterior() { return (Aresta*)Lista::retornaLista(); };
        Aresta* ultimaAresta() { return (Aresta*)Lista::fimLista(); };

};

class Grafo: private Lista {

    private:
        Vertice* encontraNo(int id);
        Vertice* encontraNo(Grafo*g,int id);
        bool encontraAresta(Vertice *v, int id);
        int buscaEmProfConexo(Vertice *v ,int contaVisi);
        vector<int> buscaMesmaCompConexo(Vertice *v, vector<int> c);
        vector<int> buscaCompForteConexas(Grafo *g,Vertice *v, vector<int> compForteConexas);
        bool direcionado;

    public:
        int quantNos;
        Grafo();
        Grafo(bool dir);
        ~Grafo();

        int contaNos() { return Lista::contaItems(); }
        void imprimeGrafo(Grafo* g);
        Grafo * setNaoVisitado(Grafo *g);
        vector<int> ordenaFreBusca(vector<int> ordemC,vector<int>freqNos);
        Grafo* geraGrafoTransposto();
        vector<int> buscaFreqNoConexas(Vertice *v, int *calFre, vector<int> freqNos);

        Vertice* primeiroNo() { return (Vertice*)Lista::inicioLista(); };
        Vertice* proximoNo() { return (Vertice*)Lista::caminhaLista(); };
        Vertice* noAnterior() { return (Vertice*)Lista::retornaLista(); };
        Vertice* ultimoNo() { return (Vertice*)Lista::fimLista(); };


        Vertice* adicionaNo(int id);
        void adicionaAresta(int id_origem, int id_destino);
        void adicionaAresta(int id_origem, int id_destino, float peso);
        void removeNo(int id);
        void removeAresta(int id_no1, int id_no2);
        int grauNo(int id);
        bool kRegular();
        bool completo();
        bool nosSaoAdjacentes(int id1, int id2);
        bool conexo();
        bool mesmaComponenteConexa(int id1, int id2);
        bool noArticulacao(int id);
        bool arestaPonte(int id1, int id2);
        vector< vector<int> > quantCompConexo();

        vector< vector<int> > quantCompForteConexos();


};


#endif
