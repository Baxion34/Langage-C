#include <stdio.h>

int main() {
    int A = 1;
    int B = 2;
    int C = 3;
    int *P1=NULL, *P2=NULL;

    P1 = &A;
    P2 = &C;
    *P1 = (*P2)++;
    P1 = P2;
    P2 = &B;
    *P1 -= *P2;
    ++*P2;
    *P1 *= *P2;
    A = ++*P2**P1;
    P1 = &A;
    *P2 = *P1 /= *P2;
    return 0;
}