
#include "VehiclePosition.h"
#include "Road.h"
#include <utility>
#include <string>



class Vehicle{

	int id;
	int length;
	int breath;
	char rep;					//Think of a better name
	vehiclePosition position;

	int velocity;
	int maxVelocity;				//minimum velocity is 0....no backwards movement allowed as of now

	pair<int,int> accelerationRange;	//needs to be a multiple of 2
	int acceleration;					//needs to be a multiple of 2
	string type;

public:

	Vehicle(int length, int breadth, char rep, vehiclePosition position, int id, int velocity, int maxVelocity, pair<int,int> accelerationRange, int acceleration, string type)
	{

		//If error arises, consider allocating space for user defined objects
		this.length=length;
		this.breadth=breath;
		this.rep=rep;
		this.position=position;
		this.id=id;
		this.velocity=velocity;
		this.maxVelocity=maxVelocity;
		this.accelerationRange=accelerationRange;
		this.acceleration=acceleration;
		this.type = type;
	}



	//decides next acceleration, next velocity, next position using environment from the road. 
	//updates internal values
	//returns position of vehicle for updation in the road instance --------------- IDEA: need we return vehiclePosition or can we just update the Road here?
	vehiclePosition setParameters(Road&road);


	//getters
	int getVelocity()
	{	return velocity;	}

	int getAcceleration()
	{	return acceleration;	}

	vehiclePosition getPosition()
	{	return position;	}

	char getRep();
	{	return rep;		}

	void setId(int id)
	{	this.id=id;	}

}





