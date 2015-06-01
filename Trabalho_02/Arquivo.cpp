#include "Arquivo.h"
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

Grafo* Arquivo::lerArquivo(char *ar, Grafo *gd)
{
    char diretorio[100] = "instancias//";
    strcat(diretorio,ar);
    this->arquivoLeitura.open(diretorio,ios::in);
    //Grafo * grafo = new Grafo();
    int m1 = 0, m2 = 0;
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
    while(! this->arquivoLeitura.eof())
    {
        sscanf(buff, "%d %d", &m1, &m2); // Realiza leitura das arestas no formato: "(int) (int)"
        gd->adicionaAresta(m1,m2);    // ... e adiciona aresta no grafo.
        this->arquivoLeitura.getline(buff,16);
        cont++;
    }

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
void Arquivo::gravaArquivo(Grafo *g, char* nomArquivo,int nVertice, int nAresta, float grauMedio)
{
    Grafo *g2 = g;
    Vertice *k = g2->primeiroNo();
    int n_grau_x = 0, grauV = 0 ,grauK = 0;
    char nomeArquivo[100];
    char diretorio[100] = "arquivos_gerados//";
    int quatVertice = g->contaNos();

    strncpy ( nomeArquivo, nomArquivo, strlen(nomArquivo) - 4);
    strcat(nomeArquivo,"_info.txt");
    strcat(diretorio,nomeArquivo);
    cout << "Gerando arquivo " << nomeArquivo << endl;

    this->arquivoGravacao.open(diretorio, ios::trunc);

    this->arquivoGravacao << "Número de Vértice -> " << nVertice << endl;
    this->arquivoGravacao << "Número de Arestas -> " << nAresta << endl;
    this->arquivoGravacao << "Grau Médio do Grafo -> " << grauMedio << endl;
    for(Vertice *v = g->primeiroNo(); v != NULL; v = g->proximoNo() )
    {
        if (!v->foiVisitado())
        {
            v->setaVisitado(true);
            grauV = v->pegaGrau();
            n_grau_x++;
            for(k = g2->primeiroNo(); k != NULL; k = g2->proximoNo())
            {
                grauK = k->pegaGrau();
                if (grauK == grauV)
                {
                    k->setaVisitado(true);
                    n_grau_x++;
                }
            }
            k = g2->primeiroNo();
            this->arquivoGravacao << "\nQuantidade de vertice com grau " << v->pegaGrau() << " -> " <<  n_grau_x << endl;
            this->arquivoGravacao << "   Frequência relativa de grau " << v->pegaGrau() << " -> " << ( ((float)n_grau_x ) / ( (float)quatVertice ) )<< endl;
            n_grau_x = 0;
        }
    }
    for (k = g->primeiroNo(); k != NULL; k = g->proximoNo())/// seta todos os vertices como nao visitado
    {
        k->setaVisitado(false);
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
void Arquivo::gravaArquivo(char* nomArquivo, vector< vector<int> > comForteConexo)
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
