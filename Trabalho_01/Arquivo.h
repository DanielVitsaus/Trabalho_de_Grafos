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
        Arquivo() { this->arquivoLeitura.open("grafos.txt",ios::in); this->arquivoGravacao.open("grafos_Info.txt", ios::trunc); };
        Grafo* lerArquivo();
        void gravaArquivo(int nVertice, int nAresta, float grauMedio);

};

#endif // ARQUIVO_H_INCLUDED
