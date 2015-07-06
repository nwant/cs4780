#include <sstream>
#include <algorithm>
#include <iomanip>
#include "BinaryUtility.h"

word BinaryUtility::add(const word a, const word b, bool &overflow) {
  word sum;
  overflow = false;

  bitset<1> carry(0);
  for (int i = 0; i < WORD_SIZE; i++) {
    sum[i] = (a[i] ^ b[i]) ^ carry[0];
    carry[0] = ((a[i] & b[i]) | (a[i] & carry[0])) | (b[i] & carry[0]);
  }

  return sum;
}

word BinaryUtility::leftRotate(const word a, const unsigned long shift) {
  bitset<WORD_SIZE> ret(a.to_string());
  bitset<WORD_SIZE> toRotate;

  unsigned long modShift = shift % WORD_SIZE;

  for (int i = 0; i < modShift; i++) {
    unsigned long pos = a.size() - 1 - i;
    unsigned long newPos = (pos + modShift) % a.size();
    toRotate.set(newPos, a.test(pos));
  }
  ret = ret << modShift;
  return ret | toRotate;
}

string BinaryUtility::asciiToHex(const string aStr) {
  stringstream ss;

  for (unsigned int i = 0; i < aStr.length(); i++) {
    ss << hex << (int)aStr.at(i);
  }

  return ss.str();
}

string BinaryUtility::hexToBin(const string hexStr) {
  string ret = "";

  for (int i = 0; i < hexStr.length(); i++) {
    switch(hexStr[i]) {
      case '1': ret.append("0001"); break;
      case '2': ret.append("0010"); break;
      case '3': ret.append("0011"); break;
      case '4': ret.append("0100"); break;
      case '5': ret.append("0101"); break;
      case '6': ret.append("0110"); break;
      case '7': ret.append("0111"); break;
      case '8': ret.append("1000"); break;
      case '9': ret.append("1001"); break;
      case 'A':
      case 'a': ret.append("1010"); break;
      case 'B':
      case 'b': ret.append("1011"); break;
      case 'C':
      case 'c': ret.append("1100"); break;
      case 'D':
      case 'd': ret.append("1101"); break;
      case 'E':
      case 'e': ret.append("1110"); break;
      case 'F':
      case 'f': ret.append("1111"); break;
      default: ret.append("0000"); break;
    }
  }
  return ret;
}

string BinaryUtility::binToHex(const string binStr) {
  int base10 = 0;
  for (int i; i < binStr.length(); i++) {
    base10 *= 2;
    base10 += binStr[i] == '1' ? 1 : 0;
  }

  stringstream ss;
  ss <<  hex << setw(8) << setfill('0') << base10;

  return ss.str();
}

vector<byte> BinaryUtility::hexToBytes(const string hexStr) {
  vector<byte> ret;
  bool padLastHex = (hexStr.length() % 2) != 0;
  unsigned int lastHexPos = hexStr.length() - 1;
  int offset = hexStr.length() - 1;
  while (offset >= 0) {
  //for (unsigned int i = 0; i < hexStr.length(); i++) {
    string b = hexToBin(hexStr.substr(offset, 1));
    offset--;
    if (offset == lastHexPos && padLastHex) {
      b = "0000" + b;
    } else {
      b = hexToBin(hexStr.substr(offset, 1)) + b;
    }
    offset--;
    ret.push_back(byte(b));
  }
  return ret;
}


vector<word> BinaryUtility::hexToWords(const string hexStr) {
  vector<word> ret;
  unsigned int offset = 0;
  while (offset < hexStr.length()) {
    string w = "";
    for (int i = 0; i < 8; i++) {
      if(offset >= hexStr.length()) {
        w = "0000" + w;
      } else {
        w = hexToBin(hexStr.substr(hexStr.length() - offset - 1, 1)) + w;
      }
      offset++;
    }
    ret.push_back(word(w));
  }
  return ret;
}

vector<block> BinaryUtility::wordsToBlocks(const vector<word> words) {
  vector<block> ret;
  block blk;
  for(unsigned int i = 0; i < words.size(); i++) {
    blk.clear();
    blk.push_back(words.at(i));
    i++;
    if(i < words.size()) {
      blk.push_back(words.at(i));
    } else {
      blk.push_back(word(0x0000));
    }
    ret.push_back(blk);
  }
  return ret;
}

string BinaryUtility::alternateEndianness(const string hexStr) {
  string ret;
  stringstream ss;
  unsigned int offset = 0;
  while (offset < hexStr.length()) {
    ss.clear();
    string byte = hexStr.substr(offset, 2);
    ret = byte + ret;
    offset += 2;
  }
  return ret;
}

bitvector BinaryUtility::hexToBitVector(const string hexStr, int vectorSize) {
  string bin = hexToBin(hexStr);
  bitvector ret;
  for (unsigned int i = 0; i < vectorSize; i++) {
    if (i >= bin.length()) {
      ret.push_back(false);
    } else {
      bool bit = bin.at(i) == '1';
      ret.push_back(bit);
    }
  }
  return ret;
}

string BinaryUtility::bitVectorToBin(bitvector vector) {
  string bin = "";
  for (unsigned int i = 0; i < vector.size(); i++) {
    if (vector.at(i)) {
      bin.append("1");
    } else {
      bin.append("0");
    }
  }
  return bin;
}

unsigned long BinaryUtility::toULong(const word w) {
  return w.to_ulong();
}

word BinaryUtility::clone(const word w) {
  return word(w.to_string());
}