#pragma once
#include<iostream>
class AI
{
public:
	std::pair<int, int> basic(int digitMap[][3]);
	std::pair<int, int> greedy(int digitMap[][3]);
	bool checkOWin(int i, int j);
};

