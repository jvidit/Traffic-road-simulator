#include "Road.h"
#include <iostream>
    
    void Road::initialise_positionArr()
    {
        for(int i=0;i<width;i++)
        {
            for(int j=0;j<length;j++)
            {
                /////RAISE ERROR HERE TO HANDLE COLLISIONS
                positionArr[i][j]='-';
            }
        }
    }

    Road::Road (int length,int width,TrafficLight trafficLight,int id)
    {
    	this->length=length;
    	this->width=width;
    	this->trafficLight=trafficLight;
    	this->id=id;
        this->initialise_positionArr();
    }

    Road::Road()
    {
       this->initialise_positionArr(); 
    }

    void Road::moveVehicle(Vehicle &vehicle)
    {

    	char representation=vehicle.getRepresentation();

    	//clear vehicle from current position
    	VehiclePosition currentVehiclePosition=vehicle.getPosition();
    	int leftPos,downPos,upPos,rightPos;

        
    	leftPos=max(currentVehiclePosition.rightPos-currentVehiclePosition.length+1,0); 
        rightPos=min(currentVehiclePosition.rightPos,length);
        downPos=currentVehiclePosition.upPos+currentVehiclePosition.width-1;
        upPos=currentVehiclePosition.upPos;            //Note that downPos>upPos in matrix notationif((currentPosition.rightPos-vehicle.getLength())<0 ) 
        if(downPos > width -1) 
            throw "vehiclePosition cannot be resolved!";
        

    	for(int i=upPos;i<=downPos;i++)
    	{
    		for(int j=leftPos;j<=rightPos;j++)
    			positionArr[i][j]='_';
    	}

        VehiclePosition newVehiclePosition = vehicle.updatePositionVelocityAcceleration (length, width, trafficLight, positionArr);


    	//moving to new place
        leftPos=max(newVehiclePosition.rightPos-newVehiclePosition.length+1,0); 
        rightPos=min(newVehiclePosition.rightPos,length);
        downPos=newVehiclePosition.upPos+newVehiclePosition.width-1;
        upPos=newVehiclePosition.upPos;            //Note that downPos>upPos in matrix notationif((currentPosition.rightPos-vehicle.getLength())<0 ) 
        if(downPos > width -1) 
            throw "vehiclePosition cannot be resolved!";
        
        
    	for(int i=upPos;i<=downPos;i++)
    	{
    		for(int j=leftPos;j<=rightPos;j++)
    		{
    			/////RAISE ERROR HERE TO HANDLE COLLISIONS
    			positionArr[i][j]=representation;
    	}

    }

        

    }

    void Road::showRoad()
    {
    	for(int i=0;i<width;i++)
    	{
    		for(int j = 0;j<length;j++)
    			cout<<positionArr[i][j];
    		cout<<endl;
    	}
    }


    void Road::operator = (const Road &road)
    {
        id=road.id;
        length=road.length;
        width=road.width;
        trafficLight=road.trafficLight;
        for(int i = 0;i<roadMaxWidth;i++)
        {
            for(int j=0;j<roadMaxLength;j++)
                positionArr[i][j]=road.positionArr[i][j];
        }
    }
    

