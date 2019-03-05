class TrafficLight
{
    int id;                                                             //ID of traffic light
    int position;
    int redPeriod;
    int greenPeriod;
    int redFirst;

public:
    
    //TrafficLight constructor

    TrafficLight(int id, int position, int redPeriod, int greenPeriod, int redFirst);

    
    //Returns true if traffic light is red
    bool isRed(int t);
    
    //Returns true if traffic light is green
    bool isGreen(int t);
    
    int getPosition();
};
