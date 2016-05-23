#include <stdio.h>
#include <stdlib.h>
#define uint unsigned int

int main(int argc, char *argv[])
{
  setvbuf(stdout, 0, _IONBF, 0);
  if (argc != 2)
  {
    printf("Usages: ./test k\nWhere k is the int key");
    return 1;
  }
  int key = atoi(argv[1]);
  char input[100];
  printf("Give text to cipher: \n");
  fgets(input, sizeof(input), stdin);
  for (uint i = 0; input[i] != '\n'; i++)
  {
    if (input[i] >= 'a' && input[i] <= 'z')
    {
      if (input[i] + key > 'z')
      {
        input[i] = 'a' - 1 + (input[i] + key - 'z');
      }
      else
      {
        input[i] += key;
      }
    }
    if (input[i] >= 'A' && input[i] <= 'Z')
    {
      if (input[i] + key > 'Z')
      {
        input[i] = 'A' - 1 + (input[i] + key - 'Z');
      }
      else
      {
        input[i] += key;
      }
    }
  }
  printf("%s\n", input);
  return 0;
}
