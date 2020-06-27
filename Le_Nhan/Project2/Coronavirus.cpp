#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;
#include"Coronavirus.h"

Coronavirus::Coronavirus()
{
	log("Coronavirus Contructor\n");
	//loadADNInformation();
}

Coronavirus::~Coronavirus()
{
	log("Corornavirus Detructor\n");
}

Coronavirus::Coronavirus(const Coronavirus& obj)
{
	m_dna = obj.m_dna;
	m_resistance = obj.m_resistance;
}
void Coronavirus::loadADNInformation()
{
	ifstream readFileATGX("C:/Users/DELL/source/repos/Project2/Project2/ATGX.bin");
	if (readFileATGX.fail())
	{
		cout << "FIle bi loi";
	}
	//If read file not error
	if (!readFileATGX.fail())
	{
		while (!readFileATGX.eof())
		{
			string readATGX;
			readFileATGX >> readATGX;
			m_dna = readATGX;
		}
	}
	log("Coronavirus loadADNInformation()\n");
}

int Coronavirus::reduceResistance(int i_medicineResistance)
{
	m_resistance = m_resistance - i_medicineResistance;
	log("Coronavirus reduceResistance\n");
	return m_resistance;
}

int Coronavirus::getResistance()
{
	return m_resistance;
}