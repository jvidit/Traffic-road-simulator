

//#include "VehiclePosition.h"
//contains length, breath, and the upper right point of vehicle
class VehiclePosition
{

public:

	int rightPos;
	int upPos;
	

	void operator = (const VehiclePosition &vehiclePosition) 
	{ 
        rightPos=vehiclePosition.rightPos;
        upPos=vehiclePosition.upPos;
    }
};


