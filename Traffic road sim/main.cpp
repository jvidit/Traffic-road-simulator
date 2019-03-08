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
        int start = 0;

        //NOTE: using substring can lead to segmentation errors
        while(getline(configFile, line))
        {
            
            line.erase(remove_if(line.begin(), line.end(), ::isspace),line.end());

            if (line.size()>=20&&!strcmp(line.substr(0, 20).c_str(),"START_SPECIFICATIONS"))
                start =1;
            else if (start == 0)
                continue;
            else if (line.size()>=4&&!strcmp(line.substr(0, 4).c_str(),"road"))
            {
                int commentPos = line.find("#");
                int delimiterPos = line.find("=");

                string LHS = line.substr(0, delimiterPos);

                int RHS = stoi(line.substr(delimiterPos + 1, commentPos));

                roadAndTrafficLightSpecs.push_back(make_pair(LHS,RHS));

            }
            else if (line.size()>=7&&!strcmp(line.substr(0, 7).c_str(),"default"))
            {
                int commentPos = line.find("#");
                int delimiterPos = line.find("=");

                string LHS = line.substr(0, delimiterPos);
                int RHS=0;
                if(!strcmp(LHS.c_str(),"defaultVehicleRepresentation"))
                    RHS=line.substr(delimiterPos + 1, commentPos)[0]-'a';
                else
                    RHS = stoi(line.substr(delimiterPos + 1, commentPos));

                defaultVehicleSpecs.push_back(make_pair(LHS,RHS));
            }
            else if (line.size()>=15&&!strcmp(line.substr(0, 15).c_str(),"startVehicleDef"))
            {
                getline(configFile, line);
               
                
                int commentPos = line.find("#");
                int delimiterPos = line.find("=");
                
                string LHS = line.substr(0, delimiterPos);
                string RHS = line.substr(delimiterPos + 1, commentPos);
                string vehicleType;

                if (!strcmp(LHS.c_str(), "vehicleType"))
                   vehicleType = RHS;
                //else
                //    throw "Specify vehicleType!";


                vector<pair<string,int> > vehicleSpecs;

                 while(getline(configFile, line))
                 {
                    
                    line.erase(remove_if(line.begin(), line.end(), ::isspace),line.end());

                    if(line.size()>=7&&!strcmp(line.substr(0, 7).c_str(),"vehicle"))
                    {
                        int commentPos = line.find("#");
                        int delimiterPos = line.find("=");

                        string LHS = line.substr(0, delimiterPos);
                        int RHS;
                        if(!strcmp(LHS.c_str(),"vehicleRepresentation"))
                            RHS=line.substr(delimiterPos + 1, commentPos)[0]-'a';
                        else
                            RHS = stoi(line.substr(delimiterPos + 1, commentPos));
            
                        vehicleSpecs.push_back(make_pair(LHS,RHS));
                    }
                    else if (line.size()>=3&&!strcmp(line.substr(0, 3).c_str(),"end"))
                    {
                        specifications.addVehicleTemplate (vehicleType, vehicleSpecs);
                        break;
                    }
                    else 
                        continue;
                 }
                
            }
            else if (line.size()>=3&&!strcmp(line.substr(0, 3).c_str(),"END"))
            {
                break;
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

vector<AddVehicleEvent> readSimulationFlow(string fileName)
{

    ifstream configFile (fileName);
    
    vector<AddVehicleEvent> simulationFlow;
    

    if (configFile.is_open())
    {
        string line;
        int start = 0;
        int time = 0;

        //NOTE: using substring can lead to segmentation errors
        while(getline(configFile, line))
        {
            line.erase(remove_if(line.begin(), line.end(), ::isspace),line.end());

            if (line.size()>=16&&!strcmp(line.substr(0, 16).c_str(),"START_SIMULATION"))
                start =1;
            else if (start == 0)
                continue;
            else if (line.size()>=4&&!strcmp(line.substr(0,4).c_str(),"pass"))
                {
                    int commentPos = line.find("#");
                    int delimiterPos = line.find("=");
                    time+=stoi(line.substr(delimiterPos + 1, commentPos));
                }
            else if (line.size()>=15&&!strcmp(line.substr(0, 15).c_str(),"startVehicleSim"))
            {
                getline(configFile, line);

                int commentPos = line.find("#");
                int delimiterPos = line.find("=");

                string LHS = line.substr(0, delimiterPos);
                string RHS = line.substr(delimiterPos + 1, commentPos);
                string vehicleType;

                if (!strcmp(LHS.c_str(), "vehicleType"))
                   vehicleType = RHS;
               /*
                else
                    throw "Specify vehicleType!";
                */
                int lane;
                

                while(getline(configFile, line))
                 {
                    line.erase(remove_if(line.begin(), line.end(), ::isspace),line.end());

                    if(line.size()>=7&&!strcmp(line.substr(0, 7).c_str(),"vehicle"))
                    {
                        int commentPos = line.find("#");
                        int delimiterPos = line.find("=");

                        string LHS = line.substr(0, delimiterPos);
                        int RHS = stoi(line.substr(delimiterPos + 1, commentPos));
                        
                        if(!strcmp(LHS.c_str(),"vehicleLane"))
                            lane = RHS;
                        
                    }
                    else if (line.size()>=3&&!strcmp(line.substr(0, 3).c_str(),"end"))
                    {
                        AddVehicleEvent addVehicleEvent(time,specifications.getVehicleTemplate(vehicleType),lane);
                        simulationFlow.push_back(addVehicleEvent);
                        break;
                    }
                    else 
                        continue;
                 }
                
            }
            else if (line.size()>=3&&!strcmp(line.substr(0, 3).c_str(),"END"))
                break;
            else
                continue;
    
        }
        
    }
    else 
    {
        cerr << "Couldn't open config file.\n";
    }

    return simulationFlow;

     
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




int main()
{

    string configFile="./config.ini";
    readSpecifications (configFile);



    Road road=specifications.getRoadTemplate();
    int roadLength=road.getLength();

    vector<AddVehicleEvent> addVehicle = readSimulationFlow(configFile);
    vector<Vehicle> sortedByRightPos;

    int time=-1;



    while(sortedByRightPos.size() || addVehicle.size())
    {

        cout<<"Vehicle Positions\n";
        for(int i=0;i<sortedByRightPos.size();i++)
        {
            cout<<sortedByRightPos[i].getPosition().rightPos<<"\n";
        }


        cout<<sortedByRightPos.size()<<" "<<addVehicle.size()<<endl;
        if(time==10)
            return 0;
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




















