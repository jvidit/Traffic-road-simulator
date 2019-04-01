#ifndef ADDVEHICLEEVENT_H
#define ADDVEHICLEEVENT_H

#include "Vehicle.h"
#include <iostream>

class AddVehicleEvent
{
    int timestamp; //time instant of event
    Vehicle vehicle;
    
    static int vehicleId;
    
public:
    

    AddVehicleEvent(int timestamp, Vehicle VehicleTemplate, int lane);
    
    AddVehicleEvent();

    Vehicle getVehicle();

    int getTimeStamp();
	
	
};

#endif