#ifndef ARQUIVO_H_INCLUDED
#define ARQUIVO_H_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include "Grafo.h"

using namespace std;

class Arquivo
{
    private:
        ifstream arquivoLeitura;
        ofstream arquivoGravacao;

    public:
        Grafo* lerArquivo(char *ar);
        void gravaArquivo(Grafo *g, char* nomArquivo,int nVertice, int nAresta, float grauMedio);

};

#endif // ARQUIVO_H_INCLUDED
