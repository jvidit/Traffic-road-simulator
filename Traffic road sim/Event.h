

class Event
{

    String description;

    int eventType;
    // 0 - create road
    // 1 - create traffic light
    // 2 - create vehicle and mov to position P

    int timestamp; //time instant of event

    Road road;
    TrafficLight trafficLight;
    Vehicle vehicle;
    
    //Default Paramaters
    
    //params for road
    static int defaultRoadId;                                                             //ID of road
    static int defaultRoadLength;                                                         //length of road
    static int defaultRoadWidth;                                                          //width of road
    static trafficLight defaultRoadTrafficLight;           

    //params for traffic light
    static int defaultTrafficLightId;                                                             //ID of traffic light
    static int defaultTrafficLightPosition;
    static int defaultTrafficLightRedPeriod;
    static int defaultTrafficLightGreenPeriod;
    static int defaultTrafficLightRedFirst;

    //params for creating and moving vehicle
    static int defaultVehicleId;
    static int defaultVehicleLength;
    static int defaultVehicleWidth;
    static char defaultVehicleRepresentation;       //Think of a better name
    static vehiclePosition defaultVehiclePosition;
    static int defaultVehicleVelocity;
    static int defaultVehicleMaxVelocity;           //minimum velocity is 0....no backwards movement allowed as of now
    static pair<int,int> defaultAccelerationRange;  //needs to be a multiple of 2
    static int defaultVehicleAcceleration;          //needs to be a multiple of 2



public:
    

	//depending on type of event, allocates memory to road, traffic light or vehicle
	Event(int timestamp,String description);


    int getTimeStamp();

	String getDescription();
	
	
}
