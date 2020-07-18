#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;
class Coronavirus {
private:
	string m_dna;
	int m_resistance;
public:
	void setDna(string dna);
	string getDna();
	void setResistance(int m_resistance);
	int getResistance();
	


	Coronavirus();
	~Coronavirus();
	Coronavirus(const Coronavirus& x);
	void loadADNInformation();
	void reduceResistance(int i_medicineResistance);
	virtual void doBorn() = 0;
	virtual void doDie() = 0;
	virtual vector<Coronavirus*> doClone() = 0;
	virtual void initResistance() = 0;
	virtual string toString() = 0;

};

