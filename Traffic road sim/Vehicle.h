#ifndef VEHICLE_H
#define VEHICLE_H


#include "VehiclePosition.h"
#include <utility>
#include <string>
#include "Constants.h"
#include "TrafficLight.h"


using namespace std;

class Vehicle{

	int id;
	int length;
	int width;
	char representation;					
	VehiclePosition position;
    int velocity;
	int maxVelocity;				    //minimum velocity is 0...no backwards movement allowed as of now
	pair <int,int> accelerationRange;	//needs to be a multiple of 2
	int acceleration;					//needs to be a multiple of 2
	string type;

public:

	Vehicle( int id, int length, int width, char representation, VehiclePosition position, int velocity, int maxVelocity, pair<int,int> accelerationRange, int acceleration, string type);

	Vehicle();
	//decides next acceleration, next velocity, next position using environment from the road. 
	//updates internal values
	//returns position of vehicle for updation in the road instance --------------- IDEA: need we return vehiclePosition or can we just update the Road here?

	//VehiclePosition updateState(Road road);

	//getters


	VehiclePosition getPosition();

	char getRepresentation();

    //setters
    void setId(int id);

    void setUpPos (int lane);

    VehiclePosition updatePositionVelocityAcceleration (int roadLength, int roadWidth, TrafficLight trafficLight, char positionArr[roadMaxWidth][roadMaxLength],int time);

    void operator = (const Vehicle &vehicle);
    
};


#endif
