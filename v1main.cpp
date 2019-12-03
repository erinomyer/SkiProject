#include <iostream>
#include <vector>
#include <list>
#include "Mapv1.hpp"

using namespace std;

int main()
{
    // cout << "making colo" << endl;
    Colorado *stateOf = new Colorado;
    stateOf->buildCities();
    stateOf->buildHighways();
    stateOf->printColorado();
    // stateOf->addCity("Denver");
    // stateOf->addCity("Boulder");
    // stateOf->addHighway("Denver", "Boulder", 10);

    // cout << "making chair" << endl;
    // Chairlift *newLift = new Chairlift;
    // // cout << "out" << endl;
    // newLift->name = "AlpenGlow";
    // // cout << "of" << endl;
    // newLift->waitTime = 7;

    // // cout << "Creating resort node" << endl;
    // // cout << newLift->name << endl;
    // ResortNode *testResort = new ResortNode;
    // // cout << "HERE" << endl;
    // testResort->addChair("AlpenGlow", 7);
    // testResort->addChair("Indian Peaks", 3);
    // // cout << "hear" << endl;
    // // cout << testResort->findChair("AlpenGlow")->name;
    // // testResort->addRun("AlpenGlow", "HornBlower", "Dream", "Indian Peaks");
    // // testResort->addRun("AlpenGlow", "HornBlower", "Around the Horn", NULL);
    // testResort->addRunToChair("Hornblower", "Blue", "AlpenGlow");
    // testResort->addRunToChair("The one that gets to the bottom from Hornblower", "Blue", "AlpenGlow");
    // testResort->addRunToRun("Hornblower", "The one that gets to the bottom from Hornblower");
    // testResort->addChairToRun("The one that gets to the bottom from Hornblower", "AlpenGlow");
    // // cout << "hre" << endl;

}