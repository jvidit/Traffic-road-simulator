


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
    
    //Returns true if traffic light is red
    bool isRed(int t);
    
    //Returns true if traffic light is green
    bool isGreen(int t);
    
    int getPosition();
}
