//
//  main.cpp
//  The Graph
//
//  Created by Jacob Byerline on 11/16/19.
//  cssc0927   Red ID: 821301215
//  Copyright © 2019 Jacob Byerline. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "Graph.hpp"

#define BUFFSIZE 1000

using namespace std;

int main(int argc, const char * argv[]) {
    
    string input;
    string values[BUFFSIZE];
    Graph myFirstGraph;

    // File input stream
    ifstream CSVFile ("/Users/jacobbyerline/Desktop/vietnam.csv", ifstream::in);
    for (int i = 0; CSVFile.good(); i++) {
        getline ( CSVFile, input, '\n' );
        values[i] = input;
    }
    
    // Parse input string so that graph can read it
    for(int i = 0; i < BUFFSIZE; i++){
        if(values[i] == "") break;
        string temp = values[i];
        string source = "";
        string destination = "";
        string scost = "";
        int cost = 0;
        int commaCount = 0;
        for(int j = 0; j < temp.length(); j++) {
            if(temp[j] == ','){
                commaCount++;
            }
            else if(commaCount == 0){
                source = source + temp[j];
            }
            else if(commaCount == 1){
                destination = destination + temp[j];
            }
            else if(commaCount == 2){
                scost = scost + temp[j];
                cost = stoi(scost);
            }
        }
        // Add source, destination, cost to graph
        myFirstGraph.addSourceDestination(source, destination, cost);
    }
    
    // Output file stream
    ofstream outFile;
    outFile.open ("/Users/jacobbyerline/Desktop/curContents.txt");
    
    // Run and print totalVerticies function
    outFile << "Total Vertices: " << myFirstGraph.totalVertices() << endl;
    
    // Run and print w/o inbound edges function
    list<string>temp = myFirstGraph.withoutInboundEdges();
    if(!temp.empty()){
        outFile << "Vertices with no inbound edges: ";
        for (string temporary : temp) {
            outFile << temporary << " ";
        }
        outFile << endl;
    }
    else{
        outFile << "All vertices have inbound edges" << endl;
    }
    
    // Run and print w/o outbound edges function
    list<string>temp1 = myFirstGraph.withoutOutboundEdges();
    if(!temp1.empty()){
        outFile << "Vertices with no outbound edges: ";
        for (string temporary1 : temp1) {
            outFile << temporary1 << " ";
        }
        outFile << endl;
    }
    else{
         outFile << "All vertices have outbound edges" << endl;
    }
    
    // Run and print has self edges function
    list<string>temp2 = myFirstGraph.withSelfEdges();
    if(!temp.empty()){
        outFile << "Vertices with self edges: ";
        for (string temporary2 : temp2) {
            outFile << temporary2 << " ";
        }
        outFile << endl;
    }
    else{
        outFile << "No vertices have self edges " << endl;
    }
    
    // Run and print heaviest weight function
    outFile << "Heaviest weight: " << myFirstGraph.edgeWithHeaviestWeight() << endl;
    
    return 0;
}
