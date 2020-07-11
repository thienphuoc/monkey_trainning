#include "Definition.h"
#include "CoronaVirus.h"
#include "CoronaVirus.h"
#include "AlphaCoronaVirus.h"
#include "BetaCoronaVirus.h"

using namespace std;

class Patient
{
public:
	enum STATE
	{
		DIE,
		ALIVE
	};
	STATE m_state;
	Patient();
	~Patient();
	void initResistance();
	void doStart();
	void takeMedicine(int i_medicine);
	void doDie();
	STATE getState();
	void setResistance(int newResistance);
	


protected:
	int m_resistance;
	list<CoronaVirus*> m_virusList;
	

	


};
