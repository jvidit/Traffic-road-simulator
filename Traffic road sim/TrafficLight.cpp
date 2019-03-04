class TrafficLight
{
    int id;                                                             //ID of traffic light
    int position;
    int redPeriod;
    int greenPeriod;
    int redFirst;

public:
    
    //TrafficLight constructor
    TrafficLight(int id, int position, int redPeriod, int greenPeriod, int redFirst)

    {
        this.position=position;
        this.redPeriod=redPeriod;
        this.greenPeriod=greenPeriod;
        this.redFirst=redFirst;
        this.id=id;
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
