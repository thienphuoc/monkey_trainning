#pragma once
#include "Coronavirus.h"
#include<time.h>
enum Color {
	RED = 0x0000ff,
	BLUE = 0xff0000
};
class AlphaCoronavirus : public Coronavirus {
private:
	Color color;
public:
	void setColor(Color color);
	Color getColor();
	void doBorn();
	void doDie();
	vector<Coronavirus*>  doClone();
	void initResistance();
	AlphaCoronavirus();
	~AlphaCoronavirus();
	string toString();

};

