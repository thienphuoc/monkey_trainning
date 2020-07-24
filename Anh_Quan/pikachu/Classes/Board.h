/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __BOARD_H__
#define __BOARD_H__

#include<vector>

class Board {
private:
    int n_rows, n_columns;
    std::vector<std::vector<int>> _pokemons;
    
public:
    int _x = -1, _y = -1;
    int pokemonCount;

    Board(int n_rows, int n_columns, int n_types, std::vector<int> count);
    int getNRows();

    int getNColumns();

    void addPokemon(int x, int y, int type);

    int getPokemon(int x, int y);

    void removePokemon(int x, int y);
    
    bool selectPokemon(int x, int y);
    
    bool canConnect(int _x, int _y, int x, int y);
    
    std::vector<std::pair<int , int>> findPath(int _x, int _y, int x, int y);
};

#endif
