#include "Arquivo.h"
#include "Grafo.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <cstdlib>

using namespace std;


Grafo* Arquivo::lerArquivo(char *ar)
{
    char diretorio[100] = "instancias//";
    strcat(diretorio,ar);
    this->arquivoLeitura.open(diretorio,ios::in);
    Grafo * grafo = new Grafo();
    int m1 = 0, m2 = 0, j = 0;
    char valor[16];
    char buff[16];

    if (!this->arquivoLeitura.is_open())
    {
        cout << "Arquivo nao encontrado ou danificado" << endl;
        exit(0);
    }

    cout << "Lendo o arquivo " << ar << " ... " << endl;
    this->arquivoLeitura.getline(buff,16);
    this->arquivoLeitura.getline(buff,16);
    while(! this->arquivoLeitura.eof())
    {
        for(int i = 0; buff[i] != '\0' ; i++ )
        {
            if(buff[i] == ' ')
            {
                m1 = atoi(valor);
                j = 0;
                i++;
            }
            valor[j] = buff[i];
            j++;
        }
        valor[j] = '\0';
        j = 0;
        m2 = atoi(valor);
        for(int i = 0; i < 16; i++)
        {
            valor[i] = '\0';
        }
        grafo->adicionaAresta(m1,m2);
        //cout << m1 << " | " << m2 << endl;
        this->arquivoLeitura.getline(buff,16);
    }
    this->arquivoLeitura.close();
    cout << "O arquivo " << ar << " foi lido com sucesso! " << endl;
    return grafo;
}

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
            this->arquivoGravacao << "Frequência relativa de grau " << v->pegaGrau() << " -> " << ( ((float)n_grau_x ) / ( (float)quatVertice ) )<< endl;
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
}
