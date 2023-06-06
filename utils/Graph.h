#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <queue>
#include <stack>

using namespace std;

class Graph
{
private:
    unordered_map<string, list<vector<string>>> vertices;
    unordered_map<string, int> visitedList;

public:
    Graph()
    {
        {
            vertices = {};
        }
    }
    ~Graph()
    {
        vertices.clear();
        visitedList.clear();
    }
    Graph(unordered_map<string, list<vector<string>>> &v)
    {
        vertices = v;
    }

    unordered_map<string, list<vector<string>>> &getVertices()
    {
        return vertices;
    }

    int checkCycles()
    {
        unordered_set<string> currentPath;
        // color all vertices to white at first
        for (auto &vertex : vertices)
        {
            visitedList[vertex.first] = 0;
        }

        // cycle end
        string secondClassInCycle = "";

        // calling each unvisited vertex
        for (auto vertex : vertices)
        {
            if (visitedList[vertex.first] == 0)
            {
                if (checkCyclesAux(vertex.first, visitedList, currentPath))
                {
                    return 1; // cycle
                }
                // current path is used for checking indirect cycles
                currentPath.clear();
            }
        }
        // no cycles
        return 0;
    }
    int checkCyclesAux(string className, unordered_map<string, int> &visitedList, unordered_set<string> &currentPath)
    {
        // color gray
        visitedList[className] = 1;
        currentPath.insert(className);
        // iterating over the adjacent vertices
        list<vector<string>>::iterator it;
        for (it = vertices[className].begin(); it != vertices[className].end(); it++)
        {
            for (string prereq : *it)
            {
                if (visitedList[prereq] == 1)
                {
                    cout << "not viable" << endl;
                    cout << "Direct Cycle : " << className << " && " << prereq << endl;
                    return 1; // cycle
                }
                else if (visitedList[prereq] == 0)
                {
                    // program counter is used as stack
                    if (checkCyclesAux(prereq, visitedList, currentPath))
                    {
                        return 1; // cycle
                    }
                }
                else if (currentPath.count(prereq) > 0)
                {
                    cout << "not viable" << endl;
                    cout << "Indirect Cycle : " << className << " && " << prereq << endl;
                    return 1; // cycle
                }
            }
        }
        // color black
        visitedList[className] = 2;
        return 0;
    }

    int checkSixSemester()
    {
        // find the classes that don't have any prerequisites
        unordered_set<string> classesWithNoPrereqs;
        for (auto &vertex : vertices)
        {
            if (vertex.second.empty())
            {
                classesWithNoPrereqs.insert(vertex.first);
            }
        }
        // TODO : only do a BFS on the classes that don't have any prerequisites
        // reverse the edges
        // unordered_map<string, list<vector<string>>> reverseEdges;
        // list<vector<string>>::iterator it;

        // Check the six-semester requirement for all vertices
        for (const auto &startVertex : vertices)
        {
            checkSixSemesterAux(startVertex.first);
        }
        return 0;
    }
    int checkSixSemesterAux(string startVertex)
    {
        // Initialize distances to all other nodes to -1 (unknown)
        unordered_map<string, int> distance;
        for (auto &vertex : vertices)
        {
            distance[vertex.first] = -1;
        }

        // Use BFS to compute distances from the start node
        distance[startVertex] = 0;
        queue<string> q;
        q.push(startVertex);
        while (!q.empty())
        {
            // pop
            string currVertex = q.front();
            q.pop();
            // look at the adjacent vertices
            list<vector<string>>::iterator it;

            for (it = vertices[currVertex].begin(); it != vertices[currVertex].end(); it++)
            {
                for (string prereq : *it)
                {
                    if (distance[prereq] == -1)
                    {
                        distance[prereq] = distance[currVertex] + 1;
                        if (distance[prereq] > 6)
                        {
                            cout << startVertex << " requires more than six semesters to finish" << endl;
                            return 1;
                        }
                        // push the adjacent vertex
                        q.push(prereq);
                    }
                }
            }
        }
        return 0;
    }

    int showGraph()
    {
        for (auto &vertex : vertices)
        {
            cout << vertex.first << " -> ";
            list<vector<string>>::iterator it;
            for (it = vertex.second.begin(); it != vertex.second.end(); it++)
            {
                for (string prereq : *it)
                {
                    cout << prereq << " ";
                }
            }
            cout << endl;
        }
        return 0;
    }
};

#endif