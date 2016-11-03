#ifndef ALFA_H_INCLUDED
#define ALFA_H_INCLUDED

using namespace std;

class Alfa{

    private:
        float valorAlfa;
        float quantVezesUsado;
        float melhorCusto;
        float somaTotalCusto;
        float media;
        float Q;
        float probabilidade;

    public:

        Alfa(float valorAlfa);
        void setAlfa(float valorAlfa);
        void setQuantVezesUsado(float quantVezesUsado);
        void setSomaTotalCusto(float soma);
        void setMelhorCusto(float melhorCusto);
        void setMedia(float media);
        void setQ(float q);
        void setProbabilidade(float probabilidade);

        float getAlfa();
        float getQuantVezesUsado();
        float getMelhorCusto();
        float getSomaTotalCusto();
        float getMedia();
        float getQ();
        float getProbabilidade();


} ;

#endif // ALFA_H_INCLUDED
