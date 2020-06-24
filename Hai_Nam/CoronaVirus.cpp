#include "CoronaVirus.h"
#include <fstream>



//void CoronaVirus::show2()
//{
//    cout << "in base class";
//}

CoronaVirus::CoronaVirus()
{
    m_dna = "";
    m_virusResistance = 0;
    //log("CoronaVirus constructor() \n");
}

CoronaVirus::CoronaVirus(CoronaVirus& obj)
{
    m_dna = obj.m_dna;
    m_virusResistance = obj.m_virusResistance;
   // log("CoronaVirus Copyconstructor() \n");
}

CoronaVirus::~CoronaVirus()
{
   // log("CoronaVirus Destructor() \n");
}

void CoronaVirus::loadADNInformation()
{
    fstream newFile;
    newFile.open("ATGX.txt", ios::in);
    if (newFile.is_open())
    {
        while (getline(newFile, m_dna))
        {
            cout << m_dna << endl;
        }
    }
    newFile.close();
   // log("CoronaVirus loadADNinformation() \n");
}

int CoronaVirus::reduceResistance(int i_medicineResistance)
{
    int a = 1;
    int b = 60;
    i_medicineResistance = randFunction(a, b);
    m_virusResistance -= i_medicineResistance;
    return m_virusResistance; 
    //log("CoronaVirus reduceResistance() \n");
}

void CoronaVirus::setDNA(string setDNA)
{
    m_dna = setDNA;
  //  log("CoronaVirus setDNA() \n");
}

void CoronaVirus::setVirusResistance(int setVirusResistance)
{
    m_virusResistance = setVirusResistance;
   // log("CoronaVirus setVirusResistance() \n");
}

int CoronaVirus::getVirusResistance()
{
    return m_virusResistance;
  //  log("CoronaVirus getVirusResistance() \n");

}
