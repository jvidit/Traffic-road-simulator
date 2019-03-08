#include "Constants.h"

SpecConsts::SpecConsts()
{
     defaultRoadId =1 ;                                                             //ID of road
	defaultRoadLength = 50;                                                         //length of road
	defaultRoadWidth = 6;        
                                                  //width of road
	defaultTrafficLightId = 1 ;                                                     //ID of traffic light
	defaultTrafficLightRedPeriod =20;
	defaultTrafficLightGreenPeriod =20;
	defaultTrafficLightRedFirst =1;


     defaultVehicleId = 0;
     defaultVehicleLength = 2;
     defaultVehicleWidth = 2;
     defaultVehicleRepresentation = ' ';       
     defaultVehiclePosition.upPos=0;
     defaultVehiclePosition.rightPos=0;
     defaultVehicleVelocity = 1;
     defaultVehicleMaxVelocity = 2;           //minimum velocity is 0....no backwards movement allowed as of now
     defaultVehicleAccelerationRange = make_pair(-1,2);               
     defaultVehicleAcceleration = 0;  
}
