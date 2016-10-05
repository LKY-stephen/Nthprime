#pragma once
#include "prime.h"
#include <iostream>

const uint32 wheelhole[wheelfactornumber] = { 0,2,3,4,5, 6,8,9,10,12, 14,15,16,18,20, 21,22,24,25,26, 27,28 };
uint32 wheel[wheelsize] = { 0 };

const uint32 segmenthole[segmentfactornumber] = {2,3,5,7,11,13,17 };
uint32 segment[segmentsize] = {1};

bool sieve[segmentsize] = {false};

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
		uint32 i = 2, m = 0, k = 0,s = (bound / logx), j = 0, pNext = 0, pPrimes = 0;
		uint64  count = 3, high,low, l = 0 ; //primes contain 2,3,5
		uint32 *primes = new uint32[s];//save the sieve prime
		uint32 *next = new uint32[s];//save the next sieve position

		//init bound array
		for (i = 0; i < bound; i++)
		{
			p_lib[i] = false;
		}
		//init wheel array
		for ( i = 0; i < wheelfactornumber; i++)
		{
			wheel[wheelhole[i]] = 1;
		}
		//init prime lib
		 i = 2;
		 s = 2;
		while(i<bound)
		{
			if (s >= wheelsize)
			{
				s -= wheelsize;
			}
			if (wheel[s++])
			{
				p_lib[i] = true;
				i++;
				continue;
			}
			if (!p_lib[i]) 
			{
				count++;
				if (count == n)
				{
					delete [] primes;
					delete[] p_lib;
					delete[] next;
					return i;
				}
				primes[pPrimes++] = i;
				for ( j = i*i; j < bound; j += i)
				{
					p_lib[j] = true;
				}
				next[pNext++] = j-bound;
			}
			i++;
		}


		delete[] p_lib;
		l = bound % 2 ? bound : bound + 1;
		//init segment
		for (i = 0; i < segmentfactornumber; i++)
		{
			s = segmenthole[i];
			for (j = 1; j < segmentsize; j++)
			{
				if (segment[j])
				{
					continue;
				}
				else if (!(j%s))//select the factor don't need to calculate
				{
					segment[j] = 1;
				}
			}
		}
		m = bound%segmentsize;
		s = l - bound;
		for (low = bound; low <= maxmum; low += segmentsize)
		{
			high = low + segmentsize - 1 < maxmum - 1 ? low + segmentsize - 1 : maxmum - 1;
			j = high - low;
			//init the sieve
			for (i = 0; i <= j; i++)
			{
				if (m >= segmentsize)
				{
					m -= segmentsize;
				}
				sieve[i] = segment[m++] ? true : false;
			}


			i = 4;//2,3,5,7,11,13,17 has definetly been erased
			//sieve
			while (i < pPrimes)
			{
				if (next[i] > segmentsize)
				{
					next[i++] -= segmentsize;
					continue;
				}
				j = next[i];
				k = primes[i];

				while (j < segmentsize)
				{
					sieve[j] = true;
					j += k;
				}
				next[i++] = j-segmentsize;
			}
			//count
			
			j = high - low;
			while (s <= j)
			{
				if (sieve[s] == false)
				{
					if (++count == n)
					{
						delete[] primes;
						delete[] next;
						return s+low;
					}
				}
				s += 2;
			}
			l = s + low;
			s -= segmentsize;
		}
		delete[] primes;
		delete[] next;
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

