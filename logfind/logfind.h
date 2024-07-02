#ifndef _logfind_h
#define _logfind_h

#include <stdio.h>

extern int MAX_DATA;
extern int MAX_PATH;

void findFrom(char * fileName, char * target, FILE *fp);

void dirwalk(char *, void (*fcn)(char *));

#endif
