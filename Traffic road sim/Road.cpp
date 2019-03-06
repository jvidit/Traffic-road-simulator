

#include "Road.h"


const int maxWidth=20;
const int maxLength=1000;

using namespace std;

class Road
{

    int id;                                                             //ID of road
    int length;                                                         //length of road, default = 100
    int width;                                                          //width of road, default = 5
    TrafficLight trafficLight;                                          //Traffic Light

    
    char postitionArr[maxWidth][maxLength];                             //The road itself
    
    //initialises the array
    void initialise_arr()
    {
    	for(int i = 0;i<maxWidth;i++)
    	{
    		for(int j=0;j<maxLength;j++)
    			postitionArr[i][j]='_';
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

    void moveVehicle(Vehicle v, VehiclePosition pos)
    //gotta make provision to display cars not in full view
    {

    	char c=v.getRep();

    	//clear vehicle from current position
    	VehiclePosition current=v.getPosition();
    	int leftPos,downPos,upPos,rightPos;

    	leftPos=max((current.rightPos-length),0);
        rightPos=min(current.rightPos,maxLength-1);
    	downPos=current.upPos+width;
		upPos=current.upPos;            //Note that downPos>upPos in matrix notation

    	for(int i=upPos;i<=downPos;i++)
    	{
    		for(int j=leftPos;j<=rightPos;j++)
    			postitionArr[i][j]='-';
    	}

    	//moving to new place
        leftPos=max((pos.rightPos-length),0);
        rightPos=min(pso.rightPos,maxLength-1);
        downPos=pos.upPos+width;
        upPos=pos.upPos;
        
        
    	for(int i=upPos;i<=downPos;i++)
    	{
    		for(int j=leftPos;j<=rightPos;j++)
    		{
    			/////RAISE ERROR HERE TO HANDLE COLLISIONS
    			postitionArr[i][j]=c;
    		}
    	}
    }

    void showRoad()
    {
    	for(int i=0;i<width;i++)
    	{
    		for(int j = 0;j<length;j++)
    			cout<<postitionArr[i][j];
    		cout<<endl;
    	}
    }
    
};
