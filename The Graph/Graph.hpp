//
//  Graph.hpp
//  The Graph
//
//  Created by Jacob Byerline on 11/16/19.
//  cssc0927   Red ID: 821301215
//  Copyright © 2019 Jacob Byerline. All rights reserved.
//

#ifndef Graph_hpp
#define Graph_hpp

#include <map>
#include <list>
#include <utility>
#include <set>

class Graph{
private:
    // Create map<string, pair<string, int>>
    std::map<std::string, std::list<std::pair<std::string, int>>> GraphList;
    
    // Create sets to make data management easier
    std::set<std::string> vertices;
    std::set<std::string> sources;
    std::set<std::string> destinations;
    
    // Create private functions, not accesible by the user.
    bool addEdge(std::string, std::string, int);
    void addVertex(std::string);
    bool containsEdge(std::string, std::string);
    bool containsVertex(std::string);
    bool removeVertex(std::string);
    bool removeEdges(std::string, std::string);
public:
    // Create public functions that driver/user class uses.
    void addSourceDestination(std::string, std::string, int);
    int totalVertices();
    std::list<std::string> withoutInboundEdges();
    std::list<std::string> withSelfEdges();
    std::list<std::string> withoutOutboundEdges();
    std::string edgeWithHeaviestWeight();
};

#endif

