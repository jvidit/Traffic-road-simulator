#include "VehiclePosition.h"
	

	void VehiclePosition::operator = (const VehiclePosition &vehiclePosition) 
	{ 
        rightPos=vehiclePosition.rightPos;
        upPos=vehiclePosition.upPos;
        length=vehiclePosition.length;
        width=vehiclePosition.width;
    }



