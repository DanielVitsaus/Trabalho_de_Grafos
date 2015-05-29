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
        bool foiVisitado() { return this->visitado; };
        void setaVisitado(bool vi) { this->visitado = vi; };
        int pegaId() { return this->id; };
        int pegaGrau() { return Lista::contaItems(); };
        void adicionaAresta(int id_destino) { Lista::adicionaItem(new Aresta(id_destino)); };
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
        bool encontraAresta(Vertice *v, int id);
        int buscaEmProfConexo(Vertice *v ,int contaVisi);
        vector<int> buscaMesmaCompConexo(Vertice *v, vector<int> c);


    public:
        int contaNos() { return Lista::contaItems(); }

        Vertice* primeiroNo() { return (Vertice*)Lista::inicioLista(); };
        Vertice* proximoNo() { return (Vertice*)Lista::caminhaLista(); };
        Vertice* noAnterior() { return (Vertice*)Lista::retornaLista(); };
        Vertice* ultimoNo() { return (Vertice*)Lista::fimLista(); };

        /// Funções exigidas na especificação do trabalho
        /* 1 ok */ Vertice* adicionaNo(int id);
        /* 1 ok */ void adicionaAresta(int id_origem, int id_destino);
        /* 1 ok */ void removeNo(int id);
        /* 1 ok */ void removeAresta(int id_no1, int id_no2);
        /* 2 ok */ int grauNo(int id);
        /* 3 ok */ bool kRegular();
        /* 4 ok */ bool completo();
        /* 5 ok */ bool nosSaoAdjacentes(int id1, int id2);
        /* 6 ok */ bool conexo();
        /* 7 ok */ bool mesmaComponenteConexa(int id1, int id2);
        /* 8 ok */ bool noArticulacao(int id);
        /* 9 ok */ bool arestaPonte(int id1, int id2);
        /* 10 OK*/ vector< vector<int> > quantCompConexo();

        /// Falta a leitura e gravação de arquivos

};


#endif
