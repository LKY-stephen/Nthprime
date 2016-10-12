#pragma once
#include <iostream>
#include "prime.h"

using namespace std;


int main()
{
	uint32 n;
	uint64 answer;
	try
	{
	   cin >> n;
	}
	catch (exception& e)  
  	{  
           cout << "Standard exception: " << e.what() << endl;  
	   return 1;
   	}  
	//n = 1000000000;
	answer = findnthprime(n);
	if (answer == 0)
	{
           cout << "invalid input" << endl;
	}
	else
	{
	   cout << answer<< endl;
	}
	return 0;
	
}
