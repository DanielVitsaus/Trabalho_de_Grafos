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
    Grafo *g1 = new Grafo();
    vector< vector<int> > quantConxo;
    char arquivo[Tex_Arquivo] = " ";
    char r;
    int op = -1, id = 0;

    cout << "    ******  TRABALHO DE GRAFOS ******" << endl;

    while (true)
    {
        if (strcmp (arquivo, " ") == 0)
        {
            cout << " **** ANTES DE ACESSAR AS OPÇÕES **** " << endl;
            cout << "Digite o nome do arquivo como no exemplo:\n\n **** EX: nome_do_arquivo.txt ****\n" << endl;
            cin >> arquivo;
            g1 = ler_grava->lerArquivo(arquivo);
            printf("\e[H\e[2J");
        }

        cout << "Escolha uma das opções:" << endl;
        cout <<  "  1 -> Trocar arquivo:" << endl;
        cout <<  "  2 -> Grau do nó:" << endl;
        cout <<  "  3 -> Verificar se é K-Regular:" << endl;
        cout <<  "  4 -> Verificar se é completo:" << endl;
        cout <<  "  5 -> Verificar se dois nós são adjacentes:" << endl;
        cout <<  "  6 -> Verificar se o grafo é conexo:" << endl;
        cout <<  "  7 -> Verifica se dois nós estão em uma mesma componente conexa:" << endl;
        cout <<  "  8 -> Verifica se um dado nó é de articulação:" << endl;
        cout <<  "  9 -> Verifica se uma dada aresta é ponte:" << endl;
        cout <<  "  10 ->Verificar quantas componentes conexa tem o grafos," <<endl;
        cout <<  "       qual é o tamanha da mior e menor compomente:" << endl;
        cout <<  "  11 ->Gerar informações sobre o grafo:" << endl;
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
                        for (int i = 0; i < g1->contaNos(); i++) {
                                g1->removeNo(i);
                        }
                        cout << "Grafo anterior removido!!\n" << endl;
                        cout << "Digite o nome do arquivo como no exemplo:\n ** EX: nome_do_arquivo.txt **\n" << endl;
                        cin >> arquivo;
                        g1 = ler_grava->lerArquivo(arquivo);
                    }
            break;

            case 2:
                    cout << "Digite o ID do nó:" << endl;
                    cin >> id;
                    if (g1->grauNo(id) != -1)
                        cout << " O nó de ID -> " << id << " tem grau " << g1->grauNo(id) << "\n"<< endl;
                    else
                        cout << " Não exite um no com o ID -> " << id << "\n"<< endl;
            break;

            case 3:
                    if (g1->kRegular())
                        cout << " O grafo é K-Regular!!\n" << endl;
                    else
                        cout << " O grafo não é K-Regular!!\n" << endl;
            break;

            case 4:
                    if (g1->completo())
                        cout << " O Grafo é completo \n" << endl;
                    else
                        cout << " O grafo no é completo \n "<< endl;
            break;

            case 5:
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

            case 6:
                    if(g1->conexo())
                        cout << " O grafo é conexo\n" << endl;
                    else
                        cout << " O grafo não é conexo!!\n" << endl;
            break;

            case 7:
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

            case 8:
                    cout << "Digite o ID do nó:" << endl;
                    int no;
                    cin >> no;
                    if (g1->noArticulacao(no))
                        cout << " O no é articulação!!\n" << endl;
                    else
                        cout << " O no não é articulação!!\n" << endl;
            break;

            case 9:
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

            case 10:
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
                                maior = quantConxo[i].size();

                            if (menor > (int)quantConxo[i].size())
                                menor = quantConxo[0].size();
                        }
                        cout << " A maior componente conexa tem " << maior << " nós !!" << endl;
                        cout << " A menor componente conexa tem " << menor << " nós !!\n" << endl;
                    }
            break;
            case 11:
                    int nAresta , nGrauTotal;
                    nAresta = 0;
                    nGrauTotal = 0;
                    float mediaGrau ;
                    Vertice *v ;
                    v = g1->primeiroNo();
                    for(v = g1->primeiroNo(); v != NULL; v = g1->proximoNo())
                    {
                        nGrauTotal += v->pegaGrau();
                        nAresta += v->contaItems();
                    }
                    mediaGrau =  ( (float)nGrauTotal ) / ( (float)g1->contaNos() ) ;

                    ler_grava->gravaArquivo(g1, arquivo, g1->contaNos(), (nAresta/2), mediaGrau );
            break;
            case 0:
                cout << "Removendo Grafo ..." << endl;
                for (int i = 0; i < g1->contaNos(); i++)
                {
                    g1->removeNo(i);
                }
                cout << "Grafo removido!!" << endl;
                delete g1;
                exit(EXIT_SUCCESS);
            break;
        }

    }

    return 0;
}





