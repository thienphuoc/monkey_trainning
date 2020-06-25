#include "CoronaVirus.h"

CoronaVirus::CoronaVirus()
{
    log("CoronaVirus constructor()");
}

CoronaVirus::~CoronaVirus(){
    log("CoronaVirus destructor()")
}
CoronaVirus::CoronaVirus(CoronaVirus& obj)
{
    m_dna = obj.m_dna;
    m_virusResistance = obj.m_virusResistance;
    log("CoronaVirus copy constructor()");
}


void CoronaVirus::loadADNInformation()
{
    fstream adnFile;
    adnFile.open("ATGX.bin", ios::in);
    if (adnFile.is_open())
    {
        getline(adnFile, m_dna);
    }
    newFile.close();

    log("CoronaVirus loadADNInformation()")
}

int CoronaVirus::reduceResistance(int i_medicineResistance)
{
    i_medicineResistance = randFunction(1, 60);
    m_virusResistance -= i_medicineResistance;

    return m_virusResistance;
}

void CoronaVirus::setDNA(string DNA)
{
    m_dna = DNA;
}

void CoronaVirus::setVirusResistance(int VirusResistance)
{
    m_virusResistance = VirusResistance;
}

int CoronaVirus::getVirusResistance()
{
    return m_virusResistance;

}