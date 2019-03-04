


class trafficLight
{
    int Id;                                                             //ID of traffic light
    int position;
    int redPeriod;
    int greenPeriod;
    int redFirst;

public:
    
    
    //Traffic light constructor
    trafficLight(int position, int redPeriod, int greenPeriod, int redFirst, int id);
    {
        this.position=position;
        this.redPeriod=redPeriod;
        this.greenPeriod=greenPeriod;
        this.redFirst=redFirst;
        this.Id=id;
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
