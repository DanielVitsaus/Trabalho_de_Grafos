#include "LeituraGravacao.h"
#include "Grafo.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <cstdlib>
#include <dirent.h>

using namespace std;


vector<char*> LeituraGravacao::listaArquivos(){

    DIR *dir = 0;
    struct dirent *entrada = 0;
    unsigned char isFile = 0x8;

    vector<char*> diretorios;

    dir = opendir ("instancias");

    if (dir == 0) {
        std::cerr << "Nao foi possivel abrir diretorio." << std::endl;
        exit (1);
    }
    //Iterar sobre o diretorio
    while (true){
        entrada = readdir(dir);
        if(entrada == NULL){
            break;
        }
        if (entrada->d_type == isFile){
            diretorios.push_back(entrada->d_name);
            //cout << diretorios[i]<< endl;
        }

    }

    closedir (dir);

    return diretorios;

}

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
    this->arquivoLeitura.open(diretorio,ios::binary);
    int m1 = 0, m2 = 0, m3 = 0;
    char buff[16];
    int cont = 1;
    int i = 0;
    char l;
    if (!this->arquivoLeitura.is_open())
    {
        cout << "Arquivo nao encontrado ou danificado" << endl;
        exit(0);
    }

    cout << "Lendo o arquivo " << ar << " ... " << endl;

    //this->arquivoLeitura.seekg(0, this->arquivoLeitura.end);
    //int length = this->arquivoLeitura.tellg();
    //this->arquivoLeitura.seekg(0, this->arquivoLeitura.beg);
    //char * buffer = new char [length];
    //this->arquivoLeitura.read(buffer, length);

    //buffer[length+1] = '\0'
    this->arquivoLeitura.getline(buff,16); // Le quantidade de nos
    sscanf(buff, "%d", &gd->quantNos);
    this->arquivoLeitura.getline(buff,20); // Le primeira linha
    // Processa as arestas criando os nos que não existem
    //int i = 0;

    //srand ( time(NULL) + 1 );
    while(! this->arquivoLeitura.eof())
   // while(i < length)
    {
        //cout << buffer[i] ;
        //i++;
        /*
        this->arquivoLeitura.getline(buff,1024);
        cout << buff << endl;
        */
        sscanf(buff, "%c %d %d %d",&l, &m1, &m2, &m3);
        gd->adicionaAresta(m1,m2);
        gd->encontraNo(m1)->SetPesoV((i % 200) + 1);
        i++;
        gd->encontraNo(m2)->SetPesoV((i % 200) + 1);
        this->arquivoLeitura.getline(buff,16);
        cont++;
        i++;


    }
    //gd->imprimeGrafo(gd);
    this->arquivoLeitura.close();
    cout << "O arquivo foi " << ar << " lido com sucesso! "<<  cont <<" linhas processadas.\n" << endl;
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
void LeituraGravacao::gravaArquivo(Grafo *g, char* nomArquivo,int nVertice, int nAresta, float grauMedio)
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
    //g->setNaoVisitado(g);
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
void LeituraGravacao::gravaArquivoResultado(char* nomArquivo, string resultado)
{
    char nomeArquivo[100];
    char diretorio[100] = "arquivos_gerados//";

    strcpy ( nomeArquivo, nomArquivo);
    strcat(nomeArquivo,"_info.csv");
    strcat(diretorio,nomeArquivo);
    cout << "Gerando arquivo " << nomeArquivo << endl;

    this->arquivoGravacao.open(diretorio, ios::trunc);

    this->arquivoGravacao << resultado << endl;

    cout << "Arquivo " << nomeArquivo << " gerado !!"<<"\n" << endl;
    this->arquivoGravacao.close();

}
