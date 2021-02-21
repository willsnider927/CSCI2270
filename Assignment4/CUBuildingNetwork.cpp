/*******************************************************************/
/*                CUBuildingNetwork Implementation                 */
/*******************************************************************/
/* TODO: Implement the member functions of class CUBuildingNetwork */
/*       This class uses a linked-list of CUBuilding nodes to      */
/*       represent communication paths between buildings           */
/*******************************************************************/

#include "CUBuildingNetwork.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;

/*
 * Purpose: Constructor for empty linked list
 * @param none
 * @return none
 */
CUBuildingNetwork::CUBuildingNetwork() 
{
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
 *   between the CUBuilding *previous and the CUBuilding that follows it in the network.
 * @param previous name of the Building that comes before the new Building
 * @param buildingName name of the new Building
 * @param numOfroom
 * @return none
 */
void CUBuildingNetwork::addBuildingInfo(CUBuilding* previous, string buildingName, int totalRoom) 
{
    // TODO: Copy-paste your solution from Assignment 3
    CUBuilding* building = new CUBuilding;
    building->name = buildingName;
    building->next = 0;
    building->totalRoom = totalRoom;
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
 * Purpose: populates the network with the predetermined CUBuildings
 * @param none
 * @return none
 */
void CUBuildingNetwork::loadDefaultSetup()
{
    // TODO: Copy-paste your solution from Assignment 3
    deleteEntireNetwork();
    addBuildingInfo(head, "FLMG", 2);
    addBuildingInfo(searchForBuilding("FLMG"), "DLC", 10);
    addBuildingInfo(searchForBuilding("DLC"), "ECOT", 6);
    addBuildingInfo(searchForBuilding("ECOT"), "CASE", 5);
    addBuildingInfo(searchForBuilding("CASE"), "AERO", 4);
    addBuildingInfo(searchForBuilding("AERO"), "RGNT", 9);
    // MODIFICATION: Use deleteEntireNetwork function before adding buildings

}

/*
 * Purpose: Search the network for the specified building and return a pointer to that node
 * @param buildingName name of the building to look for in network
 * @return pointer to node of buildingName, or NULL if not found
 *
 */
CUBuilding* CUBuildingNetwork::searchForBuilding(string buildingName)
{
    // TODO: Copy-paste your solution from Assignment 3
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
 * Purpose: Relay a message through the linked list until the specified CUBuilding
 * @param string receiver
 * @param string msg
 */
void CUBuildingNetwork::transmitRoomInfo(string receiver)
{
    // TODO: Copy-paste your solution from Assignment 3
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
void CUBuildingNetwork::printNetwork() 
{
    // TODO: Copy-paste your solution from Assignment 3
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

/****************************************************/
/*  ASSIGNMENT 4: Functions to be completed below.  */
/****************************************************/

/*
 * Purpose: Delete the CUBuilding in the network with the specified name.
 * @param buildingName name of the CUBuilding to delete in the network
 * @return none
 */
void CUBuildingNetwork::deleteCUBuilding(string buildingName) 
{
    // TODO: Complete this function
    if (isEmpty()) {
        cout << "The list is empty." << endl;
        return;
    }
    CUBuilding* delRoom = searchForBuilding(buildingName);
    if (delRoom == NULL) {
        cout << "Building does not exist." << endl;
        return;
    } 
    else if (delRoom != head) {
        CUBuilding* curr = head;
        while (curr->next != delRoom) {
            curr = curr->next;
        }
        curr->next = delRoom->next;
        delete delRoom;
        delRoom = NULL;
        return;
    }
    else {
        head = head->next;
        delete delRoom;
        delRoom = NULL;
        return;
    }
}

/*
 * Purpose: deletes all CUBuildings in the network starting at the head CUBuilding.
 * @param: none
 * @return: none
 */
void CUBuildingNetwork::deleteEntireNetwork()
{
    // TODO: Complete this function
    if (isEmpty()) {
        return;
    }
    CUBuilding* curr = head->next;
    CUBuilding* prev = head;
    while (curr != NULL) {
        cout << "deleting: " << prev->name << endl;
        delete prev;
        prev = curr;
        curr = curr->next;
    }
    cout << "deleting: " << prev->name << endl;
    delete prev;
    prev = NULL;
    head = NULL;
    cout << "Deleted network" << endl;
    return;
}

/*
* Purpose: Creates a loop from last node to the CUBuilding specified.
* @param buildingName name of the CUBuilding to loop back
* returns the last node before loop creation (to break the loop)
*/
CUBuilding* CUBuildingNetwork::createLoop(string buildingName) 
{
    // TODO: Complete this function
    CUBuilding* loop = searchForBuilding(buildingName);
    CUBuilding* last = head;
    while (last->next != NULL) {
        last = last->next;
    }
    if (loop == NULL) {
        return last;
    }
    last->next = loop;
    return last;
}

/*
 * Purpose: to detect loop in the linked list
 * @return: true if loop is detected, else false
 */
bool CUBuildingNetwork::detectLoop() 
{
    // TODO: Complete this function
    CUBuilding* S = head;
    CUBuilding* F = head;
    while (F != NULL) {
        F = F->next->next;
        S = S->next;
        if (S == F) {
            return true;
        }
    }
    return false;
}

/*
 * Purpose: Take the chunk of nodes from start index to end index
 *          Move that chunk to the end of the List
 * @param: start_index, end_index
 * @return: none
 */
void CUBuildingNetwork::readjustNetwork(int start_index, int end_index)
{
    // TODO: Complete this function
    if (isEmpty()) {
        cout << "Linked List is Empty" << endl;
        return;
    }
    CUBuilding* last = head;
    int lastIDX = 0;
    while (last->next != NULL) {
        last = last->next;
        lastIDX++;
    }
    if (end_index < 0 || end_index >= lastIDX) {
        cout << "Invalid end index" << endl;
        return;
    }
    if (start_index < 0 || start_index >= lastIDX) {
        cout << "Invalid start index" << endl;
        return;
    }
    if (start_index > end_index) {
        cout << "Invalid indices" << endl;
        return;
    }
    CUBuilding* start = head;
    CUBuilding* end = head;
    CUBuilding* pre_start = start;
    for (int i = 0; i < start_index; i++) {
        pre_start = start;
        start = start->next;
    }
    for (int i = 0; i < end_index; i++) {
        end = end->next;
    }
    last->next = start;
    if (start == head) {
        head = end->next;
    }
    else {
        pre_start->next = end->next;
    }
    end->next = NULL;
    return;
}

/*
 * Purpose: Destructor to delete the entire list on program termination
 * @param none
 * @return none
 */
CUBuildingNetwork::~CUBuildingNetwork()
{
    // TODO: Complete this function
    deleteEntireNetwork();
}
