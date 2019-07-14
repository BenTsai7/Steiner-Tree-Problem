#include "Graph.h"
bool Graph::getInput(const char* filename){
    if(isread) return false;
    std::ifstream ifs;
    ifs.open(filename);
    if(!ifs) return false;//open file error
    std::string sign;
    std::string Nodes("Nodes");
    while(sign.compare(Nodes)!=0){
        ifs>>sign;
    }
    ifs>>nodenum>>sign>>edgenum;
    //initial graph and edges
    graph = new int*[nodenum];
    for(int i=0;i<nodenum;++i){
        graph[i] = new int[nodenum];
    }
    for(int i=0;i<nodenum;++i)
        for(int j=0;j<nodenum;++j)
            graph[i][j]=INF;
    edges = new Edge [edgenum];
    //get input
    for(int i=0;i<edgenum;++i){
        ifs>>sign>>edges[i].from>>edges[i].to>>edges[i].weight;
        --edges[i].from;
        --edges[i].to;
        graph[edges[i].from][edges[i].to] = edges[i].weight;
        graph[edges[i].to][edges[i].from] = edges[i].weight;
    }
    std::string Terminals("Terminals");
    while(sign.compare(Terminals)!=0){
        ifs>>sign;
    }
    ifs>>sign;
    //start to get terminals
    ifs>>terminalnum;
    terminals = new int[terminalnum];
    for(int i=0;i<terminalnum;++i){
        ifs>>sign>>terminals[i];
        --terminals[i];
    }
    ifs.close();
    isread=true;
    return true;
};

Graph::~Graph(){
    if(isread) clear();
};

void Graph::clear(){
    if(!isread) return;
    isread=false;
    for(int i=0;i<nodenum;++i)
        delete[] graph[i];
    delete[] graph;
    delete[] terminals;
};

void Graph::getEdges(bool* nodes,std::set<Edge>& set){
    for(int i=0;i<edgenum;++i){
        bool a=false,b=false;
        a = (nodes[edges[i].to]);
        b = (nodes[edges[i].from]);
        if(a&&b) set.insert(edges[i]);
    }
};

void Graph::print(){
    printf("Graph:\n");
    printf("nodenum: %d\n",nodenum);
    for(int i=0;i<nodenum;++i){
        for(int j=0;j<nodenum;++j){
            if(graph[i][j]==INF) printf("-1 "); 
            else printf("%d ",graph[i][j]);
        }
        printf("\n");
    }
    printf("Edegs:\n");
    for(int i=0;i<edgenum;++i) printf("%d %d %d\n",edges[i].from+1,edges[i].to+1,edges[i].weight);
    printf("Terminals:\n");
    for(int i=0;i<terminalnum;++i) printf("%d ",terminals[i]+1);
    printf("\n");
};
void Graph::getGraphCopy(int**& g){
    g = new int*[nodenum];
    for(int i=0;i<nodenum;++i){
        g[i] = new int[nodenum];
    }
    for(int i=0;i<nodenum;++i)
        for(int j=0;j<nodenum;++j)
            g[i][j]=graph[i][j];
};
void Graph::freeGraph(int** g){
    for(int i=0;i<nodenum;++i)
        delete[] g[i];
    delete[] g;
};