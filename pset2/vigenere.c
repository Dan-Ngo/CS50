#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define uint unsigned int

int main(int argc, char *argv[])
{
  setvbuf(stdout, 0, _IONBF, 0);
  if (argc != 2)
  {
    printf("Usages: ./test k\nWhere k is the string key");
    return 1;
  }
  char input[100];
  char key[100];
  uint i = 0;
  uint spaces = 0;
  int keyvalue;
  while ( *(argv[1] + i - 1) != '\0' )
  {
    key[i++] = *(argv[1] + i);
  }
  printf("Give text to cipher: \n");
  fgets(input, sizeof(input), stdin);
  for (i = 0; input[i] != '\n'; i++)
  {
    keyvalue = key[(i - spaces)% strlen(key)] - 'a';
    printf("Keyvalue: %d\n", keyvalue);
    if (input[i] >= 'a' && input[i] <= 'z')
    {
      if (input[i] + keyvalue > 'z')
      {
        input[i] = 'a' - 1 + (input[i] + keyvalue - 'z');
      }
      else
      {
        input[i] += keyvalue;
      }
    }
    else if (input[i] >= 'A' && input[i] <= 'Z')
    {
      if (input[i] + keyvalue > 'Z')
      {
        input[i] = 'A' - 1 + (input[i] + keyvalue - 'Z');
      }
      else
      {
        input[i] += keyvalue;
      }
    }
    else
    {
      spaces++;
    }
  }
  printf("%s\n", input);
  return 0;
}
