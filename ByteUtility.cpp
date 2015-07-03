#include <cstring>
#include <sstream>
#include <iostream>
#include "ByteUtility.h"


std::string ByteUtility::asciiToHex(const std::string aStr) {
  std::stringstream ss;

  for (int i = 0; i < aStr.length(); i++) {
    ss << std::hex << (int)aStr.at(i);
  }

  return ss.str();
}


std::vector<byte> ByteUtility::hexStringToBytes(const std::string hex) {
  std::vector<byte> ret;
  std::stringstream ss;
  unsigned int buffer;
  int offset = 0;
  while (offset < hex.length()) {
    ss.clear();
    ss << hex.substr(offset, 2);
    ss >> std::hex >> buffer;
    ret.push_back(static_cast<byte>(buffer));
    offset += 2;
  }

  return ret;
}

std::string ByteUtility::bytesToHexString(const std::vector<byte> bytes) {
  std::stringstream ss;
  ss << std::hex;
  for (int i = 0; i < bytes.size(); i++) {
   ss << (int)bytes[i];
  }

  return ss.str();
}