
//Design Changes made:
//1. Combined "move to position" and "create vehicle" in the same event, as no "move to position" events are made during simulation
//2. Rather than generating things(i.e., road, traffic light and vehicle) based on the event in the main, Event itself generates the instances of objects


class Event
{

	//useful for debugging
    String description;

public:

	int eventType;
    // 0 - create road
    // 1 - create traffic light
    // 2 - create vehicle and mov to position P
   
    int timestamp;

  	Road road;
  	TrafficLight tl;
  	Vehicle vehicle;
	

	//depending on type of event, allocates memory to road, traffic light or vehicle
	Event(int timestamp,String message);
    /*IDEA - We dont need to set default parameters in our other classes, we can pass parameters from here by using static variables*/


	String getEventDescription()
	{	return description;		}
	
}
