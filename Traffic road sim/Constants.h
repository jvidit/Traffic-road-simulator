#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "VehiclePosition.h"
#include <utility>
#include <string>

using namespace std;

const int roadMaxWidth = 200;
const int roadMaxLength = 2000;
const int simulationTimeDuration = 1;
const int alpha = 30;
const float spacingFact = 0.1;
const int pauseTime = 100;
const double turningRange = 60;
const double turningShift = 5;
const double angularVelocity = 2;

class SpecConsts
{
public:

	int defaultRoadId;                                                             //ID of road
	int defaultRoadLength;                                                         //length of road
	int defaultRoadWidth;        
                                                  //width of road
	int defaultTrafficLightId;                                                     //ID of traffic light
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
    pair<int,int> defaultVehicleAccelerationRange;  
    int defaultVehicleAcceleration;  
    int defaultVehicleColourRed;
    int defaultVehicleColourGreen;
    int defaultVehicleColourBlue;      

    int maxAllowedVelocity;
    int minAllowedAcceleration;
    int maxAllowedAcceleration;


    SpecConsts();
};


#endif