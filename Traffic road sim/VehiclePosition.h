#ifndef VEHICLEPOSITION_H
#define VEHICLEPOSITION_H

//contains length, breath, and the upper right point position of vehicle
class VehiclePosition
{

public:
	int rightPos;
	int upPos;
	

	void operator = (const VehiclePosition &pvehiclePosition);
};



#endif

