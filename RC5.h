#ifndef RC5_RC5_H
#define RC5_RC5_H

#include <vector>
#include <bitset>
#include <math.h>
#include <string>
#include "BinaryUtility.h"
using namespace std;

//const int WORD_SIZE                                   // w
const unsigned int WORD_BYTES = 4;                           // u
const unsigned int KEY_BYTES = 8;                            // b  -- key size = 64 bytes
const unsigned int ROUNDS = 12;                                  // r
const int S_SIZE = 26;                                  // t = 2r + 2
const int KEY_WORDS = (unsigned int)ceil(KEY_BYTES / WORD_BYTES);  // c

class RC5 {
public:
  RC5(){};
  RC5(const string keyhex);
  string encrypt(const string plaintext);
private:
  vector<word> _S;
  string cipher(block blk);
  void generateSubArray(string keyhex);
  word add(const word a, const word b);
  word leftRotate(const word a, const unsigned long shift);
  unsigned long toULong(const word word);
  void clone(word & dest, const word src);
};


#endif //RC5_RC5_H
