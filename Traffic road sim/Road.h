#ifndef ROAD_H
#define ROAD_H


class Road
{

    int id;                                                             //ID of road
    int length;                                                         //length of road, default = 100
    int width;                                                          //width of road, default = 5
    trafficLight tl;                                                    //Traffic Light

    const int maxLanes;
    const int maxLength;
    char arr[maxLanes][maxLength];                                                 //The road itself
    
    //initialises the array
    void initialise_arr();
    
public:
    
    //Constructor
    road (int length,int width,trafficLight tl,int id);

    void moveVehicle(Vehicle v, vehiclePosition pos);
    //gotta make provision to display cars not in full view

    void showRoad();    
    
};


#endif