/*
  Name:        quad.cpp
  Copyright:   Version 0.1
  Author:      Rodrigo Luis de Souza da Silva
  Last Update: 03/09/2014
  Release:     18/09/2004
  Description: Simple opengl program
*/

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <ctype.h>
#include <time.h>
#include <math.h>

#include <iostream>
#include <string.h>
#include "Lista.h"
#include "Grafo.h"
#include "Arquivo.h"
#include "Ponto.h"

#define Tex_Arquivo 100

using namespace std;

Arquivo *ler_grava = new Arquivo();
Grafo *g1 = new Grafo();
vector< vector<int> > quantConxo;

Vertice* v;
Vertice* v1;
Aresta* a;
char arquivo[Tex_Arquivo] = " ";
char r;
int op = -1, id = 0;
bool menu = false;
bool t = false,t2 = false;
float tamanhoMundo, rotationX = 25.0, rotationY = 0.0 ,d = 25.0, mediaGrau, move1 = 0.0, move2 = 0.0;
int   last_x, last_y, distOrigem = 0, nAresta = 0, nGrauTotal = 0;
int tamViewX , tamViewY , posViewX = 10.0 ,posViewY = 10.0;
Ponto* central;

float kc = 0.1f;
float kl = 0.04f;
float kq = 0.0005f;

// Material da base
GLfloat base_ambient[]   = { 0.1, 0.1, 0.1, 1.0 };
GLfloat base_difusa[]    = { 0.8, 0.0, 0.0, 1.0 };
GLfloat base_especular[] = { 0.8, 0.0, 0.0, 1.0 };
GLfloat base_emissao[]   = { 0.0, 0.0, 0.0, 1.0 };
GLfloat base_brilho[]    = { 128.0 };

// Material do teapot
GLfloat object_ambient[]   = { 0.25725, 0.1995, 0.0745, 1.0 };
GLfloat object_difusa[]    = { 0.80164, 0.60648, 0.22648, 1.0 };
GLfloat object_especular[] = { 0.828281, 0.555802, 0.366065, 1.0 };
GLfloat object_emissao[]   = { 0.0, 0.0, 0.0, 1.0 };
GLfloat object_brilho[]    = { 160.0 };

// Defini parametros da luz
GLfloat cor_luz[]			= { 1.0f, 1.0f, 1.0f, 1.0};
GLfloat cor_luz_amb[]	= { 1.0, 1.0, 1.0, 1.0};
GLfloat posicao_luz[]	= { 0.0, 0.0, 0.0, 0.0};
GLfloat cor_fonte_luz[]	= { 1.0, 1.0, 1.0, 1.0};
GLfloat cor_emissao[]	= { 0.0, 0.0, 0.0, 1.0 };

int width = 1152, height = 720;
//int width = 640*1.2, height = 480*1.2;

void renderScene(void);
void init (void);
void keyboard(unsigned char key, int x, int y);

void showMenu();
void motion(int x, int y );
void mouse(int button, int state, int x, int y);
void idle ();
void reshape (int w, int h);
void setMaterial(void);
void PontoCentral();
void Views();
void DesenhaBordas();

int main(int argc, char** argv)
{
   if (strcmp (arquivo, " ") == 0)
    {
        cout << " **** ANTES DE ACESSAR AS OPÇÕES **** " << endl;
        cout << "Digite o nome do arquivo como no exemplo:\n\n **** EX: nome_do_arquivo.txt ****\n" << endl;
        cin >> arquivo;
        g1 = ler_grava->lerArquivo(arquivo);
        quantConxo = g1->quantCompConexo();
        g1->adicionaNo(0);
        g1->mesmaComponenteConexa(0,0);
        tamanhoMundo = (float)g1->tamanhaoGrafo;
        distOrigem = (tamanhoMundo);
        cout << quantConxo.size() << endl;
        tamViewX = (width/ ceil(sqrt( (int)quantConxo.size())));
        tamViewY = (height/ceil(sqrt( (int)quantConxo.size())));
    }
    //PontoCentral();
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (width, height);
   glutInitWindowPosition (550, 0);
   glutCreateWindow ("Quad Test");
   init ();
   glutDisplayFunc(renderScene);
   glutReshapeFunc(reshape);
   glutMouseFunc( mouse );
   glutMotionFunc( motion );
   glutKeyboardFunc(keyboard);
   glutIdleFunc(idle);

	printf("Pressione ESC para fechar.\n");

   glutMainLoop();

   return 0;
}

void setMaterial(GLfloat *ambiente, GLfloat *difusa, GLfloat *especular,
					  GLfloat *brilho, GLfloat *emissao )
{
   // Define os parametros da superficie a ser iluminada
   glMaterialfv(GL_FRONT, GL_AMBIENT, ambiente);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, difusa);
   glMaterialfv(GL_FRONT, GL_SPECULAR, especular);
   glMaterialfv(GL_FRONT, GL_SHININESS, brilho);
   glMaterialfv(GL_FRONT, GL_EMISSION, emissao);
}

void PontoCentral(){
    float max_x,max_y,max_z, min_x,min_y,min_z;
    //central = new Vetor();
    v = g1->primeiroNo();
    max_x = g1->p[v->pegaId()]->getX();
    max_y = g1->p[v->pegaId()]->getY();
    max_z = g1->p[v->pegaId()]->getZ();
    min_x = g1->p[v->pegaId()]->getX();
    min_y = g1->p[v->pegaId()]->getY();
    min_z = g1->p[v->pegaId()]->getZ();

    for(v = g1->primeiroNo() ; v != NULL; v = g1->proximoNo()){
        if (max_x <= g1->p[v->pegaId()]->getX()){
            max_x = g1->p[v->pegaId()]->getX();
        }
        if (min_x > g1->p[v->pegaId()]->getX()){
            min_x = g1->p[v->pegaId()]->getX();
        }
        if (max_y <= g1->p[v->pegaId()]->getY()){
            max_y = g1->p[v->pegaId()]->getY();
        }
        if (min_y > g1->p[v->pegaId()]->getY()){
            min_y = g1->p[v->pegaId()]->getY();
        }
        if (max_z <= g1->p[v->pegaId()]->getZ()){
            max_z = g1->p[v->pegaId()]->getZ();
        }
        if (min_z > g1->p[v->pegaId()]->getZ()){
            min_z = g1->p[v->pegaId()]->getZ();
        }
    }

    central = new Ponto((max_x + min_x)/2, (max_y + min_y)/2, (max_z + min_z)/2);
}

// Motion callback
void motion(int x, int y )
{
   rotationX += (float) (y - last_y);
   rotationY += (float) (x - last_x);

   last_x = x;
   last_y = y;
}

// Mouse callback
void mouse(int button, int state, int x, int y)
{
   if ( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN )
   {
      last_x = x;
      last_y = y;
   }
}

void idle ()
{
  glutPostRedisplay();
}

void reshape (int w, int h)
{
   width = w;
   height = h;
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
}
void DesenhaBordas()
{
   glBegin(GL_LINES);
      glColor3f (1.0, 0.0, 0.0);
      //glRotatef( 2.0, 10.0, 1.0, 0.0 );
      glVertex3f(-tamViewX, -(height-tamViewY), 0.0);
      glVertex3f(tamViewX, -(height-tamViewY), 0.0);

      glColor3f (  0.0,   1.0, 0.0);
      glVertex3f(0.0, (height-tamViewY), 0.0);
      glVertex3f(0.0,  -(height-tamViewY), 0.0);
   glEnd();
}

void Views()
{
   //glViewport (0.0, 0.0, width, height);
   int tamViewX = (width/ ceil(sqrt( (int)quantConxo.size()))), tamViewY = (height/ceil(sqrt( (int)quantConxo.size()))), posViewX = 0.0 ,posViewY = 0.0;

   glClear (GL_COLOR_BUFFER_BIT);
   glRotatef( rotationY, 0.0, 1.0, 0.0 );
   glRotatef( rotationX, 1.0, 0.0, 0.0 );

   //glTranslatef(move1,0.0,move2);
   glPushMatrix();
        for (int i = 0; i < (int)quantConxo.size(); i++)
        {
            glPushMatrix();
            for (int j = 0; j < (int)quantConxo[i].size(); j++)
            {
                glViewport (posViewX, posViewY, tamViewX, tamViewY);
                glMatrixMode (GL_PROJECTION);
                glLoadIdentity ();
                gluPerspective(60.0, (GLfloat) width/(GLfloat) height, 1.0, 2000000.0);

                glMatrixMode(GL_MODELVIEW);
                glLoadIdentity ();
                gluLookAt (distOrigem, distOrigem, distOrigem, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

                //glPushMatrix();
                    //DesenhaBordas();
                //glPopMatrix();

                glPushMatrix();
                glRotatef( rotationY, 0.0, 1.0, 0.0 );
                glRotatef( rotationX, 1.0, 0.0, 0.0 );
                glTranslatef(move1,0.0,move2);
                    glColor3ub( g1->p[quantConxo[i][j]]->getR(), g1->p[quantConxo[i][j]]->getG(), g1->p[quantConxo[i][j]]->getB() );
                    glPointSize(6);
                    glBegin(GL_POINTS);
                        glVertex3f(g1->p[quantConxo[i][j]]->getX(), g1->p[quantConxo[i][j]]->getY(), g1->p[quantConxo[i][j]]->getZ());
                    glEnd();

                    v = g1->encontraNo(quantConxo[i][j]);

                    glLineWidth(2);

                    glColor3ub( g1->p[quantConxo[i][j]]->getR(), g1->p[quantConxo[i][j]]->getG(), g1->p[quantConxo[i][j]]->getB() );
                    glBegin(GL_LINES);
                        for(int k = 0; k < (int)v->aresta.size(); k++){
                            glVertex3f(g1->p[quantConxo[i][j]]->getX(), g1->p[quantConxo[i][j]]->getY(), g1->p[quantConxo[i][j]]->getZ());
                            glVertex3f(g1->p[v->aresta[k]]->getX(), g1->p[v->aresta[k]]->getY(), g1->p[v->aresta[k]]->getZ());
                        }
                    glEnd();
               glPopMatrix();

            }
            glPopMatrix();
            posViewX += tamViewX;
            if (posViewX+10 > width)
            {
                 posViewX = 0.0;
                 posViewY += tamViewY;
            }

        }
   glPopMatrix();
}


void renderScene(void)
{
   float k = 0.0;

   if (menu)
   {
       showMenu();
       glutPostRedisplay();
   }

   if (!t){
       glClear (GL_COLOR_BUFFER_BIT);
       glViewport (0.0, 0.0, width, height);
       //glClearColor (0.3, 0.3, 0.3, 0.3);
       glMatrixMode (GL_PROJECTION);
       glLoadIdentity ();
       gluPerspective(45, (GLfloat) width/(GLfloat) height, 1.0, 2000000.0);

       glMatrixMode(GL_MODELVIEW);
       glLoadIdentity ();
       gluLookAt (distOrigem/2, distOrigem, distOrigem/2, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

       // Limpar todos os pixels
       glClear (GL_COLOR_BUFFER_BIT);

       glPushMatrix();
          glTranslatef(posicao_luz[0],posicao_luz[1],posicao_luz[2]);
          glLightfv(GL_LIGHT0, GL_POSITION, posicao_luz);
          glMaterialfv(GL_FRONT, GL_DIFFUSE, cor_fonte_luz);
          glMaterialfv(GL_FRONT, GL_EMISSION, cor_emissao);
       glPopMatrix();

       glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, kc);
       glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, kl);
       glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, kq);

       // Desenhar um polígono branco (retângulo)

       glRotatef( rotationY, 0.0, 1.0, 0.0 );
       glRotatef( rotationX, 1.0, 0.0, 0.0 );
       glTranslatef(move1,0.0,move2);
       glPushMatrix();
            for (int i = 0; i < (int)quantConxo.size(); i++)
            {

                for (int j = 0; j < (int)quantConxo[i].size(); j++)
                {
                    glPushMatrix();
                        if(t2)
                            glTranslatef(k,k,k);
                        glColor3ub( g1->p[quantConxo[i][j]]->getR(), g1->p[quantConxo[i][j]]->getG(), g1->p[quantConxo[i][j]]->getB() );
                        glPointSize(6);
                        glBegin(GL_POINTS);
                            glVertex3f(g1->p[quantConxo[i][j]]->getX(), g1->p[quantConxo[i][j]]->getY(), g1->p[quantConxo[i][j]]->getZ());
                        glEnd();
                    glPopMatrix();

                   v = g1->encontraNo(quantConxo[i][j]);

                   glPushMatrix();
                    glLineWidth(2);
                    if(t2)
                        glTranslatef(k,k,k);
                     glColor3ub( g1->p[quantConxo[i][j]]->getR(), g1->p[quantConxo[i][j]]->getG(), g1->p[quantConxo[i][j]]->getB() );
                        glBegin(GL_LINES);
                            for(int k = 0; k < (int)v->aresta.size(); k++){
                                glVertex3f(g1->p[quantConxo[i][j]]->getX(), g1->p[quantConxo[i][j]]->getY(), g1->p[quantConxo[i][j]]->getZ());
                                glVertex3f(g1->p[v->aresta[k]]->getX(), g1->p[v->aresta[k]]->getY(), g1->p[v->aresta[k]]->getZ());
                            }
                        glEnd();
                    glPopMatrix();
                }
                k += d;
            }
    glPopMatrix();
  }
  else
  {
    Views();
  }

   glutSwapBuffers ();
   //glutPostRedisplay();
}


void init (void)
{
   glClearColor (0.3, 0.3, 0.3, 0.3);
   glShadeModel (GL_SMOOTH);
   glEnable(GL_DEPTH_TEST);

   glEnable(GL_COLOR_MATERIAL);


   glEnable(GL_DEPTH_TEST);               // Habilita Z-buffer
   glEnable(GL_CULL_FACE);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

  // Define parametros da luz 0
   glLightfv(GL_LIGHT0, GL_AMBIENT, cor_luz_amb);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, cor_luz);
   glLightfv(GL_LIGHT0, GL_SPECULAR, cor_luz);
   glLightfv(GL_LIGHT0, GL_POSITION, posicao_luz);

}

void keyboard(unsigned char key, int x, int y)
{
   switch (tolower(key))
   {
       case '+' :
         distOrigem -= 5;
      break;
      case '-' :
         distOrigem += 5;
      break;
      case 'p':
            distOrigem -= tamanhoMundo/4;
            cout << distOrigem << endl;
      break;
      case 'l':
            distOrigem += tamanhoMundo/4;
            cout << distOrigem << endl;
      break;
      case 'm':
            menu = true;
      break;
      case 't':
          t = !t;
      break;
      case 'y':
          t2 = !t2;
      break;
      case 'q':
          d -= 2;
      break;
      case 'e':
          d += 2;
      break;
      case 'a':
          move1 -= 2.0;
      break;
      case 'd':
          move1 += 2.0;
      break;
      case 'w':
          move2 -= 2.0;
      break;
      case 's':
          move2 += 2.0;
      break;
      case 'c':
          move2 = 0.0;
          move1 = 0.0;
      break;
      case 'z':
          move2 += 20.0;
      break;
      case 'x':
          move2 -= 20.0;
      break;
      case 'v':
          move1 += 20.0;
      break;
      case 'b':
          move1 -= 20.0;
      break;
      case 27:
         exit(0);
      break;
   }
}

void showMenu()
{

    cout << "    ******  TRABALHO DE GRAFOS ******" << endl;


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
                        g1->p.clear();
                        delete(g1);
                        cout << "Grafo anterior removido!!\n" << endl;
                        cout << "Digite o nome do arquivo como no exemplo:\n ** EX: nome_do_arquivo.txt **\n" << endl;
                        cin >> arquivo;
                        g1 = ler_grava->lerArquivo(arquivo);
                        quantConxo = g1->quantCompConexo();
                        g1->mesmaComponenteConexa(0,0);
                        tamanhoMundo = (float)g1->tamanhaoGrafo;
                        distOrigem = (tamanhoMundo);
                    }
            break;

            case 2:
                cout << "O grafo tem -> " << g1->contaNos() << " vertices !!\n" << endl;
            break;

            case 3:
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
                        quantConxo = g1->quantCompConexo();
                        g1->mesmaComponenteConexa(0,0);
                    }
                    else if( (r == 'a' || r == 'A') && ( g1->p.size() - g1->contaNos() ) )
                    {
                        cout << "Voce pode adicionar " << (g1->p.size() - g1->contaNos()) << endl;
                        cout << "Digite o ID do no!" << endl;
                        cin >> ad;
                        if (ad < (int)g1->p.size() ){
                            g1->adicionaNo(ad);
                            cout << "No de ID -> "<<ad<< " adicionado!!\n" << endl;
                            quantConxo = g1->quantCompConexo();
                            g1->mesmaComponenteConexa(0,0);
                        }
                        else
                            cout << "Digite um ID menor que " << g1->p.size() << endl;
                    }
                    else
                        cout << "Voce nao pode adicionar mais nos !!" << endl;
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
                        quantConxo = g1->quantCompConexo();
                        g1->mesmaComponenteConexa(0,0);
                    }
                    else if(r == 'a' || r == 'A')
                    {
                        cout << "Digite a primeira extremidade da aresta:" << endl;
                        cin >> adAr1;
                        cout << "Digite a segunda extremidade da aresta:" << endl;
                        cin >> adAr2;
                        g1->adicionaAresta(adAr1,adAr2);
                        cout << "Aresta -> "<<adAr1 << " - " << adAr2 << " foi adicionada!!\n" << endl;
                        quantConxo = g1->quantCompConexo();
                        g1->mesmaComponenteConexa(0,0);
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
                        }
                        cout << " A maior componente conexa tem " << maior << " nós !!" << endl;
                        cout << " A menor componente conexa tem " << menor << " nós !!\n" << endl;
                    }
            break;
            case 15:
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
            default: //showMenu(); //menu = false;
            break;
        }
        printf("\e[H\e[2J");

        menu = false;
}

