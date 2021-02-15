/****************************************************************/
/*                CUBuildingNetwork Implementation                 */
/****************************************************************/
/* TODO: Implement the member functions of class CUBuildingNetwork */
/*     This class uses a linked-list of CUBuilding structs to      */
/*     represet communication paths between buildings             */
/****************************************************************/

#include "CUBuildingNetwork.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;
/*
 * Purpose: Constructer for empty linked list
 * @param none
 * @return none
 */
CUBuildingNetwork::CUBuildingNetwork() {
    /* finished. do not touch. */
    head = NULL;
}

/*
 * Purpose: Check if list is empty
 * @return true if empty; else false
 */
bool CUBuildingNetwork::isEmpty()
{
/* finished. do not touch. */
    return (head == NULL);
}

/*
 * Purpose: Add a new building to the network
 *   between the building *previous and the Building that follows it in the network.
 * @param previous name of the Building that comes before the new Building
 * @param buildingName name of the new Building
 * @param numOfroom
 * @return none
 */
void CUBuildingNetwork::addBuildingInfo(CUBuilding* previous, string buildingName, int numOfroom) {
    CUBuilding* building = new CUBuilding;
    building->name = buildingName;
    building->next = 0;
    building->totalRoom = numOfroom;
    building->numberMessages = 0;

    if (previous == 0) {
        building->next = head;
        head = building;
        cout << "adding: " << buildingName << " (HEAD)" << endl;
    }
    else {
        building->next = previous->next;
        previous->next = building;
        cout << "adding: " << buildingName << " (prev: " << previous->name << ")"<< endl;
    }
}


/*
 * Purpose: populates the network with the predetermined buildings
 * @param none
 * @return none
 */
void CUBuildingNetwork::loadDefaultSetup()
{
    addBuildingInfo(head, "FLMG", 2);
    addBuildingInfo(searchForBuilding("FLMG"), "DLC", 10);
    addBuildingInfo(searchForBuilding("DLC"), "ECOT", 6);
    addBuildingInfo(searchForBuilding("ECOT"), "CASE", 5);
    addBuildingInfo(searchForBuilding("CASE"), "AERO", 4);
    addBuildingInfo(searchForBuilding("AERO"), "RGNT", 9);
}

/*
 * Purpose: Search the network for the specified building and return a pointer to that node
 * @param buildingName name of the building to look for in network
 * @return pointer to node of buildingName, or NULL if not found
 *
 */
CUBuilding* CUBuildingNetwork::searchForBuilding(string buildingName)
{
    CUBuilding* curr = head;
    while(curr != NULL) {
        if (curr->name == buildingName) {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}


/*
 * Purpose:
 * @param string receiver
 * @param string msg
 */
void CUBuildingNetwork::transmitRoomInfo(string receiver) {
    if (head == NULL) {
        cout << "Empty list" << endl;
        return;
    }
    CUBuilding* final = searchForBuilding(receiver);
    if (final == NULL) {
        cout << "Building not found" << endl;
        return;
    }    
    CUBuilding* curr = head;
    while (curr != NULL) {
        curr->message = "available room at " + curr->name + " is " + to_string(curr->totalRoom);
        curr->numberMessages++;
        cout << curr->name << " [# messages received: " << curr->numberMessages <<"] received: " << curr->message << endl;
        if (curr == final) {
            return;
        }
        curr = curr->next;
    }
}

/*
 * Purpose: prints the current list nicely
 * @param ptr head of list
 */
void CUBuildingNetwork::printNetwork() {
    CUBuilding* curr = head;
    cout << "== CURRENT PATH ==" << endl;
    if (head == NULL) {
        cout << "nothing in path" << endl << "===" << endl;
        return;
    }
    while (curr != NULL) {
        cout << curr->name << "(" << curr->totalRoom << ") -> ";
        curr = curr->next;
    }
    cout << "NULL" << endl << "===" << endl;
  }
