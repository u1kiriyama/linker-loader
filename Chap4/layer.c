extern int num;
void printnum();
void func1();
void func2();

int main()
{
    printnum();
    num++; printnum();
    func1(); printnum();
    func2(); printnum();
    exit(0);
}
/*
layer_sub1.o:
000000000000001e T func1
0000000000000000 B num        <-- D(global Data Symbol) for FreeBSD. B is global bss sybmol.
                 U printf
0000000000000000 T printnum

layer_sub2.o:
0000000000000000 T func2
                 U num
*/