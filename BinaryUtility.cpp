#include <sstream>
#include <algorithm>
#include "BinaryUtility.h"

bitset<WORD_SIZE> BinaryUtility::add(const bitset<WORD_SIZE> a, const bitset<WORD_SIZE> b, bool &overflow) {
  bitset<WORD_SIZE> sum;
  overflow = false;

  bitset<1> carry(0);
  for (int i = 0; i < WORD_SIZE; i++) {
    sum[i] = (a[i] ^ b[i]) ^ carry[0];
    carry[0] = ((a[i] & b[i]) | (a[i] & carry[0])) | (b[i] & carry[0]);
  }

  overflow = carry[0];
  return sum;
}

bitset<WORD_SIZE> BinaryUtility::leftRotate(const bitset<WORD_SIZE> a, const int shift) {
  bitset<WORD_SIZE> ret(a.to_string());
  bitset<WORD_SIZE> toRotate;

  for (int i = 0; i < shift; i++) {
    int pos = a.size() - 1 - i;
    int newPos = (pos + shift) % a.size();
    toRotate.set(newPos, a.test(pos));
  }
  ret = ret << shift;
  return ret | toRotate;
}

string BinaryUtility::asciiToHex(const string aStr) {
  stringstream ss;

  for (int i = 0; i < aStr.length(); i++) {
    ss << hex << (int)aStr.at(i);
  }

  return ss.str();
}

vector<byte> BinaryUtility::hexStringToBytes(const string hexStr) {
  vector<byte> ret;
  stringstream ss;
  unsigned int buffer;
  int offset = 0;
  while (offset < hexStr.length()) {
    ss.clear();
    ss << hexStr.substr(offset, 2);
    ss >> hex >> buffer;
    ret.push_back(static_cast<byte>(buffer));
    offset += 2;
  }
  return ret;
}

string BinaryUtility::bytesToHexString(const vector<byte> bytes) {
  stringstream ss;
  ss << hex;
  for (int i = 0; i < bytes.size(); i++) {
    ss << (int)bytes[i];
  }
  return ss.str();
}

vector<byte> BinaryUtility::alternateEndianness(const vector<byte> bytes) {
  vector<byte> ret(bytes);
  reverse(ret.begin(), ret.end());
  return ret;
}

bitset<32> BinaryUtility::toWord(const byte byte) {
  return bitset<32>(byte);
}

int BinaryUtility::toInt(const bitset<32> word) {
  return static_cast<int>(word.to_ulong());
}