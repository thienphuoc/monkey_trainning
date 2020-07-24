#include "Board.h"
#include <map>
#include <queue>
#include <algorithm>
#include <vector>
#include <time.h>
using namespace std;

Board::Board(int n_rows, int n_colums, int n_types, vector<int> count) : n_rows(n_rows), n_colums(n_colums), 
_pokemon(vector<vector < int >> (n_rows, vector<int>(n_colums, -1)))
{
	map<int, int> countType;
	srand(time(NULL));
	for (int x = 0; x < n_rows; x++)
	{
		for (int y = 0; y < n_colums; y++)
		{
			int type;
			do {
				type = rand() % n_types;
			} while (countType[type] >= count[type]);

			countType[type] += 1;
			addPokemon(x, y, type + 1);

		}
	}
}

int Board::getColums()
{
	return n_colums;
}

int Board::getRows()
{
	return n_rows;
}

void Board::addPokemon(int x, int y, int type)
{
	_pokemon[x][y] = type;
}

int Board::getPokemon(int x, int y)
{
	return _pokemon[x][y];
}

void Board::removePokemon(int x, int y)
{
	_pokemon[x][y] = -1;
}


bool Board::selectPokemon(int x, int y)
{
	if (_x == -1 && _y == -1 || _pokemon[x][y] != _pokemon[_x][_y] || !canConnect(_x, _y, x, y)) {
		return false;
	}
	return true;
}

bool Board::canConnect(int _x, int _y, int x, int y)
{
	auto path = findPath(_x, _y, x, y);

	return path.size() >= 2 && path.size() <= 4;
}


vector<pair<int, int>> Board::findPath(int _x, int _y, int x, int y)
{
	vector<vector<int>> e(n_rows + 2, vector<int>(n_colums + 2, 0));
	for (int i = 0; i < n_rows; i++)
	{
		for (int j = 0; j < n_colums; j++)
		{
			e[i + 1][j + 1] = _pokemon[i][j] != -1;
		}
	}

	pair<int, int> s = { _x + 1, _y + 1 };
	pair<int, int> t = { x + 1, y + 1 };


	const int dx[4] = { -1, 0, 1, 0 };
	const int dy[4] = { 0, 1, 0, -1 };

	deque<pair<int, int >> q;
	vector<vector<pair<int, int>>> trace(e.size(), vector<pair<int, int>>(e[0].size(), make_pair(-1, -1)));
	q.push_back(t);
	trace[t.first][t.second] = make_pair(-2, -2);
	e[s.first][s.second] = 0;
	e[t.first][t.second] = 0;
	while (!q.empty())
	{
		auto u = q.front();
		q.pop_front();
		if (u == s)
		{
			break;
		}
		for (int i = 0; i < 4; i++)
		{
			int x = u.first + dx[i];
			int y = u.second + dy[i];
			while (x >= 0 && x < e.size() && y >= 0 && y < e[0].size() && e[x][y] == 0)
			{
				if (trace[x][y].first == -1)
				{
					trace[x][y] = u;
					q.push_back({ x, y });
				}
				x = x + dx[i];
				y = y + dy[i];
			}
		}
	}

	vector<pair<int, int>> res;
	if (trace[s.first][s.second].first != -1)
	{
		while (s.first != -2)
		{
			res.push_back({ s.first - 1, s.second - 1 });
			s = trace[s.first][s.second];
		}
	}

	return res;
}

