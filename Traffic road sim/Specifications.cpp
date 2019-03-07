#include "Specifications.h"

using namespace std;

SpecConsts specConsts;



    Specifications::Specifications()
    { }
    
    //sets roadTempelate, trafficLightTempelate 
        void Specifications::addRoadAndTrafficLightTemplate ( vector<pair<string,int> > roadAndTrafficLightSpecs)
    {
        //params for road
        int roadId = specConsts.defaultRoadId;                                                             
        int roadLength = specConsts.defaultRoadLength;                                                         
        int roadWidth = specConsts.defaultRoadWidth;                                                         
        

        //params for trafficLight
        int trafficLightid = specConsts.defaultTrafficLightId;                                                             
        int trafficLightposition = specConsts.defaultTrafficLightPosition;
        int trafficLightredPeriod = specConsts.defaultTrafficLightRedPeriod;
        int trafficLightgreenPeriod = specConsts.defaultTrafficLightGreenPeriod;
        int trafficLightredFirst = specConsts.defaultTrafficLightRedFirst;

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
    }
             
    void Specifications::addDefaultVehicleSpecs(vector<pair<string,int> > defaultVehicleSpecs) 
    {
        const char *toBeCompared;
        int toBeAssigned;

        //setting dfault parameters for vehicles from config
        for (int i = 0; i < defaultVehicleSpecs.size(); i++)
        {

            toBeCompared=(defaultVehicleSpecs[i].first).c_str();
            toBeAssigned=defaultVehicleSpecs[i].second;


            if(!strcmp(toBeCompared,"defaultVehicleId"))
                specConsts.defaultVehicleId = toBeAssigned;
            else if(!strcmp(toBeCompared,"defaultVehicleLength"))
                specConsts.defaultVehicleLength = toBeAssigned;
            else if(!strcmp(toBeCompared,"defaultVehicleWidth"))
                specConsts.defaultVehicleWidth = toBeAssigned;
            else if(!strcmp(toBeCompared,"defaultVehicleRepresentation"))
                specConsts.defaultVehicleRepresentation = toBeAssigned;
            else if(!strcmp(toBeCompared,"defaultVehicleLane"))
                {
                    specConsts.defaultVehiclePosition.upPos = toBeAssigned;
                    specConsts.defaultVehiclePosition.rightPos = 0;
                }
            else if(!strcmp(toBeCompared,"defaultVehicleVelocity"))
                specConsts.defaultVehicleVelocity = toBeAssigned;
            else if(!strcmp(toBeCompared,"defaultVehicleMaxVelocity"))
                specConsts.defaultVehicleMaxVelocity = toBeAssigned;
            else if(!strcmp(toBeCompared,"defaultVehicleMinAcceleration"))
                specConsts.defaultVehicleAccelerationRange.first = toBeAssigned;
            else if(!strcmp(toBeCompared,"defaultVehicleMaxAccelaration"))
                specConsts.defaultVehicleAccelerationRange.second = toBeAssigned;
            else if(!strcmp(toBeCompared,"defaultVehicleAcceleration"))
               specConsts.defaultVehicleAcceleration = toBeAssigned;


        }
    }


    
    void Specifications::addVehicleTemplate (string vehicleType, vector<pair<string,int> > vehicleSpecs)
    {
        int vehicleId = specConsts.defaultVehicleId;
        int vehicleLength = specConsts.defaultVehicleLength;
        int vehicleWidth = specConsts.defaultVehicleWidth;
        char vehicleRepresentation = (specConsts.defaultVehicleRepresentation == ' ')? vehicleType[0] : specConsts.defaultVehicleRepresentation;                  
        VehiclePosition vehiclePosition = specConsts.defaultVehiclePosition;
        int vehicleVelocity = specConsts.defaultVehicleVelocity;
        int vehicleMaxVelocity = specConsts.defaultVehicleMaxVelocity;                 //minimum velocity is 0...no backwards movement allowed as of now
        pair<int,int> vehicleAccelerationRange = specConsts.defaultVehicleAccelerationRange ; //needs to be a multiple of 2
        int vehicleAcceleration = specConsts.defaultVehicleAcceleration;                   //needs to be a multiple of 2
        

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
        
        TrafficLight trafficLightTemplate=specs.trafficLightTemplate;
        Road roadTemplate=specs.roadTemplate;
        map<string,Vehicle> vehicleTemplates=specs.vehicleTemplates;
    }
    

