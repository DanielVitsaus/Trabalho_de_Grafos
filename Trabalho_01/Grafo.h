#ifndef VERTICE_H_INCLUDED
#define VERTICE_H_INCLUDED
#include "Lista.h"
#include <iostream>
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
        Aresta* encontraAresta(int id);

    public:
        Vertice(int Id) { this->id=Id; };
        int pegaId() { return this->id; };
        int pegaGrau() { return Lista::contaItems(); };
        void adicionaAresta(int id_destino) { Lista::adicionaItem(new Aresta(id_destino)); };
        void removeAresta() { Lista::deletaItem(Lista::it); };
        bool removeAresta(int id);
        Aresta* primeiraAresta() { return (Aresta*)Lista::inicioLista(); };
        Aresta* proximaAresta() { return (Aresta*)Lista::caminhaLista(); };
        Aresta* arestaAnterior() { return (Aresta*)Lista::retornaLista(); };
        Aresta* ultimaAresta() { return (Aresta*)Lista::fimLista(); };

};

class Grafo: private Lista {

    private:
        Vertice* encontraNo(int id);
        Aresta* encontraAresta(Vertice *v, int id);

        Vertice* primeiroNo() { return (Vertice*)Lista::inicioLista(); };
        Vertice* proximoNo() { return (Vertice*)Lista::caminhaLista(); };
        Vertice* noAnterior() { return (Vertice*)Lista::retornaLista(); };
        Vertice* ultimoNo() { return (Vertice*)Lista::fimLista(); };

    public:
        int contaNos() { return Lista::contaItems(); }

        // Funções exigidas na especificação do trabalho
        /* 1 ok */ Vertice* adicionaNo(int id);
        /* 1 ok */ void adicionaAresta(int id_origem, int id_destino);
        /* 1 ok */ void removeNo(int id);
        /* 1 ok */ void removeAresta(int id_no1, int id_no2);
        /* 2 ok */ int grauNo(int id);
        /* 3 */ bool kRegular();
        /* 4 */ bool completo();
        /* 5 */ bool nosSaoAdjacentes(int id1, int id2);
        /* 6 */ bool conexo();
        /* 7 */ bool mesmaComponenteConexa(int id1, int id2);
        /* 8 */ bool noArticulacao(int id);
        /* 9 */ bool arestaPonte(int id1, int id2);

};


#endif
