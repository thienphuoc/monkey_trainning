#pragma once

#include <vector>
using namespace std;


class Board
{
	int n_rows, n_colums;
	vector<vector<int>> _pokemon;

public:
	int _x = -1, _y = -1;
	Board(int n_rows, int n_colums, int n_types, vector<int> count);

	int getRows();
	int getColums();
	void addPokemon(int x, int y, int type);
	int getPokemon(int x, int y);
	void removePokemon(int x, int y);

	bool selectPokemon(int x, int y);
	bool canConnect(int _x, int _y, int x, int y);
	vector<pair<int, int>>findPath(int _x, int _y, int x, int y);

};
