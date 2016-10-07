#pragma once
#include "prime.h"
#include <iostream>

const int wheelhole[wheelfactornumber] = { 0,2,3,4,5, 6,8,9,10,12, 14,15,16,18,20, 21,22,24,25,26, 27,28 };
bool wheel[wheelsize] = { false };

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

	//init sieve system
	bool *p_lib = new bool[bound];
	bool *sieve = new bool[segmentsize];
	uint32 count = 3,i = 2,blocksize = 0, start = segmentfactornumber - 3, wheelpointer = 0, s = 0, pointer = 0,tempprime=0,j = 0,tempnext2=0 ;
	uint64 high, low, l = 0, tempnext1=0; //primes contain 2,3,5
	uint32 *primes = new uint32[bound];//save the sieve prime
	uint64 *next = new uint64[bound];//save the next sieve position


	for (i = 0; i < wheelfactornumber; i++)
	{
		wheel[wheelhole[i]] = true;
	}
	for (i = 0,s=0; i < bound; i++)
	{
		if (s >= wheelsize)
		{
			s -= wheelsize;
		}
		p_lib[i] = wheel[s++] ? false : true;
	}
	//init wheel array
	
	//init prime lib
	i = 2;
	while (i<bound)
	{
		if (p_lib[i])
		{
			
			if (count++ == n)
			{
				delete[] primes;
				delete[] p_lib;
				delete[] next;
				return i;
			}
			primes[pointer] = i;
			tempnext1 = i;
			tempnext1 *= i;
			for (; tempnext1 < bound; tempnext1 += i)
			{
				p_lib[tempnext1]= false;
			}
			next[pointer++] = tempnext1-bound;
		}
		i++;
	}


	delete[] p_lib;
	
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

	l = bound % 2 ? bound : bound + 1;
	s = l - bound;
	for (low = bound; low <= maxmum; low += segmentsize)
	{
		wheelpointer = low%segmentsize;
		high = low + segmentsize - 1 < maxmum - 1 ? low + segmentsize - 1 : maxmum - 1;
		blocksize = high - low+1;
		//init the sieve
		for (i = 0; wheelpointer < segmentsize&&i < blocksize; i++)
		{
			sieve[i] = segment[wheelpointer++];
		}
		if (i < blocksize)
		{
			wheelpointer -= segmentsize;
			for (; i < blocksize; i++)
			{
				sieve[i] = segment[wheelpointer++];
			}
		}


		i = start;//2,3,5,7,11,13 has definetly been erased
		while (i < pointer)
		{
			if (next[i] > segmentsize)
			{
				next[i++] -= segmentsize;
				continue;
			}
			tempnext2 = next[i];
			tempprime = primes[i];
			for (; tempnext2 < segmentsize; tempnext2 += tempprime)
			{
				sieve[tempnext2] = true;
			}
			next[i] = tempnext2 - segmentsize;
			i++;
		}


		while (s < segmentsize)
		{
			if (!sieve[s])
			{
				if (++count == n)
				{
					delete[] primes;
					delete[] next;
					delete[] sieve;
					return s+low;
				}
			}
			s += 2;
		}
		s -= segmentsize;
	}
	delete[] primes;
	delete[] next;
	delete[] sieve;
	return 0;
}

void judgebin(uint32 *n, uint64 *maxmun, uint32 *square)
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
