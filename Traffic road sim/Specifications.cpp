#include <map>
#include <utility> 
#include <vector>
#include <string>
#include "TrafficLight.h"
#include "Road.h"
#include "Vehicle.h"
#include "VehiclePosition.h"

using namespace std;

class Specifications
{
    
    TrafficLight trafficLightTemplate;
    Road roadTemplate;
    map<string,Vehicle> vehicleTemplates;

    //Default Paramaters
    
    //params for road
    int defaultRoadId;                                                             //ID of road
    int defaultRoadLength;                                                         //length of road
    int defaultRoadWidth;                                                          //width of road
              

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
    VehiclePosition defaultVehiclePosition;
    int defaultVehicleVelocity;
    int defaultVehicleMaxVelocity;           //minimum velocity is 0....no backwards movement allowed as of now
    pair<int,int> defaultVehicleAccelerationRange;  //needs to be a multiple of 2
    int defaultVehicleAcceleration;          //needs to be a multiple of 2

public: 

    Specifications()
    { }

    //constructor: sets roadTempelate, trafficLightTempelate and default params for vehicles
    Specifications (vector<pair<string,int>> roadAndTrafficLightSpecs, vector<pair<string,int>> defaultVehicleSpecs)
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

        
        //setting roadAndTrafficLight params from config to be passed to Road and TrafficLight constructors
        for (int i = 0; i < roadAndTrafficLightSpecs.size(); i++)
        {
            if(!strcmp(roadAndTrafficLightSpecs[i].first,"roadId"))
                roadId = roadAndTrafficLightSpecs[i].second;
            else if(!strcmp(roadAndTrafficLightSpecs[i].first,"roadLength"))
                roadLength = roadAndTrafficLightSpecs[i].second;
            else if(!strcmp(roadAndTrafficLightSpecs[i].first,"roadWidth"))
                roadWidth = roadAndTrafficLightSpecs[i].second;

            else if(!strcmp(roadAndTrafficLightSpecs[i].first,"trafficLightid"))
                trafficLightid = roadAndTrafficLightSpecs[i].second;
            else if(!strcmp(roadAndTrafficLightSpecs[i].first,"trafficLightposition"))
                trafficLightposition = roadAndTrafficLightSpecs[i].second;
            else if(!strcmp(roadAndTrafficLightSpecs[i].first,"trafficLightredPeriod"))
                trafficLightredPeriod = roadAndTrafficLightSpecs[i].second;
            else if(!strcmp(roadAndTrafficLightSpecs[i].first,"trafficLightgreenPeriod"))
                trafficLightgreenPeriod = roadAndTrafficLightSpecs[i].second;
            else if(!strcmp(roadAndTrafficLightSpecs[i].first,"trafficLightredFirst"))
                trafficLightredFirst = roadAndTrafficLightSpecs[i].second;

        }

        this.trafficLightTemplate = new TrafficLight(trafficLightId, trafficLightPosition, trafficLightRedPeriod, trafficLightGreenPeriod, trafficLightRedFirst);
        this.roadTemplate = new road (roadLength, roadWidth, this.trafficLightTemplate, int roadId);

                                                 
        //default params for vehicles
        defaultVehicleId = 0;
        defaultVehicleLength = 2;
        defaultVehicleWidth = 2;
        defaultVehicleRepresentation = ' ';       
        defaultVehiclePosition = make_pair(0,0);
        defaultVehicleVelocity = 1;
        defaultVehicleMaxVelocity = 2;           //minimum velocity is 0....no backwards movement allowed as of now
        defaultVehicleAccelerationRange = make_pair(-2,4);               //needs to be a multiple of 2
        defaultVehicleAcceleration = 0;   


        //setting default parameters for vehicles from config
        for (int i = 0; i < defaultVehicleSpecs.size(); i++)
        {
            if(!strcmp(defaultVehicleSpecs[i].first,"defaultVehicleId"))
                defaultVehicleId = defaultVehicleSpecs[i].second;
            else if(!strcmp(defaultVehicleSpecs[i].first,"defaultVehicleLength"))
                defaultVehicleLength = defaultVehicleSpecs[i].second;
            else if(!strcmp(defaultVehicleSpecs[i].first,"defaultVehicleWidth"))
                defaultVehicleWidth = defaultVehicleSpecs[i].second;
            else if(!strcmp(defaultVehicleSpecs[i].first,"defaultVehicleRepresentation"))
                defaultVehicleRepresentation = defaultVehicleSpecs[i].second;
            else if(!strcmp(defaultVehicleSpecs[i].first,"defaultVehicleLane"))
                {
                    defaultVehiclePosition.second = defaultVehicleSpecs[i].second;
                    defaultVehiclePosition.first = 0;
                }
            else if(!strcmp(defaultVehicleSpecs[i].first,"defaultVehicleVelocity"))
                defaultVehicleVelocity = defaultVehicleSpecs[i].second;
            else if(!strcmp(defaultVehicleSpecs[i].first,"defaultVehicleMaxVelocity"))
                defaultVehicleMaxVelocity = defaultVehicleSpecs[i].second;
            else if(!strcmp(defaultVehicleSpecs[i].first,"defaultVehicleMinAcceleration"))
                defaultVehicleAccelerationRange.first = defaultVehicleSpecs[i].second;
            else if(!strcmp(defaultVehicleSpecs[i].first,"defaultVehicleMaxAccelaration"))
                defaultVehicleAccelerationRange.second = defaultVehicleSpecs[i].second;
            else if(!strcmp(defaultVehicleSpecs[i].first,"defaultVehicleAcceleration"))
                defaultVehicleAcceleration = defaultVehicleSpecs[i].second;


        }


        vehicleTemplates = new map<string,Vehicle>(); 
    }
    
    addVehicleTemplate (string vehicleType, vector<pair<string,int>> vehicleSpecs)
    {
        int vehicleId = defaultVehicleId;
        int vehicleLength = defaultVehicleLength;
        int vehicleWidth = defaultVehicleWidth;
        char vehicleRepresentation = (defaultVehicleRepresentation == ' ')? vehicleType[0] : defaultVehicleRepresentation;                  
        VehiclePosition vehiclePosition = defaultVehiclePosition;
        int vehicleVelocity = defaultVehicleVelocity;
        int vehicleMaxVelocity = defaultVehicleMaxVelocity;                 //minimum velocity is 0...no backwards movement allowed as of now
        pair<int,int> vehicleAccelerationRange = defaultAccelerationRange ; //needs to be a multiple of 2
        int vehicleAcceleration = defaultVehicleAcceleration;                   //needs to be a multiple of 2
        

        for (int i = 0; i < vehicleSpecs.size(); i++)   
        {
            if(!strcmp(vehicleSpecs[i].first,"vehicleId"))
                vehicleId = vehicleSpecs[i].second;
            else if(!strcmp(vehicleSpecs[i].first,"vehicleLength"))
                vehicleLength = vehicleSpecs[i].second;
            else if(!strcmp(vehicleSpecs[i].first,"vehicleWidth"))
                vehicleWidth = vehicleSpecs[i].second;
            else if(!strcmp(vehicleSpecs[i].first,"vehicleRepresentation"))
                vehicleRepresentation = vehicleSpecs[i].second;
            else if(!strcmp(vehicleSpecs[i].first,"vehicleLane"))
                {
                    vehiclePosition.second = vehicleSpecs[i].second;
                    vehiclePosition.first = 0;
                }
            else if(!strcmp(vehicleSpecs[i].first,"vehicleVelocity"))
                vehicleVelocity = vehicleSpecs[i].second;
            else if(!strcmp(vehicleSpecs[i].first,"vehicleMaxVelocity"))
                vehicleMaxVelocity = vehicleSpecs[i].second;
            else if(!strcmp(vehicleSpecs[i].first,"vehicleMinAcceleration"))
                vehicleAccelerationRange.first = VehicleSpecs[i].second;
            else if(!strcmp(vehicleSpecs[i].first,"vehicleMaxAccelaration"))
                vehicleAccelerationRange.second = vehicleSpecs[i].second;
            else if(!strcmp(vehicleSpecs[i].first,"vehicleAcceleration"))
                vehicleAcceleration = vehicleSpecs[i].second;


        }

        vehicleTemplates[vehicleType] = new Vehicle(vehicleId, vehicleLength, vehicleWidth, vehicleRepresentation, vehiclePosition, vehicleVelocity, vehicleMaxVelocity, vehicleAccelerationRange, vehicleAcceleration, string vehicleType);
        
               
        
        
                   
        
           
    }

}