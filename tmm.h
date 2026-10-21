/*
 Copyright (c) 2026 StitcyYT Open Source Project.
 author: StitcyYT
 This file is part of the StitcyYT Open Source Project.
 It handles complex math addition and other math operations.
*/

#ifndef TMM_H
#define TMM_H

//defenitions
#define pi 3.14159265358979323846 // HAHAHA GET PI'ED
#define e 2.71828182845904523536 // e
#define _zta 0.57721566490153286060 // zeta
#define _gamma 0.57721566490153286060 // gamma

#ifdef TMM_IMPLEMENTATION
// c"name" stands for complex as you can see cadd and csub are complex functions.
void cadd(long long a, long long b, long long *To) {
    long long az = a;
    while (az >= 10) {
        az = az - 10;
    }
    *To = (a-az)+(b+az);
}

void csub(long long a, long long b, long long *To) {
    long long az = a;
    while (az >= 10) {
        az = az - 10;
    }
    *To = (a-az)-(b-az);
}

#endif // TMM_IMPLEMENTATION

#endif // TMM_H