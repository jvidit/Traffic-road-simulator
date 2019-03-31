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
    {    return this->position;    }

    char Vehicle::getRepresentation()
    {    return representation;        }

    bool Vehicle::isAttainable(double phi, char positionArr[roadMaxWidth][roadMaxLength],int roadWidth)
    {

        int ptx=position.upPos,pty=position.rightPos,l=position.length,w=position.width;
        double ang = phi;
        int d1=0;
        while(d1!=w)
        {
            int ptx1=ptx+d1*cos(ang*3.14/180);                //x moves along with lanes
            int pty1=pty+d1*sin(ang*3.14/180);                //y moves along road length
        
            
            int d2=0;
            while(d2!=l)
            {

                int ptx2=ptx1+d2*sin(ang*3.14/180);
                if(ptx2<0 || ptx2>=roadWidth)
                    return false;

                int pty2=max(0,int(pty1-d2*cos(ang*3.14/180)));
                
                if(positionArr[ptx2][pty2]!='-')
                    return false;

                d2++;
            }
            d1++;
        }
        return true;
    }


    pair<double,double> Vehicle::attainableRange(char positionArr[roadMaxWidth][roadMaxLength],int roadWidth)
    {
        double theta=position.theta;
        pair<double,double> ans = make_pair(theta,theta);
         
        while(theta!=turningRange)
        {  
            theta+=turningShift;
            if(isAttainable(theta,positionArr,roadWidth))
                ans.second+=turningShift;
            else 
                break;
        }

        theta=position.theta;
        while(theta!=-turningRange)
        {
            theta-=turningShift;
            if(isAttainable(theta,positionArr,roadWidth))
                ans.first-=turningShift;
            else 
                break;
        }

        return ans;
    }



    int Vehicle::getRightDistance(double phi,char positionArr[roadMaxWidth][roadMaxLength],int roadWidth, TrafficLight trafficLight, int time,int roadLength)
    {
        int ptx=position.upPos,pty=position.rightPos,w=position.width,distanceAvailable=0;
        double ang = phi;
        

        while(distanceAvailable<(roadLength-position.rightPos))
        {
            int d1=0,flag=0;

            int ptx1 = ptx - distanceAvailable*sin(ang*3.14/180);
            int pty1 = pty + distanceAvailable*cos(ang*3.14/180);

            while(d1!=w)
            {
                int ptx2 = ptx1 + d1*cos(ang*3.14/180);
                int pty2 = max(0,int(pty1 + d1*sin(ang*3.14/180)));

                if(ptx2<0 || ptx2>=roadWidth || positionArr[ptx2][pty2]!='-' || hasRedAhead(trafficLight, time, pty2))
                {
                    flag=1;
                    break;
                }

                d1++;
            }
            if(flag)
                break;
            distanceAvailable++;
        }

        //distanceAvailable is the least value to which the vehicle cant move inline, hence 1 must be subtracted from it
        return (distanceAvailable--)*cos(ang*3.14/180);    
    }


    bool Vehicle::hasRedAhead(TrafficLight tl, int time, int pos)
    {
        return (tl.isRed(time) && (pos==tl.getPosition())) ;
    }


    // notice the order of update 
    // execute once at time 0 
    VehiclePosition Vehicle::updatePositionVelocityAcceleration (int roadLength, int roadWidth, TrafficLight trafficLight, char positionArr[roadMaxWidth][roadMaxLength], int time, vector<Vehicle> sortedByRightPos)
    {

        double theta = position.theta;
        int aspiredRightDistance = lookAheadFactor*max(maxVelocity/2,int(velocity*cos(theta))),availableRightDistance;


        pair<double,double> p = attainableRange(positionArr, roadWidth);
        double ambientAngle = theta;


        availableRightDistance=getRightDistance(ambientAngle, positionArr, roadWidth, trafficLight, time, roadLength);


        for(double ang = p.first;ang<=p.second;ang+=turningShift)
        {
            int temp_dist = getRightDistance(ang, positionArr, roadWidth, trafficLight, time, roadLength);
            int updateAngle=0;
            if(availableRightDistance>=aspiredRightDistance)                        //already have an angle >= aspiredRightDistance
            {
                if(temp_dist>=aspiredRightDistance && abs(ang)<abs(ambientAngle))    //found an angle with lesser magnitude
                    updateAngle=1;
            }
            else                                                                    //dont have an angle >= aspiredRightDistance
            {
                if(temp_dist>availableRightDistance)                                //found an angle with higher availableRightDistance
                    updateAngle=1;
            }

            if(updateAngle)
            {
                ambientAngle = ang;
                availableRightDistance = temp_dist;
            }
        }


        //tilting vehicle 
        if(theta>ambientAngle)
            theta-=min(theta-ambientAngle, angularVelocity);
        else
            theta+=min(ambientAngle-theta, angularVelocity);

        position.theta=theta;

        availableRightDistance = getRightDistance(theta, positionArr, roadWidth, trafficLight, time, roadLength); 


        //acceleration logic
        

        int nextDistance=min(int(availableRightDistance/(cos(theta*3.14/180))),maxVelocity);    

        int nextVelocity=nextDistance;                                    //next distance is always less then or equal to maxVelocity
        int nextAcceleration =  min(  max((nextVelocity - (this->velocity)),(this->accelerationRange).first) , (this->accelerationRange).second);
        
        acceleration=nextAcceleration;
        this->velocity+=acceleration;

        position.updatePos(velocity);
         

         
         cout<<representation<<" aspiredRightDistance "<<aspiredRightDistance<<"availableRightDistance "<<availableRightDistance<<"nextDistance "<<nextDistance<<"\navailableAngle "<<p.first<<" "<<p.second<<" ambientAngle "<<ambientAngle<<endl;
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
        
         


           pair<int,int> vertex1 = position.clockwiseVertex1();
         pair<int,int> vertex2 = position.clockwiseVertex2();
         pair<int,int> vertex3 = position.clockwiseVertex3();
         pair<int,int> vertex4 = position.clockwiseVertex4();

         int x1=vertex1.first - spacingFact*alpha; 
         int y1=roadWidth-(vertex1.second + spacingFact*alpha); 
         int x2=vertex2.first - spacingFact*alpha; 
         int y2=roadWidth-(vertex2.second - spacingFact*alpha); 
         int x3=vertex3.first + spacingFact*alpha; 
         int y3=roadWidth-(vertex3.second - spacingFact*alpha); 
         int x4=vertex4.first + spacingFact*alpha; 
         int y4=roadWidth-(vertex4.second + spacingFact*alpha); 
         

         glLoadIdentity();
         glColor3f(colourRed,colourGreen,colourBlue);
         glBegin(GL_POLYGON);
           glVertex2i(x4,y4);
           glVertex2i(x3,y3);
           glVertex2i(x2,y2);
           glVertex2i(x1,y1);
           glEnd();    
    }




    void Vehicle::setId(int id)
    {    this->id=id;    }





