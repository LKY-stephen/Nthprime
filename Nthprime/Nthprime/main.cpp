#pragma once
#include <iostream>
#include "prime.h"

using namespace std;


void main()
{
	uint64 n;
	cin >> n;
	cout<<findnthprime(n)<<endl;
}