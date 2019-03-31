#ifndef VEHICLE_H
#define VEHICLE_H


#include "VehiclePosition.h"
#include <utility>
#include <string>
#include "Constants.h"
#include "TrafficLight.h"
#include <vector>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


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
	int colourRed;
	int colourBlue;
	int colourGreen;
	
	bool hasRedAhead(TrafficLight tl, int time, int pos);

	bool isAttainable(double phi, char positionArr[roadMaxWidth][roadMaxLength],int roadWidth);//returns whether vehicle attain an absolute rotation of phi

	pair<double,double> attainableRange(char positionArr[roadMaxWidth][roadMaxLength],int roadWidth);//returns the range of angles in which car can move

	int getRightDistance(double phi,char positionArr[roadMaxWidth][roadMaxLength],int roadWidth, TrafficLight trafficLight,int time, int roadLength);//returns the horizontal component of distance available in the in-line path of the car


public:

	Vehicle( int id, int length, int width, char representation, VehiclePosition position, int velocity, int maxVelocity, pair<int,int> accelerationRange, int acceleration, string type, int colourRed, int colourBlue, int colourGreen);

	Vehicle();
	//decides next acceleration, next velocity, next position using environment from the road. 
	//updates internal values
	//returns position of vehicle for updation in the road instance --------------- IDEAelse if(!strcmp(toBeCompared,"defaultVehicleAcceleration"))
              
	//VehiclePosition updateState(Road road);

	//getters


	VehiclePosition getPosition();

	char getRepresentation();

    //setters
    void setId(int id);

    void setUpPos (int lane);


    VehiclePosition updatePositionVelocityAcceleration (int roadLength, int roadWidth, TrafficLight trafficLight, char positionArr[roadMaxWidth][roadMaxLength],int time,vector<Vehicle> sortedByRightPos);

    void operator = (const Vehicle &vehicle);

    void glVehicleShow(int roadWidth);
    
};


#endif
