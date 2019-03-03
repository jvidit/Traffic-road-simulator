


class trafficLight
{
    int Id;                                                             //ID of traffic light
    int position;
    int redPeriod;
    int greenPeriod;
    int redFirst;

public:
    
    
    //Traffic light constructor
    trafficLight(int pos, int red=5, int green=5, int rfirst=1, int idd)
    {
        position=pos;
        redPeriod=red;
        greenPeriod=green;
        redFirst=rfirst;
        idd=Id;
    }
    
    //Returns true if traffic light is red
    bool isRed(int t)
    {
        t%=(redPeriod+greenPeriod);
        
        if( (redFirst and t<redPeriod) or (!redFirst and t>=greenPeriod))
            return true;
        return false;
    }
    
    //Returns true if traffic light is green
    bool isGreen(int t)
    {   return not(isRed(t));   }
    
    
    int getPosition()
    {   return position;    }
    


}
