#ifndef VEHICLEPOSITION_H
#define VEHICLEPOSITION_H

#include<utility>
#include<cmath>

//contains length, breath, and the upper right point position of vehicle
using namespace std;

class VehiclePosition
{

public:
	int rightPos;
	int upPos;
	int length;
	int width;
	double theta;
	pair<int,int> clockwiseVertex1();
	pair<int,int> clockwiseVertex2();
	pair<int,int> clockwiseVertex3();
	pair<int,int> clockwiseVertex4(); 
	void operator = (const VehiclePosition &pvehiclePosition);
	VehiclePosition();
	void updatePos(int velocity);
};



#endif

