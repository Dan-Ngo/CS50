#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Input: Length of shower
// OUtput: Water bottle equivalent to water used

int main(void)
{
    // Set buffer size to 0 to fix printf/fgets problem
  setvbuf(stdout, 0, _IONBF, 0);
char minutesStr[4]; // This limits minutes to < 999
int minutes = 0;
int i = 0;
do {
    printf("minutes: ");

    do
    {
          //Get user input
        fgets(minutesStr, sizeof(minutesStr), stdin);
          //Inc i based on leading 0's
        for(i = 0; minutesStr[i] == '0'; ++i);
    }  //While all #'s scanned so far are 0's
    while(i == sizeof(minutesStr) -1);
      //If there is a valid input here
    if(i != 0 && !strchr(minutesStr, '\n')){
          //Reduce size of the input by i
        int len = sizeof(minutesStr) - i -1;
          //Moves deleted portion of minutesStr into current portion
        memmove(minutesStr, minutesStr + i, len);
          //Take overflow input out of the buffer and repeat
        fgets(minutesStr + len, sizeof(minutesStr) - len, stdin);
    }
    minutes = strtol (minutesStr, NULL, 10);
} while ( minutes < 1);

printf("bottles: %d\n", (minutes * 12));
  return 0;
}
