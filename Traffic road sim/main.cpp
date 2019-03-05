#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;


vector<string> readConfig(string fileName)
{
    ifstream configFile (fileName);
    vector<string> eventStrings;

    if (configFile.is_open())
    {
        string line;
        string eventString = "";
        

        while(getline(configFile, line))
        {
            line.erase(remove_if(line.begin(), line.end(), ::isspace),line.end());
            if(line[0] == '#' || line.empty())
                continue;
            else if (strcmp(line.substr(0, 4),"Road_Id"))
            {
                if(!(strcmp(eventString,""))) 
                    eventStrings.push_back(eventString);

            }
            else if (strcmp(line.substr(0, 12),"Vehicle_Id"))
            {
                if(!(strcmp(eventString,""))) 
                    eventStrings.push_back(eventString);
                
            }
            int commentPos = line.find("#");
            int delimiterPos = line.find("=");

            eventString = line.substr(0, delimiterPos);
            eventString = eventString+line.substr(delimiterPos + 1, commentPos);
            
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