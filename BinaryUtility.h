#ifndef PROJ1_RC5_WORDUTILITY_H
#define PROJ1_RC5_WORDUTILITY_H
#include <string>
#include <vector>
#include <bitset>
using namespace std;

const int WORD_SIZE = 32;

typedef unsigned char byte;

class BinaryUtility {
public:
  bitset<WORD_SIZE> add(const bitset<WORD_SIZE> a, const bitset<WORD_SIZE> b, bool & overflow);
  bitset<WORD_SIZE> leftRotate(const bitset<WORD_SIZE> a, const int shift);
  string asciiToHex(const string aStr);
  vector<byte> hexStringToBytes(const string hexStr);
  string bytesToHexString(const vector<byte> bytes);
  vector<byte> alternateEndianness(const vector<byte> bytes);
  bitset<32> toWord(const byte);
  int toInt(const bitset<32> word);
};


#endif //PROJ1_RC5_WORDUTILITY_H
