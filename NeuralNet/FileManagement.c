#include <stdio.h>
#include <stdlib.h>

#include "FileManagement.h"

int countLines(FILE *file) 
{
    int count = 0;
    int ch;
    while ((ch = fgetc(file)) != EOF)
    {
        if (ch == '\n')
        {
            count++;
        }
    }

    fseek(file, 0, SEEK_SET);
    return count;
}

void parseFile(FILE *file, double *trainxs, double *trainys, int dataLength) 
{
    for (int i=0; i<dataLength; ++i) 
    {
        fscanf(file, "%lf %lf", trainxs+i, trainys+i);
    }
}