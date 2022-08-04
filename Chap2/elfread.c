#include <stdio.h>
#include <stdlib.h>
#include <elf.h>

int main()
{
    Elf64_Ehdr *ehdr;

    ehdr = (Elf64_Ehdr *)0x0000000000400000;

//readelf -h elfsamp
//ELF Header:
//  Magic:   7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00 
    printf("0x%02x%c%c%c\n",
        ehdr->e_ident[EI_MAG0],
        ehdr->e_ident[EI_MAG1],
        ehdr->e_ident[EI_MAG2],
        ehdr->e_ident[EI_MAG3]);
    exit (0);
}