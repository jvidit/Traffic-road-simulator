#include "AddVehicleEvent.h"
#include "VehiclePosition.h"

int AddVehicleEvent::vehicleId = 0;

AddVehicleEvent::AddVehicleEvent(int timestamp, Vehicle vehicleTemplate, int lane = -1)
{
	vehicleId++;
	this->vehicle = vehicleTemplate;
	vehicle.setId(vehicleId);
	VehiclePosition pos;
	if(lane!=-1)
		pos.upPos=lane;
	pos.rightPos=0;
}


AddVehicleEvent::AddVehicleEvent()
{	}


int AddVehicleEvent::getTimeStamp()
{	return timestamp;	}
	
