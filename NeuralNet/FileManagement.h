#ifndef FILEMANAGEMENT_H
#define FILEMANAGEMENT_H

int countLines(FILE *file);
void parseFile(FILE *file, double *trainxs, double *trainys, int dataLength);

#endif
