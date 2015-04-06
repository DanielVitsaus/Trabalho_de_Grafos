#include "Grafo.h"
#include <iostream>
#include <vector>
using namespace std;

///* -------------------------------------------- CLASSE GRAFO ------------------------------------------ *///

vector< vector<int> > Grafo::quantCompConexo()
{
    Vertice* v;
    vector< vector<int> > quantConexo;
    vector<int> compVisitado;

    for (v = this->primeiroNo(); v != NULL; v = this->proximoNo()) /// percorre os vertices
    {
        if (v->foiVisitado() == false)/// pega o primeiro vertice nao visitado
        {
             quantConexo.push_back( buscaMesmaCompConexo(v,compVisitado) );
             compVisitado.clear();
        }
    }
    return quantConexo;
}

/// Retorna os ids de uma componente Conexa
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

/// Verifica se dois vertices estao em uma mesmo conponente conexa
bool Grafo::mesmaComponenteConexa(int id1, int id2)
{
    bool comp = false, idV1 = false, idV2 = false;
    vector<int> compVisitado; /// armazena os ids de uma componente conexa
    Vertice* v;
    if (this->conexo())
    {
        return true;
    }
    else
    {
        for (v = this->primeiroNo(); v != NULL; v = this->proximoNo()) /// percorre os vertices
        {
            if (v->foiVisitado() == false)/// pega o primeiro vertice nao visitado
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
    for (v = this->primeiroNo(); v != NULL; v = this->proximoNo())/// seta todos os vertices como nao visitado
    {
        v->setaVisitado(false);
    }

    return comp;
}

/// Busca em Profundidade para verificar se o Grafo é conexo
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

/// Verifica se o grafo eh conexo
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

/// verifica se o grafo eh completo
bool Grafo::completo(){
    int aux;
    int numVertices = this->contaNos(); ///armazena a quantidade de nós existentes
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

///Vetifica se a aresta existe
bool Grafo::encontraAresta(Vertice *v, int id)
{
    return v->existeAresta(id);
}

/// verifica se a aresta é ponte
bool Grafo::arestaPonte(int id1, int id2)
{
    Vertice * v1 = this->encontraNo(id1);
    Vertice * v2 = this->encontraNo(id1);

    if ( this->encontraAresta(v1,id2) || this->encontraAresta(v2,id1)) /// verifica se as arestas exitem
    {
        this->removeAresta(id1, id2);

        if(this->conexo())
        {
            this->adicionaAresta(id1, id2); ///readiciona a aresta eliminada antes de informar se a aresta é ponte ou não
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

///verifica se o no eh de articulacao
bool Grafo::noArticulacao(int id)
{
    Vertice *re = this->encontraNo(id);
    vector<int> are; ///vector para armazenar as arestas do no que vai ser removido
    for (Aresta *i = re->primeiraAresta() ; i != NULL ; i = re->proximaAresta())
    {
        are.push_back(i->pegaIdDestino());/// add as arestas
    }

    this->removeNo(id);

    if(this->conexo())
    {
        ///adiciona novamente o vertice e as arestas
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
        ///adiciona novamente o vertice e as arestas
        this->adicionaNo(id);
        for (int i = 0; i < (int)are.size(); i++)
        {
            this->adicionaAresta(id, are[i]);
        }
        are.clear();
        return true;
    }
}

///Verifica se o grafo é K-Regular
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

///Verifica se o nos soa adjacentes
bool Grafo::nosSaoAdjacentes(int id1, int id2)
{
    Vertice *v1 = this->encontraNo(id1);
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

/// Encontra um Vertice com a id dada
Vertice* Grafo::encontraNo(int id) {

        Vertice *v = this->primeiroNo();

        while (v) {
            if (v->pegaId()==id) return v;
            else v = this->proximoNo();
        }

        return 0;
}

/// Adiciona um Vertice com a id dada caso não exista, caso exista retorna ponteiro para o Vertice
Vertice* Grafo::adicionaNo(int id) {

    Vertice *v = this->encontraNo(id); /// Tenta encontrar Vertice com essa id

    if (!v) {  /// Se não encontrou, cria...
        v = new Vertice(id);
        this->adicionaItem(v);
    }

    return v;
}

/// Adiciona uma aresta em id_origem, apontando para id_destino
void Grafo::adicionaAresta(int id_origem, int id_destino) {

    /// Procura nós destino e origem, se não existirem, cria!
    Vertice *vd = this->adicionaNo(id_destino);
    Vertice *vo = this->adicionaNo(id_origem);

    vo->adicionaAresta(id_destino);
    vd->adicionaAresta(id_origem);

}

/// Procura o Vertice que possui a id dada, e deleta caso encontre
void Grafo::removeNo(int id) {

    /// encontra nó com vertice id, se não encontrar retorna
    Vertice *v = this->encontraNo(id);
    if (!v) return;

    Vertice *v2 = this->primeiroNo();

    /// Percorre todos os vertices...
    while (v2) {
        /// O Vertice tem alguma Aresta para o Vertice a ser deletado? Remove Aresta, e pula para o proximo Vertice !
        if (v2->removeAresta(id)) {
            v->removeAresta(v2->pegaId());
        }
        /// Senão, pula para o proximo Vertice
        v2 = this->proximoNo();
    }
    Lista::deletaItem(v);
    delete v;
}

/// Remove uma aresta entre dois vertices
void Grafo::removeAresta(int id_no1, int id_no2) {

    ///  Encontra os Vertices com as id's dadas, no grafo
    Vertice *v1 = this->encontraNo(id_no1);
    Vertice *v2 = this->encontraNo(id_no2);

    if (!(v1&&v2)) return ;

    v1->removeAresta(id_no2);
    v2->removeAresta(id_no1);

}

/// Grau de um nó
int Grafo::grauNo(int id) {

    Vertice *v = this->encontraNo(id);

    if (v) return v->pegaGrau();
    else return 0;


}

///* ---------------------------------------- CLASSE VERTICE --------------------------------------- *///

bool Vertice::existeAresta(int id)
{
    Aresta *a = this->encontraAresta(id);
    if (a)
        return true;
    else
        return false;

}

/// Encontra uma Aresta para id no Vertice v
Aresta* Vertice::encontraAresta(int id) {

    Aresta *a = this->primeiraAresta();

    while (a) {
        if (a->pegaIdDestino()==id) return a;
        else a = this->proximaAresta();
    }

    return 0;
}

/// Remove aresta do Vertice se encontra-la
bool Vertice::removeAresta(int id) {

    Aresta *a = this->encontraAresta(id);
    if (a) {
        Lista::deletaItem(a);
        delete a;
        return true;
    }
    else
        return false;

};

///* ---------------------------------------- CLASSE ARESTA ---------------------------------------- *///


