


class Road
{
    int id;                                                             //ID of road
    int length;                                                         //length of road, default = 100
    int width;                                                          //width of road, default = 5
    TrafficLight trafficLight;                                          //Traffic Light
    char positionArr[10][1000];                                         //The road itself
    
    //initialises the array
    void initialise_positionArr();
    
    public:
    
    //Constructor
    road (int id,int length,int width,TrafficLight trafficLight);

    void moveVehicle(Vehicle vehicle, vehiclePosition position);
    //gotta make provision to display cars not in full view

    void showRoad();    
    
};
