#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <fstream>
#include <map>

#include "Schedule.h"

using namespace std;

void makeSchedule(string schedFile, Schedule &studentSchedule)
{
    // declarations
    ifstream inFS;
    string aLine;

    string aClass;
    string semester;

    // third argument is the custom comparator
    map<string, string> schedList;
    unordered_map<string, int> semesterCounter;
    unordered_map<string, bool> takenCourses;

    // input check
    inFS.open(schedFile);
    if (!inFS.is_open())
    {
        cerr << "Failed to open file " << schedFile << endl;
        exit(1);
    }

    // read the input file
    while (getline(inFS, aLine))
    {
        stringstream ss(aLine);

        // adding the classes and the semester to a map (BST)
        // it basically stores the elements in sorted order
        while (ss >> aClass >> semester)
        {
            // check course
            if (!takenCourses[aClass])
                takenCourses[aClass] = true;
            else
            {
                cerr << "Error: course " << aClass << " is taken more than once\n";
                exit(1);
            }
            // check semester count
            if (semesterCounter.find(semester) == semesterCounter.end())
                semesterCounter[semester] = 1;
            else if (semesterCounter[semester] <= 3)
            {
                semesterCounter[semester]++;
            }
            else
            {
                cerr << "Error: too many courses taken in semester " << semester << endl;
                exit(1);
            }
            // add the class and semester pair into the map
            schedList[aClass] = semester;
        }
    }
    inFS.close();
    studentSchedule = Schedule(schedList);
}

int checkSchedule(Graph &prereqGraph, Schedule &studentSchedule)
{
    if (studentSchedule.checkPrerequisites(prereqGraph) == 0)
    {
            cout << "Student schedule is correct." << endl;
            return 0;
    }
    return 1;
}