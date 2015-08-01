/* Nathaniel Want
 * CS4780 Project 2 */
#include <stdlib.h>
#include <iostream>
#include <vector>
using namespace std;

typedef uint64_t dword;

/* modExp
 * --------
 * let b = base, e = exponent, p = prime and k = the modular exponentiation
 * compute b^e (mod p) using modular exponentiation technique.
 */
dword modExp(dword b, dword e, dword p) {
  dword k = 1;

  while (e > 0) {
    if ( (e & 1) > 0) {
      k = (k * b) % p;
    }
    e >>= 1;
    b = (b * b) % p;
  }
  return k;
}

int main(int argc, char* argv[]) {
  dword pvtExp;
  vector<dword> input;

  // check to make sure private exponent is provided
  if (argc == 1) {
    cout << "You must provide a private exponent";
    return 1;
  } else if (argc > 2) {
    cout << "dh only takes one argument for the private exponent";
    return 1;
  }

  // get the private exponent
  pvtExp = static_cast<uint64_t>(atoi(argv[1]));

  // read in the prime, generator, and the generated partial secret from std input
  dword buffer;
  while(cin >> buffer) {
    input.push_back(buffer);
  }
  dword prime = input.at(0);
  dword generator = input.at(1);
  dword partialSecret = input.at(2);

  // new partial secret = (generator)^(private exponent) mod prime
  dword newPartialSecret = modExp(generator, pvtExp, prime);

  // shared secret = (partialSecret)^(private exponent) mod prime
  dword sharedSecret = modExp(partialSecret, pvtExp, prime);


  // output the generated shared secret to std error
  cerr << sharedSecret << endl;

  // output the prime, generator, and the generated partial secret to std output
  cout << prime << endl;
  cout << generator << endl;
  cout << newPartialSecret << endl;

  return 0;
}
