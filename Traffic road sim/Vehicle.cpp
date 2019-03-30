#include "Vehicle.h"
#include <iostream>

             
	Vehicle::Vehicle( int id, int length, int width, char representation, VehiclePosition position, int velocity, int maxVelocity, pair<int,int> accelerationRange, int acceleration, string type, int colourRed, int colourGreen, int colourBlue)
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
		this->colourRed=colourRed;
		this->colourBlue=colourBlue;
		this->colourGreen=colourGreen;
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



	bool Vehicle::hasRedAhead(TrafficLight tl, int time, int nextDistance)
	{
		return (tl.isRed(time) && (position.rightPos+nextDistance)==tl.getPosition());
	}


    // notice the order of update 
    // execute once at time 0 
	VehiclePosition Vehicle::updatePositionVelocityAcceleration (int roadLength, int roadWidth, TrafficLight trafficLight, char positionArr[roadMaxWidth][roadMaxLength], int time, vector<Vehicle> sortedByRightPos)
	{
		int nextDistance=0,nextVelocity,nextAcceleration,laneShift=0;	

		bool considerOverTaking=false;
		int expectedDistance=max(this->velocity, maxVelocity/2); 	
		int rightPos=position.rightPos;
		int upPos=position.upPos;
		int downPos=upPos+width-1;


		while(nextDistance<=maxVelocity)
		{
			int flag=0;
			for(int i=upPos;i<=downPos;i++)
			{
				if(hasRedAhead(trafficLight, time, nextDistance))						//Traffic light is red ahead 
				{
					flag=1;
					break;
				}
				if((positionArr[i][rightPos + 1 + nextDistance*alpha] != '-'))		//Has a car ahead
				{
					if(expectedDistance>nextDistance)
						considerOverTaking=true;
					flag=1;
					break;
				}
			}
			if(flag)
				break;
			nextDistance++;
		}

		//cout<<"In Vehicle "+type+" "<<expectedDistance<<" "<<nextDistance<<" "<<considerOverTaking*987<<endl; 

		//Note: the vehicle will attempt only 2 lanes of overtaking at one time instant, also it will prefer to overtake from the right
		//In our model, that implies an increase in the lane position of the car
		/*if(considerOverTaking)
		{
			int dist[5*alpha];										//disti is the distance available in lane[downPos+i-2]
			for(int ind=-2*alpha;ind<=2*alpha;ind++)
			{
				if(upPos+ind<0 || downPos+ind>=roadWidth)
				{
					dist[ind+2*alpha]=0;
					continue;
				}
				int temp_dist=0;
				while(temp_dist<=maxVelocity)
				{
					int flag=0;
					for(int i=upPos+ind;i<=downPos+ind;i++)
					{
						if(hasRedAhead(trafficLight, time, temp_dist) || (positionArr[i][rightPos + 1 + temp_dist] != '-'))
						{
							flag=1;
							break;
						}
					}
					if(flag)
						break;
					temp_dist++;
				}
				dist[ind+2*alpha]=min(temp_dist,maxVelocity);
			}

			int priority[5]={-2,-1,2,1,0};
			for(int i=0;i<5;i++)
			{
				int temp_dist=dist[priority[i]+2*alpha];
				if(temp_dist>=nextDistance || temp_dist>=expectedDistance)		
				{	
					laneShift=priority[i];
					nextDistance=temp_dist;
				}
			}
		}

		*/
		nextDistance=min(maxVelocity,nextDistance);		
		nextVelocity=nextDistance;									//next distance is always less then or equal to maxVelocity
		nextAcceleration =  min(  max((nextVelocity - (this->velocity)),(this->accelerationRange).first) , (this->accelerationRange).second);
		
		acceleration=nextAcceleration;
		this->velocity+=acceleration;
		position.rightPos+=this->velocity;

		position.upPos+=laneShift;
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
		colourRed=vehicle.colourRed;
		colourBlue=vehicle.colourBlue;
		colourGreen=vehicle.colourGreen;
	}

	void Vehicle::glVehicleShow(int roadWidth)
	{
		
	 	int upPos = (roadWidth-position.upPos) - spacingFact*alpha;
	 	int rightPos = (position.rightPos+1) - spacingFact*alpha;
	 	int downPos = (upPos-width) + 2*spacingFact*alpha;
	 	int leftPos = (rightPos-length) + spacingFact*alpha;
	 	glLoadIdentity();
	 	glColor3f(colourRed,colourGreen,colourBlue);
	 	glBegin(GL_POLYGON);
   		glVertex2i(leftPos,upPos);
   		glVertex2i(leftPos,downPos);
   		glVertex2i(rightPos,downPos);
   		glVertex2i(rightPos,upPos);
   		glEnd();	


	}




