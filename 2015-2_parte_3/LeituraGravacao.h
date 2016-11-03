#ifndef ARQUIVO_H_INCLUDED
#define ARQUIVO_H_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include "Grafo.h"

using namespace std;

class LeituraGravacao
{
    private:
        ifstream arquivoLeitura;
        ofstream arquivoGravacao;

    public:
        Grafo* lerArquivo(char *ar,Grafo *gd);
        vector<char*> listaArquivos();
        void gravaArquivoResultado(char* nomArquivo, string reslutado);
        void gravaArquivo(Grafo *g, char* nomArquivo,int nVertice, int nAresta, float grauMedio);

};

#endif // ARQUIVO_H_INCLUDED
