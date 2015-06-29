#include <cstdlib>
#include "rnd.h"

Rnd::Rnd() {
    srand(rdtsc());
}

unsigned int Rnd::meurand(unsigned int minimo, unsigned int maximo) {
    return minimo + (rand()%((maximo-minimo)+1));
}
