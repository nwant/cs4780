#include <sstream>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include "RC5.h"

RC5::RC5(const string keyhex) {
  this->generateSubArray(keyhex);
}

string RC5::encrypt(const string plaintext) {
  BinaryUtility bu = BinaryUtility();
  stringstream ss;
  string pt(plaintext);

  //cout << "Plaintext" << plaintext << endl;
  // convert to little endian hex
  pt = bu.asciiToHex(pt);

  //cout << "Plaintext in hex: " << pt << endl;
  pt = bu.alternateEndianness(pt);
  //cout << "Plaintext in hex, little endian : " << pt << endl;

  vector<word> ptWords = bu.hexToWords(pt);
  for (int i = 0; i < ptWords.size(); i++) {
    cout << "plaintest word " << i << ": " << bu.binToHex(ptWords[i].to_string()) << endl;
  }
  cout << endl;

  // break into blocks and encrypt each block
  vector<block> ptBlocks = bu.wordsToBlocks(bu.hexToWords(pt));

  cout << endl;

  for (unsigned int i = 0; i < ptBlocks.size(); i++) {
    cout << "plaintext block " << i << ": " << bu.binToHex(ptBlocks[i][0].to_string()) << " " << bu.binToHex(ptBlocks[i][1].to_string()) << endl;
    ss << cipher(ptBlocks.at(i));
    cout << "ciphertext block " << i << ": " << cipher(ptBlocks.at(i)) << endl;
  }

  return ss.str();
}

string RC5::cipher(block blk) {
  word A, B;
  //cout << "entering cipher" << endl;
  //cout << "Before encryption: " << endl;
  //cout << "A: " << BinaryUtility().binToHex(blk.at(0).to_string()) << endl;
  //cout << "B: " << BinaryUtility().binToHex(blk.at(1).to_string()) << endl << endl;
  clone(A, blk.at(0));
  clone(B, blk.at(1));

  clone(A, add(A, _S[0]));
  clone(B, add(B, _S[1]));
  for(unsigned int i = 1; i <= ROUNDS; i++) {
    clone(A, add(leftRotate((A ^ B), toULong(B)), _S[2*i]));
    clone(B, add(leftRotate((B ^ A), toULong(A)), _S[(2*i)+1]));
  }
  //cout << "After encryption: " << endl;
  //cout << "A: " << BinaryUtility().binToHex(A.to_string()) << endl;
  //cout << "B: " << BinaryUtility().binToHex(B.to_string()) << endl << endl;
  //cout << "leaving cipher" << endl;
  return BinaryUtility().binToHex(B.to_string()) + BinaryUtility().binToHex(A.to_string());
}

void RC5::generateSubArray(string keyhex) {
  BinaryUtility bu = BinaryUtility();

  int u = WORD_BYTES;
  word P(0xb7e15163);
  word Q(0x9e3779b9);


  // initialize S Array
  _S.push_back(P);   // S[0] = P
  //cout << "S[0]: " << bu.binToHex(_S[0].to_string()) << endl;
  for (unsigned int i=1; i <= (S_SIZE-1) ; i++) {
    word newWord;
    clone(newWord, add(_S[i-1], Q));
    _S.push_back(newWord);   // S[i] = S[i-1] + Q
//    cout << "S[" << i << "]: " << bu.binToHex(newWord.to_string()) << endl;
}
  //cout << endl;

//  for (unsigned int i=0; i< S_SIZE; i++) {
//    cout << "S[" << i << "]: "  << bu.binToHex(_S.at(i).to_string()) << endl;
//  }
//  cout << endl;

  // initialize L
  word L [KEY_WORDS];
  for (unsigned int i = 0; i < KEY_WORDS; i++) {
    word nullWord = word(0x0000);
    clone(L[i], nullWord);
  }

//  for (unsigned int i = 0; i < KEY_WORDS; i++) {
//    cout << "L[" << i << "]: " << bu.binToHex(L[i].to_string()) << endl;
//  }


  // generate L array:
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

//  for (unsigned int i = 0; i < KEY_BYTES; i++) {
//    cout << "K[" << i << "]: " << bu.binToHex(K[i].to_string()) << endl;
//  }
//  cout << endl;
//  for (unsigned int i = 0; i < KEY_WORDS; i++) {
//    cout << "L[" << i << "]: " << bu.binToHex(L[i].to_string()) << endl;
//  }
//  cout << endl;

  // generate S array based on key
  unsigned int i = 0;
  unsigned int j = 0;
  word C;
  word D;
  int count = 3 * max(26, KEY_WORDS);
  C.reset();
  D.reset();
  while(count >= 0) {

    cout << "Count: "  << (78 - count) << endl;
    cout << "C: " <<  bu.binToHex(C.to_string()) << endl;
    cout << "D: " <<  bu.binToHex(D.to_string()) << endl;
    cout << "i: " << i << endl;
    cout << "j: " << j << endl;
    cout << "S[" << i << "] : "  << bu.binToHex(_S[i].to_string()) << endl << endl;
    cout << "S[" << i << "] + C: "  <<  bu.binToHex(add(_S[i], C).to_string()) << endl << endl;
    cout << "S[" << i << "] + C + D: "  << bu.binToHex(add(add(_S[i], C), D).to_string()) << endl << endl;
    cout << "(S[" << i << "] + C + D) <- 3: "  << bu.binToHex(leftRotate(add(add(_S[i], C), D), 3).to_string());
    cout << " **(should be new S[" << i << "]: " << endl << endl;
    cout << "L[" << j << "] : "  << bu.binToHex(L[j].to_string()) << endl << endl;
    cout << "L[" << j << "] + C: " << bu.binToHex(add(L[j], C).to_string()) << endl << endl;
    cout << "L[" << j << "] + C + D: "  << bu.binToHex(add(add(L[j], C), D).to_string()) << endl << endl;
    cout << "C + D : "  << toULong(add(C, D)) << endl << endl;
    cout << "(L[" << j << "] + C + D) <- (C + D): "  << bu.binToHex(leftRotate(add(add(L[j], C), D), toULong((add(C, D)))).to_string());
    cout << "  **(should be new L[" << j << "]: " << endl << endl;
    //cout << "S[" << i << "]: " << bu.binToHex(_S[i].to_string()) << endl << endl;
    //cout << "L[" << j << "]: " << bu.binToHex(L[j].to_string()) << endl << endl << endl;

    //_S[i] = leftRotate(add(add(_S[i], C), D), 3);
    //L[j] = leftRotate(add(add(L[j], C), D), toULong(add(C, D)));
    clone(_S[i], leftRotate(add(add(_S[i], C), D), 3));
    clone(L[j], leftRotate(add(add(L[j], C), D), toULong(add(C, D))));
    clone(C, _S[i]);
    clone(D, L[j]);

    cout << "after calulation" << endl;
    cout << "C = S[" << i << "] --> D: " << bu.binToHex(C.to_string()) << endl;
    cout << "D = L[" << j << "] --> D: " << bu.binToHex(D.to_string()) << endl;
    cout << "(" << i << " + 1) % " << S_SIZE << ": "  << (i + 1) % S_SIZE << endl;
    cout << "(" << j << " + 1) % " << KEY_WORDS << ": " << (j + 1) % KEY_WORDS << endl << endl;

    i = (i + 1) % S_SIZE;
    j = (j + 1) % KEY_WORDS;

    //cout << "--------------------------------------------------------------" << endl;

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
  return BinaryUtility().clone(dest, src);
}



