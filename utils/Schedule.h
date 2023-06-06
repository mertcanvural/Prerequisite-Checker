#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <utility>
#include <unordered_map>
#include <map>
#include <string>
#include "Graph.h"

#include <algorithm>

using namespace std;

bool compareSemesters(const pair<string, string> &a, const pair<string, string> &b)
{

    int year1 = stoi(a.second.substr(0, 4));
    int year2 = stoi(b.second.substr(0, 4));
    string sem1 = a.second.substr(4);
    string sem2 = b.second.substr(4);

    if (year1 < year2)
    {
        return true;
    }
    else if (year1 > year2)
    {
        return false;
    }

    if (sem1 == "Fall" && (sem2 == "Spring" || sem2 == "Summer"))
    {
        return true;
    }
    else if (sem1 == "Spring" && sem2 == "Summer")
    {
        return true;
    }
    else
    {
        return false;
    }
}

// custom comparator
// custom comparator for the semesters

class Schedule
{
private:
    map<string, string> scheduleList;

public:
    Schedule()
    {
        scheduleList = {};
    }
    Schedule(map<string, string> &schedList)
    {
        scheduleList = schedList;
    }

    int checkPrerequisites(Graph &prereqGraph)
    {
        //
        unordered_map<string, bool> courseTaken;
        unordered_map<string, list<vector<string>>> vertices = prereqGraph.getVertices();

        // sorting the semesters in order
        vector<pair<string, string>> sorted_courses(scheduleList.begin(), scheduleList.end());
        sort(sorted_courses.begin(), sorted_courses.end(), compareSemesters);

        for (const auto &course : sorted_courses)
        {
            if (vertices.find(course.first) == vertices.end())
            {
                courseTaken[course.first] = true;
            }
            else if (vertices[course.first].empty())
            {
                courseTaken[course.first] = true;
            }
            else
            {
                list<vector<string>>::iterator it;
                for (it = vertices[course.first].begin(); it != vertices[course.first].end(); it++)
                {
                    for (string prereq : *it)
                    {
                        if (courseTaken[prereq] != true)
                        {
                            cout << "Schedule is bad." << endl;
                            cout << course.first << " is attempted to be taken before " << prereq << endl;
                            exit(1);
                        }
                    }
                }
            }
        }
        return 0;
    }
};

#endif
