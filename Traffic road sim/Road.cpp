#include "TrafficLight.h"
#include "VehiclePosition.h"
#include "Vehicle.h"
#include <iostream>
#include "Constants.h"


using namespace std;

class Road
{

    int id;                                                             //ID of road
    int length;                                                         //length of road, default = 100
    int width;                                                          //width of road, default = 5
    TrafficLight trafficLight;                                          //Traffic Light

    
    char positionArr[roadMaxWidth][roadMaxLength+1];                             //The road itself
    
    //initialises the array
    void initialise_arr()
    {
    	for(int i = 0;i<roadMaxWidth;i++)
    	{
    		for(int j=0;j<roadMaxLength;j++)
    			positionArr[i][j]='_';
    	}
    }
    
public:
    
    //Constructor
    Road (int length,int width,TrafficLight trafficLight,int id)
    {
    	this->length=length;
    	this->width=width;
    	this->trafficLight=trafficLight;
    	this->id=id;
    }

    void moveVehicle(Vehicle &vehicle)
    //gotta make provision to display cars not in full view
    {

    	char representation=vehicle.getRepresentation();

    	//clear vehicle from current position
    	VehiclePosition currentVehiclePosition=vehicle.getPosition();
    	int leftPos,downPos,upPos,rightPos;

        
    	leftPos=min(max(currentVehiclePosition.rightPos-currentVehiclePosition.length,0),roadMaxLength); //leftPos can be equal to rightPos
        rightPos=min(currentVehiclePosition.rightPos,roadMaxLength);
        downPos=currentVehiclePosition.upPos+currentVehiclePosition.width;
        upPos=currentVehiclePosition.upPos;            //Note that downPos>upPos in matrix notationif((currentPosition.rightPos-vehicle.getLength())<0 ) 
        if(downPos > roadMaxWidth -1) 
            throw "vehiclePosition cannot be resolved!";
        

    	for(int i=upPos;i<=downPos;i++)
    	{
    		for(int j=leftPos;j<=rightPos;j++)
    			positionArr[i][j]='-';
    	}

        VehiclePosition newVehiclePosition = vehicle.updatePositionVelocityAcceleration (length, width, trafficLight, positionArr);


    	//moving to new place
        leftPos=min(max(newVehiclePosition.rightPos-newVehiclePosition.length,0),roadMaxLength); //leftPos can be equal to rightPos
        rightPos=min(newVehiclePosition.rightPos,roadMaxLength);
        downPos=newVehiclePosition.upPos+newVehiclePosition.width;
        upPos=newVehiclePosition.upPos;            //Note that downPos>upPos in matrix notationif((currentPosition.rightPos-vehicle.getLength())<0 ) 
        if(downPos > roadMaxWidth -1) 
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

    void showRoad()
    {
    	for(int i=0;i<width;i++)
    	{
    		for(int j = 0;j<length;j++)
    			cout<<positionArr[i][j];
    		cout<<endl;
    	}
    }


    void operator = (const Road &road)
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
    
};
