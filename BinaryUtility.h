#ifndef RC5_WORDUTILITY_H
#define RC5_WORDUTILITY_H

#include <string>
#include <vector>
#include <bitset>
using namespace std;

const unsigned int BYTE_SIZE = 8;
const unsigned int WORD_SIZE = BYTE_SIZE * 4;
const unsigned int BLOCK_SIZE = WORD_SIZE * 2;

//typedef unsigned char byte;
typedef bool bit;
typedef vector<bit> bitvector;
typedef bitset<BYTE_SIZE> byte;
typedef bitset<WORD_SIZE> word;
typedef bitset<BLOCK_SIZE> block;

class BinaryUtility {
public:
  word add(const word a, const word b, bool & overflow);
  word leftRotate(const word a, const int shift);
  string asciiToHex(const string aStr);
  string hexToBin(const string hexStr);
  string binToHex(const string binStr);
  string alternateEndianness(const string hexStr);
  bitvector hexToBitVector(const string hexStr, int vectorSize);
  string bitVectorToBin(bitvector vector);
  unsigned int toInt(const word word);
};


#endif //RC5_WORDUTILITY_H
