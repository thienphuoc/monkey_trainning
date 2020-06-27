#include"Log.h"
#include<iostream>
using namespace std;

void log(string i_msg)
{
	cout<<i_msg;
}

int Random(int a, int b)
{
	int n_random = rand() % (b - a + 1) + a;
	return n_random;
}