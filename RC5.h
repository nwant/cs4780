#ifndef PROJ1_RC5_RC5_H
#define PROJ1_RC5_RC5_H

#include <vector>
#include <bitset>
#include <math.h>
#include "BinaryUtility.h"
using namespace std;

//const int WORD_SIZE                                   // u
const int KEY_NUM_BYTES = 8;                            // b  -- key size = 56 bytes
const int ROUNDS = 12;                                  // r
const int S_SIZE = 2 * ROUNDS + 2;                      // t = 2r + 2
const int c = (int)ceil(KEY_NUM_BYTES/WORD_SIZE);       // c

class RC5 {
public:
  RC5(const string keyhex);
  char * encrypt(const char block);
private:
  vector<bitset<32>> _S;
  void generateSubArray(string keyhex);
  bitset<32> add(const bitset<32> a, const bitset<32> b);
  bitset<32> leftRotate(const bitset<32> a, const int shift);
  int toInt(const bitset<32> word);
};


#endif //PROJ1_RC5_RC5_H
