#include "RRTNew.h"
using namespace std;
//Beginning of Constructors
double upper_limit[3]={100,100,100};
double lower_limit[3]={-100,-100,-100};

//Random Functions
vector<double> Rand()
{
double randomval=0;
randomval=(double) rand()/(RAND_MAX);
vector<double> randval;
for(int i=0;i<3;i++)
{
randval.push_back (randomval*(upper_limit[i]-lower_limit[i])+lower_limit[i]);
}
return randval;


}

RRTNodes::RRTNodes()
{
Parent=NULL;
}

RRTNodes::RRTNodes(vector<double> config)
{

Parent=NULL;
//std::copy(config,config+3,configuration);
configuration=config;
}

RRTNodes::RRTNodes(vector<double> config,RRTNodes* parent)
{
Parent=parent;
configuration=config;
//std::copy(config,config+3,configuration);
}
//Destructor
RRTNodes::~RRTNodes()
{
Parent=NULL;
configuration.clear();
}

RRTNodes* RRTNodes::getparent()
{

return Parent;

}


vector<double> RRTNodes::getconfig()
{
return configuration;
}

// Constructors for Tree

Tree::Tree()
{
_nodes.clear();
}
//Destructor
Tree::~Tree()
{
_nodes.clear();
}
//functions
void Tree::addnode(RRTNodes* Node)
{
_nodes.push_back(Node);
}

vector<RRTNodes*> Tree::getnodes()
{

return _nodes;
}

RRTNodes* NearestNeighbor(vector<double> config, Tree& tree )
{

double temp=1000000;
double len=0;
int index=0;
for(int i =0; i<tree.getnodes().size();i++)
{
len=EuclidDist(config,tree.getnodes()[i]->getconfig());
if (len<temp)
{
temp=len;
index=i;
}}
return tree.getnodes()[index];
}
//Other Functions

double EuclidDist(vector<double> config1, vector<double> config2)
{
double dist;
for(int i=0;i<3;i++)
{
dist=(pow(config1[i]-config2[i],2));
}
return sqrt(dist);
}
void RRTconnect(Tree& t, RRTNodes* nearest,vector<double> config )
{
vector<double> unitvector;
RRTNodes* step;
step=nearest;
double Dist;
Dist=EuclidDist(config,nearest->getconfig());
for(int i=0; i<config.size();i++)
{
unitvector.push_back(0.75*((config[i]-nearest->getconfig()[i])/Dist));
}

do
{
if(collision(vectoradd(step->getconfig(),unitvector))==true)
{
step=new RRTNodes(vectoradd(step->getconfig(),unitvector),step);
t.addnode(step);
}
}while(EuclidDist(config,step->getconfig())>=0.25);

}

bool collision(vector<double> config)
{
return true;
}

vector<double> vectoradd(vector<double> v1,vector<double> v2)
{
vector<double> v3;
for(int i=0; i<v1.size();i++)
{
v3.push_back(v1[i]+v2[i]);
}
return v3;
}

vector<double> vectorsubtract(vector<double> v1,vector<double> v2)
{
vector<double> v3;
for(int i=0; i<v1.size();i++)
{
v3.push_back(v1[i]-v2[i]);
}
return v3;
}

vector<RRTNodes*> RRTBuild(vector<double> initial,vector<double> goal)
{
RRTNodes* start;
vector<double> qrand;
start=new RRTNodes (initial);
Tree t;
t.addnode(start);
RRTNodes* Nearest;
float bias=0.15;
do{
if((float) rand()/(RAND_MAX)> bias)
{qrand=Rand(); }//Write Rand function
else qrand=goal;
Nearest=NearestNeighbor(qrand,t);
RRTconnect(t,Nearest,qrand);

}while(EuclidDist(t.getnodes()[t.getnodes().size()-1]->getconfig(),goal)>=0.25);


}
