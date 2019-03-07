#ifndef SPECIFICATIONS_H
#define SPECIFICATIONS_H

#include <map>
#include <utility> 
#include <vector>
#include <cstring>
#include "TrafficLight.h"
#include "Road.h"
#include "Vehicle.h"
#include "VehiclePosition.h"
#include "Constants.h"


class Specifications
{
	int id;
	TrafficLight trafficLightTemplate;
	Road roadTemplate;
	map<string,Vehicle> vehicleTemplates;

public:	

    Specifications();
	void addRoadAndTrafficLightTemplate ( vector<pair<string,int> > roadAndTrafficLightSpecs);
    void addDefaultVehicleSpecs(vector<pair<string,int> > defaultVehicleSpecs);
	void addVehicleTemplate (string vehicleType, vector<pair<string,int> > vehicleSpecs);
    void operator = (const Specifications &specs);
    Road getRoadTemplate();
    Vehicle getVehicleTemplate(string vehicleType);

};

#endif
