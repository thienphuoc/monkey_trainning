
#include "CoronaVirus.h"
#include "Definition.h"

using namespace std;

class AlphaCoronaVirus : public CoronaVirus
{
private:
	enum Color
	{
		BLUE = 0x0000ff,
		RED = 0xff0000
	};

	Color m_color;
public: 
	AlphaCoronaVirus();
	~AlphaCoronaVirus();
	AlphaCoronaVirus(const AlphacoronaVirus& obj);
};

