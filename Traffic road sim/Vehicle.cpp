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



	//decides next acceleration, next velocity, next position using environment from the road. 
	//updates internal values
	//returns position of vehicle for updation in the road instance --------------- IDEA: need we return vehiclePosition or can we just update the Road here?
	//VehiclePosition updateState(Road road)
	//{	return NULL;	}


	//getters
	int Vehicle::getVelocity()
	{	return velocity;	}

	int Vehicle::getAcceleration()
	{	return acceleration;	}

	VehiclePosition Vehicle::getPosition()
	{	return position;	}

	char Vehicle::getRepresentation()
	{	return representation;		}

	int Vehicle::getLength()
	{	return length;		}

	int Vehicle::getWidth()
	{	return width;		}

	void Vehicle::setId(int id)
	{	this->id=id;	}

	void Vehicle::updatePositionVelocityAccelaration (VehiclePosition vehiclePosition, int velocity, int acceleration)
	{
		this->position=vehiclePosition;
		this->velocity=velocity;
		this->acceleration=acceleration;
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







