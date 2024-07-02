#include <stdio.h>
#include "logfind.h"
#include <ctype.h>
#include <string.h>
#include "dirent.h"
#include <stdlib.h>
#include "dbg.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdbool.h>
#include "logfind.h"

void findFrom(char * fileName, char * target, FILE * fp) {
    if ((fp = fopen(fileName, "r")) == NULL) {
        printf("logfind: cannot open %s\n", fileName);
        return;
    }

    char buffer[MAX_DATA];
    while (fgets(buffer, MAX_DATA - 1, fp) != NULL) {
        if (strcasestr(buffer, target) != NULL) {
            printf("Found the file: <%s> containing the pattern.", fileName);
            return;
        }
    }
    printf("Pattern not found in this file: <%s>", fileName);
}


void dirwalk(char *dir, void (*fcn)(char *)) 
{
    char name[MAX_PATH];
    struct dirent *dp;
    DIR *dfd;

    if ((dfd == opendir(dir)) == NULL) {
        fprintf(stderr, "dirwalk: cannot open %s\n", dir);
        return;
    }
    while ((dp = readdir(dfd)) != NULL) {
        if(strcmp (dp->d_name, ".") == 0 || strcmp(dp->d_name, "..")) {
            continue;
        }
        // skip if the directory is . or ..
        if (strlen(dir) + strlen(dp->d_name) + 2 > sizeof(name)) {
            fprintf(stderr, "dirwalk: name %s %s too long\n", dir, dp->d_name);
        }
        else {
            sprintf(name, "%s/%s", dir, dp->d_name);
            (*fcn)(name);
        }
    }
    closedir(dfd);
}
