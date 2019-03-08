
#include "Vehicle.h"
#include <iostream>
             
	Vehicle::Vehicle( int id, int length, int width, char representation, VehiclePosition position, int velocity, int maxVelocity, pair<int,int> accelerationRange, int acceleration, string type)
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
	VehiclePosition Vehicle::updatePositionVelocityAcceleration (int roadLength, int roadWidth, TrafficLight trafficLight, char (&positionArr)[roadMaxWidth][roadMaxLength+1])
	{
		
		bool canMove=true;
		for(int i=position.upPos;i<=position.upPos+width-1;i++)
		{
			cout<<positionArr[i][position.rightPos+1]<<" ";
			if(positionArr[i][position.rightPos+1]!='_')
			{
				canMove=false;
				break;
			}
		}
		cout<<"vehicle id "<<id<<" "<<canMove<<endl;
		if(canMove)
			acceleration= 1-velocity;	//if vel=0, then acc=1. if vel=0, then acc=1
		else
			acceleration= -velocity;	//if vel=0, then acc=0. if vel=1, then acc=-1
		
		velocity+=acceleration;
		position.rightPos+=velocity;
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







