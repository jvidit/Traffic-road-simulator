#include "Road.h"
#include <iostream>

    Road::Road (int length,int width,TrafficLight trafficLight,int id)
    {
    	this->length=length;
    	this->width=width;
    	this->trafficLight=trafficLight;
    	this->id=id;
    }

    Road::Road()
    { }

    void Road::moveVehicle(Vehicle &vehicle)
    //gotta make provision to display cars not in full view
    {

    	char representation=vehicle.getRepresentation();

    	//clear vehicle from current position
    	VehiclePosition currentPosition=vehicle.getPosition();
    	int leftPos,downPos,upPos,rightPos,length,width;

        length = vehicle.getLength();
        width = vehicle.getWidth();

    	leftPos=max((currentPosition.rightPos-length),0);
        rightPos=min(currentPosition.rightPos,maxLength-1);
    	downPos=currentPosition.upPos+width;
		upPos=currentPosition.upPos;            //Note that downPos>upPos in matrix notation

    	for(int i=upPos;i<=downPos;i++)
    	{
    		for(int j=leftPos;j<=rightPos;j++)
    			postitionArr[i][j]='-';
    	}

    	//moving to new place
        //leftPos=max((vehiclePosition.rightPos-length),0);
        //rightPos=min(vehiclePosition.rightPos,maxLength-1);
        //downPos=vehiclePosition.upPos+width;
        //upPos=vehiclePosition.upPos;
        
        
    	//for(int i=upPos;i<=downPos;i++)
    	//{
    	//	for(int j=leftPos;j<=rightPos;j++)
    	//	{
    			/////RAISE ERROR HERE TO HANDLE COLLISIONS
    		//	postitionArr[i][j]=representation;
    	//	}
    	//}

        


        //vehicle.updatePositionVelocityAccelaration (position, velocity, acceleration)
    }

    void Road::showRoad()
    {
    	for(int i=0;i<width;i++)
    	{
    		for(int j = 0;j<length;j++)
    			cout<<postitionArr[i][j];
    		cout<<endl;
    	}
    }


    void Road::operator = (const Road &road)
    {
        id=road.id;
        length=road.length;
        width=road.width;
        trafficLight=road.trafficLight;
        for(int i = 0;i<maxWidth;i++)
        {
            for(int j=0;j<maxLength;j++)
                postitionArr[i][j]=road.postitionArr[i][j];
        }
    }
    

