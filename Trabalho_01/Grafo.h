#ifndef VERTICE_H_INCLUDED
#define VERTICE_H_INCLUDED
#include "Lista.h"

class Vertice;
class Aresta;

class Aresta: public Item {

    private:
        int id_vert_dst;   // ID do vertice de destino

    public:
        Aresta(int id_vert_dst) { this->id_vert_dst = id_vert_dst; };
        int pegaIdDestino() { return this->id_vert_dst; };

};

class Vertice: public Lista, public Item {

    private:
        float peso;
        int grau;

    public:
        Vertice(int Id) { Item::setaInfo(Id); this->grau = 0; };
        Vertice(int Id, float peso) { Item::setaInfo(Id); this->peso = peso; this->grau = 0; };
        int pegaId() { return Item::pegaInfo(); };
        float pegaPeso() { return this->peso; };
        void setaPeso(float peso) { this->peso = peso; };
        int pegaGrau() { return this->grau; };
        void incGrau() { this->grau++; };
        void decGrau() { this->grau--; };

};

class Grafo: private Lista {

    private:
        Vertice *encontraNo(int id);

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
