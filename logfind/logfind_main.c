#include <stdio.h>
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

#define MAX_DATA 100
#define MAX_PATH 1024

char ** strparse (char input[]);
void findFrom(char * fileName, char * target, FILE * fp);
void dirwalk(char *, void (*fcn)(char *));

int main(int argc, char *argv[])
{
    // read the input string
    // and store the words in an array targets[]
    char *targets[argc - 1];
    int i = 1;
    if (argc <= 1) {
        printf("There's no word received, please specify what you need.");
        return 1;
    } else {
        while (i < argc) {
            targets[i-1] = argv[i];
            i++;
        }
    }

    i = 0;
    int targetsSize = sizeof(targets) / sizeof (char *);
    while (i < targetsSize) {
        printf("%s\n", targets[i]);
        i++;
    }

    // find the target words among system logs (path: ~/var/log)
    /*
     * 1) [x] read files and get lines of string 
     * 
     * future updates: 
     * 1) [] walk through the directory's files (as found in K&R)
     * 2) [?] parse the text string by spaces
     */
    FILE * fp = NULL;
    char * fileName = "README.md";
    char * line = NULL;

    findFrom(fileName, targets[0], fp);
    // TODO: apply the findFrom function above to ~/var/log directory

    return 0;
    // above is just for test
        while (--argc > 0) {
            if ((fp = fopen(*++argv, "r")) == NULL) {
                printf("logfind: cannot open %s\n", *argv);
                return 1;
            } else {
                //...
                fclose(fp);
            }
        }
        return 0;
}

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

// TODO: I can initialise the array of strings in main() 
// then this func manipulate the result array and change this function's return type to void
char ** strparse(char input[]) {
    char ** returnStr;
    int i = 0;
    int j = 0;
    char * newStr;
    while (input[i] != '\n') {
        if (input[i] != ' ') {
            strncat(newStr, &input[i], 1);
        } else {
            //returnStr[j] = newStr;
            newStr = &input[i++];
            i++;
            j++;
        }
        i++;
    }

    return returnStr;
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
