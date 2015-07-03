#include <iostream>
#include <string>
#include <vector>
#include "RC5.h"
#include "ByteUtility.h"

const int P = 0xb7e15163;
const int Q = 0x9e3779b9;

int main() {

  ByteUtility utility = ByteUtility();

  std::string testKey1 = "4847464544434241";

  std::cout << "key input: " << testKey1 << std::endl;
  std::vector<byte> keyBytes = utility.hexStringToBytes(testKey1);
  std::cout << "key output: " << utility.bytesToHexString(keyBytes) << std::endl;


  std::string testMessage = "abcdefghijklmnopqrstuvwxyzabcdef";

  std::cout << "message as ascii: " << testMessage << std::endl;
  std::vector<byte> messageBytes = utility.hexStringToBytes(utility.asciiToHex(testMessage));
  std::cout << "message as hex: " << utility.bytesToHexString(messageBytes)<< std::endl;
  std::vector<byte> messageBytesLittleEndian = utility.alternateEndianness(messageBytes);
  std::cout << "message as hex little endian :" << utility.bytesToHexString(messageBytesLittleEndian) << std::endl;

  return 0;
}