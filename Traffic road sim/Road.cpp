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
        int upPos,rightPos;

        
        
        rightPos=min(currentVehiclePosition.rightPos,length-1);
        upPos=currentVehiclePosition.upPos;            //Note that downPos>upPos in matrix notationif((currentPosition.rightPos-vehicle.getLength())<0 ) 
        /*
        if(downPos > width -1) 
            throw "vehiclePosition cannot be resolved!";
        */

        int ptx=upPos,pty=rightPos,l=currentVehiclePosition.length,w=currentVehiclePosition.width;
        double ang = currentVehiclePosition.theta;
        int d1=0;
        
        while(d1!=w)
        {
            int ptx1=ptx+d1*cos(ang*3.14/180);              //x moves along with lanes
            int pty1=pty+d1*sin(ang*3.14/180);              //y moves along road length
            
            int d2=0;
            while(d2!=l)
            {


                
                int ptx2=max(0,int(ptx1+d2*sin(ang*3.14/180)));
                int pty2=max(0,int(pty1-d2*cos(ang*3.14/180)));
               
                positionArr[ptx2][pty2]='-';
                d2++;
            }
            d1++;
        }

    }

    void Road::moveVehicle(Vehicle &vehicle, int time, vector<Vehicle> sortedByRightPos)
    {


    	char representation=vehicle.getRepresentation();
        int upPos,rightPos;

        this->removeVehicle(vehicle);

        VehiclePosition newVehiclePosition = vehicle.updatePositionVelocityAcceleration (length, width, trafficLight, positionArr, time, sortedByRightPos);

    //moving to new place
        
        rightPos=min(newVehiclePosition.rightPos,length-1);
        upPos=newVehiclePosition.upPos;            //Note that downPos>upPos in matrix notationif((currentPosition.rightPos-vehicle.getLength())<0 ) 
        

        /*
        if(downPos > width -1) 
            throw "vehiclePosition cannot be resolved!";
        */


        int ptx=upPos,pty=rightPos,l=newVehiclePosition.length,w=newVehiclePosition.width;
        double ang = newVehiclePosition.theta;
        int d1=0;
        while(d1!=w)
        {
            int ptx1=ptx+d1*cos(ang*3.14/180);              //x moves along with lanes
            int pty1=pty+d1*sin(ang*3.14/180);              //y moves along road length
        
            
            int d2=0;
            while(d2!=l)
            {

                int ptx2=max(0,int(ptx1+d2*sin(ang*3.14/180)));
                int pty2=max(0,int(pty1-d2*cos(ang*3.14/180)));
            
                positionArr[ptx2][pty2]=representation;
                d2++;
            }
            d1++;
        }


    }

    void Road::showRoad(int time)
    {
    	
        if(trafficLight.isRed(time))
        {
            for(int i=0;i<width;i++)
            {
                for(int j = 0;j<length;j++)
                    {
                        if ((i%alpha==0) &&(j==trafficLight.getPosition()))
                        cout<<positionArr[i][j]<<'|';
                        else if((i%alpha==0) && (j%alpha==0))
                        cout<<positionArr[i][j];
                    }
                if(i%alpha==0)
                    cout<<endl;
            }
        }
        else
        {
            for(int i=0;i<width;i++)
            {
                for(int j = 0;j<length;j++)
                        if((i%alpha==0) && (j%alpha==0))
                        cout<<positionArr[i][j];
                if(i%alpha==0)
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
        
        int trafficLightPosition = (trafficLight.getPosition()+1);
        if(trafficLight.isRed(t))
            glColor3f(1,0,0);
        else
            glColor3f(0,1,0);
        glLoadIdentity();
        glBegin(GL_POLYGON);
        glVertex2i(trafficLightPosition,width);
        glVertex2i(trafficLightPosition,0);
        glVertex2i(trafficLightPosition+(alpha+5)/5,0);
        glVertex2i(trafficLightPosition+(alpha+5)/5,width);
        glEnd();    
     }


















