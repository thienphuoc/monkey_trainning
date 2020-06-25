#include "Definition.h"
#include "CoronaVirus.h"

using namespace std;

class Patient
{
private:
	int m_resistance;
	list<CoronaVirus*> m_virusList;
	enum STATE
	{
		0 = DIE,
		1 = ALIVE
	};
	State m_state;

public:
	Patient();
	~Patient();
	void initResistance();
	void doStart();
	void takeMedicine();
	void doDie();
	State getState();
};
