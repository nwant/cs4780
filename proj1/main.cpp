#include <stdio.h>
#include <time.h>

#define KEYSIZE 8	 /* size of key, in bytes */
typedef unsigned int WORD; /* Should be 32-bit = 4 bytes        */

typedef enum { ShiftLeft, ShiftRight } ShiftDir;


typedef enum { KeyWords = KEYSIZE / 4,
	       NumRounds = 12,  /* Number of cryptographic rounds  */
	       TableSize = 26   /* size of table = 2 * (NumRounds + 1) */
} bogus;


WORD Table[ TableSize ];
WORD L[KeyWords]; 



WORD ROT(const WORD x, const WORD y, const ShiftDir dir)
{

  const unsigned int ShiftAmt = (y & (unsigned int)0x1f);
  const unsigned int ShiftBack = 0x20 - ShiftAmt;
  unsigned int result;
  
  if (dir == ShiftLeft)
    result = (x << ShiftAmt) | (x >> ShiftBack);
  else
    result = (x >> ShiftAmt) | (x << ShiftBack);
  return result;
} /* ROT */



void SetKey( unsigned char KeyChar )
{
    static unsigned int KeyCntr;
    static unsigned int Shift;

    int ix = KeyCntr >> 2;

    /* this is simply a machine independent way of setting L[i] to 
       KeyChar[i], without being affect by "endianess". */
    L[ ix ] = (L[ ix ] & (~(0xff << Shift))) | (KeyChar << Shift);

    Shift = (Shift + 8) & 0x1f;
    KeyCntr = (KeyCntr + 1) & (KEYSIZE - 1);  /* This Depends on KEYSIZE being */
                                              /* a power of two.  The & will   */
                                              /* cause the KeyCntr to wrap     */
                                              /* and only have values in the   */
                                              /* range 0..KEYSIZE-1.           */
}  /* RC5_Crypto */




 /* 2 WORD: input plain text, output encrypted text    */
void encrypt(WORD *PlainText, WORD *CryptoText)
{ 

  WORD i, temp;
  WORD A;
  WORD B;

  A = PlainText[0] + Table[0];
  B = PlainText[1] + Table[1];

  for (i = 1; i <= NumRounds; i++) {
    //temp = i << 1;
    A = ROT(A^B, B, ShiftLeft) + Table[2*i];
    B = ROT(A^B, A, ShiftLeft) + Table[(2*i)+1];
  }
  CryptoText[0] = A; 
  CryptoText[1] = B;  
}  /* RC5_Cypto::encrypt */



/* 2 WORD input encrypted text, output plain text    */
void decrypt(WORD *CryptoText, WORD *PlainText) 
{ 
  WORD i, temp;
  WORD B; 
  WORD A;

  B = CryptoText[1]; 
  A = CryptoText[0];

  for (i=NumRounds; i > 0; i--) { 
    //temp = i << 1;
    B = ROT(B - Table[(2*i)+1],A, ShiftRight)^A;
    A = ROT(A - Table[2*i],  B, ShiftRight)^B;
  }
  PlainText[1] = B-Table[1]; 
  PlainText[0] = A-Table[0];  
} 	/*  decrypt */




void setup() /* secret input key K[0...KEYSIZE-1]   */
{ 
  /* magic constants (courtesty of RSA) */
  static const WORD ROM[ TableSize ] = { 0xb7e15163, 0x5618cb1c, 0xf45044d5,
                                         0x9287be8e, 0x30bf3847, 0xcef6b200,
                                         0x6d2e2bb9, 0x0b65a572, 0xa99d1f2b,
                                         0x47d498e4, 0xe60c129d, 0x84438c56,
                                         0x227b060f, 0xc0b27fc8, 0x5ee9f981,
                                         0xfd21733a, 0x9b58ecf3, 0x399066ac,
                                         0xd7c7e065, 0x75ff5a1e, 0x1436d3d7,
                                         0xb26e4d90, 0x50a5c749, 0xeedd4102,
                                         0x8d14babb, 0x2b4c3474};
  WORD i;
  WORD A;
  WORD B;
  WORD j;
  WORD k;
  
  /* Copy "ROM" into "RAM" */
  for (i=0; i < TableSize; i++) 
    Table[i] = ROM[i];

  /* 3*t > 3*KeyWords */

  A = 0;
  B = 0;
  i = 0;
  j = 0;

  for (k=0; k < 3*TableSize; k++) {
    Table[i] = ROT(Table[i]+(A+B),3, ShiftLeft);
    A = Table[i];
    L[j] = ROT(L[j]+(A+B),(A+B), ShiftLeft);  
    B = L[j]; 
    i= (i+1) & (TableSize-1);  /* using '&' for % only works for powers of 2  */
    j= (j+1) & (KeyWords-1);
  }
} 	/* setup */



/*
   Testbench for crytography algorithm
 */
int main()
{ 
  WORD i, j;
  WORD PlainText1[2], PlainText2[2];
  WORD CryptoText[2] = {0,0};
  time_t t0, t1;
  char *keystr = "HGFEDCBA";

  printf("Key: %x%x%x%x%x%x%x%x\n",
         keystr[0], keystr[1], keystr[2], keystr[3], keystr[4], keystr[5], keystr[6], keystr[7]);

  WORD Input1[8], Input2[2];
  WORD Encrypt1[8] = {0,0,0,0,0,0,0,0};

  printf("Input: abcdefghijklmnopqrstuvwxyzabcdef\n");

  Input1[0] = 0x64636261;
  Input1[1] = 0x68676665;
  Input1[2] = 0x6c6b6a69;
  Input1[3] = 0x706f6e6d;
  Input1[4] = 0x74737271;
  Input1[5] = 0x78777675;
  Input1[6] = 0x62617a79;
  Input1[7] = 0x66656463;

  if (sizeof(WORD)!=4) 
    printf("RC5 error: WORD has %d bytes.\n",sizeof(WORD));

  for (i = 1; i<8; i++)
    {
      PlainText1[0] = Input1[i-1];
      PlainText1[1] = Input1[i];
      for (j=0; j < KEYSIZE; j++)
         SetKey((unsigned char)keystr[j]);
      /* Setup, encrypt, and decrypt */
      setup();
      encrypt(PlainText1,CryptoText);
      decrypt(CryptoText,PlainText2);

      /* Print out results, checking for decryption failure */
      printf("\nBlock %i: plaintext %.8lX %.8lX  --->  ciphertext %.8lX %.8lX  \n",
             i, PlainText1[0], PlainText1[1], CryptoText[0], CryptoText[1]);
      if (PlainText1[0]!=PlainText2[0] || PlainText1[1]!=PlainText2[1])
        printf("Decryption Error!");
    }

  char *keystr2 = "!(b2$,c8";

  printf("\n\nKey: %x%x%x%x%x%x%x%x\n",
         keystr2[0], keystr2[1], keystr2[2], keystr2[3], keystr2[4], keystr2[5], keystr2[6], keystr2[7]);

  printf("Input: Encrypt");

  PlainText1[0] = 0x67ba7623;
  PlainText1[1] = 0xfcb076d6;

  for (j=0; j < KEYSIZE; j++)
    SetKey((unsigned char)keystr[j]);

  setup();
  encrypt(PlainText1,CryptoText);
  decrypt(CryptoText,PlainText2);

  /* Print out results, checking for decryption failure */
  printf("\nBlock 0: plaintext %.8lX %.8lX  --->  ciphertext %.8lX %.8lX  \n",
         PlainText1[0], PlainText1[1], CryptoText[0], CryptoText[1]);
  if (PlainText1[0]!=PlainText2[0] || PlainText1[1]!=PlainText2[1])
    printf("Decryption Error!");
}


 