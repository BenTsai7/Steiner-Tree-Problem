#include"ILS.h"
inline static int Kruskal(Solution& s);//used by Evaluationfunc
void ILS::run(){
    //initial solution and temperature
    Solution s0(g->getTerminalpt(),g->getNodenum(),g);
    s0.initialguess();//initial guess
    bestres = INF;
    srand((unsigned int)(time(NULL)));//intial random generator
    Solution lastbest;
    lastbest.setCost(INF);
    bool firstbest=true;
    int iter = equilibrium;
    int lastbestcost;
    while(iter){
        bool islocalbest=false;
        int count=0;
        while(!islocalbest){//not in the best local solution
            //generate a neighbor solution s'
            Solution s;
            s0.getNeighbor(s);
            //Evaluate
            int cost = Evaluationfunc(s)-Evaluationfunc(s0);
            //accept
            if(cost<=0) {
                s0=s;
                count=0;
                if(s0.getCost()<bestres) bestres=s0.getCost();
            }
            else{
                //add local count times
                ++count;
                if(count==localcount) {islocalbest=true;}//jump out local
            }   
            //s0.print();
        }
        if(firstbest){
            lastbest=s0;
            lastbestcost = s0.getCost();
        }
        else{
            if(s0.getCost()<=lastbestcost) {lastbest=s0;lastbestcost = s0.getCost();}
            else s0=lastbest;
        }
        islocalbest=false;
        count=0;
        --iter;
    }
}
//use Kruskal to caculate MST cost,it will be the evaluation result
int ILS::Evaluationfunc(Solution& s){
    //don't need recalculate
    if(s.ifCal()) return s.getCost();
    //need calculate
    int res = Kruskal(s);
    s.setCost(res);
    return res;
};
//used by Evaluationfunc
inline static int Kruskal(Solution& s){
    int ans=0,count=0;
    std::set<Edge> edges;
    (s.getGraph())->getEdges(s.getNodes(),edges);//get edges
    //sort edges while getEdges
    Union_Find_Set ufs(s.getNodes(),(s.getGraph())->getNodenum());//initial union-find set
    int edgenum = edges.size();
    for(auto iter=edges.begin();iter!=edges.end();++iter){
        if(ufs.join(iter->from,iter->to)){ //judge yes or not in the same block
            ans += iter->weight; //add it into MST
            ++count;
            if(count==s.getNodenum()-1) break;
        }
    }
    //if(count<s.getNodenum()-1) ans=INF;
    if(count<s.getNodenum()-1){
        //the nodes chosen not connected, using approximate evaluate shortest path
        ans=0;   
        int** graph;
        bool* solution = s.getNodes();
        Graph* g = s.getGraph();
        g->getGraphCopy(graph);
        int nodenum = g->getNodenum();//get Total
        int chosevertex = s.getNodenum();//get chosen
        int terminalnum = g->getTerminalnum();
        const int* terminalpt = g->getTerminalpt();
        int index[nodenum];//index map
        int terminalmap[chosevertex];
        //initial terminal map
        //map terminals to 0..1..2..3..4..5
        int tmpcount=0;
        for(int i=0;i<nodenum;++i){
            if(solution[i]==true){
                terminalmap[tmpcount]=i;
                ++tmpcount;
            }
        }
        for(int i=1;i<nodenum;++i) index[i]=i;
        index[0]=terminalmap[0];
        index[terminalmap[0]]=0;
        for(int t=0;t<chosevertex-1;++t){//iterator t times
            int dis[nodenum];
            bool vis[nodenum];
            std::vector<int> path[nodenum];
            for(int i=0;i<nodenum;++i){
                if(graph[index[0]][index[i]]!=INF)
                    {path[i].push_back(0);path[i].push_back(i);}
            }
            for(int i=0;i<nodenum;++i){
                dis[i]= graph[index[0]][index[i]];
                vis[i]=false;
            }
            dis[0]=0;
            vis[0]=true;
            for(int i=0;i<nodenum-1;++i){
                int v,w;
                int min=INF;
                for(w=0;w<nodenum;++w)
                    if(dis[w]<min&&!vis[w]){
                        v=w;
                        min=dis[w];
                    }
                vis[v]=true;
                for(int w=0;w<nodenum;++w){
                    if(!vis[w]){
                        if(min+graph[index[v]][index[w]]<dis[w]){
                            dis[w] = min+graph[index[v]][index[w]];
                            path[w].clear();
                            for(int i=0;i<path[v].size();++i) path[w].push_back(path[v][i]);
                            path[w].push_back(w);
                        }
                    }
                }
            }
            //route set to 0
            std::vector<int> &router = path[index[index[terminalmap[t+1]]]];
            ans+=dis[index[terminalmap[t+1]]];
            for(int i=0;i<router.size()-1;++i){
                int indexa = router[i];
                int indexb = router[i+1];
                graph[index[indexa]][index[indexb]]=0;
                graph[index[indexb]][index[indexa]]=0;
            }
        }
        g->freeGraph(graph);
    }
    return ans;
};