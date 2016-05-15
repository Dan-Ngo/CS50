#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Input: Credit Card Number
// Output: If valid >> its corresponding company
// Output: Else "INVALID"

int main(void)
{
  setvbuf(stdout, 0, _IONBF, 0);
  printf("Enter credit card number: ");
  int cardNum, i;
  int eodsum = 0;
  int aod = 0;
  char cardStr[40];

  fgets(cardStr, sizeof(cardStr), stdin);
  for ( i = 1; cardStr[i] != 0 && cardStr[i] != 10; i += 2 )
  {
    switch ( cardStr[i] - '0' )
    {
      case 5:
        eodsum += 1;
        break;
      case 6:
        eodsum += 3;
        break;
      case 7:
        eodsum += 5;
        break;
      case 8:
        eodsum += 7;
        break;
      case 9:
        eodsum += 9;
        break;
      default:
        eodsum += ( cardStr[i] - '0' ) * 2;
        break;
    }
    aod += cardStr[i-1] - '0';
  }
  if ( cardStr[i-1] - '0' >= 0 )
    aod += cardStr[i-1] - '0';
  else
    i--;
  printf("aod: %d ", aod);
  printf("eod: %d ", eodsum);
  int finalsum = aod + eodsum;
  printf("i: %d\n", i);

  bool valid = false;
  if ( finalsum % 10 == 0 )
    switch ( i )
    {
      case 13:
        if ( cardStr[0] - '0' == 4 )
        {
          printf("VISA\n");
          valid = true;
        }
        break;
      case 15:
        if ( cardStr[0] - '0' == 3 &&
              cardStr[1] - '0' == 4 || cardStr[1] - '0' == 7 )
        {
          printf("AMEX\n");
          valid = true;
        }
        break;
      case 16:
        if ( cardStr[0] - '0' == 5 &&
              cardStr[1] - '0' < 6 && cardStr[1] - '0' > 0)
        {
          printf("MASTERCARD\n");
          valid = true;
        }
        break;
      default:
        break;
    }
    if ( valid == false )
      printf("INVALID\n");

  //cardNum = strtol(cardString, NULL, 10);

  return 0;
}
