
#ifndef ROAD_H
#define ROAD_H


#include "TrafficLight.h"
#include "VehiclePosition.h"
#include "Vehicle.h"
#include "Constants.h"

class Road
{

    int id;                                                             //ID of road
    int length;                                                         //length of road, default = 100
    int width;                                                          //width of road, default = 5
    TrafficLight trafficLight;                                         //Traffic Light                                                //Traffic Light
    
    char positionArr[roadMaxWidth][roadMaxLength];                                                 //The road itself

    
    //initialises the postionArray
    void initialise_positionArr();
    
public:
    
    //Constructor

    Road (int length,int width,TrafficLight trafficLight,int id);

    Road();
    
    void moveVehicle(Vehicle &vehicle);
    //gotta make provision to display cars not in full view

    void showRoad();    
    void operator = (const Road &road);

    int getLength();

    void setTrafficLight(int time);
};


#endif
