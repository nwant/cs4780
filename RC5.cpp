#include "RC5.h"

RC5::RC5(const string keyhex) {
  generateSubArray(keyhex);
}


void RC5::generateSubArray(string keyhex) {
  BinaryUtility bu = BinaryUtility();

  int t = S_SIZE;
  int u = WORD_SIZE;
  bitset<32> P(0xb7e15163);
  bitset<32> Q(0x9e3779b9);
  vector<bitset<32>> S;

  S.at(0) = P;
  for (unsigned int i=1; i <= (t-1); i++) {
    S.at(i) = add(S.at(i-1), Q);
  }

  int b = KEY_NUM_BYTES;

  bitset<32> L [c];
  vector<byte> keybytes = bu.hexStringToBytes(keyhex);
  for (int i = (b-1); i >= 0; i--) {
    L[i/u] = add((L[i/u] << 8), bu.toWord(keybytes.at(i)));
  }

  unsigned int i = 0;
  unsigned int j = 0;
  bitset<32> C, D;
  for(int count; i < max(t,c); i++) {
    C = S.at(i) = leftRotate(add(add(S.at(i), C), D), 3);
    D = L[j] = leftRotate( add(add(L[j], C), D) , toInt((add(C, D))) );

  }

  this->_S.swap(S);
}

bitset<WORD_SIZE> RC5::add(const bitset<32> a, const bitset<32> b) {
  bool overflow;
  return BinaryUtility().add(a, b, overflow);
}

bitset<32> RC5::leftRotate(const bitset<32> a, const int shift) {
  return BinaryUtility().leftRotate(a, shift);
}

int RC5::toInt(const bitset<32> word) {
  return BinaryUtility().toInt(word);
}