#pragma once
#include "prime.h"
#include <iostream>

const int wheelhole[wheelfactornumber] = { 0,2,3,4,5, 6,8,9,10,12, 14,15,16,18,20, 21,22,24,25,26, 27,28 };
int wheel[wheelsize] = { 0 };

const int segmenthole[segmentfactornumber] = { 2,3,5,7,11,13 };
bool segment[segmentsize] = { true };

uint64 findnthprime(uint32 n)
{

	uint64 maxmum;
	uint32 bound;

	//determin bin
	judgebin(&n, &maxmum, &bound);
	if (!maxmum)
	{
		return 0;
	}


	bool *p_lib = new bool[bound];
	bool *sieve = new bool[segmentsize];
	uint32 blocksize = 0, start = segmentfactornumber - 3, wheelpointer = 0;
	uint64  count = 3, high, i = 2, low, l = 0, s = 0, pNext = 0, pPrimes = 0, j = 0; //primes contain 2,3,5
	uint32 *primes = new uint32[bound];//save the sieve prime
	uint64 *next = new uint64[bound];//save the next sieve position

	for (i = 0; i < bound; i++)
	{
		p_lib[i] = true;
	}
	//init wheel array
	for (i = 0; i < wheelfactornumber; i++)
	{
		wheel[wheelhole[i]] = 1;
	}
	//init prime lib
	i = 2;
	s = 2;
	while (i<bound)
	{
		if (s >= wheelsize)
		{
			s -= wheelsize;
		}
		if (wheel[s++])
		{
			p_lib[i] = false;
			i++;
			continue;
		}
		if (p_lib[i])
		{
			count++;
			if (count == n)
			{
				delete[] primes;
				delete[] p_lib;
				delete[] next;
				return i;
			}
			primes[pPrimes++] = i;
			for (j = i*i; j < bound; j += i)
			{
				p_lib[j] = false;
			}
			next[pNext++] = j ;
		}
		i++;
	}


	delete[] p_lib;
	l = bound % 2 ? bound : bound + 1;
	//init segment
	for (i = 1; i < segmentsize; i++)
	{
		for (j = 0; j < segmentfactornumber; j++)
		{
			if ((i%segmenthole[j]) == 0)//select the factor don't need to calculate
			{
				segment[i] = true;
				break;
			}
		}
	}

	for (low = bound; low <= maxmum; low += segmentsize)
	{
		wheelpointer = low%segmentsize;
		high = low + segmentsize - 1 < maxmum - 1 ? low + segmentsize - 1 : maxmum - 1;
		blocksize = high - low;
		//init the sieve
		for (i = 0; wheelpointer < segmentsize&&i <= blocksize; i++)
		{
			sieve[i] = segment[wheelpointer++];
		}
		if (i <= blocksize)
		{
			wheelpointer -= segmentsize;
			for (; i <= blocksize; i++)
			{
				sieve[i] = segment[wheelpointer++];
			}
		}


		i = start;//2,3,5,7,11,13 has definetly been erased
		while (i < pPrimes)
		{
			if (next[i] > high)
			{
				i++;
				continue;
			}
			if (next[i] < low)
			{
				return 0;
			}
			j = next[i] - low;
			for (; j < segmentsize; j += primes[i])
			{
				sieve[j] = true;
			}
			next[i] = j + low;
			i++;
		}

		while (l <= high)
		{
			if (sieve[l - low] == false)
			{
				count++;
				if (count == n)
				{
					delete[] primes;
					delete[] next;
					delete[] sieve;
					return l;
				}
			}
			l += 2;
		}
	}
	delete[] primes;
	delete[] next;
	delete[] sieve;
	return 0;
}

void judgebin(uint32 * n, uint64 * maxmun, uint32 * square)
{
	//determin which bin contain the prime
	if (*n <= 0) {
		*maxmun = 0;
		*square = 0;
	}
	else if (*n <= binsize) {
		*maxmun = 2038074744;
		*square = 45145;
	}
	else if (*n <= binsize * 2) {
		*maxmun = 4222234742;
		*square = 64978;
	}
	else if (*n <= binsize * 3) {
		*maxmun = 6461335110;
		*square = 80382;
	}
	else if (*n <= binsize * 4) {
		*maxmun = 8736028058;
		*square = 93466;
	}
	else if (*n <= binsize * 5) {
		*maxmun = 11037271758;
		*square = 105058;
	}
	else if (*n <= binsize * 6) {
		*maxmun = 13359555404;
		*square = 115583;
	}
	else if (*n <= binsize * 7) {
		*maxmun = 15699342108;
		*square = 125297;
	}
	else if (*n <= binsize * 8) {
		*maxmun = 18054236958;
		*square = 134366;
	}
	else if (*n <= binsize * 9) {
		*maxmun = 20422213580;
		*square = 142906;
	}
	else if (*n <= binsize * 10) {
		*maxmun = 22801763490;
		*square = 151002;
	}
	else
	{
		*maxmun = 0;
		*square = 0;
	}
}
