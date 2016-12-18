#define RRTNew_H
#include<iostream>
#include<vector>
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
using namespace std;

class RRTNodes
{
public:
    vector<double> configuration;  //Configuration that Each Node holds
    RRTNodes* Parent;       //The Pointer to the Nodes parent
    RRTNodes* getparent(); // Function to get the parent of given node
    RRTNodes();                             // Empty Constructor
    ~RRTNodes();                            // Destructor
    RRTNodes(vector<double> config);         // Constructor when you get a Config
    RRTNodes(vector<double> config, RRTNodes* parent);   //Constructor when you get a Config and the pointer
    vector<double> getconfig();
//void printconfig();                          // Get the Configuration of Given Node
};

class Tree
{
public:
    vector<RRTNodes*> _nodes;
    void addnode(RRTNodes* node);
    vector<RRTNodes*> getnodes();
//void deletenode(RRTNodes* node);
Tree();
~Tree();
};

//double EuclidDist(double Config1[3], double Config2[3]);
RRTNodes* NearestNeighbor(vector<double> Config,  Tree& tree);
double EuclidDist(vector<double> Config1, vector<double> Config2);
void RRTconnect(Tree &t, RRTNodes* node, vector<double> Config);
vector<RRTNodes*> RRTBuild(vector<double> initial,vector<double> goal);
bool collision(vector<double> config);
vector<double> vectoradd(vector<double> v1,vector<double> v2);
vector<double> vectorsubtract(vector<double> v1,vector<double> v2);
vector<double> Rand();
