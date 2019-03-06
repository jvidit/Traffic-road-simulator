#include "TrafficLight.h"


    //TrafficLight constructor
    TrafficLight::TrafficLight()
    {}
    

    TrafficLight::TrafficLight(int id, int position, int redPeriod, int greenPeriod, int redFirst)

    {
        this->position=position;
        this->redPeriod=redPeriod;
        this->greenPeriod=greenPeriod;
        this->redFirst=redFirst;
        this->id=id;
    }
    
    //Returns true if traffic light is red
    bool TrafficLight::isRed(int t)
    {
        t%=(redPeriod+greenPeriod);
        
        if( (redFirst and t<redPeriod) or (!redFirst and t>=greenPeriod))
            return true;
        return false;
    }
    
    //Returns true if traffic light is green
    bool TrafficLight::isGreen(int t)
    {   return not(isRed(t));   }
    
    
    int TrafficLight::getPosition()
    {   return position;    }
    

    void TrafficLight::operator = (const TrafficLight &trafficLight)
    {
        id=trafficLight.id;
        position=trafficLight.position;
        redPeriod=trafficLight.redPeriod;
        greenPeriod=trafficLight.greenPeriod;
        redFirst=trafficLight.redFirst;
    }



