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
    	pos.second = upPos-width*cos(x) ; 
    	return pos;
    }

    pair<int,int> VehiclePosition::clockwiseVertex3()
	{
		pair <int, int> pos ; 
		double x = theta*3.14159/180;
  		pos.first = rightPos-length*cos(x)+width*sin(x); 
    	pos.second = upPos-length*sin(x)-width*cos(x); 
    	return pos;
    }

     pair<int,int> VehiclePosition::clockwiseVertex4()
	{
		pair <int, int> pos ; 
		double x = theta*3.14159/180;
  		pos.first = rightPos-length*cos(x); 
    	pos.second = upPos-length*sin(x); 
    	return pos;
    }



