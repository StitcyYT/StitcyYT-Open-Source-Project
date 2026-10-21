#include <stdio.h>
#define TMM_IMPLEMENTATION
#include "tmm.h"

int main() {
    long long int a, b;
    long long int result = 0;
    scanf("%lld %lld", &a, &b);
    cadd(a, b, &result);
    printf("%d\n", result);
    return 0;
}