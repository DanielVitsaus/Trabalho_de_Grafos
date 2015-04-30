
#include <stdio.h>
#include <GL/glut.h>
#include "Ponto.h"
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

Ponto::Ponto(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

float Ponto::getX()
{
    return this->x;
}

float Ponto::getY()
{
    return this->y;
}

float Ponto::getZ()
{
    return this->z;
}

void Ponto::setR(int r)
{
    this->r = (GLubyte)r;
}
void Ponto::setG(int g)
{
    this->g = (GLubyte)g;
}
void Ponto::setB(int b)
{
    this->b = (GLubyte)b;
}
GLubyte Ponto::getR()
{
    return this->r;
}
GLubyte Ponto::getG()
{
    return this->g;
}
GLubyte Ponto::getB()
{
    return this->b;
}
