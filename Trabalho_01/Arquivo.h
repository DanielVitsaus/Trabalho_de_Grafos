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
        Arquivo() { this->arquivoLeitura.open("Teste.txt",ios::in); this->arquivoGravacao.open("grafos_Gerado.txt", ios::app); };
        Grafo* lerArquivo();
        void gravaArquivo();

};

#endif // ARQUIVO_H_INCLUDED
