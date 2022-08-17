#include <stdio.h>

extern int __fini_array_end;
extern int data_start;
extern int edata;
extern int end;

int main()
{
    printf("&__fini_array_end = 0x%08x\n", (int) &__fini_array_end);
    printf("&data_start       = 0x%08x\n", (int) &data_start);
    printf("&edata            = 0x%08x\n", (int) &edata);
    printf("&end              = 0x%08x\n", (int) &end);
    exit (0);
}

/*
gcc -c edata.c -Wall
gcc edata.o -Wall -o edataMy -T linkerscriptMy <- line 149 _data_start = . ; PROVIDE (data_start = .);
&data_start       = 0x00601030
&edata            = 0x00601040
&end              = 0x00601048

check nm edata.o
objdump -h edataMy
 24 .data         00000010  0000000000601030  0000000000601030  00001030  2**3
                  CONTENTS, ALLOC, LOAD, DATA
 25 .bss          00000008  0000000000601040  0000000000601040  00001040  2**0
                  ALLOC

*/
