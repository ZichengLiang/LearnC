#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct Person {
    char *name;
    int age;
    int height;
    int weight;
};

struct Person Person_create(char *name, int age, int height, int weight){
    // return a pointer typed as Person
    // allocate a chunk of memory with the size of Person, and create a pointer to the structrue
    // error check
    struct Person who; 
    who.name = name;
    who.age = age;
    who.height = height;
    who.weight = weight;

    // what is stdrup? here it is used to retrive the value of pointer name;
    // who -> ... can just be considered as *(ptr + 1) but with mutable pointer type;
    return who;
}

void Person_destroy(struct Person who){
    //free(who->name);
}

void Person_print(struct Person who){
    printf("Name: %s\n", who.name);
    printf("\tAge: %d\n", who.age);
    printf("\tHeight: %d\n", who.height);
    printf("\tWeight: %d\n", who.weight);
}

int main(int argc, char *argv[]){
    // make two people structures
    struct Person joe = Person_create("Joe Alex", 32, 64, 140);
    struct Person frank = Person_create("Frank Blank", 20, 72, 180);

    // print them out and where they are in memory
    Person_print(joe);
    Person_print(frank);
    // %p is the format for printing out an address


    // make everyone age 20 years and print them again
    joe.age += 20;
    frank.age += 20;
    
    Person_print(joe);
    Person_print(frank);
    return 0;
}
