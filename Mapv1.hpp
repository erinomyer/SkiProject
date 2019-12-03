#include <iostream>
#include <vector>
#include <list>

using namespace std;

struct Chairlift; //empty struct definitions to allow a Run to be constructed
struct runEdge;
struct Run
{
    Run()
    {
        this->name = "";
        this->lift = NULL;
    }
    string name;
    vector<runEdge*> branches;
    Chairlift *lift; //init to NULL, only change when lift ends at a chair
    string difficulty; //Green, Blue, Black Diamond, Double Black, Triple Black
};

//directed edge between two Run objs.
//will be added to a Run's branches vec
struct runEdge
{
    Run *nextRun; //pointer to the adjacent Run
};

//'vertex' in the Resort graph
struct Chairlift
{
    Chairlift()
    {
        this->name = "";
        this->waitTime = 0;
    }
    string name; //name of the Chairlift
    int waitTime; //could be a product of distance from parking lot & number of skiiers on a day?

    vector<Run*> accessibleRuns; //each chairlift has distinctly accessible runs, with little overlap
                                 //i.e. a run will likely not be accessible by two lifts

};



struct ResortMap
{
    // ResortMap()
    // {
    //     columns = 0;
    //     rows = 0;
    // }
    const static int columns;
    const static int rows;
    string ResortMap[134][24];
};

//ResortNodes are 
class ResortNode
{
    private:
            // need hash table of renters' rentals (maybe attributes about how many chairlift rides they've taken, etc)
            //index generated by hashing the given name
        // CONST int mapWidth = 134;
        // CONST int mapHeight = 24;
        string resortName;
        string resortLogo[134][24]; //may not get to all of these
        string resortMap[134][24]; //how to specify dimensions? could do it specifically for Eldo, since that's probably the only one I'll finish lol

        string pass; //'IKON', 'EPIC', 'RESORT', 'NONE'. charge pricePerDay if 'NONE' 
        float pricePerDay; //0 if they have pass!
        int numSkiers; //could be determined each day, as a product of some scalable population multiplier (eldora's may be smaller than breck's) & a weekday multiplier?
        vector <Chairlift*> lifts; //vector of this resorts chairlifts. each chairlift will have its own vector of accessible runs

    public:
        ResortNode();
        ~ResortNode(); //do we need this? //probably not
        void addChair(string chairName, int chairTime);
        Chairlift* findChair(string chairName);
        void addRunToChair(string runToAdd, string runDiff, string liftToAddTo); //creates a run with the given difficulty, adds it to the lift's accessibleRuns
        void addChairToRun(string runToAddTo, string liftToAdd); //adds a chair to a run. signifies that you have reached the bottom of a slope
        void addRunToRun(string runToAddTo, string runToAdd); //creates a run edge and a run, points the run edge to the run, and adds that run edge to runToAddTo's branches vec
        Run* findRun(string runName);
        void printMountain(); //will print this resort's map (if we've gotten to it. odds are, we won't, and this will only function for Eldora)
        int getPrice(int numPatrons);
        Chairlift* takeRun(string chairName); //will take you up the specified chairlift, display the runs you can take at the top, and display choices on the way down for forked paths. 
                                              //returns a pointer to the Chairlift that you ended up at
        void setMap(int columns, int rows);

};


//will be pushed onto a customer's rental list at their index in the rental hash table
struct Rental
{
    Rental()
    {
        this->numDays = 0;
        this->name = "";
    }
    int numDays;
    string name;
};

class RentalHash
{
    private:
        int tablesize;
        list<Rental> *rentals;//pointer to a list containing all of your rentals
    public:

};

struct Highway;

struct CityNode
{
    CityNode()
    {
        this->cityName = "";
        this->visited = false;
        this->resort = NULL;
        this-> previous = NULL;
    }
    string cityName;
    bool visited; //for use earching for the smallest distance. make sure to unvisit!
    vector <Highway*> adjH; //list of this city's adjacent cities
    Rental *resort; // NULL if this city doesn't have a ski resort
    CityNode *previous; //to be used in shortest path. need to unvisit each time!!
};

//edge between two cities
struct Highway
{
    Highway()
    {
        distance = 0.0;
        city = NULL;
        name = "";
    }
    float distance;
    string name;
    int travelTime;
    //possibly a 'closed' bool to represent bad weather?
    CityNode *city;
};

//graph of Colorado
//comprised of a vector of cityNodes connected by highways
//cities with ski resorts (e.g. breck) will point to a resortNode
class Colorado
{
    private:
        vector<CityNode*> cities; //graph of Colorado's cities & resorts (i.e. vertices)
        float snowfall; //should range from 0-100 (real quick)
        string month; //will be used as a multiplier to determine value of snowfall

    public:
        Colorado(); //will call addCity & addHighway to create major "hub" cities & the highways that connect them
        void buildCities();
        void buildHighways();
        void addCity(string cityName);
        CityNode* searchCities(string cityName); //return the city in Colorado with the given name (if it exists)
        void addHighway(string firstCity, string secondCity, string name, float distance, int travelTime);
        // void deleteCity(cityNode); 
        // void deleteHighway(CityNode, cityNode); ////why would we need this? maybe to 'close' a highway during bad conditions??? -> see update to highway struct 
        void printColorado(); //maybe display something where the user is located? or centered there?

        void unvisitCities(); //unvisit each city in Colorado. to be done after finding paths
        int determineSnowfall(string month);
        CityNode* shortestPath(CityNode *startCity, CityNode *endCity);

};
                                                                               