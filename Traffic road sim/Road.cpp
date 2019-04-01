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

        
        leftPos=(int)(vehiclePosition.backmidx); 
        rightPos=(int)(leftPos+vehiclePosition.length-1);
        downPos=(int)(vehiclePosition.backmidy+vehiclePosition.width/2-1);
        upPos=(int)(downPos-vehiclePosition.width+1);            //Note that downPos>upPos in matrix notationif((currentPosition.rightPos-vehicle.getLength())<0 ) 

        cout<<"\n"<<leftPos<<" "<<rightPos<<" "<<downPos<<" "<<upPos;
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
        VehiclePosition position = vehicle.getPosition();
        double ptx=position.backmidy,pty=position.backmidx,l=position.length,w=position.width;
        double ang = position.theta;
        double d1=(-w/2);
        while(d1!=(w/2))
        {
            double ptx1=ptx+d1*cos(ang*pi/180);              //x moves along with lanes
            double pty1=pty+d1*sin(ang*pi/180);              //y moves along road length
     
         
            double d2=0;
            while(d2!=l)
            {

                double ptx2=ptx1-d2*sin(ang*pi/180);
                double pty2=max((double)0,(pty1+d2*cos(ang*pi/180)));
                positionArr[(int)ptx2][(int)pty2]='-';
                
                d2++;
            }
            d1++;
        }



    }

    void Road::moveVehicle(Vehicle &vehicle, int time, vector<Vehicle> sortedByRightPos)
    {


    	char representation=vehicle.getRepresentation();
        
        this->removeVehicle(vehicle);

        VehiclePosition newVehicleposition = vehicle.updatePositionVelocityAcceleration (length, width, trafficLight, positionArr, time, sortedByRightPos);

    //moving to new place
       
        double ptx=newVehicleposition.backmidy,pty=newVehicleposition.backmidx,l=newVehicleposition.length,w=newVehicleposition.width;
        double ang = newVehicleposition.theta;
        double d1=(-w/2);
        while(d1!=(w/2))
        {
            double ptx1=ptx+d1*cos(ang*pi/180);              //x moves along with lanes
            double pty1=pty+d1*sin(ang*pi/180);              //y moves along road length
     
         
            double d2=0;
            while(d2!=l)
            {

                double ptx2=ptx1-d2*sin(ang*pi/180);
                double pty2=max((double)0,(pty1+d2*cos(ang*pi/180)));
                positionArr[(int)ptx2][(int)pty2]=representation;
                
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


















