#include <stdio.h>
#include <ctype.h>
#include <string.h>

// forward declarations
int can_print_it (char ch);
void print_letters(char arg[], int argl);

void print_arguments(int argc, char *argv[])
{
    int i = 1; // skip the command itself

    for (i = 1; i < argc; i++){
        print_letters(argv[i], strlen(argv[i]));
    }
}

void print_letters(char arg[], int argl)
{
    int i = 0;

    for (i = 0; i < argl; i++){
        char ch = arg[i];

        if (isalpha(ch) || isdigit(ch)){
            printf("'%c' == %d ", ch, ch);
        }
    }

    printf("\n");
}


int main (int argc, char *argv[])
{
    print_arguments(argc, argv);
    return 0;
}
