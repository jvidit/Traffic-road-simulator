#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "VehiclePosition.h"
#include <utility>
#include <string>

using namespace std;

const int roadMaxWidth = 20;
const int roadMaxLength = 1000;
const int simulationTimeDuration = 1;
const string configFile = "config.ini";

class SpecConsts
{
public:

	int defaultRoadId;                                                             //ID of road
	int defaultRoadLength;                                                         //length of road
	int defaultRoadWidth;        
                                                  //width of road
	int defaultTrafficLightId;                                                     //ID of traffic light
	int defaultTrafficLightPosition;
	int defaultTrafficLightRedPeriod;
	int defaultTrafficLightGreenPeriod;
	int defaultTrafficLightRedFirst;


    int defaultVehicleId;
    int defaultVehicleLength;
    int defaultVehicleWidth;
    char defaultVehicleRepresentation;       
    VehiclePosition defaultVehiclePosition;
    int defaultVehicleVelocity;
    int defaultVehicleMaxVelocity;           //minimum velocity is 0....no backwards movement allowed as of now
    pair<int,int> defaultVehicleAccelerationRange;  //needs to be a multiple of 2
    int defaultVehicleAcceleration;          //needs to be a multiple of 2


    SpecConsts();
};


#endif