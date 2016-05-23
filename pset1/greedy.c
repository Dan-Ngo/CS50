#include <stdio.h>

int main(void)
{
  float input;
  setvbuf(stdout, 0, _IONBF, 0);
  do
  {
    printf("How much change is owed?\n");

  }
  while (input < 0 || input > 10);

  printf("input: %f\n", input);
  return 0;
}
