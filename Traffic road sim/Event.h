

class AddVehicleEvent
{

    
    int timestamp; //time instant of event

    Vehicle vehicle;
   
public:
    

	//depending on type of event, allocates memory to road, traffic light or vehicle
	Event(int timestamp,Vehicle vehicleTemplate);
    {
        this.timestamp=timestamp;
        vehicle=new Vehicle();
        
    }

    int getTimeStamp();

	String getDescription();
	
	
}
