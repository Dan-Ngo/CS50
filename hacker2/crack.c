#define _XOPEN_SOURCE 700
#define uint unsigned int
#define KEYSIZE 13
#define PASSWORDSIZE 8
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "crypt3.h"

static const char validchar[] =
"0123456789/."
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz";
static const int validcharsize = sizeof(validchar) - 1;

void permutations();
char *decrypt();

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

  //DEBUGGING INFO
  // printf("what is here: %c and %c and %c\n", testpassword[PASSWORDSIZE - 1],
  //         testpassword[PASSWORDSIZE], testpassword[PASSWORDSIZE + 1]);
  // printf("contents of key: %s\n", key);
  // printf("size of testpassword: %d\n", sizeof(testkey));
  // printf("contents of testpassword[]: %s\n", testpassword);
  // printf("size of argv[1]: %d\nsize of testpassword[]: %d\n",
  //       strlen(argv[1]), sizeof(testkey)/sizeof(testkey[0]));

  permutations(testkeyptr, key, testpassword, salt);
  //printf("contents of key[]: %s\n", key);
  printf("contents of testpassword[]: %s\n", testpassword);
  //printf("crypted testpassword: %s\n", crypt(testpassword, salt));
  printf("crypted input: %s\n", crypt(key, salt));
  // printf("contents of testpassword[]: %s", testpassword);
  // decrypt(bit, testpasswordptr, testpassword, key, salt);

  // printf("Decrypt Found: %s\n", check);
  return 0;
}

void permutations(char *testkeyptr, char *key, char testpassword[], char salt[])
{
  uint i = 0;
  //Find what salt is from the key
  testpassword[0] = salt[0];
  testpassword[1] = salt[1];
  // testpassword[2] = 'R';
  // testpassword[3] = 'V';
  // testpassword[4] = 'A';
  // testpassword[5] = 'R';
  // testpassword[6] = salt[1];

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
      //printf("testpassword crypt: %s\n", crypt(testpassword, salt));
      //printf("key crypt: %s\n", crypt(key, salt));
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
            //printf("testpassword crypt: %s\n", crypt(testpassword, salt));
            //printf("key crypt: %s\n", crypt(key, salt));
            return;
          }
          j = 2;
        }
      }
      if (!strcmp(crypt(testpassword, salt), key))
      {
        //printf("testpassword crypt: %s\n", crypt(testpassword, salt));
        //printf("key crypt: %s\n", crypt(key, salt));
        return;
      }
      printf("%s\n", testpassword);
      *ptrarr[i] = *validcharptr[i];
    }
  }
  return;
}
