#include <algorithm>
#include <iostream>
#include <unistd.h>
#include <map>
#include "network_manager.h"
#include "gplot.h"
#include "path.h"
using namespace std;

// create NetworkManager first
NetworkManager *nm = new NetworkManager();
map<string, vector<Edge *>> adv;
vector<Edge *> dfs_paths;
vector<Vertex *> existed_vertices;

void dfs(string src);

int main(int argc, char** argv){
    // build basic topo
    nm->add_switch("a");
    nm->add_switch("b");
    nm->add_switch("c");
    nm->add_switch("d");    
    nm->add_switch("e");


    nm->connect("a", "b");
    nm->connect("b", "c");
    nm->connect("c", "d");
    nm->connect("d", "e");
    nm->connect("e", "c");
    nm->connect("e", "b");
    nm->connect("c", "a");
	


	nm->print_all_e();	
	nm-> print_all_v();

/////////////////////////////////////////////////////////////////////////////////
	// create path
    Path *path;
    path=new Path();
    // create tree from edge list
    path->append(nm->elist);
    // find paths (will return std::vector<std::vector<Node *>> object)

	path->find_paths(std::string("e"), std::string("a"));
    // debug (show the paths found between 2 vertices that user specified)
    path->debug();
	
//////////////////////////////////////////////////////////check degree of node//////////
 
 /*  int counter ;
   
   origin_elist = elist ->next;
   for(int  i = 0; i < 2 ; i++)
	   while(elist != NULL){
            if((elist ->head->name)==(vlist[i]->name) ||(elist->tail->name)==(vlist[i]->name))
                counter = counter +1 ;  

            else
                counter =	;
               
                origin_elist = elist ->next;
	   }
    degree[i][1]=counter;
    if(counter % 2!=0)
        degree[i][2] = 1 ;
    else   	
        degree[i][2] = 0 ;
    counter = 0;
	
	elist = nm-> elist;
	
}
for(int  i = 0; i < 2 ; i++){
	cout << degree[i][1]<<"i"<<degree[i][2]<<end1;
	
}*/
/////////////////////////////////////////////////////////////////////////////   

   
    

/////////////////////////////////////////////////////////////////////////////////////////////////	


/////////////////////////////////////////////////////////////////////////////////////////////////////





    return 0;
}