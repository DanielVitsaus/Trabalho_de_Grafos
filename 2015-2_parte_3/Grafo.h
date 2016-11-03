/** \brief Grafo.h
 *
 */
#ifndef VERTICE_H_INCLUDED
#define VERTICE_H_INCLUDED
#include <iostream>
#include <vector>

#include "Lista.h"
#include "Alfa.h"


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
        float razao;
        float pesoV;
        Vertice(int Id) { this->id=Id; this->visitado = false; particao = 0; };
        ~Vertice();
        bool foiVisitado() { return this->visitado; };
        void setaVisitado(bool vi) { this->visitado = vi; };
        int pegaId() { return this->id; };
        int pegaGrau() { return Lista::contaItems(); };
        int pegaGrauDecre() { return Lista::contaItemsDecre(); };
        void decreGrau() { Lista::decrementaItem(); };
        void adicionaAresta(int id_destino) { Lista::adicionaItem(new Aresta(id_destino)); };
        void adicionaAresta(int id_destino, float peso) { Lista::adicionaItem(new Aresta(id_destino, peso)); };
        void removeAresta() { Lista::deletaItem(Lista::it); };
        void setParticao(int part){ this->particao = part; };
        void setRazao(float razao){ this->razao = razao; };
        void SetPesoV(float pesoV){ this->pesoV = pesoV; };
        float getPesoV(){ return this->pesoV; };
        float getRazao(){ return this->razao; };
        int getParticao() { return this->particao; };
        bool removeAresta(int id);
        bool existeAresta(int id);
        Aresta* primeiraAresta() { return (Aresta*)Lista::inicioLista(); };
        Aresta* proximaAresta() { return (Aresta*)Lista::caminhaLista(); };
        Aresta* arestaAnterior() { return (Aresta*)Lista::retornaLista(); };
        Aresta* ultimaAresta() { return (Aresta*)Lista::fimLista(); };
        Aresta* encontraAresta(int id);
        float pegaPesoAresta(int id);

        static bool ordenaVerticeRazao(const Vertice* v1, const Vertice* v2);

};

class Grafo: private Lista {

    private:
        int buscaEmProfConexo(Vertice *v ,int contaVisi);
        bool encontraAresta(Vertice *v, int id);
        bool direcionado;
        void imprimirFecho(vector<int> c);

        Vertice* encontraNo(Grafo*g,int id);
        vector<int> buscaMesmaCompConexo(Vertice *v, vector<int> c);
        vector<int> buscaCompForteConexas(Grafo *g,Vertice *v, vector<int> compForteConexas);

        void decrementaGrau(vector<Vertice*> lista, int no);
        vector<Vertice*> ordenaVertice();
        vector<Vertice*> atualizaLista(vector<Vertice*> lista, int id);
        vector<Vertice*> melhorSolu(float &melhorCusto, float &somaValor, float &alfa,  float alfa2, vector<Vertice*> solu, vector<Vertice*> soluParcial);
        int escolheAlfa(vector<Alfa*> alfa);


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

        Vertice* encontraNo(int id);
        Vertice* primeiroNo() { return (Vertice*)Lista::inicioLista(); };
        Vertice* proximoNo() { return (Vertice*)Lista::caminhaLista(); };
        Vertice* noAnterior() { return (Vertice*)Lista::retornaLista(); };
        Vertice* ultimoNo() { return (Vertice*)Lista::fimLista(); };

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ////  Parte 1 ////

        Vertice* adicionaNo(int id);
        void adicionaAresta(int id_origem, int id_destino);
        void adicionaAresta(int id_origem, int id_destino, float peso);
        void removeNo(int id);
        void removeAresta(int id_no1, int id_no2);
        int grauNo(int id);
        int ordemGrafo();
        bool conexo();


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ///// Parte 3 ////

        vector<Vertice*> ContrutivoCoberturaPonderada(float alfaGuloso, float &tempoGuloso);
        vector<Vertice*> CoberturaRamdomizado(float alfaRand, int numIteracao, float &tempoRand);
        vector<Vertice*> CoberturaReativo( vector<Alfa*> alfa, float &alfaReativo, int numIteracaoBloco, int numIteracao, float &tempoReativo);


};


#endif
