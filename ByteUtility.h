#include <string>
#include <vector>
#ifndef PROJ1_RC5_BYTEUTILITY_H
#define PROJ1_RC5_BYTEUTILITY_H

typedef unsigned char byte;

class ByteUtility {
public:
  std::string asciiToHex(const std::string aStr);
  std::vector<byte> hexStringToBytes(const std::string hex);
  std::string bytesToHexString(const std::vector<byte> bytes);
  std::vector<byte> asLittleEndian(const std::vector<byte> bytes);
private:
};


#endif //PROJ1_RC5_BYTEUTILITY_H
