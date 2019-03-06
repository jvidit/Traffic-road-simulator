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


using namespace std;

Specifications specifications;


vector<string> readConfig(string fileName)
{
    ifstream configFile (fileName);
    
    vector<pair<string,int> > roadAndTrafficLightSpecs;
    vector<pair<string,int> > defaultVehicleSpecs;
    vector<pair<string,int> > vehicleSpecs;
    vector<string> eventStrings;

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
            else if (!strcmp(line.substr(0, 7).c_str(),"vehicle"))
            {
                int commentPos = line.find("#");
                int delimiterPos = line.find("=");

                string LHS = line.substr(0, delimiterPos);
                int RHS = stoi(line.substr(delimiterPos + 1, commentPos));

                vehicleSpecs.push_back(make_pair(LHS,RHS));
            }
            
            specifications=*(new Specifications(roadAndTrafficLightSpecs, defaultVehicleSpecs));
    
        }
        
    }
    
    else 
    {
        cerr << "Couldn't open config file.\n";
    }

    return eventStrings;
}

int main()
{
    
    vector<string> eventStrings = readConfig ("config.ini");
    for(int i=0;i<eventStrings.size();i++)
    {
        cout<<eventStrings[i]<<endl;

    }


    
}
