#ifndef RC5_RC5_H
#define RC5_RC5_H

#include <vector>
#include <bitset>
#include <math.h>
#include "BinaryUtility.h"
using namespace std;

//const int WORD_SIZE                                   // u
const int KEY_NUM_BYTES = 8;                            // b  -- key size = 64 bytes
const int ROUNDS = 12;                                  // r
const int S_SIZE = 2 * ROUNDS + 2;                      // t = 2r + 2
const int c = (int)ceil(KEY_NUM_BYTES/WORD_SIZE);       // c

class RC5 {
public:
  RC5(const string keyhex);
  //string encrypt(string plaintext);
private:
  vector<word> _S;
  void generateSubArray(string keyhex);
  word add(const word a, const word b);
  word leftRotate(const word a, const int shift);
  unsigned int toInt(const word word);
};


#endif //RC5_RC5_H
