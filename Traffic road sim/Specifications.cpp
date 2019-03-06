#include "Specifications.h"

using namespace std;



    Specifications::Specifications()
    { }
    
    //constructor: sets roadTempelate, trafficLightTempelate and default params for vehicles
    Specifications::Specifications ( vector<pair<string,int> > roadAndTrafficLightSpecs, vector<pair<string,int> > defaultVehicleSpecs)
    {

        // default params for road
        defaultRoadId = 1;
        defaultRoadLength = 100;
        defaultRoadWidth = 6;

        //default params for trafficLight
        defaultTrafficLightId = 1;                                                    
        defaultTrafficLightPosition = defaultRoadLength/2;
        defaultTrafficLightRedPeriod = 20;
        defaultTrafficLightGreenPeriod = 20;
        defaultTrafficLightRedFirst = 1;

        
        //params for road
        int roadId = defaultRoadId;                                                             
        int roadLength = defaultRoadLength;                                                         
        int roadWidth = defaultRoadWidth;                                                         
        

        //params for trafficLight
        int trafficLightid = defaultTrafficLightId;                                                             
        int trafficLightposition = defaultTrafficLightPosition;
        int trafficLightredPeriod = defaultTrafficLightRedPeriod;
        int trafficLightgreenPeriod = defaultTrafficLightGreenPeriod;
        int trafficLightredFirst = defaultTrafficLightRedFirst;

        const char *toBeCompared;
        int toBeAssigned;

        //setting roadAndTrafficLight params from config to be passed to Road and TrafficLight constructors
        for (int i = 0; i < roadAndTrafficLightSpecs.size(); i++)
        {

            toBeCompared=(roadAndTrafficLightSpecs[i].first).c_str();
            toBeAssigned=roadAndTrafficLightSpecs[i].second;

            if(!strcmp(toBeCompared,"roadId"))
                roadId = toBeAssigned;
            else if(!strcmp(toBeCompared,"roadLength"))
                roadLength = toBeAssigned;
            else if(!strcmp(toBeCompared,"roadWidth"))
                roadWidth = toBeAssigned;

            else if(!strcmp(toBeCompared,"trafficLightid"))
                trafficLightid = toBeAssigned;
            else if(!strcmp(toBeCompared,"trafficLightposition"))
                trafficLightposition = toBeAssigned;
            else if(!strcmp(toBeCompared,"trafficLightredPeriod"))
                trafficLightredPeriod = toBeAssigned;
            else if(!strcmp(toBeCompared,"trafficLightgreenPeriod"))
                trafficLightgreenPeriod = toBeAssigned;
            else if(!strcmp(toBeCompared,"trafficLightredFirst"))
                trafficLightredFirst = toBeAssigned;

        }

        this->trafficLightTemplate = *(new TrafficLight(trafficLightid, trafficLightposition, trafficLightredPeriod, trafficLightgreenPeriod, trafficLightredFirst));
        this->roadTemplate = *(new Road(roadLength, roadWidth, this->trafficLightTemplate, roadId));

                                                 
        //default params for vehicles
        defaultVehicleId = 0;
        defaultVehicleLength = 2;
        defaultVehicleWidth = 2;
        defaultVehicleRepresentation = ' ';       
        defaultVehiclePosition.upPos=defaultRoadWidth;
        defaultVehiclePosition.rightPos=0;
        defaultVehicleVelocity = 1;
        defaultVehicleMaxVelocity = 2;           //minimum velocity is 0....no backwards movement allowed as of now
        defaultVehicleAccelerationRange = make_pair(-2,4);               //needs to be a multiple of 2
        defaultVehicleAcceleration = 0;   


        //setting default parameters for vehicles from config

       

        for (int i = 0; i < defaultVehicleSpecs.size(); i++)
        {

            toBeCompared=(defaultVehicleSpecs[i].first).c_str();
            toBeAssigned=defaultVehicleSpecs[i].second;


            if(!strcmp(toBeCompared,"defaultVehicleId"))
                defaultVehicleId = toBeAssigned;
            else if(!strcmp(toBeCompared,"defaultVehicleLength"))
                defaultVehicleLength = toBeAssigned;
            else if(!strcmp(toBeCompared,"defaultVehicleWidth"))
                defaultVehicleWidth = toBeAssigned;
            else if(!strcmp(toBeCompared,"defaultVehicleRepresentation"))
                defaultVehicleRepresentation = toBeAssigned;
            else if(!strcmp(toBeCompared,"defaultVehicleLane"))
                {
                    defaultVehiclePosition.upPos = toBeAssigned;
                    defaultVehiclePosition.rightPos = 0;
                }
            else if(!strcmp(toBeCompared,"defaultVehicleVelocity"))
                defaultVehicleVelocity = toBeAssigned;
            else if(!strcmp(toBeCompared,"defaultVehicleMaxVelocity"))
                defaultVehicleMaxVelocity = toBeAssigned;
            else if(!strcmp(toBeCompared,"defaultVehicleMinAcceleration"))
                defaultVehicleAccelerationRange.first = toBeAssigned;
            else if(!strcmp(toBeCompared,"defaultVehicleMaxAccelaration"))
                defaultVehicleAccelerationRange.second = toBeAssigned;
            else if(!strcmp(toBeCompared,"defaultVehicleAcceleration"))
                defaultVehicleAcceleration = toBeAssigned;


        }


        
    }
    
    void Specifications::addVehicleTemplate (string vehicleType, vector<pair<string,int> > vehicleSpecs)
    {
        int vehicleId = defaultVehicleId;
        int vehicleLength = defaultVehicleLength;
        int vehicleWidth = defaultVehicleWidth;
        char vehicleRepresentation = (defaultVehicleRepresentation == ' ')? vehicleType[0] : defaultVehicleRepresentation;                  
        VehiclePosition vehiclePosition = defaultVehiclePosition;
        int vehicleVelocity = defaultVehicleVelocity;
        int vehicleMaxVelocity = defaultVehicleMaxVelocity;                 //minimum velocity is 0...no backwards movement allowed as of now
        pair<int,int> vehicleAccelerationRange = defaultVehicleAccelerationRange ; //needs to be a multiple of 2
        int vehicleAcceleration = defaultVehicleAcceleration;                   //needs to be a multiple of 2
        

        const char *toBeCompared;
        int toBeAssigned;

        

        for (int i = 0; i < vehicleSpecs.size(); i++)   
        {

            toBeCompared=(vehicleSpecs[i].first).c_str();
            toBeAssigned=vehicleSpecs[i].second;

            if(!strcmp(toBeCompared,"vehicleId"))
                vehicleId = toBeAssigned;
            else if(!strcmp(toBeCompared,"vehicleLength"))
                vehicleLength = toBeAssigned;
            else if(!strcmp(toBeCompared,"vehicleWidth"))
                vehicleWidth = toBeAssigned;
            else if(!strcmp(toBeCompared,"vehicleRepresentation"))
                vehicleRepresentation = toBeAssigned;
            else if(!strcmp(toBeCompared,"vehicleLane"))
                {
                    vehiclePosition.upPos = toBeAssigned;
                    vehiclePosition.rightPos = 0;
                }
            else if(!strcmp(toBeCompared,"vehicleVelocity"))
                vehicleVelocity = toBeAssigned;
            else if(!strcmp(toBeCompared,"vehicleMaxVelocity"))
                vehicleMaxVelocity = toBeAssigned;
            else if(!strcmp(toBeCompared,"vehicleMinAcceleration"))
                vehicleAccelerationRange.first = toBeAssigned;
            else if(!strcmp(toBeCompared,"vehicleMaxAccelaration"))
                vehicleAccelerationRange.second = toBeAssigned;
            else if(!strcmp(toBeCompared,"vehicleAcceleration"))
                vehicleAcceleration = toBeAssigned;


        }

        vehicleTemplates[vehicleType] = *(new Vehicle(vehicleId, vehicleLength, vehicleWidth, vehicleRepresentation, vehiclePosition, vehicleVelocity, vehicleMaxVelocity, vehicleAccelerationRange, vehicleAcceleration, vehicleType));
           
    }
    
    void Specifications::operator = (const Specifications &specs)
    {
        // default params for road
        defaultRoadId = specs.defaultRoadId;
        defaultRoadLength = specs.defaultRoadLength;
        defaultRoadWidth = specs.defaultRoadWidth;

        //default params for trafficLight
        defaultTrafficLightId = specs.defaultTrafficLightId;                                                    
        defaultTrafficLightPosition = specs.defaultTrafficLightPosition;
        defaultTrafficLightRedPeriod = specs.defaultTrafficLightRedPeriod;
        defaultTrafficLightGreenPeriod = specs.defaultTrafficLightGreenPeriod;
        defaultTrafficLightRedFirst = specs.defaultTrafficLightRedFirst;

        defaultVehicleId = specs.defaultVehicleId;
        defaultVehicleLength = specs.defaultVehicleLength;
        defaultVehicleWidth = specs.defaultVehicleWidth;
        defaultVehicleRepresentation = specs.defaultVehicleRepresentation;       
        defaultVehiclePosition = specs.defaultVehiclePosition;
        defaultVehicleVelocity = specs.defaultVehicleVelocity;
        defaultVehicleMaxVelocity = specs.defaultVehicleMaxVelocity;           //minimum velocity is 0....no backwards movement allowed as of now
        defaultVehicleAccelerationRange = specs.defaultVehicleAccelerationRange;               //needs to be a multiple of 2
        defaultVehicleAcceleration = specs.defaultVehicleAcceleration;   

        TrafficLight trafficLightTemplate=specs.trafficLightTemplate;
        Road roadTemplate=specs.roadTemplate;
        map<string,Vehicle> vehicleTemplates=specs.vehicleTemplates;
    }
    

