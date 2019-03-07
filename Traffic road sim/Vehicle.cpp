
#include "Vehicle.h"

             
	Vehicle::Vehicle( int id, int length, int width, char representation, VehiclePosition Position, int velocity, int maxVelocity, pair<int,int> accelerationRange, int acceleration, string type)
	{

		//If error arises, consider allocating space for user defined objects
		this->length=length;
		this->width=width;
		this->representation=representation;
		this->position=position;
		this->id=id;
		this->velocity=velocity;
		this->maxVelocity=maxVelocity;
		this->accelerationRange=accelerationRange;
		this->acceleration=acceleration;
		this->type=type;
	}

	Vehicle::Vehicle()
    { }


	//getters


	VehiclePosition Vehicle::getPosition()
	{	return this->position;	}

	char Vehicle::getRepresentation()
	{	return representation;		}


	void Vehicle::setId(int id)
	{	this->id=id;	}



    // notice the order of update 
    // execute once at time 0 
	VehiclePosition Vehicle::updatePositionVelocityAcceleration (int roadLength, int roadWidth, TrafficLight trafficLight, char positionArr[roadMaxWidth][roadMaxLength+1])
	{
		
		if(position.rightPos >=  roadLength) 
		{
			velocity = 0;
			acceleration = 0;
		}
		else
		{
			acceleration = 2; //decide accelaration
			velocity = velocity + acceleration*simulationTimeDuration;
			position.rightPos = position.rightPos  + 0.5*acceleration*simulationTimeDuration*simulationTimeDuration;
		}
		return position;
	}


	void Vehicle::operator = (const Vehicle &vehicle)
	{
		length=vehicle.length;
		width=vehicle.width;
		representation=vehicle.representation;
		position=vehicle.position;
		id=vehicle.id;
		velocity=vehicle.velocity;
		maxVelocity=vehicle.maxVelocity;
		accelerationRange=vehicle.accelerationRange;
		acceleration=vehicle.acceleration;
		type=vehicle.type;
	}







