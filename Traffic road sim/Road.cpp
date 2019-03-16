#include "Road.h"
#include <iostream>
#include <vector>
    
    void Road::initialise_positionArr()
    {
        for(int i=0;i<roadMaxWidth;i++)
        {
            for(int j=0;j<roadMaxLength;j++)
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

    void Road::addVehicle(Vehicle &vehicle)
    {


        char representation=vehicle.getRepresentation();
        

        //clear vehicle from current position
        VehiclePosition vehiclePosition=vehicle.getPosition();
        int leftPos,downPos,upPos,rightPos;

        
        leftPos=max(vehiclePosition.rightPos-vehiclePosition.length+1,0); 
        rightPos=min(vehiclePosition.rightPos,length);
        downPos=vehiclePosition.upPos+vehiclePosition.width-1;
        upPos=vehiclePosition.upPos;            //Note that downPos>upPos in matrix notationif((currentPosition.rightPos-vehicle.getLength())<0 ) 
        /*
        if(downPos > width -1) 
            throw "vehiclePosition cannot be resolved!";
        */
        
        for(int i=upPos;i<=downPos;i++)
        { 
            for(int j=leftPos;j<=rightPos;j++)
            {
                /////RAISE ERROR HERE TO HANDLE COLLISIONS
                
                positionArr[i][j]=representation;

           }

        }

        

    }

    void Road::removeVehicle(Vehicle &vehicle)
    {
        
        //clear vehicle from current position
        VehiclePosition currentVehiclePosition=vehicle.getPosition();
        int leftPos,downPos,upPos,rightPos;

        
        leftPos=max(currentVehiclePosition.rightPos-currentVehiclePosition.length+1,0); 
        rightPos=min(currentVehiclePosition.rightPos,length);
        downPos=currentVehiclePosition.upPos+currentVehiclePosition.width-1;
        upPos=currentVehiclePosition.upPos;            //Note that downPos>upPos in matrix notationif((currentPosition.rightPos-vehicle.getLength())<0 ) 
        /*
        if(downPos > width -1) 
            throw "vehiclePosition cannot be resolved!";
        */

        for(int i=upPos;i<=downPos;i++)
        {
            for(int j=leftPos;j<=rightPos;j++)
                positionArr[i][j]='-';
        }
    }

    void Road::moveVehicle(Vehicle &vehicle, int time, vector<Vehicle> sortedByRightPos)
    {


    	char representation=vehicle.getRepresentation();
        int leftPos,downPos,upPos,rightPos;

    	this->removeVehicle(vehicle);

        VehiclePosition newVehiclePosition = vehicle.updatePositionVelocityAcceleration (length, width, trafficLight, positionArr, time, sortedByRightPos);

    	//moving to new place
        leftPos=max(newVehiclePosition.rightPos-newVehiclePosition.length+1,0); 
        rightPos=min(newVehiclePosition.rightPos,length);
        downPos=newVehiclePosition.upPos+newVehiclePosition.width-1;
        upPos=newVehiclePosition.upPos;            //Note that downPos>upPos in matrix notationif((currentPosition.rightPos-vehicle.getLength())<0 ) 
        

        /*
        if(downPos > width -1) 
            throw "vehiclePosition cannot be resolved!";
        */
        

    	for(int i=upPos;i<=downPos;i++)
    	{ 
    		for(int j=leftPos;j<=rightPos;j++)
    		{
    			/////RAISE ERROR HERE TO HANDLE COLLISIONS
                
    			positionArr[i][j]=representation;

    	   }

        }

        

    }

    void Road::showRoad(int time)
    {
    	
        if(trafficLight.isRed(time))
        {
            for(int i=0;i<width;i++)
            {
                for(int j = 0;j<length;j++)
                    if (j==trafficLight.getPosition())
                        cout<<positionArr[i][j]<<'|';
                    else
                        cout<<positionArr[i][j];
                cout<<endl;
            }
        }
        else
        {
            for(int i=0;i<width;i++)
            {
                for(int j = 0;j<length;j++)
                        cout<<positionArr[i][j];
                cout<<endl;
            }
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

    int Road::getLength()
    {   return length;     }

    int Road::getWidth()
    {   return width;     }


    void Road::glRoadTrafficLightShow(int t)
     {
        
        int trafficLightPosition = alpha*(trafficLight.getPosition()+1);
        if(trafficLight.isRed(t))
            glColor3f(1,0,0);
        else
            glColor3f(0,1,0);
        glLoadIdentity();
        glBegin(GL_POLYGON);
        glVertex2i(trafficLightPosition,alpha*width);
        glVertex2i(trafficLightPosition,0);
        glVertex2i(trafficLightPosition+(alpha+5)/5,0);
        glVertex2i(trafficLightPosition+(alpha+5)/5,alpha*width);
        glEnd();    
     }


















