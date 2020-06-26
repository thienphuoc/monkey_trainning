#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "CoronaVirus.h"
#include "Definition.h"
#include "Patient.h"

using namespace std;

CoronaVirus::CoronaVirus()
{
    log("CoronaVirus constructor()");
}

CoronaVirus::~CoronaVirus() {
    log("CoronaVirus destructor()");
}
CoronaVirus::CoronaVirus(CoronaVirus& obj)
{
    m_dna = obj.m_dna;
    m_resistance = obj.m_resistance;
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
    adnFile.close();

    log("CoronaVirus loadADNInformation()");
}

int CoronaVirus::reduceResistance(int i_medicineResistance)
{
    //i_medicineResistance = randFunction(1, 60);
    m_resistance -= i_medicineResistance;

    return m_resistance;
    log("CoronaVirus reduceResistance");
}

void CoronaVirus::setDNA(string DNA)
{
    m_dna = DNA;
    log("CoronaVirus setDNA");
}

void CoronaVirus::setVirusResistance(int VirusResistance)
{
    m_resistance = VirusResistance;
    log("CoronaVirus setVirusResistance");
}

int CoronaVirus::getVirusResistance()
{
    return m_resistance;
    log("CoronaVirus getVirusResistance");

}