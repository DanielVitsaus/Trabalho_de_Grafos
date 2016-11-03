#include "LeituraGravacao.h"
#include "Grafo.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <cstdlib>

using namespace std;

/** \brief Funçao que le e adiciona o vertice em um grafo G
 *
 * \param char *ar -> nome do arquivo para a leitura
 * \param Grafo *gd -> grafo a ser adicionados os vertices
 * \return Grafo *gd
 *
 */
Grafo* LeituraGravacao::lerArquivo(char *ar, Grafo *gd)
{
    char diretorio[100] = "instancias//";
    strcat(diretorio,ar);
    this->arquivoLeitura.open(diretorio,ios::in);
    int m1 = 0, m2 = 0, m3 = 0;
    char buff[16];
    int cont = 2;

    if (!this->arquivoLeitura.is_open())
    {
        cout << "Arquivo nao encontrado ou danificado" << endl;
        exit(0);
    }

    cout << "Lendo o arquivo " << ar << " ... " << endl;

    this->arquivoLeitura.getline(buff,16); // Le quantidade de nos
    sscanf(buff, "%d", &gd->quantNos);
    this->arquivoLeitura.getline(buff,16); // Le primeira linha
    // Processa as arestas criando os nos que não existem
    srand ( time(NULL) + 1 );
    while(! this->arquivoLeitura.eof())
    {
        sscanf(buff, "%d %d %d", &m1, &m2, &m3); // Realiza leitura das arestas no formato: "(int) (int)"
        if (m3 > 0)
        {
            gd->adicionaAresta(m1,m2,m3);
        }
        else
        {
            gd->adicionaAresta(m1,m2, rand() % 100 +1);
        }
            // ... e adiciona aresta no grafo.
        this->arquivoLeitura.getline(buff,16);
        cont++;
    }
    gd->imprimeGrafo(gd);
    this->arquivoLeitura.close();
    cout << "O arquivo " << ar << " foi lido com sucesso! "<<  cont <<" linhas processadas.\n" << endl;
    return gd;
}

/** \brief Funcao que gera um aquirvo com as informacoes do grafo G como frequencia de cada vertice, quantos vertice,
 *         quantas arestas e o grau medio de cada vertice.
 *
 * \param Grafo *g
 * \param char* nomArquivo
 * \param int nVertice
 * \param int nAresta
 * \param float grauMedio
 *
 */
void LeituraGravacao::gravaArquivo(Grafo *g, char* nomArquivo)
{
    Grafo *g2 = g;
    Vertice *k = g2->primeiroNo();
    char nomeArquivo[100];
    char diretorio[100] = "arquivos_gerados//";
    int quatVertice = g->contaNos();

    strncpy ( nomeArquivo, nomArquivo, strlen(nomArquivo) - 4);
    strcat(nomeArquivo,"_info.txt");
    strcat(diretorio,nomeArquivo);
    cout << "Gerando arquivo " << nomeArquivo << endl;

    this->arquivoGravacao.open(diretorio, ios::trunc);

    this->arquivoGravacao << "Número de Vértice -> " << quatVertice << endl;

    for(Vertice *v = g->primeiroNo(); v != NULL; v = g->proximoNo() )
    {
       this->arquivoGravacao << v->pegaId() << " -> ";
        for (Aresta *a = v->primeiraAresta() ; a != NULL; a = v->proximaAresta())
        {
            this->arquivoGravacao << a->pegaIdDestino() << " (P-> " << a->pegaPeso() << ") ";
        }
        this->arquivoGravacao << endl;
    }

    this->arquivoGravacao << endl;
    cout << "Arquivo " << nomeArquivo << " gerado !!"<<"\n" << endl;
    this->arquivoGravacao.close();
    delete(k);
}

/** \brief Funcao que gera um arquivo com as componetes fortemente conexa do grafo passando o nome do arquivo e um vector com as componentes
 *
 * \param char* nomArquivo
 * \param vector< vector<int> > comForteConexo
 *
 */
void LeituraGravacao::gravaArquivo(char* nomArquivo, vector< vector<int> > comForteConexo)
{
    char nomeArquivo[100];
    char diretorio[100] = "arquivos_gerados//";

    strncpy ( nomeArquivo, nomArquivo, strlen(nomArquivo) - 4);
    strcat(nomeArquivo,"_info.txt");
    strcat(diretorio,nomeArquivo);
    cout << "Gerando arquivo " << nomeArquivo << endl;

    this->arquivoGravacao.open(diretorio, ios::trunc);

    this->arquivoGravacao << "Componentes Fortemente Conexas " <<  endl;
    for(int i = 0; i < (int)comForteConexo.size(); i++)
    {
        for (int j = 0; j < (int)comForteConexo[i].size(); j++)
        {
             this->arquivoGravacao << comForteConexo[i][j] << " ";
        }
        this->arquivoGravacao << endl;
    }

    cout << "Arquivo " << nomeArquivo << " gerado !!"<<"\n" << endl;
    this->arquivoGravacao.close();

}
