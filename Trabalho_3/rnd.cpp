#include <cstdlib>
#include "rnd.h"

Rnd::Rnd() {
    srand(rdtsc());
}

/** \brief Gera um valor aleatório entre os valores de mínimo e máximo
 *
 * \param unsigned int minimo
 * \param unsigned int maximo
 * \return unsigned int minimo + (rand()%((maximo-minimo)+1))
 */
unsigned int Rnd::meurand(unsigned int minimo, unsigned int maximo) {
    return minimo + (rand()%((maximo-minimo)+1));
}
