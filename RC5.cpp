#include <sstream>
#include <algorithm>
#include "RC5.h"

RC5::RC5(const string keyhex) {
  this->generateSubArray(keyhex);
}

string RC5::encrypt(const string plaintext) {
  BinaryUtility bu = BinaryUtility();
  stringstream ss;
  string pt(plaintext);
  // convert to little endian hex
  pt = bu.asciiToHex(pt);
  pt = bu.alternateEndianness(pt);

  // break into blocks and encrypt each block
  vector<block> ptBlocks = bu.wordsToBlocks(bu.hexToWords(pt));
  for (unsigned int i = 0; i < ptBlocks.size(); i++) {
    ss << cipher(ptBlocks.at(i));
  }

  return ss.str();
}

string RC5::cipher(block blk) {
  word A = blk.at(0);
  word B = blk.at(1);
  int r = ROUNDS;

  A = add(A, _S[0]);
  B = add(B, _S[1]);
  for(unsigned int i = 0; i < r; i++) {
    A = add(leftRotate((A ^ B), toInt(B)), _S[2*i]);
    B = add(leftRotate(B ^ A, toInt(A)), _S[(2*i)+1]);
  }
  string ciphertext = B.to_string() + A.to_string();
  return ciphertext;
}

void RC5::generateSubArray(string keyhex) {
  BinaryUtility bu = BinaryUtility();

  int t = S_SIZE;
  int u = WORD_NUM_BYTES;
  word P(0xb7e15163);
  word Q(0x9e3779b9);
  //int c = (int)ceil(KEY_NUM_BYTES/WORD_NUM_BYTES); // c
  //vector<word> S; // vector is of size t = 2r + 2

  // initialize S
  for (unsigned int i = 0; i < WORD_SIZE; i++) {
    _S[i] = word(0x0000);
  }

  _S[0] = P;   // S[0] = P
  for (unsigned int i=1; i <= (t-1); i++) {
    _S[i] = add(_S[i - 1], Q);   // S[i] = S[i-1] + Q
  }

  int b = KEY_NUM_BYTES;

  // initialize L
  word L [c];
  for (unsigned int i = 0; i < c; i++) {
    L[i] = word(0x0000);
  }

  string littleEndianKeyHex = bu.alternateEndianness(keyhex);
  bitvector K = bu.hexToBitVector(littleEndianKeyHex, 64);
  for (int i = (b-1); i >= 0; i--) {
    word K_i = (K[i] == true) ? word(0x0001) : word(0x0000);
    L[i/u] = add((L[i/u] << 8), K_i); // L[i/u] = (L[i/u] <- 8) + K[i]
  }

  unsigned int i = 0;
  unsigned int j = 0;
  word C = word(0x0000);
  word D = word(0x0000);
  int count = 3 * max(t, c);
  while(count >= 0) {
    //word test = add(_S[i], C);
    _S[i] = leftRotate(add(add(_S[i], C), D), 3);
    C = word(_S[i].to_string());
    D = L[j] = leftRotate(add(add(L[j], C), D), toInt((add(C, D))));
    i = (i + 1) % t;
    j = (j + 1) % c;
    count--;
  };

  //this->_S.swap(S);
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



