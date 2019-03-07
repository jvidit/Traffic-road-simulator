#ifndef ADDVEHICLEEVENT_H
#define ADDVEHICLEEVENT_H

#include "Vehicle.h"

class AddVehicleEvent
{
    int timestamp; //time instant of event
    Vehicle vehicle;
    static int id;
    
public:
    

    AddVehicleEvent(int timestamp, Vehicle VehicleTemplate, int lane);
    
    AddVehicleEvent();

    Vehicle getVehicle();

    int getTimeStamp();
	
	
};

#endif