/*
 * util.h
 * Oil Collecting Vehicle Routing Problem
 * Some utilities Definition ...
 */

 // For compiling with Mersenne twister random number generator include MTWISTER 
 // compiling directive


#ifndef UTIL_H
#define UTIL_H
//#ifndef MTWISTER
//#define MTWISTER


#include <ctime>
#include <unistd.h>
#include <sys/times.h>

#include <vector>

using namespace std;
//#ifdef MTWISTER
//#define MTWISTER
void randomize(unsigned int *seed);

void setSeed(const unsigned int seed);

/* generates an integer i in {0,...,maxValue-1} */
unsigned int intRandom(const unsigned int maxValue);
unsigned int xrandomExclude (unsigned int excluded, unsigned int limit);
unsigned int xrandomRange (unsigned int min, unsigned int max);
double doubleRandom(const double maxValue);
void init_genrand(unsigned long s);
void init_by_array(unsigned long init_key[], int key_length);
unsigned long genrand_int32(void);
long genrand_int31(void);
double genrand_real1(void);
double genrand_real2(void);
double genrand_real3(void);
double genrand_res53(void);
void testaRandom(unsigned int num);
double wallClock();
double cpuTime();
//#endif

#endif /* ifndef UTIL_H */

