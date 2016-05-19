#define _XOPEN_SOURCE 700
#define uint unsigned int
#define KEYSIZE 13
#define PASSWORDSIZE 8
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include "crypt3.h"

/* To test this, comment out permutations in main and
   input a valid 8 character or less string
   (you'll be waiting a long time for > 6)
   and run program with that.

   Take the ciphered output, uncomment out permutations
   and run the program using the given ciphered text and
   the program will eventually find your original string.
*/

static const char validchar[] =
"0123456789/."
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz";
static const int validcharsize = sizeof(validchar) - 1;

void permutations(char *testkeyptr, char *key,
                  char testpassword[], char salt[]);

int main(int argc, char *argv[])
{
  if (argc == 1)
  {
    printf("Usage: ./file_name n\n");
    printf("Where n is the password to decrypt");
    return 1;
  }

  //Encrypted password and salt
  char *key = (char *)malloc(sizeof(argv[1])/sizeof(*argv[1]));
  strcpy(key, argv[1]);
  char salt[2];
  salt[0] = *key;
  salt[1] = *(key + 1);

  char testpassword[PASSWORDSIZE + 1];
  for (uint i = 0; i < PASSWORDSIZE; i++)
    testpassword[i] = '\0';
  char *testkeyptr = testpassword;
    *(testkeyptr + PASSWORDSIZE) = '\0';

  permutations(testkeyptr, key, testpassword, salt);
  printf("contents of testpassword[]: %s\n", testpassword);
  printf("crypt of given input: %s\n", crypt(key, salt));
  return 0;
}

void permutations(char *testkeyptr, char *key, char testpassword[], char salt[])
{
  uint i = 0;
  //Find what salt is from the key
  //Other entries are for "guessed characters"
  testpassword[0] = salt[0];
  testpassword[1] = salt[1];
  // testpassword[2] = 'R';
  // testpassword[3] = 'V';
  // testpassword[4] = 'A';
  // testpassword[5] = 'R';
  // testpassword[6] = 'D';

  const char *validcharptr[PASSWORDSIZE];
  char *ptrarr[PASSWORDSIZE];
  for ( i; i < PASSWORDSIZE; i++)
  {
    ptrarr[i] = testpassword + i;
    validcharptr[i] = validchar;
  }

  uint j = 2;
  uint k = validcharsize << 18;
  for (uint count = 0; count < k; count++)
  {
    if (!strcmp(crypt(testpassword, salt), key))
    {
      return;
    }
    printf("%s\n", testpassword);
    i = 2;
    for (validcharptr[i] = validchar; *validcharptr[i]; validcharptr[i]++)
    {
      while (*ptrarr[j] == 'z')
      {
        validcharptr[j] = validchar;
        *ptrarr[j] = *validcharptr[j];
        j++;
        if (*ptrarr[j] == 'z')
        {
          continue;
        }
        else
        {
          *(ptrarr[j]) = *++validcharptr[j];
          if (!strcmp(crypt(testpassword, salt), key))
          {
            return;
          }
          j = 2;
        }
      }
      if (!strcmp(crypt(testpassword, salt), key))
      {
        return;
      }
      printf("%s\n", testpassword);
      *ptrarr[i] = *validcharptr[i];
    }
  }
  return;
}
