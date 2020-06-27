#pragma once
#include<iostream>
#include<list>
#include<algorithm>
#include<fstream>
#include<string.h>
#include<cstdlib>
#include<cstring>
#include"Log.h"
#define RED 0xff0000
#define BLUE 0x0000ff
using namespace std;

class Coronavirus
{
public:
	//Contructor
	Coronavirus();
	//Destructor
	~Coronavirus();
	//copyContructor
	Coronavirus(const Coronavirus& obj);
	//load information of DNA
	void loadADNInformation();
	int reduceResistance(int i_medicineResistance);
	int getResistance();
	//aa
	virtual void doBorn() = 0;
	virtual list<Coronavirus*> doClone() = 0;
	virtual void doDie() = 0;
	virtual void initResistance() = 0;
protected:
	string m_dna;//String axit nucleic(A, T, G, X)
	int m_resistance;//virus resistance
};

