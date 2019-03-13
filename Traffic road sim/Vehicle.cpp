
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
	VehiclePosition Vehicle::updatePositionVelocityAcceleration (int roadLength, int roadWidth, TrafficLight trafficLight, char positionArr[roadMaxWidth][roadMaxLength], int time)
	{
		
		int nextDistance=0,nextVelocity,nextAcceleration;										
		int rightPos=position.rightPos;

		while(nextDistance<=maxVelocity)
		{
			int flag=0;
			for(int i=position.upPos;i<=position.upPos+width-1;i++)
			{
				if((trafficLight.isRed(time) && (rightPos+nextDistance)==trafficLight.getPosition()) || (positionArr[i][position.rightPos + 1 + nextDistance] != '-'))
				{
					flag=1;
					break;
				}
			}
			if(flag)
				break;
			nextDistance++;
		}

		nextDistance=min(maxVelocity,nextDistance);		
		nextVelocity=nextDistance;									//next distance is always less then or equal to maxVelocity
		nextAcceleration =  min(  max((nextVelocity - (this->velocity)),(this->accelerationRange).first) , (this->accelerationRange).second);
		
		acceleration=nextAcceleration;
		this->velocity+=acceleration;
		position.rightPos+=velocity;
		//need to consider collisions here

		return position;
	}

	void Vehicle::setUpPos (int lane)
	{
		position.upPos = lane;

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


	 void Vehicle::glVehicleShow(int roadWidth)
	 {
	 	
	 	int upPos = alpha*(roadWidth-position.upPos);
	 	int rightPos = alpha*position.rightPos;
	 	int downPos = (upPos-alpha*width);
	 	int leftPos = (rightPos-alpha*length);
	 	
	 	glColor3f(0,0,1);
	 	glLoadIdentity();
	 	glBegin(GL_POLYGON);
   		glVertex2i(leftPos,upPos);
   		glVertex2i(leftPos,downPos);
   		glVertex2i(rightPos,downPos);
   		glVertex2i(rightPos,upPos);
   		glEnd();	
	 }




