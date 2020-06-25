#include "AlphaCoronaVirus.h"

using namespace std;

AlphaCoronaVirus::AlphaCoronaVirus()
{
    doBorn();
    initResistance();
}

AlphaCoronaVirus::~AlphaCoronaVirus()
{
    doDie();
}

AlphaCoronaVirus::AlphaCoronaVirus(const AlphaCoronaVirus& obj)
{
    m_color = obj.m_color;
    m_virusResistance = obj.m_virusResistance;
    m_dna = obj.m_dna;
}

void AlphaCoronaVirus::doBorn() override
{
    loadADNInformation();
    Color temp = randFunction(0, 1) ? Color::BLUE : Color::RED;

}

list< CoronaVirus*> AlphaCoronaVirus::doClone() override
{
    list<CoronaVirus*> cloneList;
    AlphaCoronaVirus* newVirus = this;
    cloneList.push_back(newVirus);
    return cloneList;

}

void AlphaCoronaVirus::doDie() override
{
    log("AlphaCoronaVirus doDie()");
}

void AlphaCoronaVirus::initResistance() override
{
    switch(m_color)
    {
        case RED:  setVirusResistance(randFunction(10, 20)); 
        case BLUE: setVirusResistance(randFunction(10, 15)); 
           break;
    }
    log("AlphaCoronaVirus initResistance()");
}