#include<stdlib.h>
#include<time.h>
#include"Graph.h"
class Solution{
    private:
        bool isCal = false;
        bool* nodes=NULL; //the nodes chosen
        const int* terminals;
        int mincost=-1;//the solution's cost
        unsigned int num;//the chosen nodes's number
        unsigned int total;//the node's total number
        int terminalnum;
        Graph* g;
    public:
        Solution(){mincost;};
        Solution(const int* terminals,int total,Graph* g);
        ~Solution();
        unsigned int getNodenum(){return num;}
        unsigned int getTotal(){return total;};
        int getCost(){return mincost;};
        void setCost(int mincost){this->mincost=mincost;isCal=true;};
        void getNeighbor(Solution& s);
        bool* getNodes(){return nodes;};
        void initialguess();
        Solution& operator =(const Solution &s);
        Graph* getGraph(){return g;};
        void print();
        bool ifCal(){return isCal;}
};