#ifndef VERTICE_H_INCLUDED
#define VERTICE_H_INCLUDED
#include "Lista.h"
#include <iostream>
#include <vector>

using namespace std;

#define max_bateria 5000
#define sobra_bateria max_bateria*0.01

#define coordToId(xxx,yyy) ((xxx<<16)|yyy)
#define idToX(idid) (idid>>16)
#define idToY(idid) (idid&0x0000FFFF)

class Aresta: public Item {

    private:
        int id_dst;        // ID do vertice de destino
        double peso;        // Peso da aresta

    public:
        Aresta(int id_vert_dst) { this->id_dst = id_vert_dst; this->peso = 0; };
        Aresta(int id_vert_dst, double peso) { this->id_dst = id_vert_dst; this->peso = peso; };
        int pegaIdDestino() { return this->id_dst; };
        double pegaPeso() { return this->peso; };

};

class Vertice: public Lista, public Item {

    private:
        int id;         // ID do Vertice
        int t;
        bool visitado;  // verifica se o vertuce foi visitado

    public:
        Vertice(int Id) { this->id=Id; this->visitado = false; };
        Vertice(int x, int y, int t) { this->id=coordToId(x,y); this->t=t; this->visitado = false; };
        ~Vertice();
        Aresta* encontraAresta(int id);
        bool foiVisitado() { return this->visitado; };
        void setaVisitado(bool vi) { this->visitado = vi; };
        int pegaId() { return this->id; };
        int pegaT() { return this->t; };
        int pegaX() { return idToX(this->id); };
        int pegaY() { return idToY(this->id); };
        int pegaGrau() { return Lista::contaItems(); };
        void adicionaAresta(int id_destino) { if (!this->encontraAresta(id_destino)) Lista::adicionaItem(new Aresta(id_destino)); };
        void adicionaAresta(int id_destino, double peso) { if (!this->encontraAresta(id_destino)) Lista::adicionaItem(new Aresta(id_destino, peso)); };
        void removeAresta() { Lista::deletaItem(Lista::it); };
        bool removeAresta(int id);
        bool removeAresta(int x, int y) { return this->removeAresta(coordToId(x,y)); };
        bool existeAresta(int id);
        bool existeAresta(int x, int y) { return this->existeAresta(coordToId(x,y)); };
        Aresta* primeiraAresta() { return (Aresta*)Lista::inicioLista(); };
        Aresta* proximaAresta() { return (Aresta*)Lista::caminhaLista(); };
        Aresta* arestaAnterior() { return (Aresta*)Lista::retornaLista(); };
        Aresta* ultimaAresta() { return (Aresta*)Lista::fimLista(); };

};

class Grafo: private Lista {

    private:
        Vertice* encontraNo(int id);
        bool encontraAresta(Vertice *v, int id);

    public:
        ~Grafo();

        vector<int>* GRASP(int idbase, int iter, double maxpct);
        vector<int>* Guloso(int idbase, double pct);
        bool visitouTodosNos();

        double CustoTotal(vector<int> *ids);

        int contaNos() { return Lista::contaItems(); }

        Vertice* primeiroNo() { return (Vertice*)Lista::inicioLista(); };
        Vertice* proximoNo() { return (Vertice*)Lista::caminhaLista(); };
        Vertice* noAnterior() { return (Vertice*)Lista::retornaLista(); };
        Vertice* ultimoNo() { return (Vertice*)Lista::fimLista(); };

        /// Funções exigidas na especificação do trabalho
        Vertice* adicionaNo(int id);
        Vertice* adicionaNo(int x, int y, int t);
        void adicionaAresta(int id_origem, int id_destino);
        void removeNo(int id);
        void removeNo(int x, int y) { this->removeNo(coordToId(x,y)); };
        void removeAresta(int id_no1, int id_no2);
        int grauNo(int id);
        bool completo();

};


#endif
