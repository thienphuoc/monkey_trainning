#include "AI.h"
#include"GameScene.h"
std::pair<int, int> AI :: basic(int digitMap[][3]) {
	std::pair<int, int> Pair;
	Pair.first = 0;
	Pair.second = 0;
	bool temp1 = false;
	for (int ii = 0; ii < 3; ii++) {
		for (int jj = 0; jj < 3; jj++) {
			if (digitMap[ii][jj] == -1) {
				Pair.first = ii;
				Pair.second = jj;
				temp1 = true;
				break;
			}
		}
		if (temp1) break;
	}
	//GameScene *test = new GameScene();
	//test->print();
	return Pair;
}
std::pair<int, int> AI::greedy(int digitMap[][3]) {
	std::pair<int, int> Pair;
	bool temp1 = false;
	int tempMap[3][3];
	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			tempMap[x][y] = digitMap[x][y];
		}
	}
	GameScene *obj = new GameScene();
	for (int ii = 0; ii < 3; ii++) {
		for (int jj = 0; jj < 3; jj++) {
			if (digitMap[ii][jj] == -1) {
				digitMap[ii][jj] = 2;
				if (obj->check(ii, jj) == 2||obj->check1()==2) {//o win
					Pair.first = ii;
					Pair.second = jj;
					return Pair;
				}
				digitMap[ii][jj] = tempMap[ii][jj];

			}
		}
	}
	return AI::basic(digitMap);
}
