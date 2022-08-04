#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <elf.h>
#include <sys/stat.h>
#include <sys/mman.h>

#define IS_ELF(ehdr)\
    ((ehdr).e_ident[EI_MAG0] == ELFMAG0 &&\
     (ehdr).e_ident[EI_MAG1] == ELFMAG1 &&\
     (ehdr).e_ident[EI_MAG2] == ELFMAG2 &&\
     (ehdr).e_ident[EI_MAG3] == ELFMAG3)

int main(int argc, char *argv[])
{
  int fd, i;
  struct stat sb;
  char *head;
  Elf64_Ehdr *ehdr;
  Elf64_Shdr *shdr;
  Elf64_Shdr *shstr;

  fd = open(argv[1], O_RDONLY);
  fstat(fd, &sb);
  head = mmap(NULL, sb.st_size, PROT_READ, MAP_SHARED, fd, 0);

  ehdr = (Elf64_Ehdr *)head;

  if (!IS_ELF(*ehdr)) {
    fprintf(stderr, "This is not ELF file. (%s)\n", argv[1]);
    exit (1);
  }

  /* shstr は shdr の i = ehdr->e_shstrndx(=10 for elfsamp.o) としたもの。*/
  shstr = (Elf64_Shdr *)(head + ehdr->e_shoff + ehdr->e_shentsize * ehdr->e_shstrndx);
  printf("%lu\n", head);
  printf("%lu\n", shstr);
  printf("%lu (offset of readelf -S eflsamp.o)\n", shstr->sh_offset);

  printf("\n");
  for (i = 0; i < ehdr->e_shnum; i++) {
    shdr = (Elf64_Shdr *)(head + ehdr->e_shoff + ehdr->e_shentsize * i);
    printf("%s\n", (char *)(head + shstr->sh_offset + shdr->sh_name));
    /* shdr のアドレスについて
      .text は1440byte目になっており、セクションヘッダテーブルの開始位置と一致
      以降64byteごとになっている。
    */
    printf("\taddr : %lu\n", shdr);
    printf("\tsh_name : %lu\n", shdr->sh_name);
    printf("\tsh_offset : %lu\n", shdr->sh_offset);
    printf("\tsh_size : %lu\n", shdr->sh_size);
    printf("\tsh_info : %lu\n", shdr->sh_info);
    printf("\tsh_entsize : %lu\n", shdr->sh_entsize);
  }

  munmap(head, sb.st_size);
  close(fd);

  exit (0);
}