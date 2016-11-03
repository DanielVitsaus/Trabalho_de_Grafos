/*
 * util.c
 * Oil Collecting Vehicle Routing Problem
 * Some utilities Implementation ...
 * By Haroldo Santos
 */

#include "util.h"

#include <climits>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <sys/timeb.h>
#include <sys/resource.h>

#include <vector>
#include <iostream>

using namespace std;

#ifndef MTWISTER
#define MTWISTER
/* Code from Mersenne twister random number generator */
/* http://www.math.keio.ac.jp/~matumoto/emt.html      */

/* Period parameters */
#define N 624
#define M 397
#define MATRIX_A 0x9908b0dfUL   /* constant vector a */
#define UPPER_MASK 0x80000000UL /* most significant w-r bits */
#define LOWER_MASK 0x7fffffffUL /* least significant r bits */

static unsigned long mt[N]; /* the array for the state vector  */
static int mti=N+1; /* mti==N+1 means mt[N] is not initialized */


/* initializes mt[N] with a seed */
void init_genrand(unsigned long s) {
  mt[0]= s & 0xffffffffUL;
  for (mti=1; mti<N; mti++) {
    mt[mti] =
        (1812433253UL * (mt[mti-1] ^ (mt[mti-1] >> 30)) + mti);
    /* See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier. */
    /* In the previous versions, MSBs of the seed affect   */
    /* only MSBs of the array mt[].                        */
    /* 2002/01/09 modified by Makoto Matsumoto             */
    mt[mti] &= 0xffffffffUL;
    /* for >32 bit machines */
  }
}


/* generates a random number on [0,0xffffffff]-interval */
unsigned long genrand_int32(void) {
  unsigned long y;
  static unsigned long mag01[2]={0x0UL, MATRIX_A};
  /* mag01[x] = x * MATRIX_A  for x=0,1 */

  if (mti >= N) { /* generate N words at one time */
    int kk;

    if (mti == N+1)   /* if init_genrand() has not been called, */
      init_genrand(5489UL); /* a default initial seed is used */

    for (kk=0;kk<N-M;kk++) {
      y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
      mt[kk] = mt[kk+M] ^ (y >> 1) ^ mag01[y & 0x1UL];
    }
    for (;kk<N-1;kk++) {
      y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
      mt[kk] = mt[kk+(M-N)] ^ (y >> 1) ^ mag01[y & 0x1UL];
    }
    y = (mt[N-1]&UPPER_MASK)|(mt[0]&LOWER_MASK);
    mt[N-1] = mt[M-1] ^ (y >> 1) ^ mag01[y & 0x1UL];

    mti = 0;
  }

  y = mt[mti++];

  /* Tempering */
  y ^= (y >> 11);
  y ^= (y << 7) & 0x9d2c5680UL;
  y ^= (y << 15) & 0xefc60000UL;
  y ^= (y >> 18);

  return y;
}

/* generates a random number on [0,1]-real-interval */
double genrand_real1(void) {
  return genrand_int32()*(1.0/4294967295.0);
  /* divided by 2^32-1 */
}

/* generates a random number on [0,1)-real-interval */
double genrand_real2(void) {
  return genrand_int32()*(1.0/4294967296.0);
  /* divided by 2^32 */
}

#endif

void randomize( unsigned int *seed) {
    //unsigned int seed;
  *seed = (unsigned int)time((time_t *)NULL);
  *seed=1216330690;
#ifdef MTWISTER
  cout << "Using mersenne twister random number generator."<< endl;
  init_genrand(*seed);
#else
  cout << "Using default random number generator." << endl;
  srand(seed);
#endif
    //printf("Random seed is %d\n", *seed);
}

void setSeed(unsigned int seed) {
#ifdef MTWISTER
  init_genrand(seed);
#else
  srand(seed);
#endif
}

inline unsigned int intRandom(const unsigned int maxValue) {
#ifdef MTWISTER
  return ((double)genrand_real2())*((double)maxValue);
#else
  static unsigned int res;
  static unsigned int rgen;
  static double factor;
  rgen = rand();
  factor = ((double)rgen/(double)INT_MAX);

  res = (unsigned int) ( maxValue * factor );
  if (res==maxValue) res--;
  return res;
#endif
}

inline double doubleRandom(const double maxValue) {
#ifdef MTWISTER
  return maxValue * genrand_real1();
#else
  return (((double)rand())/((double)INT_MAX))*maxValue;
#endif
}
/***********************************************************************************
 * Funcao    : CARDINAL xrandom_range (CARDINAL min, CARDINAL max)                 *
 * Criacao   : 17/04/2002                                                          *
 * Descricao : Gera um numero aleatorio entre min e max,inclusive. Se  min <= max, *
 *             a funcao retorna min.                                               *
 * Parametros: min     - limite inferior do numero aleatorio gerado, inclusive.    *
 *             max     - limite superior do numero aleatorio gerado, inclusive.    *
 * Retorno   : Retorna o numero aleatorio gerado.                                  *
 ***********************************************************************************/

unsigned int xrandomRange (unsigned   int min, unsigned   int max)
{
#ifdef MTWISTER
  unsigned  int delta;

  delta = max - min;
  if (delta > 0)
    return  min + intRandom (delta + 1);

  return min;
#endif
}
// unsigned int xrandomRange (unsigned   int min, unsigned   int max)
// {
// #ifdef MTWISTER
//     unsigned int delta;
//
//     delta = max - min;
//     if (delta > 0)
//         return  (genrand_int32 () % delta+1);
//
//     return min;
// #endif
// }

/***********************************************************************************
 * Funcao    : CARDINAL xrandom_exclude (CARDINAL excluded, CARDINAL limit)        *
 * Criacao   : 17/04/2002                                                          *
 * Descricao : Gera um numero aleatorio entre 0 e limit - 1,  excluindo  o  numero *
 *             excluded.                                                           *
 * Parametros: excluded - numero que deve ser excluido entre os numeros gerados.   *
 *             limit    - limite superior do numero aleatorio gerado, exclusive.   *
 * Retorno   : Retorna o numero aleatorio gerado.                                  *
 ***********************************************************************************/

unsigned   int xrandomExclude (unsigned  int excluded, unsigned   int limit)
{
  unsigned   int  rand;

  rand = intRandom (limit);
  if (rand == excluded)
    rand = (intRandom (2) ? rand + 1 : rand - 1) % limit;

  return rand;
}




double wallClock() {
  struct timeb tp;
  double mili;

  ftime(&tp);
  mili = (double)( (tp.time)+((double)tp.millitm)/1000);

  return mili;
}

double cpuTime() {
  static struct rusage usage;
  getrusage(RUSAGE_SELF, &usage);
  return ((double)usage.ru_utime.tv_sec)+(((double)usage.ru_utime.tv_usec)/((double)1000000));
}





/*void quickSortVector (vector <int> &a, vector<int> &vetIndex, int begin, int end) {
    if (begin < end){
        int pivo = partitionVector (a, vetIndex, begin, end);
        quickSortVector (a, vetIndex, begin, pivo-1);
        quickSortVector (a, vetIndex, pivo+1, end);
}
}

int partitionVector (vector <int> &a, vector<int> &vetIndex, int begin, int end) {
    int e = begin + 1;
    float pivo = a[begin];
    int d = end;

    int aux;
    int auxTroca;
    while (e <= d){
        while (e <= d && (a[e] < pivo)){
            e++;
}
        while (e <= d && (a[d] >= pivo) ){
            d--;
}
        if (e < d){
            aux = vetIndex[e];
            vetIndex[e] = vetIndex[d];
            vetIndex[d] = aux;
            auxTroca    = a[e];
            a[e]        = a[d];
            a[d]        = auxTroca;
            e++;
            d--;
}
}

    aux = vetIndex[begin];
    vetIndex[begin] = vetIndex[d];
    vetIndex[d] = aux;

    auxTroca  = a[begin];
    a[begin]  = a[d];
    a[d]      = auxTroca;

    return d;
*/
//   Teste do QuickSort
//
//   vector <int> index;
//   vector <int> valores;
//   srand(time(NULL));
//
//   for (int i=0; i<15; i++){
//     index.push_back(i);
//     valores.push_back( rand()%100 );
//   }
//
//   for (int i=0; i<valores.size(); i++){
//     cout << index[i] << "->" << valores[i] << ", ";
//   }
//   cout << endl << endl;
//
//   quickSortVector (valores, index, 0, valores.size()-1 );
//
//   for (int i=0; i<valores.size(); i++){
//     cout << index[i] << "->" << valores[i] << ", ";
//   }
//   cout << endl << endl;
//}

void testaRandom(unsigned int num){
  cout << "[ " ;
  for(unsigned int i=0; i<num; i++){
    cout << xrandomRange(0,num) << " "  /*intRandom(num) <<*/;
  }
  cout << " ]" << endl;
}

