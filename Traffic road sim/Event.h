
//Design Changes made:
//1. Combined "move to position" and "create vehicle" in the same event, as no "move to position" events are made during simulation
//2. Rather than generating things(i.e., road, traffic light and vehicle) based on the event in the main, Event itself generates the instances of objects


class Event
{

	//useful for debugging
	String description;


    int eventType;
    // 0 - create road
    // 1 - create traffic light
    // 2 - create vehicle and mov to position P

    int timestamp;

    Road road;
    TrafficLight tl;
    Vehicle vehicle;
    
    //Default Paramaters
    
    //params for road
    static int defaultRoadId;                                                             //ID of road
    static int defaultRoadlength;                                                         //length of road, default = 100
    static int defaultRoadwidth;                                                          //width of road, default = 5
    static trafficLight defaultRoadTl;           

    //params for traffic light
    static int defaultTrafficLightId;                                                             //ID of traffic light
    static int defaultTrafficLightposition;
    static int defaultTrafficLightredPeriod;
    static int defaultTrafficLightgreenPeriod;
    static int defaultTrafficLightredFirst;

    //params for creating and moving vehicle
    static int defaultVehicleId;
    static int defaultVehiclelength;
    static int defaultVehiclebreath;
    static char defaultVehiclerep;         //Think of a better name
    static vehiclePosition defaultVehiclePosition;
    static int defaultVehiclevelocity;
    static int defaultVehiclemaxVelocity;        //minimum velocity is 0....no backwards movement allowed as of now
    static pair<int,int> defaultAccelerationRange;  //needs to be a multiple of 2
    static int defaultVehicleacceleration;         //needs to be a multiple of 2



public:
    

	//depending on type of event, allocates memory to road, traffic light or vehicle
	Event(int timestamp,String message);


	int eventType;
    	// 0 - create road
  	// 1 - create traffic light
  	// 2 - create vehicle and mov to position P
   
    	int timestamp;

	public:
  	Road road;
  	TrafficLight trafficLight;
  	Vehicle vehicle;
	

	//depending on type of event, allocates memory to road, traffic light or vehicle
	Event(int timestamp,String description);
     	/*IDEA - We dont need to set default parameters in our other classes, we can pass parameters from here by using static variables*/

	String getDescription();

   int getTimeStamp();

	String getDescription()
	{	return description;		}

	
}
