#include "Graph.hpp"
#include <vector>
#include <queue>
#include<iostream>

using namespace std;

void Graph::addVertex(string name) {
    for (int i = 0; i < vertices.size(); i++) { //check if already added
        if (vertices[i]->name == name) return;
    }
    vertex* newVert = new vertex;
    newVert->name = name;
    vertices.push_back(newVert); //add new vertex
}

void Graph::addEdge(string v1, string v2) {
    vertex* v1ptr = nullptr;
    vertex* v2ptr = nullptr;
    for (int i = 0; i < vertices.size(); i++) {
        if (vertices[i]->name == v1) v1ptr = vertices[i];
        if (vertices[i]->name == v2) v2ptr = vertices[i];
    } 
    if (!v1ptr || !v2ptr) return; //check if either aren't in graph

    adjVertex v1Adj; v1Adj.v = v1ptr;
    adjVertex v2Adj; v2Adj.v = v2ptr; // create edge variables
    v1ptr->adj.push_back(v2Adj);
    v2ptr->adj.push_back(v1Adj); // add edges
}

void Graph::displayEdges() {
    for(int i = 0; i < vertices.size(); i++) { // iterate through vertices 
        cout << vertices[i]->name << " --> ";
        for (auto it = vertices[i]->adj.begin(); it != vertices[i]->adj.end(); it++){ //print each vertices adjacency list
            cout << it->v->name << " ";
        }
        cout << endl;
    }
}

void Graph::breadthFirstTraverse(string sourceVertex) {
    vertex* curr = nullptr;
    for (int i = 0; i < vertices.size(); i++) { //initially set all to not be visited and find source
        vertices[i]->visited = false;
        vertices[i]->distance = 0;
        if(vertices[i]->name == sourceVertex) curr = vertices[i];
    }
    if (!curr) return; //no source

    cout << "Starting vertex (root): " << curr->name << "-> ";
    queue<vertex*> waiting;
    curr->visited = true;
    waiting.push(curr); //add root to queue

    while (!waiting.empty()) {
        curr = waiting.front();
        waiting.pop();

        for(auto it = curr->adj.begin(); it != curr->adj.end(); it++) {
            if (!it->v->visited) { //add unvisited nodes with their distance
                it->v->visited = true;
                it->v->distance = curr->distance +1;
                cout << it->v->name << "(" << it->v->distance << ")" << " ";
                waiting.push(it->v);
            }
        }
    }
}

void _breadthFirstTraverse(vertex* curr) {
    queue<vertex*> waiting;
    curr->visited = true;
    waiting.push(curr);

    while (!waiting.empty()) {
        curr = waiting.front();
        waiting.pop();

        for (auto it = curr->adj.begin(); it != curr->adj.end(); it++) {
            if (!it->v->visited) {
                it->v->visited = true;
                waiting.push(it->v);
            }
        }
    }
}

int Graph::getConnectedBuildings() {
    int colors = 1;
    for (int i = 0; i < vertices.size(); i++) { //initially set all to not be visited
        vertices[i]->visited = false;
    }

    _breadthFirstTraverse(vertices[0]); //traverse from any position first
    for (int i = 0; i < vertices.size(); i++) {
        if (!vertices[i]->visited) { //iterate until a vertex isn't visited
            colors++; //increment colors
            _breadthFirstTraverse(vertices[i]); //search from there to fully color from said vertex    
        }
    }
    return colors;
}
