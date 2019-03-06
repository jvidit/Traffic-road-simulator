

//#include "VehiclePosition.h"
//contains length, breath, and the upper right point of vehicle
class VehiclePosition
{

public:

	int rightPos;
	int upPos;
	int length;
	int breadth;

	void operator = (const VehiclePosition &pos) 
	{ 
        rightPos=pos.rightPos;
        upPos=pos.upPos;
        length=pos.length;
        breadth=pos.breadth;
    }
};


