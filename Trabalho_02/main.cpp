/*******************************************************************************************************************************
 *  Menu:
 *
 * 1 -> Trocar arquivo:" << endl;
 * 2 -> Quantas nos tem o Grafo:" << endl;
 * 3 -> Quantas arestas tem o Grafo:" << endl;
 * 4 -> Adiciona/Remove vertice:" << endl;
 * 5 -> Adiciona/Remove aresta:" << endl;
 * 6 -> Grau do nó:" << endl;
 * 7 -> Verificar se é K-Regular:" << endl;
 * 8 -> Verificar se é completo:" << endl;
 * 9 -> Verificar se dois nós são adjacentes:" << endl;
 * 10 -> Verificar se o grafo é conexo:" << endl;
 * 11 -> Verifica se dois nós estão em uma mesma componente conexa:" << endl;
 * 12 -> Verifica se um dado nó é de articulação:" << endl;
 * 13 -> Verifica se uma dada aresta é ponte:" << endl;
 * 14 ->Verificar quantas componentes conexa tem o grafos, qual é o tamanha da mior e menor compomente:" << endl;
 * 15 ->Gerar informações sobre o grafo:" << endl;
 * 0 para sair:" << endl;
 ************************************************************************************************************************************
 */



#include <iostream>
#include <string.h>
#include "Lista.h"
#include "Grafo.h"
#include "Arquivo.h"

#define Tex_Arquivo 100

using namespace std;


/**
*    Listas são compostas de Items.
*    Listas são representações de grafos, Logo Grafos são Listas.  --> Herança simples
*    Vertices são Listas de Arestas, e Items dos Grafos.  --> Herança multipla
*    Arestas são Items dos Vertices.  --> Herança simples
*/

int main()
{
    Arquivo *ler_grava = new Arquivo();
    Grafo *g1 = NULL;
    vector < vector<int> > quantConxo;
    Vertice *v;//*v2;
    char arquivo[Tex_Arquivo] = " ";
    char r;
    int op = -1, id = 0, nAresta = 0, nGrauTotal = 0;

    cout << "    ******  TRABALHO DE GRAFOS ******" << endl;

    while (true)
    {
        if (strcmp (arquivo, " ") == 0)
        {
            cout << " **** ANTES DE ACESSAR AS OPÇÕES **** " << endl;
            cout << "Digite o nome do arquivo como no exemplo:\n\n **** EX: nome_do_arquivo.txt ****\n" << endl;
            cin >> arquivo;
            g1 = new Grafo(true);
            g1 = ler_grava->lerArquivo(arquivo,g1);
        }

        cout << "Escolha uma das opções:" << endl;
        cout <<  "  1 -> Trocar arquivo:" << endl;
        cout <<  "  2 -> Quantas nos tem o Grafo:" << endl;
        cout <<  "  3 -> Quantas arestas tem o Grafo:" << endl;
        cout <<  "  4 -> Adiciona/Remove vertice:" << endl;
        cout <<  "  5 -> Adiciona/Remove aresta:" << endl;
        cout <<  "  6 -> Grau do nó:" << endl;
        cout <<  "  7 -> Verificar se é K-Regular:" << endl;
        cout <<  "  8 -> Verificar se é completo:" << endl;
        cout <<  "  9 -> Verificar se dois nós são adjacentes:" << endl;
        cout <<  "  10 -> Verificar se o grafo é conexo:" << endl;
        cout <<  "  11 -> Verifica se dois nós estão em uma mesma componente conexa:" << endl;
        cout <<  "  12 -> Verifica se um dado nó é de articulação:" << endl;
        cout <<  "  13 -> Verifica se uma dada aresta é ponte:" << endl;
        cout <<  "  14 ->Verificar quantas componentes conexa tem o grafos," <<endl;
        cout <<  "       qual é o tamanha da mior e menor compomente:" << endl;
        cout <<  "  15 ->Gerar informações sobre o grafo:" << endl;
        cout <<  "  17 ->Fecho Transitivo Direto:" << endl;
        cout <<  "  18 ->Fecho Transitivo Indireto:" << endl;
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
                cout << "O grafo tem -> " << g1->contaNos() << " vertices !!\n" << endl;
                break;

            case 3:
                    nAresta = 0;
                    nGrauTotal = 0;
                    for(v = g1->primeiroNo(); v != NULL; v = g1->proximoNo())
                    {
                        nAresta += v->contaItems();
                    }
                    cout << "O grafo tem -> " << (nAresta/2) << " arestas !!\n" << endl;
                    break;

            case 4:
                    cout << "Digite 'r' para Remover e 'a' para Adicionar nos !!\n" << endl;
                    cin >> r;
                    int ad;
                    if (r == 'r' || r == 'R')
                    {
                        cout << "Digite o ID do no!" << endl;
                        cin >> ad;
                        g1->removeNo(ad);
                        cout << "No de ID -> "<<ad<< " removido!!\n" << endl;
                    }
                    else if(r == 'a' || r == 'A')
                    {
                        cout << "Digite o ID do no!" << endl;
                        cin >> ad;
                        g1->adicionaNo(ad);
                        cout << "No de ID -> "<<ad<< " adicionado!!\n" << endl;
                    }
                    break;

            case 5:
                    cout << "Digite 'r' para Remover e 'a' para Adicionar aresta !!\n" << endl;
                    cin >> r;
                    int adAr1,adAr2;
                    if (r == 'r' || r == 'R')
                    {
                        cout << "Digite a primeira extremidade da aresta:" << endl;
                        cin >> adAr1;
                        cout << "Digite a segunda extremidade da aresta:" << endl;
                        cin >> adAr2;
                        g1->removeAresta(adAr1,adAr2);
                        cout << "Aresta -> "<<adAr1 <<" - " << adAr2 << " foi removida!!\n" << endl;
                    }
                    else if(r == 'a' || r == 'A')
                    {
                        cout << "Digite a primeira extremidade da aresta:" << endl;
                        cin >> adAr1;
                        cout << "Digite a segunda extremidade da aresta:" << endl;
                        cin >> adAr2;
                        g1->adicionaAresta(adAr1,adAr2);
                        cout << "Aresta -> "<<adAr1 << " - " << adAr2 << " foi adicionada!!\n" << endl;
                    }
                    break;

            case 6:
                    cout << "Digite o ID do nó:" << endl;
                    cin >> id;
                    if (g1->grauNo(id) != -1)
                        cout << " O nó de ID -> " << id << " tem grau " << g1->grauNo(id) << "\n"<< endl;
                    else
                        cout << " Não exite um no com o ID -> " << id << "\n"<< endl;
                    break;

            case 7:
                    if (g1->kRegular())
                        cout << " O grafo é K-Regular!!\n" << endl;
                    else
                        cout << " O grafo não é K-Regular!!\n" << endl;
                    break;

            case 8:
                    if (g1->completo())
                        cout << " O Grafo é completo \n" << endl;
                    else
                        cout << " O grafo no é completo \n "<< endl;
                    break;

            case 9:
                    cout << "Digite o ID do primeiro nó:" << endl;
                    int no1;
                    cin >> no1;
                    cout << "Digite o ID do segundo nó:" << endl;
                    int no2;
                    cin >> no2;
                    if (g1->nosSaoAdjacentes(no1, no2))
                        cout << " Os nos são adkacentes!!\n" << endl;
                    else
                        cout << " Os nos não são adjacentes!!\n" << endl;
                    break;

            case 10:
                    if(g1->conexo())
                        cout << " O grafo é conexo\n" << endl;
                    else
                        cout << " O grafo não é conexo!!\n" << endl;
                    break;

            case 11:
                    cout << "Digite o ID do primeiro nó:" << endl;
                    int n1;
                    cin >> n1;
                    cout << "Digite o ID do segundo nó:" << endl;
                    int n2;
                    cin >> n2;
                    if (g1->mesmaComponenteConexa(n1,n2))
                        cout << " Os nos estão na mesma componente!!\n" << endl;
                    else
                        cout << " Os nos não estão na mesma componente!!\n" << endl;
                    break;

            case 12:
                    cout << "Digite o ID do nó:" << endl;
                    int no;
                    cin >> no;
                    if (g1->noArticulacao(no))
                        cout << " O no é articulação!!\n" << endl;
                    else
                        cout << " O no não é articulação!!\n" << endl;
                    break;

            case 13:
                    cout << "Digite a primeira extremidade da aresta:" << endl;
                    int a1;
                    cin >> a1;
                    cout << "Digite a segunda extremidade da aresta:" << endl;
                    int a2;
                    cin >> a2;
                    if (g1->arestaPonte(a1, a2))
                       cout << "\n A aresta é ponte !!\n" << endl;
                   else
                       cout << "\n A aresta nao é ponte !!\n "<< endl;
                    break;

            case 14:
                    quantConxo = g1->quantCompConexo();
                    int maior, menor;
                    maior = quantConxo[0].size();
                    menor = maior;

                    cout << "\n O grafo tem " << quantConxo.size() << " compomentes conexas !!\n"<< endl;

                    if (quantConxo.size() > 1)
                    {
                        for(int i = 0; i < (int)quantConxo.size(); i++)
                        {
                            if (maior <= (int)quantConxo[i].size())
                                maior = (int)quantConxo[i].size();

                            if (menor > (int)quantConxo[i].size())
                                menor = (int)quantConxo[i].size();

                            quantConxo[i].clear();
                        }
                        cout << " A maior componente conexa tem " << maior << " nós !!" << endl;
                        cout << " A menor componente conexa tem " << menor << " nós !!\n" << endl;
                    }
                    quantConxo.clear();
                    break;


            case 15:
                    nAresta = 0;
                    nGrauTotal = 0;
                    float mediaGrau ;
                    v = g1->primeiroNo();
                    for(v = g1->primeiroNo(); v != NULL; v = g1->proximoNo())
                    {
                        nGrauTotal += v->pegaGrau();
                        nAresta += v->contaItems();
                    }
                    mediaGrau =  ( (float)nGrauTotal ) / ( (float)g1->contaNos() ) ;

                    ler_grava->gravaArquivo(g1, arquivo, g1->contaNos(), (nAresta/2), mediaGrau );
                    break;
            case 16:
                    quantConxo = g1->quantCompForteConexos();
                    ler_grava->gravaArquivo(arquivo, quantConxo);
                    break;

            case 17:
                     cout << "Digite o vértice a partir do qual deseja encontrar o fecho transitivo direto::" << endl;
                    int v1;
                    cin >> v1;
                    g1->fechoTransitivoDireto(v1);
                    break;

            case 18:
                     cout << "Digite o vértice a partir do qual deseja encontrar o fecho transitivo indireto::" << endl;
                    int v2;
                    cin >> v2;
                    g1->fechoTransitivoIndireto(v2);
                    break;
            case 0:
                cout << "Removendo Grafo ..." << endl;
                delete g1;
                delete ler_grava;
                cout << "Grafo removido!!" << endl;
                exit(EXIT_SUCCESS);

            default:
                break;
        }

    }

    return 0;
}





