#include "AlphaCoronaVirus.h"
#include "BetaCoronaVirus.h"
#include "Definition.h"
#include "Patient.h"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <list>
#include <string>
#include <time.h>

int main()
{
	//				TEST CASE 1
		//CoronaVirus* f1 = new AlphaCoronaVirus();
		//delete f1;
	
	//				TEST CASE 2
		//CoronaVirus* f2 = new BetaCoronaVirus();
		//delete f2;
	
	Patient p;
	p.setResistance(1000);
	const int k_medicineResistance = 1;

	int counter = 1;
	while (p.getState() == PATIENT_STATE::ALIVE)
	{
		std::cout << "\tTakeMedicine() counter: " << counter << "\n\t\ti_medicineResistance = " << k_medicineResistance << "\n\t\tPatient Resistance = " << p.getResistance() << std::endl;
		p.takeMedicine(k_medicineResistance);
		counter++;

		/*			TEST CASE 7

		if (p.getVirusNumber() == 0)
			break;
		else
			p.getVirusList();
		*/
	}

	
	/*
	if(p.getState() == PATIENT_STATE::ALIVE)
		log("The patient has been cured!\n");
	*/
	

	return 0;
}