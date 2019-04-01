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
    {   return this->position;  }

    char Vehicle::getRepresentation()
    {   return representation;      }

    bool Vehicle::isAttainable(double phi, char positionArr[roadMaxWidth][roadMaxLength],int roadWidth)
    {
        

        double ptx=position.backmidy,pty=position.backmidx,l=position.length,w=position.width;
        double ang = phi;
        double d1=(-w/2);
        while(d1!=(w/2))
        {
            double ptx1=ptx+d1*cos(ang*pi/180);              //x moves along with lanes
            double pty1=pty+d1*sin(ang*pi/180);              //y moves along road length
     
         
            double d2=0;
            while(d2!=l)
            {

                double ptx2=ptx1-d2*sin(ang*pi/180);
                if(ptx2<0 || ptx2>=roadWidth)
                    return false;

                double pty2=max((double)0,(pty1+d2*cos(ang*pi/180)));
             
                if(positionArr[(int)ptx2][(int)pty2]!='-')
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
         
        while(theta<turningRange)
        {  
            theta+=turningShift;
            if(isAttainable(theta,positionArr,roadWidth))
                ans.second=theta;
            else
                break;
        }

        theta=position.theta;
        while(theta>-turningRange)
        {
            theta-=turningShift;
            if(isAttainable(theta,positionArr,roadWidth))
                ans.first=theta;
            else
                break;
        }

        return ans;
    }



    double Vehicle::getRightDistance(double phi,char positionArr[roadMaxWidth][roadMaxLength],int roadWidth, TrafficLight trafficLight, int time,int roadLength)
    {
       
        double ptx=position.backmidy,pty=position.backmidx,l=position.length,w=position.width,distanceAvailable=length;
        double ang = phi;
     

        while(distanceAvailable<maxVelocity*lookAheadFactor+length)
        {
            int flag=0;

            double ptx1 = ptx - distanceAvailable*sin(ang*pi/180);
            double pty1 = pty + distanceAvailable*cos(ang*pi/180);

            double d1=(-w/2);
            while(d1!=(w/2))
            {
                double ptx2 = ptx1 + d1*cos(ang*pi/180);
                double pty2 = max((double)0,(pty1 + d1*sin(ang*pi/180)));

                if(ptx2<0 || ptx2>=roadWidth || positionArr[(int)ptx2][(int)pty2]!='-' || hasRedAhead(trafficLight, time, (int)pty2))
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

        return cos(ang*pi/180)*(max((double)0,distanceAvailable-length-2));    
    }


    bool Vehicle::hasRedAhead(TrafficLight tl, int time, int pos)
    {
        return (tl.isRed(time) && (pos==tl.getPosition()||pos==tl.getPosition()-1||pos==tl.getPosition()-2||pos==tl.getPosition()-3) ) ;
    }

    // notice the order of update
    // execute once at time 0
    VehiclePosition Vehicle::updatePositionVelocityAcceleration (int roadLength, int roadWidth, TrafficLight trafficLight, char positionArr[roadMaxWidth][roadMaxLength], int time, vector<Vehicle> sortedByRightPos)
    {

        double theta = position.theta;
        int aspiredRightDistance = lookAheadFactor*max(maxVelocity/2,int(velocity*cos(theta)));
        double availableRightDistance;


        pair<double,double> p = attainableRange(positionArr, roadWidth);
        double ambientAngle = theta;


        availableRightDistance=getRightDistance(ambientAngle, positionArr, roadWidth, trafficLight, time, roadLength);


        for(double ang = p.first;ang<=p.second;ang++)
        {
            double temp_dist = getRightDistance(ang, positionArr, roadWidth, trafficLight, time, roadLength);
            int updateAngle=0;
            if(availableRightDistance>=aspiredRightDistance)                        //already have an angle >= aspiredRightDistance
            {
                if(temp_dist>=aspiredRightDistance && abs(ang)<abs(ambientAngle))   //found an angle with lesser magnitude
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





        double leastAngle=0;
        if(p.second<0)
            leastAngle = p.second;
        else if(p.first>0)
            leastAngle = p.first;


        double leastAngleDist=getRightDistance(leastAngle, positionArr, roadWidth, trafficLight, time, roadLength);
        if((leastAngleDist+length/2)>=availableRightDistance)
        {
            ambientAngle = leastAngle;
            availableRightDistance = leastAngleDist;
        }
        


        //tilting vehicle
        if(theta>ambientAngle)
            theta-=min(theta-ambientAngle, angularVelocity);
        else
            theta+=min(ambientAngle-theta, angularVelocity);

        position.theta=theta;

        double finalRightDistance = getRightDistance(theta, positionArr, roadWidth, trafficLight, time, roadLength);


        //acceleration logic
     

        int nextDistance=min(int(finalRightDistance/(cos(theta*pi/180))),maxVelocity);    

        int nextVelocity=nextDistance;                                  //next distance is always less then or equal to maxVelocity
        int nextAcceleration =  min(  max((nextVelocity - (this->velocity)),(this->accelerationRange).first) , (this->accelerationRange).second);
     
        acceleration=nextAcceleration;
        this->velocity+=acceleration;


        if(time%25==0)
            cin.get();

        position.updatePos(velocity);
         

         
        cout<<representation<<" aspiredRightDistance "<<aspiredRightDistance<<"availableRightDistance "<<availableRightDistance<<"nextDistance "<<nextDistance<<"\navailableAngle "<<p.first<<" "<<p.second<<" ambientAngle "<<ambientAngle<<endl;
        cout<<"     "<<position.backmidx<<" "<<position.backmidy<<" "<<theta<<endl;
        cout<<"  Least Angle Distance "<<leastAngleDist<<" "<<"LeastAngle "<<leastAngle<<endl;
        return position;
    }

    void Vehicle::setUpPos (int lane)
    {
        position.backmidy = lane;
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
     
         


        pair<double,double> vertex1 = position.clockwiseVertex1();
        pair<double,double> vertex2 = position.clockwiseVertex2();
        pair<double,double> vertex3 = position.clockwiseVertex3();
        pair<double,double> vertex4 = position.clockwiseVertex4();

        double x1=vertex1.first - spacingFact*alpha;
        double y1=roadWidth-(vertex1.second + spacingFact*alpha);
        double x2=vertex2.first - spacingFact*alpha;
        double y2=roadWidth-(vertex2.second - spacingFact*alpha);
        double x3=vertex3.first + spacingFact*alpha;
        double y3=roadWidth-(vertex3.second - spacingFact*alpha);
        double x4=vertex4.first + spacingFact*alpha;
        double y4=roadWidth-(vertex4.second + spacingFact*alpha);
         



        glLoadIdentity();
        glColor3f(colourRed,colourGreen,colourBlue);
        glBegin(GL_POLYGON);
        glVertex2d(x4,y4);
        glVertex2d(x3,y3);
        glVertex2d(x2,y2);
        glVertex2d(x1,y1);
        glEnd();    
    }




    void Vehicle::setId(int id)
    {   this->id=id;    }












