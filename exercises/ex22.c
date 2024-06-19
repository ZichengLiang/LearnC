#include <stdio.h>
#include "ex22.h"
#include "dbg.h"

// this .c file implements all variables and functions pre-defined in ex22.h
int THE_SIZE = 1000;

// exept this one, this wasn't defined in ex22.h
// what does the keyword "static" stands for here??
static int THE_AGE = 22;

int get_age()
{
    return THE_AGE;
}

void set_age(int age)
{
    THE_AGE = age;
}

double update_ratio(double new_ratio)
{
    static double ratio = 1.0;

    double old_ratio = ratio;
    ratio = new_ratio;

    return old_ratio;
}

void print_size()
{
    log_info("I think size is: %d", THE_SIZE);
}
