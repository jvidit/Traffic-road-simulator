#ifndef ADDVEHICLEEVENT_H
#define ADDVEHICLEEVENT_H

#include "Vehicle.h"

class AddVehicleEvent
{
    int timestamp; //time instant of event
    Vehicle vehicle;
    
public:
    

    AddVehicleEvent(int timestamp, Vehicle VehicleTemplate, int id, int lane);
    
    AddVehicleEvent();



    int getTimeStamp();
	
	
};

#endif