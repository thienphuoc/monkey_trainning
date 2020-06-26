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
		DIE,
		ALIVE
	};
	STATE m_state;

public:
	Patient();
	~Patient();
	void initResistance();
	void doStart();
	void takeMedicine();
	void doDie();
	STATE getState();
};
