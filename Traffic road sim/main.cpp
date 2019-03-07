#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <utility>
#include <cstring>
#include <sstream>
#include "TrafficLight.h"
#include "Road.h"
#include "Vehicle.h"
#include "VehiclePosition.h"
#include "Specifications.h"
#include <stdio.h>
#include <string.h>
#include "AddVehicleEvent.h"

using namespace std;

Specifications specifications;


void readSpecifications(string fileName)
{
    ifstream configFile (fileName);
    
    vector<pair<string,int> > roadAndTrafficLightSpecs;
    vector<pair<string,int> > defaultVehicleSpecs;
    
    

    if (configFile.is_open())
    {
        string line;

        //NOTE: using substring can lead to segmentation errors
        while(getline(configFile, line))
        {
            line.erase(remove_if(line.begin(), line.end(), ::isspace),line.end());

            if(line[0] == '#' || line.empty())
                continue;
            else if (!strcmp(line.substr(0, 4).c_str(),"road"))
            {
                int commentPos = line.find("#");
                int delimiterPos = line.find("=");

                string LHS = line.substr(0, delimiterPos);
                int RHS = stoi(line.substr(delimiterPos + 1, commentPos));

                roadAndTrafficLightSpecs.push_back(make_pair(LHS,RHS));

            }
            else if (!strcmp(line.substr(0, 7).c_str(),"default"))
            {
                int commentPos = line.find("#");
                int delimiterPos = line.find("=");

                string LHS = line.substr(0, delimiterPos);
                int RHS = stoi(line.substr(delimiterPos + 1, commentPos));

                defaultVehicleSpecs.push_back(make_pair(LHS,RHS));
            }
            else if (!strcmp(line.substr(0, 15).c_str(),"startVehicleDef"))
            {
                getline(configFile, line);

                int commentPos = line.find("#");
                int delimiterPos = line.find("=");

                string LHS = line.substr(0, delimiterPos);
                string RHS = line.substr(delimiterPos + 1, commentPos);

                string vehicleType = RHS;
                vector<pair<string,int> > vehicleSpecs;

                 while(getline(configFile, line))
                 {
                    if(!strcmp(line.substr(0, 7).c_str(),"vehicle"))
                    {
                        int commentPos = line.find("#");
                        int delimiterPos = line.find("=");

                        string LHS = line.substr(0, delimiterPos);
                        int RHS = stoi(line.substr(delimiterPos + 1, commentPos));
            
                        vehicleSpecs.push_back(make_pair(LHS,RHS));
                    }
                    else
                    {
                        specifications.addVehicleTemplate (vehicleType, vehicleSpecs);
                        break;
                    }
                 }
                
            }
            else
                continue;
    
        }

        specifications.addRoadAndTrafficLightTemplate (roadAndTrafficLightSpecs);
        specifications.addDefaultVehicleSpecs(defaultVehicleSpecs);
        
    }
    else 
    {
        cerr << "Couldn't open config file.\n";
    }

    
}

vector<AddVehicleEvent> readSimulationFlow(string fileName);
{
     
}




void arrangeVehicle(vector<Vehicle> &v,int ind)
{
    Vehicle temp = v[ind];
    int tempRightPos = temp.getPosition().rightPos;

    v.erase(v.begin()+ind);
    while(ind<v.size())
    {
        if(tempRightPos>v[ind].getPosition().rightPos)
            ind++;
        else
            break;
    }
    v.insert(v.begin()+ind,temp);
}


int AddVehicleEvent::id=0;

int main()
{

    string configFile="config.ini";
    readSpecifications (configFile);

    Road road=specifications.getRoadTemplate();
    int roadLength=road.getLength();


    vector<AddVehicleEvent> addVehicle = readSimulationFlow(configFile);
    vector<Vehicle> sortedByRightPos;

    int time=0;

    while(sortedByRightPos.size() || addVehicle.size())
    {
        time++;
        //add new vehicles
        while(addVehicle.size())
        {
            if(addVehicle[0].getTimeStamp()!=time)
                break;

            Vehicle newVehicle=addVehicle[0].getVehicle();
            addVehicle.erase(addVehicle.begin());

            sortedByRightPos.insert(sortedByRightPos.begin(),newVehicle);
            arrangeVehicle(sortedByRightPos,0);
        }



        //show road
        cout<<"\n\nTIME INSTANT "+to_string(time)+"\n\n";
        road.showRoad();


        //changing vehicle positions for time t+1
        for(int i=sortedByRightPos.size()-1;i>=0;i--)
        {
            road.moveVehicle(sortedByRightPos[i]);
            arrangeVehicle(sortedByRightPos,i);
        }

        //deleting vehicles out of scene
        for(int i=sortedByRightPos.size()-1;i>=0;i--)
        {
            if(sortedByRightPos[i].getPosition().rightPos<roadLength)
                break;

            int leftPos=sortedByRightPos[i].getPosition().rightPos - sortedByRightPos[i].getPosition().length + 1;
            if(leftPos>=roadLength)
                sortedByRightPos.erase(sortedByRightPos.begin()+i);
        }

    }
    return 0;
    
}




















