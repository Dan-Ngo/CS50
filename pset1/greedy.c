#include <stdio.h>
#include <cs50.h>

#define QUARTER 25
#define DIME 10
#define NICKLE 5
#define PENNY 1
#define BUFSIZE 3
int main(void)
{
  char string[6];
  int count = 0;
  float input = -1;
  setvbuf(stdout, 0, _IONBF, 0);
  do
  {
    printf("How much change is owed?\n");
    fgets(string, 6, stdin);
    printf("string: %s\n", string);
    input = strtof(string, NULL);
  }
  while (input < 0 || input > 10);
  
  int cents = input * 100;
  
  printf("input: %G\n", input);
  
  for (cents; cents >= QUARTER; cents -= QUARTER)
    count++;
  for (cents; cents >= DIME; cents -= DIME)
    count++;
  for (cents; cents >= NICKLE; cents -= NICKLE)
    count++;
  for (cents; cents >= .005; cents-= PENNY)
  {
    count++;
  }
  printf("count: %d\n", count);
  return 0;
}
