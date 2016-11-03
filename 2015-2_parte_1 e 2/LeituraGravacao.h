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
        void gravaArquivo(char* nomArquivo, vector< vector<int> >comForteConexo);
        void gravaArquivo(Grafo *g, char* nomArquivo);

};

#endif // ARQUIVO_H_INCLUDED
