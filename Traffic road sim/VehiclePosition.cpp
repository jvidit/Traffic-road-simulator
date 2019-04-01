#include "VehiclePosition.h"
double piHere = 3.141592;
    

    void VehiclePosition::operator = (const VehiclePosition &vehiclePosition)
    {
        backmidx=vehiclePosition.backmidx;
        backmidy=vehiclePosition.backmidy;
        length=vehiclePosition.length;
        width=vehiclePosition.width;
        theta=vehiclePosition.theta;
    }

    VehiclePosition::VehiclePosition()
    {
        theta=0;
    }

    pair<double,double> VehiclePosition::clockwiseVertex1()
    {
     pair <double, double> pos ;
     double x = theta*piHere/180;
         pos.first = backmidx + length*cos(x)-width*sin(x)/2;
     pos.second = backmidy - length*sin(x)-width*cos(x)/2  ;
     return pos;
    }

    pair<double,double> VehiclePosition::clockwiseVertex2()
    {
     pair <double, double> pos ;
     double x = theta*piHere/180;
         pos.first = backmidx -width*sin(x)/2;
     pos.second = backmidy -width*cos(x)/2  ;
     return pos;
    }

    pair<double,double> VehiclePosition::clockwiseVertex3()
    {
     pair <double, double> pos ;
     double x = theta*piHere/180;
         pos.first = backmidx +width*sin(x)/2;
     pos.second = backmidy +width*cos(x)/2  ;
     return pos;
    }

    pair<double,double> VehiclePosition::clockwiseVertex4()
    {
     pair <double, double> pos ;
     double x = theta*piHere/180;
         pos.first = backmidx + length*cos(x)+width*sin(x)/2;
     pos.second = backmidy - length*sin(x)+width*cos(x)/2  ;
     return pos;
    }


    

    void VehiclePosition::updatePos(int velocity)
    {
     double x = theta*piHere/180;
     backmidx = backmidx + velocity*cos(x);
     backmidy = backmidy - velocity*sin(x);
    }





