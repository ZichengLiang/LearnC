#include <stdio.h>
void printAll (char **name, int *age, int count);
int main (int argc, char *argv[])
{
    // create two arrays we care about
    int ages[] = { 23, 42, 12, 89, 2 };
    char *names[] = {"Alan", "Frank", "Mary", "John", "Lara"};
    // *names[] is an array of character pointers, it's more like 
    // [0 |1 | | | ]
    // [A][F]
    // [l][r]
    // [a][a]
    // [n][n]
    //    [k]

    // safely get the size of ages
    int count = sizeof(ages) / sizeof(int); // I'm amazed by how to get the array's length in C
    printf("the size of the int array is %d\n", count);
    int i = 0;

    // first way using array indexing
    while (i < count){
        printf("%s has %d years alive.\n", names[i], ages[i]);
        i++;    
    }
    printf("---\n");

    // set up the pointers to the start of the arrays
    int *cur_age = ages; // it points to where ages[] start
    char **cur_name = &names[0]; // this is a pointer to pointers, as *names[] is an array of pointers

    // second way using pointers
    for (i = 0; i < count; i++) {
        printf("%s is %d years old.\n", 
                *(cur_name + i), *(cur_age +i));
    }
    // when using a pointer by *ptr, it gives you the VALUE in that address
    // the advantage of pointers is that they can be moved around

    printf("---\n");

    // third way, pointers are just arrays
    for (i = count - 1; i >= 0; i--){
        printf("%s is %d years old again.\n", cur_name[i], cur_age[i]);
        // you can also pretend pointers were arrays
        // you are actually telling the compiler to jump i places and return the value there
    }

    printf("---\n");

    //fourth way with pointers in a stupid complex way
    for(cur_age = ages, cur_name = names; (cur_age - ages) < count; cur_age++, cur_name++) {
        printf("%s lived %d years so far\n", *cur_name, *cur_age);
    }

    cur_name = &names[0];
    cur_age = &ages[0];
    printAll(cur_name, cur_age, count);

    return 0;
}

void printAll (char **name, int *age, int count){
    printf("---\n");
    printf("Now we use a function to print out:\n");
    for (int i = 0; i < count; i++) {
    printf("%s has lived %d years\n", *(name + i), *(age + i));
    printf("now the pointer name points to %p, age points to %p\n", name + i, age + i);
    }
}
