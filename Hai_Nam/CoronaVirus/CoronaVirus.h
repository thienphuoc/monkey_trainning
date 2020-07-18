#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "commonFunction.h"

using namespace std;

class CoronaVirus
{
public:
    CoronaVirus();
    CoronaVirus(CoronaVirus& obj);
    ~CoronaVirus();

    void loadADNInformation();
    int reduceResistance(int i_medicineResistance);
    void setDNA(string i_DNA);
    void setVirusResistance(int i_virusResistance);

    virtual void doBorn() = 0;
    virtual std::vector< CoronaVirus*> doClone() = 0;
    virtual void doDie() = 0;
    virtual void initResistance() = 0;

    int getVirusResistance();

protected:
    string m_dna;
    int m_virusResistance; // (1-30)   
};