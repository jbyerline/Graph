//
//  Graph.cpp
//  The Graph
//
//  Created by Jacob Byerline on 11/16/19.
//  cssc0927   Red ID: 821301215
//  Copyright © 2019 Jacob Byerline. All rights reserved.
//
#include <map>
#include <list>
#include <utility>
#include <string>
#include "Graph.hpp"

// Add vertices to graph if they do not already exist
void Graph::addVertex(std::string vertex){
    // vertex does not exist
    if (vertices.find(vertex) == vertices.end()) {
        vertices.insert(vertex);
    }
}

// Add edge value to graph
bool Graph::addEdge(std::string source, std::string destination, int cost) {
    // If source or destination doesnt exist, return false
    if (vertices.find(source) == vertices.end() || vertices.find(destination) == vertices.end() ) {
        return false;
    }
    // Otherwise, add edge between source and destination
    std::pair<std::string, int> pair;
    pair.first = destination;
    pair.second = cost;
    GraphList[source].push_back(pair);
    return true;
}

// Adds source data to the graph.
void Graph::addSourceDestination(std::string source, std::string destination, int cost) {
    addVertex(source);
    addVertex(destination);
    //updates source and destination sets
    if (sources.find(source) == sources.end()) {
        sources.insert(source);
    }
    if (destinations.find(destination) == destinations.end()) {
        destinations.insert(destination);
    }
    addEdge(source, destination, cost);
}

// Check to see that a given edge exists in the map
bool Graph::containsEdge(std::string source, std::string destination) {
    
    std::list<std::pair<std::string, int>> tempList = GraphList[source];
    
    for(std::pair<std::string,int> tempPair : tempList){
        if(tempPair.first == destination){
            return true;
        }
    }
    return false;
}

// Check that a vertex doesnt already exist
bool Graph::containsVertex(std::string vertex){
    // vertex does not exist
    if (vertices.find(vertex) == vertices.end()) {
        return false;
    }
    return true;
}

// Count number of vertices
int Graph::totalVertices() {
    return vertices.size();
}

// Find vertices who have edges that point away from them
std::list<std::string> Graph::withoutOutboundEdges() {
    std::list<std::string> temp;
    for (std::string vertex : vertices) {
        if (sources.find(vertex) == sources.end()) {
            temp.push_back(vertex);
        }
    }
    return temp;
}

// Find verticies who have edges that point to them
std::list<std::string> Graph::withoutInboundEdges() {
    std::list<std::string> temp;
    for (std::string vertex : vertices) {
        if (destinations.find(vertex) == destinations.end()) {
            temp.push_back(vertex);
        }
    }
    return temp;
}

// Find verticies who point to them selves (Self Edge)
std::list<std::string> Graph::withSelfEdges() {
    std::list<std::string> pointToSelfers;
    for (std::string vertex : vertices){
        std::list<std::pair<std::string, int>> tempList = GraphList[vertex];
        for(std::pair<std::string,int> tempPair : tempList){
            if(tempPair.first == vertex){
                pointToSelfers.push_back(vertex);                
            }
        }
    }
    return pointToSelfers;
}

// Find heaviest weighing edge
std::string Graph::edgeWithHeaviestWeight() {
    std::string heavyBois;
    int max = 0;
    for (std::string vertex : vertices){
        std::list<std::pair<std::string, int>> tempList = GraphList[vertex];
        for(std::pair<std::string,int> tempPair : tempList){
            if(tempPair.second > max){
                max = tempPair.second;
                heavyBois = vertex + " -> " + tempPair.first + " = " + std::to_string(max);
            }
        }
    }
    return heavyBois;
}

// Remove Vertex Function
bool Graph::removeVertex(std::string vertex) {
    //check if exists
    if (vertices.find(vertex) == vertices.end()) {
        return false;
    }
    for (std::string temp : vertices){
        std::list<std::pair<std::string, int>> tempList = GraphList[temp];
        std::list<std::pair<std::string, int>>::iterator i = tempList.begin();
        for(std::pair<std::string,int> tempPair : tempList){
            if(tempPair.first == vertex || vertex == temp) {
                tempList.erase(i);
                i++;
            }
            else{
                i++;
            }
        }
        GraphList[temp] = tempList;
    }
    
    GraphList.erase(vertex);
    sources.erase(vertex);
    destinations.erase(vertex);
    vertices.erase(vertex);
    return true;
}

// Remove Edges Function
bool Graph::removeEdges(std::string source, std::string destination) {
    std::list<std::pair<std::string, int>> tempList = GraphList[source];
    std::list<std::pair<std::string, int>>::iterator i = tempList.begin();
    for(std::pair<std::string,int> tempPair : tempList){
        if(tempPair.first == destination) {
            tempList.erase(i);
            return true;
        }
        else{
            i++;
        }
    }
    return false;
}
