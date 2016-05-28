#include <stdio.h>
#include <stdlib.h>
#define MAX 20
#define EMPTY 0
#define uint unsigned int

void init(uint board[][MAX], uint d);
void draw(uint board[][MAX], uint d);
void move(uint board[][MAX], uint *x, uint *y, uint d, uint nexttile);
int won(uint board[][MAX], uint d);

uint board[MAX][MAX];

int main(int argc, char *argv[])
{
  uint boardsize = strtol(argv[1], NULL, 10);
  uint blankx = boardsize - 1;
  uint blanky = boardsize - 1;

  setvbuf(stdout, 0, _IONBF, 0);
  if (argc != 2)
  {
    printf("Usage: ./test k\nWhere k is the size of the board\n");
    return 1;
  }
  if (boardsize < 2 || boardsize > 20)
  {
    printf("Size of board must be between 2 and 20\n");
    return 1;
  }
  init(board, boardsize);

  char input[100];
  uint nexttile;

  while (!won(board, boardsize))
  {
    draw(board, boardsize);
    printf("\n Number to move: ");
    fgets(input, sizeof(input), stdin);
    nexttile = strtol(input, NULL, 10);
    move(board, &blanky, &blankx, boardsize, nexttile);
  }
  draw(board, boardsize);
  printf("\n  You win!");
  return 0;
}

void init(uint board[][MAX], uint d)
{
  uint placeholder;
  uint count = d * d - 1;
  for (uint i = 0; i < d; i++)
    for (uint j = 0; j < d; j++)
    {
      board[i][j] = count;
      count--;
    }
  if (d % 2 == 0)
  {
    if (d == 2)
    {
      placeholder = board[0][0];
      board[0][0] = board[0][1];
      board[0][1] = placeholder;
    }
    else
    {
      placeholder = board[d-1][d-3];
      board[d-1][d-3] = board[d-1][d-2];
      board[d-1][d-2] = placeholder;
    }
  }
  return;
}

void draw(uint board[][MAX], uint d)
{
  for (uint i = 0; i < d; i++)
    for (uint j = 0; j < d; j++)
    {
      if (j == 0)
        printf("\n");
      if (board[i][j] == EMPTY)
        printf("   -");
      else
        printf("%4d", board[i][j]);
    }
  printf("\n");
  return;
}

void move(uint board[][MAX], uint *y, uint *x, uint d, uint nexttile)
{
  uint found = 0;
  if (y > 0)
  {
    if (board[*y-1][*x] == nexttile)
    {
      board[*y][*x] = nexttile;
      board[*y-1][*x] = EMPTY;
      --*y;
      found = 1;
    }
  }

  if (*y < d - 1 && found == 0)
  {
    if (board[*y+1][*x] == nexttile)
    {
      board[*y][*x] = nexttile;
      board[*y+1][*x] = EMPTY;
      ++*y;
      found = 1;
    }
  }

  if (*x > 0 && found == 0)
  {
    if (board[*y][*x-1] == nexttile)
    {
      board[*y][*x] = nexttile;
      board[*y][*x-1] = EMPTY;
      --*x;
      found = 1;
    }
  }

  if (*x < d - 1 && found == 0)
  {
    if (board[*y][*x+1] == nexttile)
    {
      board[*y][*x] = nexttile;
      board[*y][*x+1] = EMPTY;
      ++*x;
      found = 1;
    }
  }

  if (found == 0)
    printf("invalid option.  try again\n");
  return;
}

int won(uint board[][MAX], uint d)
{
  uint count = 0;
  for (uint i = 0; i < d; i++)
    for (uint j = 0; j < d; j++)
    {
      count++;
      if (j == (d-1) && i == (d-1))
        return 1;
      if (board[i][j] != count)
        return 0;
    }
  return 1;
}
