#include <stdio.h>
#define SMM_IMPLEMENTATION
#define TMM_IMPLEMENTATION
#include "smm.h"
#include "tmm.h"

int main() {
    long long int a, b;
    if (scanf("%lld %lld", &a, &b) != 2) {
        return 1;
    }
    long long int* result = (long long int*)smm_alloc(sizeof(long long int));
    if (result == NULL) {
        return 1;
    }
    cadd(a, b, result);
    printf("%lld\n", *result);
    long long int* wide_result = (long long int*)smm_realloc(result, sizeof(long long int) * 2);
    if (wide_result != NULL) {
        result = wide_result;
    }
    smm_free(result);
    return 0;
}
