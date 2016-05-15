#include <stdio.h>
#include <assert.h>

// Input: Lowerbound and upperbound
// Outputs: F to C table with given bounds

int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    printf("Usage: ./test n m\n");
    printf("Where n is lower bound, and m is upper bound");
    return(1);
  }
  assert (argc == 3);
  float a, b, c;
  sscanf(argv[1], "%f", &a);
  sscanf(argv[2], "%f", &c);
  b = a - 1;

  while (a <= c)
  {
    if ((a > 98.6) && (b < 98.6))
    {
      printf("%6.2f degrees F = %6.2f degrees C\n",
        98.6, (98.6 - 32.0) * 5.0 / 9.0);
    }
      printf("%6.2f degrees F = %6.2f degrees C\n",
        a, (a - 32.0) * 5.0 / 9.0);
      b = a;
      a = a + 10;
  }
  return 0;
}
