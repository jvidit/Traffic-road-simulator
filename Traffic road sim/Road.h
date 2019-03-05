#ifndef ROAD_H
#define ROAD_H

#include "Vehicle.h"
#include "TrafficLight.h"
#include "VehiclePosition.h"

const int maxWidth=20;
const int maxLength=1000;

class Road
{

    int id;                                                             //ID of road
    int length;                                                         //length of road, default = 100
    int width;                                                          //width of road, default = 5
    TrafficLight trafficLight;                                          //Traffic Light                                                //Traffic Light
    
    char postitionArr[maxWidth][maxLength];                                                 //The road itself

    
    //initialises the postionArray
    void initialise_positionArr();
    
public:
    
    //Constructor

    Road (int id,int length,int width,TrafficLight trafficLight);


    void moveVehicle(Vehicle vehicle, VehiclePosition position);
    //gotta make provision to display cars not in full view

    void showRoad();    
    
};


#endif
