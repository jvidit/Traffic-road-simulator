#include "VehiclePosition.h"
#include <utility>
#include <string>

using namespace std;

class Vehicle{

	int id;
	int length;
	int width;
	char representation;					//Think of a better name
	VehiclePosition position;

	int velocity;
	int maxVelocity;				//minimum velocity is 0....no backwards movement allowed as of now

	pair <int,int> accelerationRange;	//needs to be a multiple of 2
	int acceleration;					//needs to be a multiple of 2
	string type;

public:

	Vehicle(int length, int width, char representation, VehiclePosition Position, int id, int velocity, int maxVelocity, pair<int,int> accelerationRange, int acceleration, string type)
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

	Vehicle()
    { }



	//decides next acceleration, next velocity, next position using environment from the road. 
	//updates internal values
	//returns position of vehicle for updation in the road instance --------------- IDEA: need we return vehiclePosition or can we just update the Road here?
	//VehiclePosition updateState(Road road)
	//{	return NULL;	}


	//getters
	int getVelocity()
	{	return velocity;	}

	int getAcceleration()
	{	return acceleration;	}

	VehiclePosition getPosition()
	{	return position;	}

	char getRepresentation()
	{	return representation;		}

	int getLength()
	{	return length;		}

	int getWidth()
	{	return width;		}

	void setId(int id)
	{	this->id=id;	}

	void updatePositionVelocityAccelaration (VehiclePosition vehiclePosition, int velocity, int acceleration)
	{
		this->position=vehiclePosition;
		this->velocity=velocity;
		this->acceleration=acceleration;
	}


	void operator = (const Vehicle &vehicle)
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

};





