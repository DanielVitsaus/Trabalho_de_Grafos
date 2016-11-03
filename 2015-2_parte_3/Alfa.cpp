#include <iostream>

#include "Alfa.h"


using namespace std;


Alfa::Alfa(float valorAlfa){
    this->valorAlfa = valorAlfa;
    this->quantVezesUsado = 0.0;
    this->melhorCusto = 0.0;
    this->somaTotalCusto = 0.0;
    this->media = 0.0;
    this->Q = 1.0;
    this->probabilidade = 0.20;
}

void Alfa::setAlfa(float valorAlfa){
    this->valorAlfa = valorAlfa;
}

void Alfa::setQuantVezesUsado(float quantVezesUsado){
    this->quantVezesUsado += quantVezesUsado;
}

void Alfa::setMelhorCusto(float melhorCusto){
    this->melhorCusto = melhorCusto;
}

void Alfa::setSomaTotalCusto(float soma){
    this->somaTotalCusto += soma;
}

void Alfa::setMedia(float media){
    this->media = media;
}

void Alfa::setQ(float q){
    this->Q = q;
}

void Alfa::setProbabilidade(float probabilidade){
    this->probabilidade = probabilidade;
}

float Alfa::getAlfa(){ return this->valorAlfa; }
float Alfa::getQuantVezesUsado(){ return this->quantVezesUsado; }
float Alfa::getMelhorCusto(){ return this->melhorCusto; }
float Alfa::getSomaTotalCusto(){ return this->somaTotalCusto; }
float Alfa::getMedia(){ return this->somaTotalCusto / ( this->quantVezesUsado == 0 ? 1 : this->quantVezesUsado ); }
float Alfa::getQ(){ return this->Q; }
float Alfa::getProbabilidade(){ return this->probabilidade; }


