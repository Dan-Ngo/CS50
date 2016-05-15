#include <stdio.h>
#define NAME_MAX_SIZE 40
#define toUpper -32
#define initialsNum 2

int initial( char string[], int *i );
void nextString( char string[], int *i );

int main( void )
{
  setvbuf(stdout, 0, _IONBF, 0);
  printf("Enter your name: ");

  int fname = 0, lname = 0, i = 0;
    //Pointer to count to pass to function
  int *count = &i;
  char name[NAME_MAX_SIZE];
  fgets(name, sizeof(name), stdin);

  fname = initial( name, count );
  nextString( name, count );
  lname = initial( name, count );

  printf("%c%c\n", fname, lname);
  return 0;
}

int initial( char string[], int *i )
{
  for ( *i; *i < NAME_MAX_SIZE; (*i)++)
  {
    if ( string[*i] >= 'A' && string[*i] <= 'Z' )
      return string[*i];
    if ( string[*i] >= 'a' && string[*i] <= 'z' )
      return string[*i] + toUpper;
  }
}

void nextString( char string[], int *i )
{
  while ( string[*i] != ' ' )
  {
    (*i)++;
  }
  return;
}
