#include "RC5.h"

RC5::RC5(const string keyhex) {
  generateSubArray(keyhex);
}



void RC5::generateSubArray(string keyhex) {
  BinaryUtility bu = BinaryUtility();

  int t = S_SIZE;
  int u = WORD_SIZE;
  word P(0xb7e15163);
  word Q(0x9e3779b9);
  vector<bitset<WORD_SIZE> > S; // vector is of size t = 2r + 2

  S.at(0) = P;
  for (unsigned int i=1; i <= (t-1); i++) {
    S.at(i) = add(S.at(i-1), Q);
  }

  int b = KEY_NUM_BYTES;

  word L [c];
  string littleEndianKeyHex = bu.alternateEndianness(keyhex);
  bitvector K = bu.hexToBitVector(littleEndianKeyHex, 64);
  for (int i = (b-1); i >= 0; i--) {
    L[i/u] = add((L[i/u] << 8), word(static_cast<unsigned long>(K[i])));
  }

  unsigned int i = 0;
  unsigned int j = 0;
  word C, D;
  for(int count = 0; count < max(t ,c); count++) {
    C = S.at(i) = leftRotate(add(add(S.at(i), C), D), 3);
    D = L[j] = leftRotate(add(add(L[j], C), D), toInt((add(C, D))));
    i = (i + 1) % t;
    j = (j + 1) % c;
  }

  this->_S.swap(S);
}

word RC5::add(const word a, const word b) {
  bool overflow;
  return BinaryUtility().add(a, b, overflow);
}

word RC5::leftRotate(const word a, const int shift) {
  return BinaryUtility().leftRotate(a, shift);
}

unsigned int RC5::toInt(const word word) {
  return BinaryUtility().toInt(word);
}
