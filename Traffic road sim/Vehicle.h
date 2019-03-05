#ifndef VEHICLE_H
#define VEHICLE_H





class Vehicle{

	int Id;
	int length;
	int breath;
	char rep;					//Think of a better name
	vehiclePosition position;

	int velocity;
	int maxVelocity;				//minimum velocity is 0....no backwards movement allowed as of now

	pair<int,int> accelerationRange;	//needs to be a multiple of 2
	int acceleration;					//needs to be a multiple of 2

public:
	Vehicle(int length, int breadth, char rep, vehiclePosition position, int Id, int velocity, int maxVelocity, pair<int,int> accelerationRange, int acceleration);



	//decides next acceleration, next velocity, next position using environment from the road. 
	//updates internal values
	//returns position of vehicle for updation in the road instance --------------- IDEA: need we return vehiclePosition or can we just update the Road here?
	vehiclePosition setParameters(Road&road);


	//getters
	int getVelocity();

	int getAcceleration();

	vehiclePosition getPosition();

	char getRep();

}


#endif