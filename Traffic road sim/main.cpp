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
#include "Constants.h"
#include <chrono>
#include <thread>

using namespace std;

Specifications specifications;
vector<AddVehicleEvent> addVehicle;
vector<Vehicle> sortedByRightPos;
Road road;
int timeInstant;
int stop = 0 ;
int start = 0;

string configFile = "config.ini";

void readSpecifications(string s);

vector<AddVehicleEvent> readSimulationFlow(string fileName);

void arrangeVehicle(vector<Vehicle> &v,int ind);

void graphicsInitialization();

void getRoad();

void displayRoad(int t);

void runSimulation();

int main(int argc, char **argv)
{
    cout<<"Enter Configuration File name - ";
    cin>>configFile;
    cin.get();
    cout<<endl;
    readSpecifications (configFile);
    road=specifications.getRoadTemplate();
    addVehicle = readSimulationFlow(configFile);
    timeInstant=-1;

    glutInit(&argc,argv);
    graphicsInitialization();
    glutDisplayFunc(runSimulation);
    glutIdleFunc(runSimulation);
    glutMainLoop();
    return 0;
}

void runSimulation()
{

   
    int roadLength=road.getLength();
    //return 0;
    
    if(stop==1)
    {
        cout<<"\n\nTIME INSTANT "+to_string(timeInstant)+"\n\n";
        road.showRoad(timeInstant);
        displayRoad(timeInstant);
        cout<<"Press Enter to exit"<<endl;
        cin.get();
        glutDestroyWindow(1);
        return;
    }
    if(start == 0)
    {
        cout<<"Press Enter to start simulation"<<endl;
        cin.get();  
        start=1;  
    }
       
        timeInstant++;
        //add new vehicles
        while(addVehicle.size())
        {
            if(addVehicle[0].getTimeStamp()!=timeInstant)
                break;

            Vehicle newVehicle=addVehicle[0].getVehicle();
            addVehicle.erase(addVehicle.begin());
            sortedByRightPos.insert(sortedByRightPos.begin(),newVehicle);
            arrangeVehicle(sortedByRightPos,0);
            road.addVehicle(newVehicle);
        }




        //show road
        cout<<"\n\nTIME INSTANT "+to_string(timeInstant)+"\n\n";
        road.showRoad(timeInstant);
        displayRoad(timeInstant);
        
         //changing vehicle positions for time t+1
        for(int i=sortedByRightPos.size()-1;i>=0;i--)
        {
            
            road.moveVehicle(sortedByRightPos[i], timeInstant, sortedByRightPos);

            arrangeVehicle(sortedByRightPos,i);
        }

        //deleting vehicles out of scene
        for(int i=sortedByRightPos.size()-1;i>=0;i--)
        {
            if(sortedByRightPos[i].getPosition().rightPos<roadLength)
                break;

            int leftPos=sortedByRightPos[i].getPosition().rightPos - sortedByRightPos[i].getPosition().length;

            if(leftPos>=roadLength)
            {
                road.removeVehicle(sortedByRightPos[i]);
                sortedByRightPos.erase(sortedByRightPos.begin()+i);
            }
        }

    if(!(sortedByRightPos.size() || addVehicle.size()))
    {
        stop =1;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(pauseTime));
    
}



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
            else if ((line.size()>=4&&!strcmp(line.substr(0, 4).c_str(),"road"))|(line.size()>=12&&!strcmp(line.substr(0, 12).c_str(),"trafficLight")))
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
                    RHS=line.substr(delimiterPos + 1, commentPos)[0];
                else
                    RHS = stoi(line.substr(delimiterPos + 1, commentPos));

                defaultVehicleSpecs.push_back(make_pair(LHS,RHS));
            }
            else if (line.size()>=15&&!strcmp(line.substr(0, 15).c_str(),"startVehicleDef"))
            {
                getline(configFile, line);
                line.erase(remove_if(line.begin(), line.end(), ::isspace),line.end());
                
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
                            RHS=line.substr(delimiterPos + 1, commentPos)[0];
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
                line.erase(remove_if(line.begin(), line.end(), ::isspace),line.end());

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
                int lane = -1;
                

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
                            lane = alpha*RHS;
                        
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




void displayRoad(int t)
{
  glClear(GL_COLOR_BUFFER_BIT);
  //Push and pop matrix for separating circle object from Background
  
  for(int i=0;i<sortedByRightPos.size();i++)
        sortedByRightPos[i].glVehicleShow(road.getWidth());


  road.glRoadTrafficLightShow(t);  
  glutSwapBuffers();
  glFlush();
}

void graphicsInitialization()
{
    
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
    glutInitWindowSize(road.getLength(),road.getWidth());
    glutInitWindowPosition(0,0);
    glutCreateWindow(("Traffic Road Simulation- "+configFile).c_str());

    glClearColor(1,0.5,0.5,1); //Background Color
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,road.getLength(),0,road.getWidth());
    glMatrixMode(GL_MODELVIEW);

    
}









