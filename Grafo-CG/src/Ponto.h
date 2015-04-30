#ifndef PONTO_H_INCLUDED
#define PONTO_H_INCLUDED

#include <stdio.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class Ponto{

   private:
        float x,y,z;
        GLubyte r,g,b;

   public:
        float getX();
        float getY();
        float getZ();
        void setR(int r);
        void setG(int g);
        void setB(int b);
        GLubyte getR();
        GLubyte getG();
        GLubyte getB();
        Ponto(){};
        Ponto(float x, float y, float z);


};


#endif // PONTO_H_INCLUDED
