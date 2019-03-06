#include "AddVehicleEvent.h"
#include "VehiclePosition.h"


AddVehicleEvent::AddVehicleEvent(int timestamp, Vehicle vehicleTemplate, int id, int lane = -1)
{
	this->vehicle = vehicleTemplate;
	vehicle.setId(id);
	VehiclePosition pos;
	if(lane!=-1)
		pos.upPos=lane;
	pos.rightPos=0;
}


AddVehicleEvent::AddVehicleEvent()
{	}


int AddVehicleEvent::getTimeStamp()
{	return timestamp;	}
	
