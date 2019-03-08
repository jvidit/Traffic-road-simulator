#include "AddVehicleEvent.h"
#include "VehiclePosition.h"

int AddVehicleEvent::vehicleId = 0;

AddVehicleEvent::AddVehicleEvent(int timestamp, Vehicle vehicleTemplate, int lane)
{

	vehicleId++;
	this->timestamp=timestamp;
	this->vehicle = vehicleTemplate;
	vehicle.setId(vehicleId);

	
	if(lane!=-1)
		vehicle.setUpPos(lane);
	


}


AddVehicleEvent::AddVehicleEvent()
{	}

Vehicle AddVehicleEvent::getVehicle()
{	return vehicle;	}

int AddVehicleEvent::getTimeStamp()
{	return timestamp;	}
	
