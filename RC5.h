#ifndef PROJ1_RC5_RC5_H
#define PROJ1_RC5_RC5_H

struct rc5config {
  int wordSizeInBits; // w
  int wordSizeInBytes;// u
  int rounds;         // r
  int keySizeInBytes; // b
  int sizeOfSubArray; // t
};

class RC5 {
public:
  RC5(const int wordSizeInBits, const char key [], const int keyLengthInBytes);
  char * encrypt(const char block);
private:
  rc5config _config;
  char _S [];
  void configure(int wordSizeInBits, int keyLengthInBytes);
  void generateSubArray(const rc5config configuration, const char key []);
};


#endif //PROJ1_RC5_RC5_H
