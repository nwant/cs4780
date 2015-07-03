#include <math.h>
#include "RC5.h"


RC5::RC5(const int wordSizeInBytes, const char key [], const int keyLengthInBytes) {
  // configure
  this->configure(wordSizeInBytes, keyLengthInBytes);

  // copy the key to send to sub array generation function
  char keyCopy [keyLengthInBytes];
  for (int i=0; i<keyLengthInBytes; i++) {
    keyCopy[i] = key[i];
  }

  //generate substitution array
  this->generateSubArray(this->_config, keyCopy);
}

void RC5::configure(int wordSizeInBits, int keyLengthInBytes) {
  int r = this->_config.rounds = 12;

  int w = this->_config.wordSizeInBits = wordSizeInBits;
  int u = this->_config.wordSizeInBytes = w / 8;
  int b = this->_config.keySizeInBytes = keyLengthInBytes;

  int t = this->_config.sizeOfSubArray = (2 * r) + 2;
}

void RC5::generateSubArray(rc5config configuration, const char key []) {
  int c = (int)ceil(_config.keySizeInBytes / configuration.wordSizeInBytes);
  int u = this->_config.wordSizeInBytes;
  int w = this->_config.wordSizeInBits;
  char L[c];

  char P [u];
  char Q [u];

  if(w == 32){

  }


}