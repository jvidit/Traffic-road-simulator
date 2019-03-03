


class Road
{
    int Id;                                                             //ID of road
    int length;                                                         //length of road, default = 100
    int width;                                                          //width of road, default = 5
    trafficLight tl;                                                    //Traffic Light
    char arr[10][1000];                                                 //The road itself
    
    //initialises the array
    void initialise_arr();
    
public:
    
    //Constructor
    road (int l=100,int w=5,trafficLight t=NULL,int idd=1);

    void moveVehicle(Vehicle v, vehiclePosition pos);
    //gotta make provision to display cars not in full view

    void showRoad();    
    
};
