#include <iostream>
#include <string>
#include <vector>
#include "RC5.h"
#include "BinaryUtility.h"

const int P = 0xb7e15163;
const int Q = 0x9e3779b9;

int main() {

  BinaryUtility utility = BinaryUtility();

  string testKey1 = "4847464544434241";
  //string testKey1 = "ab";

//  cout << "key input: " << testKey1 << endl;
//  vector<byte> keyBytes = utility.hexStringToBytes(testKey1);
//  cout << "key output: " << utility.bytesToHexString(keyBytes) << endl;
//
//
//  string testMessage = "abcdefghijklmnopqrstuvwxyzabcdef";
//
//  cout << "message as ascii: " << testMessage << endl;
//  vector<byte> messageBytes = utility.hexStringToBytes(utility.asciiToHex(testMessage));
//  cout << "message as hex: " << utility.bytesToHexString(messageBytes)<< endl;
//  vector<byte> messageBytesLittleEndian = utility.alternateEndianness(messageBytes);
//  cout << "message as hex little endian :" << utility.bytesToHexString(messageBytesLittleEndian) << std::endl;

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

  string byte = "df";
  //cout << utility.hexToBitset(byte, 2) << endl;


  return 0;
}