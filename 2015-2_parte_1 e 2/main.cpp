#include <iostream>
#include <string.h>
#include "Lista.h"
#include "Grafo.h"
#include "LeituraGravacao.h"
#include <algorithm>

#define Tex_Arquivo 100

using namespace std;

int main()
{
    LeituraGravacao *ler_grava = new LeituraGravacao();

    Grafo *g1 = new Grafo();
    Grafo *subgrafo = new Grafo();
    vector < vector<int> > quantConxo;
    vector<int> vetVer;
    Vertice *v;//*v2;
    char direcionado;
    char arquivo[Tex_Arquivo] = " ";
    char r;
    int op = -1, id = 0, id2 = 0 , nAresta = 0;
    pair<Grafo*, float> dijkstra;


    vector<Aresta*> vetAr;
    Aresta* ar;

    cout << "    ******  TRABALHO DE GRAFOS ******" << endl;

    while (true)
    {
        if (strcmp (arquivo, " ") == 0)
        {
            cout << " **** ANTES DE ACESSAR AS OPÇÕES **** " << endl;
            cout << "Digite o nome do arquivo como no exemplo:\n\n **** EX: nome_do_arquivo.txt ****\n" << endl;
            cin >> arquivo;
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

            g1 = ler_grava->lerArquivo(arquivo,g1);
        }

        cout << "Escolha uma das opções:" << endl;
        cout <<  "  1 -> Trocar arquivo:" << endl;
        cout <<  "  2 -> A ordem do Grafo:" << endl;
        cout <<  "  3 -> Quantas arestas tem o Grafo:" << endl;
        cout <<  "  4 -> Adiciona/Remove vertice:" << endl;
        cout <<  "  5 -> Adiciona/Remove aresta:" << endl;
        cout <<  "  6 -> Grau do nó:" << endl;
        cout <<  "  7 -> Verificar se é K-Regular:" << endl;
        cout <<  "  8 -> Verificar se é completo:" << endl;
        cout <<  "  9 -> Grau do Grafo" << endl;
        cout <<  "  10 -> Verificar se o grafo é Trivial:" << endl;
        cout <<  "  11 -> Verificar se o grafo é NULO:" << endl;
        cout <<  "  12 -> Verifica se é um MultiGrafo:" << endl;
        cout <<  "  13 -> Verifica se eh Bipartido:" << endl;
        cout <<  "  14 -> Vizinhaca Aberta do NO!" <<endl;
        cout <<  "  15 -> Vizinhaca Fechada do NO:" << endl;
        cout <<  "  16 -> Menor caminho entre dois vertice:" << endl;
        cout <<  "  17 -> Busca em Largura:" << endl;
        cout <<  "  18 -> Busca em Profundidade:" << endl;
        cout <<  "  19 -> Floyd-Warshall:" << endl;
        cout <<  "  20 -> Funcao Kruskal:" << endl;
        cout <<  "  21 -> Funcao Prim:" << endl;
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
                    cout << "Digite 'r' para Remover e 'a' para Adicionar nos !!\n" << endl;
                    cin >> r;
                    int ad;
                    if (r == 'r' || r == 'R')
                    {
                        cout << "Digite o ID do no!" << endl;
                        cin >> ad;
                        Vertice *n = g1->encontraNo(ad);
                        if (n == NULL){
                            cout << "Nao eh possivel remover o no!!\n O no nao existe no grafo!!" << endl;
                        }
                        else{
                            g1->removeNo(ad);
                            cout << "No de ID -> "<<ad<< " removido!!\n" << endl;
                        }

                    }
                    else if(r == 'a' || r == 'A')
                    {
                        cout << "Digite o ID do no!" << endl;
                        cin >> ad;
                        Vertice *n = g1->encontraNo(ad);
                        if (n == NULL){
                            cout << "Nao eh possivel adicionar o no!!\nO no ja existe no grafo!!" << endl;
                        }
                        else{
                            g1->adicionaNo(ad);
                            cout << "No de ID -> "<<ad<< " adicionado!!\n" << endl;
                        }
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
                    cout << "Digite um valor para verificar a k-regularidade:" << endl;
                    cin >> id;
                    if (g1->kRegular(id))
                        cout << " O grafo é "<< id <<"-Regular!!\n" << endl;
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
                    cout << "O grau do Grafo é "<< g1->grauGrafo() << "!\n"<< endl;

                    break;

            case 10:
                    if(g1->ehTrivial())
                        cout << " O grafo é Trivial\n" << endl;
                    else
                        cout << " O grafo não é Trivial!!\n" << endl;
                    break;


            case 11:
                    if(g1->ehNulo())
                        cout << " O grafo é NULO\n" << endl;
                    else
                        cout << " O grafo não é NULO!!\n" << endl;

                    break;

            case 12:
                    g1->imprimeGrafo(g1);
                    if(g1->ehMultigrafo())
                        cout << " O grafo possui arestas multiplas!!\n" << endl;
                    else
                        cout << " O grafo não possui arestas multiplas!!\n" << endl;

                    break;

            case 13:
                    v = g1->primeiroNo();
                    if (g1->ehBipartido(v,true)){
                        cout << "O grafo eh Bipartido!!\n" << endl;
                    }
                    else{
                        cout << "O grafo nao eh Bipartido!!\n" << endl;
                    }
                    g1->setNaoVisitado(g1);

                    break;

            case 14:
                    id = 0;
                    cout << "Digite o ID do NO!!" << endl;
                    cin >> id;
                    v = g1->encontraNo(id);
                    if(v == NULL){
                        cout << "O NO nao existe no grafo!!" << endl;
                    }
                    subgrafo = g1->vizinhacaAberta(id);
                    if (subgrafo == NULL) {
                        cout << "O vertice com ID " << id << " nao possui vizinhaca!!" << endl;
                    }
                    else{
                        cout << "A vizinhaca Aberto do NO " << id << " :" << endl;
                        g1->imprimeGrafo(subgrafo);
                    }

                   break;

            case 15:
                    id = 0;
                    cout << "Digite o ID do NO!!" << endl;
                    cin >> id;
                    v = g1->encontraNo(id);
                    if(v == NULL){
                        cout << "O NO nao existe no grafo!!" << endl;
                    }
                    subgrafo = g1->vizinhacaFechada(id);
                    cout << "A vizinhaca Fechada do NO " << id << " :" << endl;
                    g1->imprimeGrafo(subgrafo);

                    break;

            case 16:
                    id = 0;
                    id2 = 0;
                    if (g1->conexo()){
                        cout << "Digite o iD dos vertices para encontra o menor caminha entre eles!" << endl;
                        cout << "Vertive 1 -> ";
                        cin >> id;
                        cout << "Vertice 2 -> ";
                        cin >> id2;
                        dijkstra = g1->menorCaminho(id,id2);
                        cout << "O valor do menor caminha entre os vertices -> "<< dijkstra.second << "\n" << endl;
                        cout << "Caminha entre os vertices:" << endl;
                        g1->imprimeGrafo(dijkstra.first);
                        ler_grava->gravaArquivo(dijkstra.first, arquivo);
                        cout << endl;
                    }
                    else{
                        cout << "\nO grafo informado não é conexo!\n" << endl;
                    }
                    break;

            case 17:
                    cout << "Digite o ID do vértice" << endl;
                    int v1;
                    cin >> v1;
                    if (g1->buscaLargura(v1)){
                        cout << "O vertice de ID -> " << v1 << " exirte no grafo!" << endl;
                    }
                    else{
                        cout << "O vertice de ID -> " << v1 << " NÂO exirte no grafo!" << endl;
                    }

                    break;

            case 18:
                    cout << "Digite o ID do vértice" << endl;
                    int v2;
                    cin >> v2;
                    if (g1->buscaProfundidade(g1->primeiroNo(),v2)){
                        cout << "O vertice de ID -> " << v2 << " exirte no grafo!" << endl;
                    }
                    else{
                        cout << "O vertice de ID -> " << v2 << " NÂO exirte no grafo!" << endl;
                    }

                    break;

            case 19:
                    g1->floyd();

                    break;

            case 20:
                    if (g1->conexo()){
                        Grafo *krusk;
                        for(Vertice* i = g1->primeiroNo(); i != NULL; i = g1->proximoNo())
                        {
                            for(Aresta* a = i->primeiraAresta(); a != NULL; a =  i->proximaAresta())
                            {
                                ar = new Aresta(i->pegaId(),a->pegaIdDestino(), a->pegaPeso());
                                vetAr.push_back(ar);
                            }
                        }

                        sort(vetAr.begin(), vetAr.end(), Aresta::ordenaArestaPeso);

                        krusk = g1->Kruskal(vetAr);
                        krusk->imprimeGrafo(krusk);
                        vetAr.clear();
                        delete krusk;

                        cout << "\n"<< endl;

                    }else{
                        cout << "\nO grafo informado não é conexo!\n" << endl;
                    }

                    break;

            case 21:
                   if(g1->conexo()){
                        Grafo *prim;

                        cout << "\n" << endl;
                        for(Vertice* i = g1->primeiroNo(); i != NULL; i = g1->proximoNo())
                        {
                            vetVer.push_back(i->pegaId());
                        }

                        prim = g1->Prim(vetVer);
                        prim->imprimeGrafo(prim);
                        cout << endl;
                        vetVer.clear();
                        delete prim;
                    }else{
                        cout << "\nO grafo informado não é conexo!\n" << endl;
                    }

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
