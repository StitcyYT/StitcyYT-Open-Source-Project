/*
 Copyright (c) 2026 StitcyYT Open Source Project.
 author: StitcyYT
 This file is part of the StitcyYT Open Source Project.
 It handles normal types like 32-bit limits.
*/

#ifndef NCT_H
#define NCT_H

#define I32_MAX 2147483647
#define I32_MIN -2147483648
#define U32_MAX 4294967295
#define U32_MIN 0
#define I64_MAX 9223372036854775807
#define I64_MIN -9223372036854775808
#define U64_MAX 18446744073709551615
#define U64_MIN 0
#define F32_MAX 3.402823466e+38F
#define F32_MIN 1.175494351e-38F
#define F64_MAX 1.7976931348623158e+308
#define F64_MIN 2.2250738585072014e-308

typedef struct {
    long long value; 
} Union;

#endif // NCT_H
