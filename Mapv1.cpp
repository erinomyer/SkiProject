#include <iostream>
#include <queue>
#include <vector>
#include "Mapv1.hpp"

using namespace std;

//ResortNode constructor
//initializes a ResortNode with empty members
ResortNode::ResortNode()
{
    resortName = "";
    pass =  "";
    pricePerDay = 0.0;
    while(!lifts.empty()) //not sure if I need to do this. I'm p sure vector init empty
    {
        lifts.pop_back();
    }
    numSkiers = 0;
}

void ResortNode::addChair(string chairName, int chairTime)
{
    //if the resort's lifts vector is empty
    if (lifts.empty())
    {
        Chairlift *newChair = new Chairlift;
        newChair->name = chairName;
        newChair->waitTime = chairTime;
        // cout << "empty and pushing!" << endl;
        lifts.push_back(newChair); //adding 
        // cout << newChair->name << " was added" << endl;
        // cout << "empty and pushing!" << endl;
        return;
    }

    bool chairExists = false;
    // cout << "ici" << endl;

    // cout << "EEP" << endl;
    //to check if this resort's lifts vector already contaings this chairlift
    for (int i = 0; i < lifts.size(); i++)
    {
        // cout << "ED" << endl;
        if (lifts[i]->name == chairName)
        {
            // cout << "MADE IT HERE" << endl;
            chairExists = true;
        }
    }

    // cout << "Outchea" << endl;

    //if the chairlift wasn't found in lifts
    if (!chairExists)
    {
        Chairlift *newChair = new Chairlift; //create it
        newChair->name = chairName; //name it
        newChair->waitTime = chairTime; //set its wait time
        lifts.push_back(newChair); //add it to the lifts vector
        // cout << newChair->name << " was added" << endl;
        // cout << "innea" << endl;
        return;
    } else { //if the chairlift was found in lifts
        cout << chairName << " already found!!" << endl;
        return;
    }


}

//returns a pointer to the desired chairLift — if it exists. NULL otherwise
Chairlift* ResortNode::findChair(string chairName)
{

    //searching lifts for a chairlift with chairName
    for (int i = 0; i < lifts.size(); i++)
    {
        if (lifts[i]->name == chairName)
        {
            return lifts[i];
        }
    }
    
    return NULL; 
}

//return a pointer to the desired run — if it exists. NULL otherwise
Run* ResortNode::findRun(string runName)
{
    //iterate through each lift in the resort
    //necessary because each lift vertex will (probably) have different accessible runs
    for (int i = 0; i < lifts.size(); i++)
    {
        //iterate through the current lift's accessible runs vector
        for (int c = 0; c < lifts[i]->accessibleRuns.size(); c++)
        {
            //if a lift with runName was found
            if (lifts[i]->accessibleRuns[c]->name == runName)
            {
                return lifts[i]->accessibleRuns[c];
            }
        }
    }

    return NULL;
}

//adding a run to a chairlift's accessible runs list
//will need to do this for every run that a lift can give access to, even if the run isn't directly below the lift. 
//(i.e. accessible by a run's branches vec)
void ResortNode::addRunToChair(string runToAdd, string runDiff, string liftToAddTo)
{
    Chairlift *chairExists = findChair(liftToAddTo);

    //if the chair doesn't exist in the resort's lifts vec
    if (chairExists == NULL)
    {
        cout << "Chair not found!" << endl;
        return;
    } else { //else, create a new run with the given characteristics
        Run *newRun = new Run;
        newRun->name = runToAdd;
        newRun->difficulty = runDiff;
        newRun->lift = NULL;
        Chairlift *toAddTo = findChair(liftToAddTo); //find the chairlift
        toAddTo->accessibleRuns.push_back(newRun); //add newRun to the chairlift's accessibleRuns vector
    }

}

void ResortNode::addChairToRun(string runToAddTo, string liftToAdd)
{
    // cout << "finding " << runToAddTo << endl;
    // Run *runToAddChairTo = findRun(runToAddTo);
    // cout << "found " << runToAddChairTo->name;

    // cout << "finding run" << endl;
    Run *runToAddChairTo = findRun(runToAddTo); //find the desired run
    // cout << "found run" << endl;
    // cout << runToAddChairTo->name << " name " << endl;

    //check to see if the lift already exists in lifts vec
    // cout << "finding chair" << endl;
    Chairlift *chairToAdd = findChair(liftToAdd);

    // cout << chairToAdd->name << " name " << endl;
    // cout << "found chair" << endl;

    //if the chair wasn't found in lifts vec
    //not sure if we'll need to check for this. 
    //if we're just hardcoding in everything, shouldn't we just be exact with it?
    if (chairToAdd == NULL) 
    {
        // cout << "making lift" << endl;
        Chairlift *newChair = new Chairlift; //create it
        // cout << "naming lift" << endl;
        newChair->name = liftToAdd; //name it
        // cout << "adding lift" << endl;
        lifts.push_back(newChair); //add it to lifts
        // cout << "setting r2ac2's lift" << endl;
        runToAddChairTo->lift = chairToAdd;
    } else { //if the chair was found
        // cout << "chair found, adding lift" << endl;
        runToAddChairTo->lift = chairToAdd;
        cout << chairToAdd->name << " (lift) was added to " << runToAddChairTo->name << " (run)" << endl;
    }
}

void ResortNode::addRunToRun(string runToAddTo, string runToAdd)
{
    Run *runToAdd2 = findRun(runToAddTo);
    Run *run2Add = new Run;
    run2Add->name = runToAdd;
    runEdge *newRunEdge = new runEdge;
    newRunEdge->nextRun = run2Add;    

    runToAdd2->branches.push_back(newRunEdge);
}

Colorado::Colorado()
{
    snowfall = 0.0;
    month = "";
}

void Colorado::buildCities()
{
    addCity("Durango");
    addCity("Telluride");
    addCity("Grand Junction");
    addCity("Colorado Springs");
    addCity("Aspen");
    addCity("Pueblo");
    addCity("Montrose");
    addCity("Sterling");
    addCity("Glenwood Springs");
    addCity("Alamosa");
    addCity("Rangely");
    addCity("Fort Collins");
    addCity("Denver");
    addCity("Boulder");
    addCity("Breckenridge");
    addCity("La Junta");
    addCity("Trinidad");
    addCity("Cortez");
    addCity("Pagosa Springs");
    addCity("Golden");
    addCity("Craig");
    addCity("Limon");
    addCity("Salida");
    addCity("Gunnison");
    addCity("Crested Butte");
}

void Colorado::buildHighways()
{
    addHighway("Durango", "Cortez", "US-160 W", 45.5, 51);
    addHighway("Cortez", "Durango", "US-160 E", 45.5, 51);
    addHighway("Durango", "Pagosa Springs", "US-160 E", 60.1, 70);
    addHighway("Pagosa Springs", "Durango", "US-160 W", 60.1, 70);
    addHighway("Durango", "Montrose", "US-550 N", 107, 147);
    addHighway("Montrose", "Durango", "US 550 S", 107, 147);
    addHighway("Cortez", "Telluride", "CO-145 N", 76.2, 93);
    addHighway("Telluride", "Cortez", "CO-145 S", 76.2, 93);
    addHighway("Telluride", "Montrose", "CO-62 E -> US 550 N", 65.7, 82);
    addHighway("Montrose", "Telluride", "US-550 S -> CO-62 W", 65.7, 82);
    addHighway("Pagosa Springs", "Alamosa", "US-160 E", 89.4, 109);
    addHighway("Alamosa", "Pagosa Springs", "US-160 W", 89.4, 109);
    addHighway("Montrose", "Grand Junction", "US-50 W", 60.3, 106);
    addHighway("Grand Junction", "Alamosa", "US-50 S", 60.3, 106);
    addHighway("Grand Junction", "Rangely", "CO-139 N", 90.3, 104);
    addHighway("Rangely", "Grand Junction", "CO-139 S", 90.3, 104);
    addHighway("Rangely", "Craig", "US-40 E", 93.2, 90);
    addHighway("Craig", "Rangely", "US-40 W", 93.2, 90);
    addHighway("Rangely", "Craig", "CO-64 E -> CO-13 N", 106, 111);
    addHighway("Craig", "Rangely", "CO-13 S -> CO-64 W", 106, 111);
    addHighway("Rangely", "Craig", "CO-64 E -> CO-13 N", 106, 111);
    addHighway("Montrose", "Gunnison", "US-50 E", 64.5, 74);
    addHighway("Gunnison", "Montrose", "US-50 W", 64.8, 74);
    addHighway("Gunnison", "Crested Butte", "CO-135 N", 27.6, 35);
    addHighway("Crested Butte", "Gunnison", "CO-135 S", 27.6, 35);
    addHighway("Grand Junction", "Glenwood Springs", "I-70 E", 86.5, 79);
    addHighway("Glenwood Springs", "Grand Junction", "I-70 W", 86.5, 79);
    addHighway("Craig", "Glenwood Springs", "CO-13 S", 117, 122);
    addHighway("Glenwood Springs", "Craig", "CO-13 N", 117, 122);
    addHighway("Rangely", "Glenwood Springs", "CO-64 E -> CO-13 S", 120, 124);
    addHighway("Glenwood Springs", "Rangely", "CO-13 N -> CO-64 W", 120, 123);
    addHighway("Craig", "Montrose", "CO-13 S", 204, 211);
    addHighway("Montrose", "Craig", "CO-13 N", 204, 211);
    addHighway("Glenwood Springs", "Montrose", "I-70 W -> US-50 E", 140, 136);
    addHighway("Montrose", "Glenwood Springs", "US-50 W -> I-70 E", 140, 136);
    addHighway("Montrose", "Glenwood Springs", "CO-133 N", 119, 147);
    addHighway("Glenwood Springs", "Montrose", "CO-133 S", 199, 147);
    addHighway("Montrose", "Glenwood Springs", "CO-65 N -> I-70 N", 142, 163);
    addHighway("Glenwood Springs", "Montrose", "I-70 W -> CO-65 S", 142, 163);
    addHighway("Gunnison", "Salida", "US-50 E", 64.3, 78);
    addHighway("Salida", "Gunnison", "US-50 W", 64.3, 78);
    addHighway("Alamosa", "Salida", "CO-17 -> US-285 N", 81.4, 82);
    addHighway("Salida", "Alamosa", "US-285 S -> CO-17", 81.5, 85);
    addHighway("Salida", "Alamosa", "US-285 S", 97.4, 104);
    addHighway("Alamosa", "Salida", "US-285 N", 97.4, 104);
    addHighway("Salida", "Pagosa Springs", "US-285 S -> US-160 W", 140, 152);
    addHighway("Pagosa Springs", "Salida", "US-160 E -> US-285 N", 140, 152);
    addHighway("Salida", "Aspen", "US-24 W -> I-70 W", 186, 215);
    addHighway("Aspen", "Salida", "I-70 E -> US-24 E", 186, 215);
    addHighway("Glenwood Springs", "Aspen", "CO-82", 41.3, 53);
    addHighway("Aspen", "Glenwood Springs", "CO-82", 41.3, 53);
}



void Colorado::addCity(string cityName)
{
    bool cityExists = false;
    
    for (int i = 0; i < cities.size(); i++)
    {
        if (cities[i]->cityName == cityName)
        {
            cityExists = true;
            break;
        }
    }
    
    if (!cityExists)
    {
        CityNode *newCity = new CityNode; //is it ok to allocate this statically? //no!
        newCity->cityName = cityName;
        cities.push_back(newCity);
        cout << newCity->cityName << " was added to cities!" << endl;
    }
}

//function to search for a city with cityName
CityNode* Colorado::searchCities(string cityName)
{
    
    //search cities for the city with cityName
    for (int i = 0; i < cities.size(); i++)
    {
        if (cities[i]->cityName == cityName)
        {
            return cities[i];
        }
    }

    //if a city with cityName wasn't found
    cout << cityName << " not found!!" << endl;
    return NULL;
}

void Colorado::addHighway(string firstCityName, string secondCityName, string hName, float distance, int travel)
{
    CityNode *firstCity = searchCities(firstCityName); //find the cityNode with name == firstCity
    CityNode *secondCity = searchCities(secondCityName); //find the second city

    Highway *firstTo2nd = new Highway;
    firstTo2nd->travelTime = travel;
    firstTo2nd->name = hName;
    firstTo2nd->city = secondCity; //creating a highway from firstCity -> secondCity
    firstTo2nd->distance = distance; //setting its distance
    firstCity->adjH.push_back(firstTo2nd); //adding that highway to firstCity's adjHighways

    Highway *secondTo1st = new Highway;
    secondTo1st->travelTime = travel;
    secondTo1st->name = hName;
    secondTo1st->city = firstCity;
    secondTo1st->distance = distance;
    secondCity->adjH.push_back(secondTo1st);
}

void Colorado::printColorado()
{
    for (int i = 0; i < cities.size(); i++)
    {
        cout << "Cities[" << i << "]:" << cities[i]->cityName << endl;
        for (int c = 0; c < cities[i]->adjH.size(); c++)
        {
            cout << "\t" << cities[i]->adjH[c]->city->cityName << " via " << cities[i]->adjH[c]->name << endl;
        }
    }
}
