#include "Arquivo.h"
#include "Grafo.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;


Grafo* Arquivo::lerArquivo()
{
    Grafo * grafo = new Grafo();
    int m1 = 0, m2 = 0, j = 0;
    char valor[16];
    char buff[16];

    if (!this->arquivoLeitura.is_open())
    {
        cout << "Arquivo nao encontrado ou danificado" << endl;
        exit(0);
    }

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
        j = 0;
        m2 = atoi(valor);
        for(int i = 0; i < 16; i++)
        {
            valor[i] = '\0';
        }
        grafo->adicionaAresta(m1,m2);
        cout << m1 << " | " << m2 << endl;
        this->arquivoLeitura.getline(buff,16);
    }
    this->arquivoLeitura.close();
    return grafo;
}

void Arquivo::gravaArquivo()
{
    this->arquivoGravacao << "Daniel" << endl;
}
