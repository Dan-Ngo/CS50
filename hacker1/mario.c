#include <stdio.h>

// Input: Height of Mario Tower
// Output: Mario tower of #'s

int main(void)
{
  setvbuf(stdout, 0, _IONBF, 0);

  char strHeight[3];
  int height, i, j;
  printf("Height: ");
  fgets(strHeight, sizeof(strHeight), stdin);
  height = strtol(strHeight, NULL, 10);

  if ( height > 23 || height < 1)
    printf("Invalid Input");
  else
    for ( i = 1; i <= height; i++ )
    {
      for ( j = height - i; j > 0; j-- )
        printf(" ");
      for ( j; j < i; j++ )
        printf("#");
      printf("  ");
      for ( j; j > 0; j-- )
        printf("#");
      for ( j; j < height; j++ )
        printf(" ");
      printf("\n");
    }


  return 0;
}
