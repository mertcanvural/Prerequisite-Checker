#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <list>
#include "Graph.h"

void buildGraph(string inputFile, Graph &prereqGraph)
{
    ifstream inFS;
    string aLine;

    unordered_map<string, list<vector<string>>> vertices;

    string aClass;
    vector<string> prereqs;
    string prereq;

    // each list element will have a container that indicates the prerequisites for a class on the same line...
    inFS.open(inputFile);

    if (!inFS.is_open())
    {
        cerr << "Failed to open file " << inputFile << endl;
        exit(1);
    }

    while (getline(inFS, aLine))
    {
        // reset the prereqs vector and prereq string
        prereqs.clear();
        prereq = "";

        stringstream ss(aLine);
        ss >> aClass;
        while (ss >> prereq)
        {
            if (vertices.find(prereq) == vertices.end())
            {
                vertices[prereq] = {};
            }
            // add the prerequisites on the line into a vector<string>
            prereqs.push_back(prereq);
        }
        // add the vector<string> into the list
        vertices[aClass].push_back(prereqs);
    }
    prereqGraph = Graph(vertices);
}

int checkViabilities(Graph &aGraph)
{
    if (aGraph.checkCycles() == 0)
    {
        if (aGraph.checkSixSemester() == 0)
        {
            cout << "Prerequsitie file is viable." << endl;
            return 0;
        }
    }
    return 1;
}