// It contains the WELL algorithm,
// introduced in <Game Programming Gems 7> by Chris Lomont.

#include "Random.h"
using namespace std;

static unsigned long rand_state[16];
static unsigned long rand_index = 0;

void InitializeRandom() {
  srand(time(NULL));
  for(int i = 0; i<16; ++i) {
    rand_state[i] = rand();
  }
  rand_index = 0;
}

unsigned long Random() {
  unsigned long a, b, c, d;
  a  = rand_state[rand_index];
  c  = rand_state[(rand_index+13)&15];
  b  = a^c^(a<<16)^(c<<15);
  c  = rand_state[(rand_index+9)&15];
  c ^= (c>>11);
  a  = rand_state[rand_index] = b^c;
  d  = a^((a<<5)&0xDA442D20UL);
  rand_index = (rand_index + 15)&15;
  a  = rand_state[rand_index];
  rand_state[rand_index] = a^b^d^(a<<2)^(b<<18)^(c<<28);
  return rand_state[rand_index];
}
