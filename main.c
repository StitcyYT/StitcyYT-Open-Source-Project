#include <stdio.h>
#define TMM_IMPLEMENTATION
#include "tmm.h"

int main() {
    int a, b;
    long long int result = 0;
    scanf("%d %d", &a, &b);
    cadd(a, b, &result);
    printf("%d\n", result);
    return 0;
}