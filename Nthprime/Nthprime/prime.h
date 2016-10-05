#pragma once
#define binsize 100000000
#define wheelfactornumber 22
#define wheelsize 30//2*3*5
#define segmentfactornumber 7
#define segmentsize 510510//2*3*5*7*11*13*17
#define logx 2

typedef unsigned long long uint64;
typedef unsigned long  uint32;



uint64 findnthprime(uint32 n);
void judgebin(uint32 *n, uint64 *maxmun, uint32 *square);