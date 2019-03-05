#include "Road.h"
#include "Vehicle.h"
#include "VehiclePosition.h"
#include <iostream>
#include <cmath>


class Road
{

    int id;                                                             //ID of road
    int length;                                                         //length of road, default = 100
    int width;                                                          //width of road, default = 5
    TrafficLight tl;                                                    //Traffic Light

    const int maxWidth=10;
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
    road (int length,int width,TrafficLight tl,int id)
    {
    	this.length=length;
    	this.wdith=width;
    	this.tl=tl;
    	this.id=id;
    }

    void moveVehicle(Vehicle v, VehiclePosition pos)
    //gotta make provision to display cars not in full view
    {

    	char c=v.getRep();

    	//clear vehicle from current position
    	VehiclePosition current=v.getPosition();
    	int leftPos,downPos,upPos,rightPos;

    	leftPos=max((current.rightPos-length),0);
        rightPos=min(current.rightPos,maxLength-1);
    	downPos=current.upPos+breadth;
		upPos=current.upPos;            //Note that downPos>upPos in matrix notation

    	for(int i=upPos;i<=downPos;i++)
    	{
    		for(int j=leftPos;j<=rightPos;j++)
    			arr[i][j]='-';
    	}

    	//moving to new place
        leftPos=max((pos.rightPos-length),0);
        rightPos=min(pso.rightPos,maxLength-1);
        downPos=pos.upPos+breadth;
        upPos=pos.upPos;
        
        
    	for(int i=upPos;i<=downPos;i++)
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
    	for(int i=0;i<width;i++)
    	{
    		for(int j = 0;j<length;j++)
    			cout<<arr[i][j];
    		cout<<endl;
    	}
    }
    
};
