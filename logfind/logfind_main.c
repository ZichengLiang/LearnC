#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "dirent.h"
#include "dbg.h"

int main(int argc, char *argv[])
{
    // read the input string as char *target[]
    // find the target words among system logs (path: ~/var/log)
    FILE *fp;
    
    if (argc == 1) {
        // no args
        printf("There's no word received, please specify what you need to find.\n");
        return 1;
    } else {
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

    // print the file's name? or lines where the record is stored?
}
