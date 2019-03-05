#include "Road.h"
#include "Vehicle.h"
#include "vehiclePosition.h"
#include <iostream>
#include <cmath>


class Road
{

    int id;                                                             //ID of road
    int length;                                                         //length of road, default = 100
    int width;                                                          //width of road, default = 5
    TrafficLight tl;                                                    //Traffic Light

    const int maxLanes=10;
    const int maxLength=1000;
    char arr[maxLanes][maxLength];                                                 //The road itself
    
    //initialises the array
    void initialise_arr()
    {
    	for(int i = 0;i<maxLanes;i++)
    	{
    		for(int j=0;j<maxLength;j++)
    			arr[i][j]='_';
    	}
    }
    
public:
    
    //Constructor
    road (int length,int width,trafficLight tl,int id)
    {
    	this.length=length;
    	this.wdith=width;
    	this.tl=tl;
    	this.id=id;
    }

    void moveVehicle(Vehicle v, vehiclePosition pos)
    //gotta make provision to display cars not in full view
    {

    	char c=v.getRep();

    	//clear vehicle from current position
    	vehiclePosition current=v.getPosition();
    	int leftPos,downPos,upPos,rightPos;

    	leftPos=max((current.rightPos-length),0);
    	downPos=max((current.upPos-breadth),0);
		upPos=min(current.upPos,maxLanes-1);
    	rightPos=min(current.rightPos,maxLength-1);

    	for(int i=downPos;i<=upPos;i++)
    	{
    		for(int j=leftPos;j<=rightPos;j++)
    			arr[i][j]='-';
    	}

    	//moving to new place
    	leftPos=max((pos.rightPos-length),0);
    	downPos=max((pos.upPos-breadth),0);
		upPos=min(pos.upPos,maxLanes-1);
    	rightPos=min(pos.rightPos,maxLength-1);

    	for(int i=downPos;i<=upPos;i++)
    	{
    		for(int j=leftPos;j<=rightPos;j++)
    		{
    			/////RAISE ERROR HERE TO HANDLE COLLISIONS
    			arr[i][j]=c;
    		}
    	}
    }

    void showRoad()
    {
    	for(int i=width-1;i>=0;i--)
    	{
    		for(int j = 0;j<length;j++)
    			cout<<arr[i][j];
    		cout<<endl;
    	}
    }
    
};
