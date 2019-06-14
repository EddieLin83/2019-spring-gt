演算法思路
步驟1.建立graph
步驟2.一開始要先檢查graph中degree為基數的點,如果沒有degree為基數的點,那此圖為尤拉圖,
	   如果有則要將此圖尤拉化,將圖尤拉化是在圖中加上一些邊,使得新圖中會存在尤拉迴圈,
	   這些加上的邊是指重覆走的邊,因此若想在兩點間加上一條邊,必須是這兩點間原本就有的邊才行
		2.1如果有degree為基數的點:找出這些點之後,會兩兩分組,然後在同一組中的兩點間加一條路徑連接它們,
		   找出最佳配對後進行下一個步驟	
		2.2如果沒有degree為基數的點:進行下一個步驟
步驟3.找尤拉迴圈,這裡採用Fleury's Algorithm可以直接找到,即為最短路徑


以下為code擷取部分大致介紹
////////////////////建立Project Announcement上測資範例的graph,並且看邊的連線是否正確////////////////////////////
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
//////////////////////////////////////找出degree為基點的點//////////////////////////////////////////////////////
 int counter ;
   int degree[2][2];
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
	
}
/////////////////////////////////////////////////////////////dfs/////////////////////////////////////////////////  
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
//////////////////////////////Fleury's Algorithm這裡有問題/////////////////////////////////////////////////////	
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
//////////////////////////////////////////////////////////////////////////////////////////////////////////////




