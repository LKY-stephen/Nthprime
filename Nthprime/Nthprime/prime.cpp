#pragma once
#include "prime.h"
#include <iostream>

const int wheelhole[wheelfactornumber] = { 0,2,3,4,5, 6,8,9,10,12, 14,15,16,18,20, 21,22,24,25,26, 27,28 };
int wheel[wheelsize] = { 0 };

const int segmenthole[segmentfactornumber] = {2,3,5,7,11,13,17 };
int segment[segmentsize] = {1};

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


		bool *p_lib= new bool[bound];
		bool *sieve = new bool[segmentsize];
		uint32 count = 3, i = 2, s = 2, pNext = 0, pPrimes = 0,j = 0 ;//primes contain 2,3,5
		uint64  high, low,l=0;
		uint32 *primes = new uint32[bound];//save the sieve prime
		uint64 *next = new uint64[bound];//save the next sieve position

		//init bound array
		for ( i = 0; i < bound; i++)
			p_lib[i] = false;
		//init wheel array
		for ( i = 0; i < wheelfactornumber; i++)
		{
			wheel[wheelhole[i]] = 1;
		}
		//init prime lib
		 i = 2;
		while(i<bound)
		{
			if (wheel[i%wheelsize])
			{
				p_lib[i] = true;
				i++;
				continue;
			}
			if (p_lib[i] == false) {
				count++;
				if (count == n) {
					delete [] primes;
					delete[] p_lib;
					delete[] next;
					delete[] sieve;
					return i;
				}
				primes[pPrimes++] = i;
				for ( j = i*i; j < bound; j += i)
				{
					p_lib[j] = true;
				}
				next[pNext++] = j;
			}
			i++;
		}
		l = bound % 2 ? bound : bound + 1;
		//init segment
		for (i = 1; i < segmentsize; i++)
		{
			for (j = 0; j < segmentfactornumber; j++)
			{
				if ((i%segmenthole[j]) == 0)//select the factor don't need to calculate
				{
					segment[i] = 1;
					break;
				}
			}
		}

		for (uint64 low = bound,s=bound; low <= maxmum; low += segmentsize) {
			high = low + segmentsize - 1 < maxmum - 1 ? low + segmentsize - 1 : maxmum - 1;
			for ( i = low; i < high; i++)
			{
				if (segment[i%segmentsize])
				{
					sieve[i-low] = true;
				}
				else
				{
					sieve[i-low] = false;
				}
			}
				
		
			i = 4;//2,3,5,7,11,13,17 has definetly been erased
			while ( i<pPrimes) 
			{
				if (next[i] > high)
				{
					i++;
					continue;
				}
				j = next[i]-low;
				for (; j < segmentsize; j += primes[i])
				{
					sieve[j] = true;
				}
				next[i] = j+low;
				i++;
			}

			for (; l <= high; l += 2)
				if (sieve[l - low] ==false) {
					count++;
					if (count == n) {
						delete[] primes;
						delete[] p_lib;
						delete[] next;
						delete[] sieve;
						return l;
					}
				}
		}
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
	else if (*n <= binsize*2) {
		*maxmun = 4222234742;
		*square = 64978;
	}
	else if (*n <= binsize*3) {
		*maxmun = 6461335110;
		*square = 80382;
	}
	else if (*n <= binsize*4) {
		*maxmun = 8736028058;
		*square = 93466;
	}
	else if (*n <= binsize*5) {
		*maxmun = 11037271758;
		*square = 105058;
	}
	else if (*n <= binsize*6) {
		*maxmun = 13359555404;
		*square = 115583;
	}
	else if (*n <= binsize*7) {
		*maxmun = 15699342108;
		*square = 125297;
	}
	else if (*n <= binsize*8) {
		*maxmun = 18054236958;
		*square = 134366;
	}
	else if (*n <= binsize*9) {
		*maxmun = 20422213580;
		*square = 142906;
	}
	else if (*n <= binsize *10) {
		*maxmun = 22801763490;
		*square = 151002;
	}
	else
	{
		*maxmun = 0;
		*square = 0;
	}
}

