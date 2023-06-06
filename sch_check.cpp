#include "./utils/prereq_util.h"
#include "./utils/sched_util.h"

#include "./utils/Schedule.h"

// sched file

int main(int argc, char *argv[])
{
    if (argc != 3)
        cout << "format : ./sch_check <prereqfile> <schedulefile>" << endl;

    string prereqFile, schedFile;

    prereqFile = argv[1];
    schedFile = argv[2];

    // Graph for the prerequisite file
    Graph prereqGraph;

    // build the prerequisite graph
    buildGraph(prereqFile, prereqGraph);

    // check the viabilities of the graph
    if (checkViabilities(prereqGraph) == 1)
    {
        // not viable
        return 1;
    }

    Schedule studentSchedule;

    // make a schedule from the schedfile.txt
    makeSchedule(schedFile, studentSchedule);

    // check the schedule for flags
    if (checkSchedule(prereqGraph, studentSchedule))
    {
        return 1;
    }
    

    return 0;
}
