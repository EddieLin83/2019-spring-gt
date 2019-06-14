#include <algorithm>
#include <iostream>
#include <unistd.h>
#include <map>
#include "network_manager.h"
#include "gplot.h"
#include "path.h"
using namespace std;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NetworkManager *nm = new NetworkManager();
map<string, vector<Edge *>> adv;
vector<Edge *> dfs_paths;
vector<Vertex *> existed_vertices;
void dfs(string src);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv){
    // build basic topo
    nm->add_switch("a");
    nm->add_switch("b");
    nm->add_switch("c");
    nm->add_switch("d");    
    nm->add_switch("e");
以上5行是建立節點並且給予名稱
    nm->connect("a", "b");
    nm->connect("b", "c");
    nm->connect("c", "d");
    nm->connect("d", "e");
    nm->connect("e", "c");
    nm->connect("e", "b");
    nm->connect("c", "a");
以上7行是建立一個有向圖,此圖為moodle裡Project Announcement中的測資範例	
	nm->print_all_e();	
以上1行是顯示出建立出的有向圖邊連接狀況是否正確
	nm-> print_all_v();
以上1行是顯示出建立出的有向圖點的儲存狀況

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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



/////////////////////////////////////////////////////////////////////////////////////////////////	
/*
pair< vector<int>, vector<double> > Dijkstra(const Graph & G, int origin, const vector<double> & cost)
{
	BinaryHeap B;

	int n = G.GetNumVertices();

	//Father of each vertex in the optimal path tree
	vector<int> father(n, -1);

	//Used to indicate whether a vertex is permanently labeled
	vector<bool> permanent(n, false);

	vector<double> pathCost(n, numeric_limits<double>::infinity());
	
	//Put s in the heap
	B.Insert(0, origin);
	pathCost[origin] = 0;

	for(int i = 0; i < n; i++)
	{
		//Select the vertex that can be reached with smallest cost
		int u = B.DeleteMin();

		permanent[u] = true;

		//Update the heap with vertices adjacent to u
		for(list<int>::const_iterator it = G.AdjList(u).begin(); it != G.AdjList(u).end(); it++)
		{
			int v = *it;
			
			if(permanent[v])
				continue;

			double c = pathCost[u] + cost[G.GetEdgeIndex(u,v)];

			//v has not been discovered yet
			if(father[v] == -1)
			{
				father[v] = u;	
				pathCost[v] = c;
				B.Insert(c, v);
			}
			//we found a cheaper connection to v
			else if( LESS(c, pathCost[v]) )
			{
				father[v] = u;
				pathCost[v] = c;
				B.ChangeKey(c, v);
			}
		}
	}

	if(B.Size() > 0)
		throw "Error: graph is not connected";

	return make_pair(father, pathCost);
}   */

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