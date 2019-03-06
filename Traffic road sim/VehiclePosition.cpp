

//#include "VehiclePosition.h"
//contains length, breath, and the upper right point of vehicle
class VehiclePosition
{

public:

	int rightPos;
	int upPos;
	int length;
	int width;

	void operator = (const VehiclePosition &vehiclePosition) 
	{ 
        rightPos=vehiclePosition.rightPos;
        upPos=vehiclePosition.upPos;
        length=vehiclePosition.length;
        width=vehiclePosition.width;
    }
};


