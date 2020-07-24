#pragma once

#include "cocos2d.h"
#include <vector>

class Board 
{
public:
    int _x = -1, _y = -1;
    Board(int n_rows, int n_columns, int n_types, std::vector<int> count);
    int getNRows();
    int getNColumns();
    void addPokemon(int x, int y, int type);
    int getPokemon(int x, int y);
    void removePokemon(int x, int y);
    bool selectPokemon(int x, int y);
    bool canConnect(int _x, int _y, int x, int y);
    std::vector<std::pair<int, int>> findPath(int _x, int _y, int x, int y);
    
private:
    int n_rows, n_columns;
    std::vector<std::vector<int>> _pokemons;
};


