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

	path->find_paths(std::string("a"), std::string("e"));
    // debug (show the paths found between 2 vertices that user specified)
    path->debug();
	
//////////////////////////////////////////////////////////problem//////////
 
  /* int counter ;
   int degree[2][2];
   origin_elist = elist ->next;
   for(int  i = 0; i < 2 ; i++)
	   while(elist != NULL){
            if((elist ->head->name)==(vlist[i]->name) ||(elist->tail->name)==(vlist[i]->name))
                counter = counter +1 ;  
aS
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
//dfs
    Edge *elist = nm->elist;

    // build the edges belong to vertex 
    while(elist!=NULL){
        adv[elist->head->name].push_back(elist);
        elist=elist->next;
    }

    // DFS
    // push this node into existed list
    existed_vertices.push_back(adv["b"].at(0)->head);
    dfs("b");

    Edge *dfs_elist=NULL, *tmp=dfs_elist;

    cout << "DFS: " << endl;
    for(int i=0;i<dfs_paths.size();i++){
        cout << dfs_paths.at(i)->head->name << "->" << dfs_paths.at(i)->tail->name << endl;
        if(tmp==NULL){
            dfs_elist = new Edge(dfs_paths.at(i));
            tmp = dfs_elist;
        } else {
            tmp->next = new Edge(dfs_paths.at(i));
            tmp = tmp->next;
        }
    }

    Gplot *gp = new Gplot();
    gp->gp_add(dfs_elist);
    gp->gp_dump(true);
    gp->gp_export("dfs/dfs");



//////////////////////////////////Fleury's Algorithm problem////////////////////////////////////////////	
/*
int tempGraph[NODE][NODE];

int findStartVert() {
   for(int i = 0; i<NODE; i++) {
      int deg = 0;
      for(int j = 0; j<NODE; j++) {
         if(tempGraph[i][j])
            deg++;    
      }

      if(deg % 2 != 0)     
         return i;         
   }
   return 0;   
}

bool isBridge(int u, int v) {
   int deg = 0;
   for(int i = 0; i<NODE; i++)
      if(tempGraph[v][i])
         deg++;

   if(deg>1) {
      return false;    
   }

   return true;  
}

int edgeCount() {
   int count = 0;
   for(int i = 0; i<NODE; i++)
      for(int j = i; j<NODE; j++)
         if(tempGraph[i][j])
            count++;
   return count;     
}

void fleuryAlgorithm(int start) {
   static int edge = edgeCount();
   for(int v = 0; v<NODE; v++) {
      if(tempGraph[start][v]) {       
         if(edge <= 1 || !isBridge(start, v)) {
            cout << start << "--" << v << " ";
            tempGraph[start][v] = tempGraph[v][start] = 0;    
            edge--;    //reduce edge
            fleuryAlgorithm(v);
         }
      }
   }
}

int main() {
   for(int i = 0; i<NODE; i++)     //copy main graph to tempGraph
      for(int j = 0; j<NODE; j++)
         tempGraph[i][j] = graph[i][j];
   cout << "Euler Path Or Circuit: ";
   fleuryAlgorithm(findStartVert());
}
   */
/////////////////////////////////////////////////////////////////////////////////////////////////////





    return 0;
}
void dfs(string src){
    for(int i=0;i<adv[src].size();i++){
        // cout << adv[src].at(i)->head->name << "=>" << adv[src].at(i)->tail->name << endl;
        // check edge is already existed or not
        if(find(dfs_paths.begin(), dfs_paths.end(), adv[src].at(i))==dfs_paths.end()){
            // check the tail is in the existed_vertices or not
            if(find(existed_vertices.begin(), existed_vertices.end(), adv[src].at(i)->tail)==existed_vertices.end()){
                // and push this edge into dfs result
                dfs_paths.push_back(adv[src].at(i));
                // not existed, then push into existed
                existed_vertices.push_back(adv[src].at(i)->tail);
                // recursive
                dfs(adv[src].at(i)->tail->name);
            }
        }
    }
}