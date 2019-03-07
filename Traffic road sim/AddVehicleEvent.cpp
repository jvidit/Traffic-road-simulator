#include "AddVehicleEvent.h"
#include "VehiclePosition.h"


AddVehicleEvent::AddVehicleEvent(int timestamp, Vehicle vehicleTemplate, int lane = -1)
{
	id++;
	this->vehicle = vehicleTemplate;
	vehicle.setId(id);
	VehiclePosition pos;
	if(lane!=-1)
		pos.upPos=lane;
	pos.rightPos=0;
}


AddVehicleEvent::AddVehicleEvent()
{	}

Vehicle AddVehicleEvent::getVehicle()
{	return vehicle;	}

int AddVehicleEvent::getTimeStamp()
{	return timestamp;	}
	
