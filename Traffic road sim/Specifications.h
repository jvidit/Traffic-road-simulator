class Specifications
{
	int id;
	TrafficLight trafficLightTemplate;
	Road roadTemplate;
	map<string,Vehicle> vehicleTemplates;

	//Default Paramaters
    
    //params for road
    int defaultRoadId;                                                             //ID of road
    int defaultRoadLength;                                                         //length of road
    int defaultRoadWidth;                                                          //width of road
    trafficLight defaultRoadTrafficLight;           

    //params for traffic light
    int defaultTrafficLightId;                                                     //ID of traffic light
    int defaultTrafficLightPosition;
    int defaultTrafficLightRedPeriod;
    int defaultTrafficLightGreenPeriod;
    int defaultTrafficLightRedFirst;

    //params for creating and moving vehicle
    int defaultVehicleId;
    int defaultVehicleLength;
    int defaultVehicleWidth;
    char defaultVehicleRepresentation;       
    vehiclePosition defaultVehiclePosition;
    int defaultVehicleVelocity;
    int defaultVehicleMaxVelocity;           //minimum velocity is 0....no backwards movement allowed as of now
    pair<int,int> defaultAccelerationRange;  //needs to be a multiple of 2
    int defaultVehicleAcceleration;          //needs to be a multiple of 2

public:	

	Specifications (int id, vector<pair<string,int>> roadAndTrafficLightSpecs, vector<pair<string,int>> defaultVehicleSpecs);
	addVehicleTemplate (string vehicleType, vector<pair<string,int>> vehicleSpecs);

}