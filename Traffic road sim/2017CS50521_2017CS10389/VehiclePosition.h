#ifndef VEHICLEPOSITION_H
#define VEHICLEPOSITION_H

#include<utility>
#include<cmath>


//contains length, breath, and the upper right point position of vehicle
using namespace std;

class VehiclePosition
{

public:
	double backmidx;
	double backmidy;
	double& rightPos = backmidx;
	int length;
	int width;
	double theta;
	pair<double,double> clockwiseVertex1();
	pair<double,double> clockwiseVertex2();
	pair<double,double> clockwiseVertex3();
	pair<double,double> clockwiseVertex4(); 
	void operator = (const VehiclePosition &pvehiclePosition);
	VehiclePosition();
	void updatePos(int velocity);
};



#endif

