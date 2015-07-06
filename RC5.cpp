#include <sstream>
#include <algorithm>
#include <iostream>
#include <iomanip>
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
    A = add(leftRotate((A ^ B), toULong(B)), _S[2*i]);
    B = add(leftRotate(B ^ A, toULong(A)), _S[(2*i)+1]);
  }
  string ciphertext = B.to_string() + A.to_string();
  return ciphertext;
}

void RC5::generateSubArray(string keyhex) {
  BinaryUtility bu = BinaryUtility();

  int u = WORD_BYTES;
  word P(0xb7e15163);
  word Q(0x9e3779b9);

//  // initialize S
//  for (unsigned int i = 0; i < S_SIZE; i++) {
//   _S[i].reset();
//  }

  _S.push_back(P);   // S[0] = P
  for (unsigned int i=1; i <= (S_SIZE-1) ; i++) {
    _S.push_back(add(_S[i - 1], Q));   // S[i] = S[i-1] + Q
  }
//
  // initialize L
  word L [KEY_WORDS];
  //word L [2];
  for (unsigned int i = 0; i < KEY_WORDS; i++) {
    L[i] = word(0x0000);
  }
//
  // Copy K into L in little-endian order.
  vector<byte> K = bu.hexToBytes(keyhex);
  for (int i = (KEY_BYTES-1); i >= 0; i--) {
    word K_i = word(K[i].to_string());
    L[i/u] = add(L[i/u] << 8, K_i);
  }
  // now:
  // K    : 7 [ K7 | K6 | K5 | K4 | K3 | K2 | K1 | K0 ] 0
  // L[1] : 3 [ K7 | K6 | K5 | K4 ] 0
  // L[0] : 3 [ K3 | K2 | K1 | K0 ] 0
//
  unsigned int i = 0;
  unsigned int j = 0;
  word C;
  word D;
  int count = 3 * max(S_SIZE, KEY_WORDS);
  C.reset();
  D.reset();
  while(count >= 0) {

//    cout << "Count: "  << count << endl;
//    cout << "C: " << endl << C << endl;
//    cout << "D: " << endl << D << endl;
//    cout << "i: " << i << endl;
//    cout << "j: " << j << endl;
//    cout << "S[" << i << "] : " << endl << _S[i].to_string() << endl;
//    cout << "S[" << i << "] + C: " << endl <<  add(_S[i], C) << endl;
//    cout << "S[" << i << "] + C + D: " << endl << add(add(_S[i], C), D) << endl;
//    cout << "(S[" << i << "] + C + D) <- 3: " << endl << leftRotate(add(add(_S[i], C), D), 3) << endl << endl;
//    cout << "L[" << j << "] : " << endl << L[j].to_string() << endl;
//    cout << "L[" << j << "] + C: " << endl << add(L[j], C) << endl;
//    cout << "L[" << j << "] + C + D: " << endl << add(add(L[j], C), D) << endl;
//    cout << "C + D : " << endl << toULong(add(C, D)) << endl;
//    cout << "(L[" << j << "] + C + D) <- (C + D): " << endl << leftRotate(add(add(L[j], C), D), toULong((add(C, D)))) << endl;
//    cout << "S[" << i << "]: " << _S[i].to_string() << endl;
//    cout << "L[" << j << "]: " << L[j].to_string() << endl;

    //_S[i] = leftRotate(add(add(_S[i], C), D), 3);
    //L[j] = leftRotate(add(add(L[j], C), D), toULong(add(C, D)));
    clone(_S[i], leftRotate(add(add(_S[i], C), D), 3));
    clone(L[j], leftRotate(add(add(L[j], C), D), toULong(add(C, D))));
    clone(C, _S[i]);
    clone(D, L[j]);

//    cout << "C = S[" << i << "] --> D: " << C << endl;
//    cout << "D = L[" << j << "] --> D: " << D << endl;
//    cout << "(" << i << " + 1) % " << S_SIZE << ": "  << (i + 1) % S_SIZE << endl;
//    cout << "(" << j << " + 1) % " << KEY_WORDS << ": " << (j + 1) % KEY_WORDS << endl << endl;
//
//    i = (i + 1) % S_SIZE;
//    j = (j + 1) % KEY_WORDS;
//
//    cout << "--------------------------------------------------------------" << endl;

    count--;
  };
}

word RC5::add(const word a, const word b) {
  bool overflow;
  return BinaryUtility().add(a, b, overflow);
}

word RC5::leftRotate(const word a, const unsigned long shift) {
  return BinaryUtility().leftRotate(a, shift);
}

unsigned long RC5::toULong(const word word) {
  return BinaryUtility().toULong(word);
}

void RC5::clone(word & dest, const word src) {
  for (unsigned int i = 0; i < src.size(); i++) {
    if(src.test(i)) {
      dest.set(i, 1);
    } else {
      dest.set(i, 0);
    }
  }
}



