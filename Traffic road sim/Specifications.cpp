#include "Specifications.h"
#include <iostream>
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
        int trafficLightId = specConsts.defaultTrafficLightId;                                                             
        int trafficLightRedPeriod = specConsts.defaultTrafficLightRedPeriod;
        int trafficLightPosition;
        int trafficLightGreenPeriod = specConsts.defaultTrafficLightGreenPeriod;
        int trafficLightRedFirst = specConsts.defaultTrafficLightRedFirst;

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
                {
                    roadLength = toBeAssigned;
                    trafficLightPosition = toBeAssigned/2;
                }
            else if(!strcmp(toBeCompared,"roadWidth"))
                roadWidth = toBeAssigned;

            else if(!strcmp(toBeCompared,"trafficLightId"))
                trafficLightId = toBeAssigned;
            else if(!strcmp(toBeCompared,"trafficLightPosition"))
                trafficLightPosition = toBeAssigned;
            else if(!strcmp(toBeCompared,"trafficLightRedPeriod"))
                trafficLightRedPeriod = toBeAssigned;
            else if(!strcmp(toBeCompared,"trafficLightGreenPeriod"))
                trafficLightGreenPeriod = toBeAssigned;
            else if(!strcmp(toBeCompared,"trafficLightRedFirst"))
                trafficLightRedFirst = toBeAssigned;
         }

        this->trafficLightTemplate = *(new TrafficLight(trafficLightId, trafficLightPosition, trafficLightRedPeriod, trafficLightGreenPeriod, trafficLightRedFirst));
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
                specConsts.defaultVehicleRepresentation = char(toBeAssigned);
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
        char vehicleRepresentation = specConsts.defaultVehicleRepresentation;                  
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
                vehicleRepresentation = char(toBeAssigned);
                
            else if(!strcmp(toBeCompared,"vehicleLane"))
                {
                    vehiclePosition.upPos = toBeAssigned;
                    vehiclePosition.rightPos = 0;
                }
            else if(!strcmp(toBeCompared,"vehicleVelocity"))
                vehicleVelocity = min(toBeAssigned,specConsts.maxAllowedVelocity);
            else if(!strcmp(toBeCompared,"vehicleMaxVelocity"))
                vehicleMaxVelocity = min(toBeAssigned,specConsts.maxAllowedVelocity);
            else if(!strcmp(toBeCompared,"vehicleMinAcceleration"))
                vehicleAccelerationRange.first = max(toBeAssigned,specConsts.minAllowedAcceleration);
            else if(!strcmp(toBeCompared,"vehicleMaxAccelaration"))
                vehicleAccelerationRange.second = min(toBeAssigned,specConsts.maxAllowedAcceleration);
            else if(!strcmp(toBeCompared,"vehicleAcceleration"))
                vehicleAcceleration = max(specConsts.minAllowedAcceleration,min(specConsts.maxAllowedAcceleration,toBeAssigned));
        }

        if(vehicleRepresentation==' ')  
                vehicleRepresentation = vehicleType[0];

        vehiclePosition.length = vehicleLength;
        vehiclePosition.width = vehicleWidth;
        
        vehicleTemplates[vehicleType] = *(new Vehicle(vehicleId, vehicleLength, vehicleWidth, vehicleRepresentation, vehiclePosition, vehicleVelocity, vehicleMaxVelocity, vehicleAccelerationRange, vehicleAcceleration, vehicleType));
        
    }
    
    void Specifications::operator = (const Specifications &specs)
    {
        
        trafficLightTemplate=specs.trafficLightTemplate;
        roadTemplate=specs.roadTemplate;
        vehicleTemplates=specs.vehicleTemplates;
    }
    

    Road Specifications::getRoadTemplate()
    {   return roadTemplate;    }


    Vehicle Specifications::getVehicleTemplate(string vehicleType)
    {   
        
        return vehicleTemplates.find(vehicleType)->second;   
    }

