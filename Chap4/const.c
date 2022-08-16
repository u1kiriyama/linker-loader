#include <stdio.h>

extern int a;

int main() // Segmentation fault. Bus error on FreeBSD acording to textbook.
{
    a = 2;
    printf("%d\n", a);
    exit(0);
}