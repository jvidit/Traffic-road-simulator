#include "VehiclePosition.h"
	

	void VehiclePosition::operator = (const VehiclePosition &vehiclePosition) 
	{ 
        rightPos=vehiclePosition.rightPos;
        upPos=vehiclePosition.upPos;
        length=vehiclePosition.length;
        width=vehiclePosition.width;
        theta=vehiclePosition.theta;
    }


    VehiclePosition::VehiclePosition()
    {
    	theta=0;
    }

    pair<int,int> VehiclePosition::clockwiseVertex1()
	{
		pair <int, int> pos ; 
  		pos.first = rightPos; 
    	pos.second = upPos ; 
    	return pos;
    }

    pair<int,int> VehiclePosition::clockwiseVertex2()
	{
		pair <int, int> pos ; 
		double x = theta*3.14159/180;
  		pos.first = rightPos+width*sin(x); 
    	pos.second = upPos+width*cos(x) ; 
    	return pos;
    }

    pair<int,int> VehiclePosition::clockwiseVertex3()
	{
		pair <int, int> pos ; 
		double x = theta*3.14159/180;
  		pos.first = rightPos-length*cos(x)+width*sin(x); 
    	pos.second = upPos+length*sin(x)+width*cos(x); 
    	return pos;
    }

    pair<int,int> VehiclePosition::clockwiseVertex4()
	{
		pair <int, int> pos ; 
		double x = theta*3.14159/180;
  		pos.first = rightPos-length*cos(x); 
    	pos.second = upPos+length*sin(x); 
    	return pos;
    }


    void VehiclePosition::updateAngle(double ang)
    {
        pair<int, int> v3 = clockwiseVertex3(), v4 = clockwiseVertex4();

        int backmidx=(v3.first+v4.first)/2;
        int backmidy=(v3.second+v4.second)/2;
        theta = ang;
        rightPos = backmidx + (length*cos(ang*3.14159/180) - (width*sin(ang*3.14159/180)/2));
        upPos= backmidy - (length*sin(ang*3.14159/180) + (width*cos(ang*3.14159/180)/2));
    }

    void VehiclePosition::updatePos(int velocity)
    {
    	double x = theta*3.14159/180;
    	rightPos = rightPos + velocity*cos(x);
    	upPos = upPos - velocity*sin(x);
    }



