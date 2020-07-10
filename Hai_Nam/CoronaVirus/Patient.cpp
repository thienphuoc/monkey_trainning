#include "Patient.h"
#include <list>

Patient::Patient()
{
    doStart();
    initResistance();
}

Patient::~Patient()
{
}

void Patient::initResistance()
{
    int a = 1000;
    int b = 9000;
    m_patientResistance = randFunction(a, b);
}

void Patient::doStart()
{
    m_state = State::ALIVE;
    const int k_virusNum = 10;
    for (size_t i = 0; i < k_virusNum; ++i)
    {
        CoronaVirus* virus = new AlphaCoronaVirus();
        virus->setVirusResistance(100);
        m_listVirusInPatient.push_back(virus);
    }
}

void Patient::doDide()
{
    m_listVirusInPatient.clear();
    m_state = State::DIE;
    
}

void Patient::takeMedicine(int i_medicineResistance)
{
    list<CoronaVirus*>::iterator it;

    int sumOfvirusResistance = 0;

    for (it = m_listVirusInPatient.begin(); it != m_listVirusInPatient.end(); ++it)
    {
        (*it)->reduceResistance(i_medicineResistance); // set value i_medicineResistance rand(1-60)
        if ((*it)->getVirusResistance() <= 0)
        {
            it = m_listVirusInPatient.erase(it); // delete it 
        }
        else
        {
            // tranfers all element of  (*it)->doClone at begin of m_listVirusinPatient
           // m_listVirusInPatient.splice()
            //(*it)->doClone();
            m_virusList.splice(m_virusList.begin(), (*it)->doClone()); // transfre elements from (*it)->doClone to begin of m_virusList
        }
        if (it == m_listVirusInPatient.end())
        {
            break;
        }
        
    }
    for (it = m_listVirusInPatient.begin(); it != m_listVirusInPatient.end(); it++)
    {
        sumOfvirusResistance += (*it)->getVirusResistance();
    }
    cout << "Total Virus Resistance : " << sumOfvirusResistance << endl;
    cout << "m_listVirusInpatient.size : " << m_listVirusInPatient.size() << endl;
    if (sumOfvirusResistance > m_patientResistance)
    {
        doDide();
    }
}

void Patient::setResistance(int i_resistance)
{
    m_patientResistance = i_resistance;
}

int Patient::getResistace()
{
    return m_patientResistance;
}

int Patient::getVirusNumbet()
{
    return (int)m_listVirusInPatient.size();
}

int Patient::getTotalVirus()
{
    int sum = 0;
    list<CoronaVirus*>::iterator it;
    for (it = m_listVirusInPatient.begin(); it != m_listVirusInPatient.end(); ++it)
    {
        sum += (*it)->getVirusResistance();
    }
    return sum;
}

void Patient::setState(State setState)
{
    m_state = setState;
}



Patient ::State Patient::getSate()
{
    return m_state;;
}



 










