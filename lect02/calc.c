#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if(argc != 4) return 1;

    int a = atoi(argv[1]);
    int b = atoi(argv[3]);
    char op = argv[2][0];

    if(op == '+') printf("%d\n", a + b);
    else if(op == '-') printf("%d\n", a - b);
    else if(op == 'X') printf("%d\n", a * b);
    else if(op == '/') printf("%d\n", a / b);

    return 0;
}
