#include "./utils/prereq_util.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
        cout << "format : ./pr_check <prereqfile>" << endl;

    string inputFile;

    inputFile = argv[1];
    // inputFile = "./txt/prereqs.txt";

    // create the graph for the prerequisites
    Graph prereqGraph;

    // build the graph
    buildGraph(inputFile, prereqGraph);

    // check the viabilities of the graph
    if (checkViabilities(prereqGraph))
    {
        // not viable
        return 1;
    }

    return 0;
}