#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char data_start, edata, end;

int i0, i1 = 1;
double d0, d1 = 0.1;
char *s0, *s1 = "sample string";

char * save_ivalue()
{
    char * p;
    int size = &edata - &data_start;
    p = malloc(size);
    memcpy(p, &data_start, size);
    return (p);
}

void reset_ivalue(char * p)
{
    memcpy(&data_start, p, (&edata - &data_start));
    memset(&edata, 0, (&end - &edata));
}

int main()
{
    char * p;
    p = save_ivalue();
    printf("i0 = %d, i1 = %d, d0 = %f, d1 = %f, s0 = %s, s1 = %s\n", i0, i1, d0, d1, s0, s1);
    i0 = 1; i1 = 2; d0 = 1.1; d1 = 1.2; s0 = "sample1"; s1 = "sample2";
    printf("i0 = %d, i1 = %d, d0 = %f, d1 = %f, s0 = %s, s1 = %s\n", i0, i1, d0, d1, s0, s1);
    reset_ivalue(p);
    printf("i0 = %d, i1 = %d, d0 = %f, d1 = %f, s0 = %s, s1 = %s\n", i0, i1, d0, d1, s0, s1);

    exit (0);
}

/*
gcc initialize.c -T linkerscriptMy -Wall -o initialize
./initialize 
i0 = 0, i1 = 1, d0 = 0.000000, d1 = 0.100000, s0 = (null), s1 = sample string
i0 = 1, i1 = 2, d0 = 1.100000, d1 = 1.200000, s0 = sample1, s1 = sample2
i0 = 0, i1 = 1, d0 = 0.000000, d1 = 0.100000, s0 = (null), s1 = sample string

gcc initialize.c -Wall -o initializeorg
./initializeorg 
i0 = 0, i1 = 1, d0 = 0.000000, d1 = 0.100000, s0 = (null), s1 = sample string
i0 = 1, i1 = 2, d0 = 1.100000, d1 = 1.200000, s0 = sample1, s1 = sample2
i0 = 0, i1 = 1, d0 = 0.000000, d1 = 0.100000, s0 = (null), s1 = sample string
*/