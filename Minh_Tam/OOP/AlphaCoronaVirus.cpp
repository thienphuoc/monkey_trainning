#pragma once
#include "AlphaCoronaVirus.h"

using namespace std;

AlphaCoronaVirus::AlphaCoronaVirus()
{
    doBorn();
    initResistance();
    log("AlphaCoronaVirus constructor");
}

AlphaCoronaVirus::~AlphaCoronaVirus()
{
    doDie();
    log("AlphaCoronaVirus destructor1");
}

AlphaCoronaVirus::AlphaCoronaVirus(const AlphaCoronaVirus& obj)
{
    m_color = obj.m_color;
    m_resistance = obj.m_resistance;
    m_dna = obj.m_dna;
}

void AlphaCoronaVirus::doBorn()
{
    loadADNInformation();
    Color m_color = randFunction(0, 1) ? Color::BLUE : Color::RED;
    log("CoronaVirus doBorn()");

}

list< CoronaVirus*> AlphaCoronaVirus::doClone() 
{
    list<CoronaVirus*> cloneList;
    AlphaCoronaVirus* newVirus = this;
    cloneList.push_back(newVirus);
    return cloneList;
    log("CoronaVirus doClone()");

}

void AlphaCoronaVirus::doDie() 
{
    log("AlphaCoronaVirus doDie()");
}

void AlphaCoronaVirus::initResistance() 
{
    switch (m_color)
    {
    case RED:  setVirusResistance(randFunction(10, 20));
        break;
    case BLUE: setVirusResistance(randFunction(10, 15));
        break;
    }
    log("AlphaCoronaVirus initResistance()");
}