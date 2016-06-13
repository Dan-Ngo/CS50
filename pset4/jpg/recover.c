/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp.h"

#define BUFSIZE 512

int main(int argc, char* argv[])
{
    FILE* file = fopen("card.raw", "r");
    if (file == NULL)
    {
        printf("file couldn't be opened");
        return 1;
    }
    int stop = 0, count = 0;
    char title[8];
    BYTE buffer[BUFSIZE];
    BYTE signature[4] = {0xFF, 0xD8, 0xFF, 0xE0};
    BYTE signature2[4] = {0xFF, 0xD8, 0xFF, 0xE0};
    FILE *img = NULL;
    while (fread(buffer, BUFSIZE, 1, file) == 1)
    {
        if (memcmp(signature, buffer, 3) == 0
        ||  memcmp(signature2, buffer, 3) == 0)
        {
            if (count > 0)
                fclose(img);
            sprintf(title, "%03d.jpg", count++);
            img = fopen(title, "a");
            fwrite(buffer, BUFSIZE, 1, img);
        }
        else if (count > 0)
        {
            fwrite(buffer, BUFSIZE, 1, img);
        }
    }
    fclose(img);
    fclose(file);
    return 0;
}
