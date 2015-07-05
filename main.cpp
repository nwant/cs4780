#include <iostream>
#include "RC5.h"

const int P = 0xb7e15163;
const int Q = 0x9e3779b9;

int main() {

  BinaryUtility utility = BinaryUtility();

  string testKey1 = "4847464544434241";

  cout << "test key: " << testKey1 << endl;
  cout << "test key to binary: " << endl;
  cout << utility.hexToBin(testKey1) << endl;
  bitvector K = utility.hexToBitVector(testKey1, 64);
  cout << "test key as bit vector: " << endl;
  cout << utility.bitVectorToBin(K) << endl;

  bitset<32> bits(0xffff0000);
  cout << "bits before rotate: " << bits << endl;
  cout << "bits after left rotate 3: " << utility.leftRotate(bits,3) << endl;

  bitset<32> a(0xf000000f);
  bitset<32> b(0xa0000002);
  bool overflow;

  cout << "  " << a << endl;
  cout << "+ " << b << endl;
  cout << "  -----------------------------------" << endl;
  cout << "  " << utility.add(a, b, overflow) << endl;
  cout << "with " << (overflow ? "overflow" : "no overflow") << endl;

  string answer = utility.binToHex(utility.add(a,b,overflow).to_string());
  cout << "answer in hex: " << answer << endl;
  cout << "in little endian: " << endl;
  cout << utility.alternateEndianness(answer) << endl;

  string test = "be13b6789adf";
  cout << test << endl;
  cout << utility.alternateEndianness(test) << endl;

  cout << "to words: " << endl;
  vector<word> words = utility.hexToWords(utility.alternateEndianness(test));
  for (unsigned int i = 0; i < words.size(); i++) {
    cout << "word " << i << ": " << words.at(i) << endl;
  }

  test += test;
  cout << "long test: " << test << endl;
  words = utility.hexToWords(test);
  vector<block> blocks = utility.wordsToBlocks(words);
  for (unsigned int i = 0; i < blocks.size(); i++) {
    cout << "block " << i << ": " << blocks.at(i)[1] << " " << blocks.at(i)[0] << endl;
  }

  string key = "4847464544434241";
  cout << "Key: " << key << endl;
  string input = "abcdefghijklmnopqrstuvwxyzabcdef";
  cout << "Input: " << input << endl;

  RC5 rc5 = RC5(key);
  string ciphertext = rc5.encrypt(input);
  cout << "Encryptions: " << endl;

  vector<word> ctWords = utility.hexToWords(utility.asciiToHex(ciphertext));
  vector<block> ctBlocks = utility.wordsToBlocks(ctWords);
  for (unsigned int i = 0; i < ctBlocks.size(); i++) {
    cout << "Block " << i << ": " << utility.binToHex(ctBlocks.at(i)[0].to_string()) << " ";
    cout << utility.binToHex(ctBlocks.at(i)[1].to_string()) << endl;
  }

  cout << endl << "Decryptions: " << endl;
  vector<word> ptWords = utility.hexToWords(utility.asciiToHex(ciphertext));
  vector<block> ptBlocks = utility.wordsToBlocks(ctWords);
  for (unsigned int i = 0; i < ptBlocks.size(); i++) {
    cout << "Block " << i << ": " << utility.binToHex(ptBlocks.at(i)[0].to_string()) << " ";
    cout << utility.binToHex(ptBlocks.at(i)[1].to_string()) << endl;
  }


  return 0;
}