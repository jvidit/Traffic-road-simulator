#ifndef ROAD_H
#define ROAD_H

class Road
{

    int id;                                                             //ID of road
    int length;                                                         //length of road, default = 100
    int width;                                                          //width of road, default = 5
    TrafficLight trafficLight;                                          //Traffic Light                                                //Traffic Light
    const int maxWidth;
    const int maxLength;
    char postitionArr[maxWidth][maxLength];                                                 //The road itself

    
    //initialises the postionArray
    void initialise_positionArr();
    
public:
    
    //Constructor

    road (int id,int length,int width,TrafficLight trafficLight);


    void moveVehicle(Vehicle vehicle, vehiclePosition position);
    //gotta make provision to display cars not in full view

    void showRoad();    
    
};


#endif
