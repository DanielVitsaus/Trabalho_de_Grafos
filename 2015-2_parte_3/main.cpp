

#include <iostream>
#include <string.h>
#include <string>
#include "Lista.h"
#include "Grafo.h"
#include "LeituraGravacao.h"
#include "util.h"
#include <algorithm>
#include <sstream>

#define Tex_Arquivo 200

using namespace std;

std::string DpS(double x)
{
    std::ostringstream oss;
    oss << x;
    return oss.str();
}

int main()
{

    LeituraGravacao *ler_grava = new LeituraGravacao();

    Grafo *g1 = new Grafo();
    Vertice *v;
    vector < vector<int> > quantConxo;
    vector<int> vetVer;
    vector<Vertice*> solucao;
    vector<Alfa*> alfa;
    vector<char*> arquivos;
    vector<Aresta*> vetAr;
    pair<Grafo*, float> dijkstra;

    //char direcionado;

    char arquivo[Tex_Arquivo] = " ";
    char nomeArGulo[Tex_Arquivo] = "GULOSO_";
    char nomeArRand[Tex_Arquivo] = "RANDOMICO_";
    char nomeArRea[Tex_Arquivo] = "REATIVO_";
    char nomeArTodos[Tex_Arquivo] = "TODOS_OS_RESULTADOS";

    char arquivo1[Tex_Arquivo] = "cc3-4n.txt";
    char arquivo2[Tex_Arquivo] = "cc9-2n.txt";
    char arquivo3[Tex_Arquivo] = "cc7-3n.txt";
    char arquivo4[Tex_Arquivo] = "cc3-1n.txt";
    char arquivo5[Tex_Arquivo] = "cc5-3n.txt";
    char arquivo6[Tex_Arquivo] = "g10000.txt";
    char arquivo7[Tex_Arquivo] = "cc6-3n.txt";
    char arquivo8[Tex_Arquivo] = "cc1-2n.txt";
    char arquivo9[Tex_Arquivo] = "cc4-2n.txt";
    char arquivo10[Tex_Arquivo] ="cc8-2n.txt";
    char arquivo11[Tex_Arquivo] ="g_1000.txt";
    char arquivo12[Tex_Arquivo] ="cc3-5n.txt";
    char arquivo13[Tex_Arquivo] ="cc3-10n.txt";
    char arquivo14[Tex_Arquivo] ="cc3-11n.txt";
    char arquivo15[Tex_Arquivo] ="cc6-2n.txt";


    char r;
    int op = -1, nAresta = 0;

    arquivos.push_back(arquivo1); arquivos.push_back(arquivo2); arquivos.push_back(arquivo3); arquivos.push_back(arquivo4); arquivos.push_back(arquivo5);
    arquivos.push_back(arquivo6); arquivos.push_back(arquivo7); arquivos.push_back(arquivo8); arquivos.push_back(arquivo9); arquivos.push_back(arquivo10);
    arquivos.push_back(arquivo11); arquivos.push_back(arquivo12); arquivos.push_back(arquivo13); arquivos.push_back(arquivo14); arquivos.push_back(arquivo15);



    string linhaAUX("\n");
    string menuTabela  ("INSTACIAS;;GULOSO;;;;;;RANDOMICO;;;;;;REATIVO;;;;;;\n");
    string menuTabela2 ("Nome;NUM-NOS-IN;MS;TEMP;MSG;AlFA;NUM-IT;NUM-NOS-S;MS;TEMP;MSR;AlFA;NUM-IT;NUM-NOS-S;MS;TEMP;MSRE;AlFA;NUM-IT;NUM-NOS-S");
    string result;
    string resul      ("RESULTADOS;;;;;;;;;;;;;;;;;;;\n");


    resul += menuTabela + menuTabela2;

    float tempoGuloso = 0.0, tempoRand = 0.0, tempoReativo = 0.0, bestGuloso = 0.0, bestRand = 0.0, bestReativo = 0.0;
    float alfaGuloso = 0.0, alfaRand = 0.0, alfaReativo = 0.0, best = 0.0;
    int numIteracaRand = 0, numIteracaoReativo = 0, numBloco = 0;
    int numSoluGuloso = 0, numSoluRand = 0, numSoluReativo = 0;


    cout << "    ***********************************************" << endl;
    cout << "    *       COBERTURA DE VERTICES PONDERADOS      *" << endl;
    cout << "    *         COM MINIMIZAÇÃO DE VERTICES         *" << endl;
    cout << "    ***********************************************" << endl;

    while (true)
    {
        if (strcmp (arquivo, " ") == 0)
        {
            cout << "\n **** ANTES DE ACESSAR AS OPÇÕES **** " << endl;
            cout << "Digite o nome do arquivo como no exemplo:\n\n **** EX: nome_do_arquivo.txt ****\n\n" << endl;
            cin >> arquivo;
            /*
            cout << "E um grafo ou um digrafo?\nDigite D para digrafo e N para grafo.\n" << endl;
            cin >> direcionado;
            if (direcionado == 'D' || direcionado == 'd')
            {
                g1 = new Grafo(true);
            }
            else
            {
                g1 = new Grafo();
            }
            */
            g1 = new Grafo();
            g1 = ler_grava->lerArquivo(arquivo,g1);
        }

        cout << "Escolha uma das opções:" << endl;
        cout <<  "  1 -> Trocar arquivo:" << endl;
        cout <<  "  2 -> A ordem do Grafo:" << endl;
        cout <<  "  3 -> Quantas arestas tem o Grafo:" << endl;
        cout <<  "  4 -> Contrutivo:" << endl;
        cout <<  "  5 -> Contrutivo Randomizado:" << endl;
        cout <<  "  6 -> Contrutivo Reativo:" << endl;
        cout <<  "  7 -> Resultado Comparativo:" << endl;
        cout <<  "  o para sair:" << endl;
        cin >> op;

        printf("\e[H\e[2J");

        switch(op)
        {
            case 1:
                    cout << "Deseja ler outro arquivo?\n Digite 's' para SIM e 'n' para NAO !!\n" << endl;
                    cin >> r;
                    if (r == 's' || r == 'S')
                    {
                        cout << "Removendo Grafo anterior ..." << endl;
                        delete g1;
                        cout << "Grafo anterior removido!!\n" << endl;
                        cout << "Digite o nome do arquivo como no exemplo:\n ** EX: nome_do_arquivo.txt **\n" << endl;
                        cin >> arquivo;
                        g1 = ler_grava->lerArquivo(arquivo,g1);
                    }
                    break;

            case 2:
                cout << "O grafo tem a ordem -> " << g1->ordemGrafo() << " !!\n" << endl;
                break;

            case 3:
                    nAresta = 0;
                    for(v = g1->primeiroNo(); v != NULL; v = g1->proximoNo())
                    {
                        nAresta += v->contaItems();
                    }
                    cout << "O grafo tem -> " << (nAresta/2) << " arestas !!\n" << endl;
                    break;

            case 4:
                    cout << "\n";
                    cout << "Processando..." << endl;
                    alfaGuloso = 0.0;
                    tempoGuloso = 0.0;
                    bestGuloso = 0.0;
                    result.clear();

                    solucao = g1->ContrutivoCoberturaPonderada(alfaGuloso, tempoGuloso);
                    for (int i = 0; i < (int)solucao.size(); i++){
                        bestGuloso += solucao[i]->pesoV;
                    }
                    strcat(nomeArGulo, arquivo);
                    cout << "**** Concluido!! ****"  << endl;
                    cout << "Resultado (total peso)-> " << bestGuloso << "\nQuantidade de nós da solução -> " << (int)solucao.size() << "\nQuantidade de nós do grafo -> " << g1->quantNos << "\nTempo gasto -> " << tempoGuloso << endl;
                    cout << endl;

                    result += "Resultado (total peso)-> " + DpS(bestGuloso) + "\nQuantidade de nós da solução -> " + DpS((int)solucao.size()) + "\nQuantidade de nós do grafo -> " + DpS(g1->quantNos) + "\nTempo gasto -> " + DpS(tempoGuloso);
                    ler_grava->gravaArquivoResultado(nomeArGulo, result);
                    result.clear();
                    solucao.clear();

                    break;
            case 5:
                    tempoRand = 0.0;
                    alfaRand = 0.0;
                    bestRand = 0.0;
                    result.clear();

                    cout << "Digite um alfa entre 0.1 ate 1.0 !" << endl;
                    cin >> alfaRand;
                    cout << "Digite a quantidade de iteração!" << endl;
                    cin >> numIteracaRand;

                    cout << "Processando..." << endl;

                    solucao = g1->CoberturaRamdomizado(alfaRand, numIteracaRand, tempoRand);

                    for (int i = 0; i < (int)solucao.size(); i++){
                        bestRand =+ solucao[i]->pesoV;
                    }
                    strcat(nomeArRand, arquivo);
                    cout << "**** Concluido!! ****"  << endl;
                    cout << "Resultado (total peso)-> " << bestRand << "\nQuantidade de nós da solução -> " << (int)solucao.size() << "\nQuantidade de nós do grafo -> " << g1->quantNos << "\nTempo gasto -> " << tempoRand << endl;
                    cout << "Numero de iterações -> " << numIteracaRand << endl;
                    cout << "Alfa escolhido -> " << alfaRand << endl;
                    cout << endl;

                    result += "Resultado (total peso)-> " + DpS(bestRand) + "\nQuantidade de nós da solução -> " + DpS((int)solucao.size()) + "\nQuantidade de nós do grafo -> " + DpS(g1->quantNos) + "\nTempo gasto -> " + DpS(tempoRand) + "\nAlfa escolhido -> " + DpS(alfaRand);
                    ler_grava->gravaArquivoResultado(nomeArRand, result);
                    result.clear();

                    solucao.clear();

                    break;
            case 6:
                    bestReativo = 0.0;
                    alfaReativo = 0.0;
                    numIteracaoReativo = 0;
                    numBloco = 0;
                    tempoReativo = 0.0;
                    result.clear();

                    alfa.clear();
                    for (float i = 0.1; i < 0.6 ; i += 0.1){
                        Alfa * a =  new Alfa(i);
                        alfa.push_back(a);
                    }

                    cout << "Digite a quantidade de iteração!" << endl;
                    cin >> numIteracaoReativo;
                    cout << "Digite a quatidade de iterações por bloco !" << endl;
                    cin >> numBloco;

                    cout << "Processando..." << endl;

                    solucao = g1->CoberturaReativo(alfa, alfaReativo, numBloco, numIteracaoReativo,tempoReativo);

                    for (int i = 0; i < (int)solucao.size(); i++){
                        bestReativo =+ solucao[i]->pesoV;
                    }
                    strcat(nomeArRea, arquivo);
                    cout << "**** Concluido!! ****"  << endl;
                    cout << "Resultado (total peso)-> " << bestReativo << "\nQuantidade de nós da solução -> " << (int)solucao.size() << "\nQuantidade de nós do grafo -> " << g1->quantNos << "\nTempo gasto -> " << tempoReativo << endl;
                    cout << "Numero de iterações -> " << numIteracaoReativo << endl;
                    cout << "Numero de iteracao bloco ->" << numBloco << endl;
                    cout << "Alfa da melhor solucao -> " << alfaReativo << endl;
                    cout << endl;

                    result += "Resultado (total peso)-> " + DpS(bestReativo) + "\nQuantidade de nós da solução -> " + DpS((int)solucao.size()) + "\nQuantidade de nós do grafo -> " + DpS(g1->quantNos) + "\nTempo gasto -> " + DpS(tempoReativo) + "\nNumero de iterações -> " + DpS(numIteracaoReativo) + "\nNumero de iteracao bloco ->" + DpS(numBloco) + "\nAlfa escolhido -> " + DpS(alfaReativo);
                    ler_grava->gravaArquivoResultado(nomeArRea, result);
                    result.clear();

                    alfa.clear();
                    solucao.clear();

                    break;

            case 7:
                    alfaGuloso = 0.0;      tempoGuloso = 0.0;       bestGuloso = 0.0;

                    tempoRand = 0.0;      bestRand = 0.0;      numIteracaRand = 100;

                    bestReativo = 0.0;     alfaReativo = 0.0;     numIteracaoReativo = 4;     numBloco = 25;     tempoReativo = 0.0;

                    result = resul;

                    alfaRand = 0.4;//alfa[xrandomRange(0, 5)]->getAlfa();

                    cout << "------ **** PROCESSANDO INSTACIAS **** ------" << endl;
                    for (int i = 0; i < (int) arquivos.size(); i++){

                        cout << "\nRemovendo Grafo anterior ..." << endl;
                        delete g1;
                        g1 = new Grafo();
                        cout << "Grafo anterior removido!!\n" << endl;
                        g1 = ler_grava->lerArquivo(arquivos[i] ,g1);

                        cout << "\nUsando Algoritmo Guloso..." << endl;
                        solucao = g1->ContrutivoCoberturaPonderada(alfaGuloso, tempoGuloso);
                        for (int j = 0; j < (int)solucao.size(); j++){
                            bestGuloso += solucao[j]->pesoV;
                        }
                        numSoluGuloso = (int)solucao.size();
                        cout << "\n Quantidade de nos da solucao -> " << numSoluGuloso << endl;
                        cout << "\n Quantidade de nos do grafos -> " << g1->quantNos << endl;
                        best = bestGuloso;
                        solucao.clear();

                        cout << "\nUsando Algoritmo Guloso Randomico..." << endl;
                        solucao = g1->CoberturaRamdomizado(alfaRand, numIteracaRand, tempoRand);

                        for (int o = 0; o < (int)solucao.size(); o++){
                            bestRand += solucao[o]->pesoV;
                        }
                        numSoluRand = (int) solucao.size();
                        cout << "\n Quantidade de nos da solucao -> " << numSoluRand << endl;
                        cout << "\n Quantidade de nos do grafos -> " << g1->quantNos << endl;
                        best = ( ((best) < (bestRand) ) ? (best) : (bestRand));
                        solucao.clear();

                        alfa.clear();
                        for (float p = 0.1; p < 0.6 ; p += 0.1){
                            Alfa * a =  new Alfa(i);
                            alfa.push_back(a);
                        }

                        cout << "\nUsando Algoritmo Guloso Randomico Reativo..." << endl;
                        solucao = g1->CoberturaReativo(alfa, alfaReativo, numBloco, numIteracaoReativo,tempoReativo);

                        for (int d = 0; d < (int)solucao.size(); d++){
                            bestReativo += solucao[d]->pesoV;
                        }
                        numSoluReativo = (int)solucao.size();
                        cout << "\n Quantidade de nos da solucao -> " << numSoluReativo << endl;
                        cout << "\n Quantidade de nos do grafos -> " << g1->quantNos << endl;
                        best = ( ((best) < (bestReativo) ) ? (best) : (bestReativo));
                        solucao.clear();

                        string t(arquivos[i]);

                        //Iformaçoes do Allgoritmo Guloso
                        linhaAUX +=  t + ";"; linhaAUX +=  DpS(g1->quantNos); linhaAUX +=  ";"; linhaAUX +=  DpS(best);  linhaAUX +=  ";";
                        linhaAUX += DpS(tempoGuloso); linhaAUX +=  ";"; linhaAUX +=  DpS(bestGuloso); linhaAUX +=  ";"; linhaAUX +=  DpS(alfaGuloso);
                        linhaAUX +=  ";"; linhaAUX +=  "1"; linhaAUX +=  ";"; linhaAUX +=  DpS(numSoluGuloso);

                        //Iformaçoes do Allgoritmo Randomico
                        linhaAUX +=  ";"; linhaAUX +=  DpS(best); linhaAUX +=  ";"; linhaAUX += DpS(tempoRand); linhaAUX +=  ";";
                        linhaAUX +=  DpS(bestRand); linhaAUX +=  ";"; linhaAUX +=  DpS(alfaRand); linhaAUX +=  ";";
                        linhaAUX +=  DpS(numIteracaRand); linhaAUX +=  ";"; linhaAUX +=  DpS(numSoluRand);  linhaAUX +=  ";";

                        //Iformaçoes do Allgoritmo Reativo
                        linhaAUX +=  DpS(best); linhaAUX +=  ";"; linhaAUX +=  DpS(tempoReativo);  linhaAUX +=  ";"; linhaAUX +=  DpS(bestReativo);
                        linhaAUX +=  ";"; linhaAUX +=  DpS(alfaReativo);  linhaAUX +=  ";"; linhaAUX +=  DpS((numIteracaoReativo * numBloco));
                        linhaAUX +=  ";"; linhaAUX +=  DpS(numSoluReativo); linhaAUX +=  ";";    linhaAUX +=  "\n";


                        result += linhaAUX;

                        linhaAUX.clear();

                        alfaGuloso = 0.0;     tempoGuloso = 0.0;        bestGuloso = 0.0;

                        tempoRand = 0.0;      bestRand = 0.0;          numIteracaRand = 100;

                        bestReativo = 0.0;    alfaReativo = 0.0;       numIteracaoReativo = 4;        numBloco = 25;      tempoReativo = 0.0;

                    }
                    ler_grava->gravaArquivoResultado(nomeArTodos, result);
                    cout << result << endl;
                    result.clear();

                    break;

            case 0:
                cout << "Removendo Grafo ..." << endl;
                g1->~Grafo();
                delete ler_grava;
                cout << "Grafo removido!!" << endl;
                exit(EXIT_SUCCESS);

            default:
                break;
        }

    }

    return 0;
}
