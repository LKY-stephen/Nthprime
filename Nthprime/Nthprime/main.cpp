#pragma once
#include <iostream>
#include "prime.h"

using namespace std;


void main()
{
	uint32 n;
	uint64 answer;
	//cin >> n;
	n = 1000000000;
	answer = findnthprime(n);
	if (answer == 0)
	{
		cout << "invalid input" << endl;
	}
	else
	{
		cout << answer<< endl;
	}
	
}