#include<math.h>
#include<vector>
#include"Graph.h"
#include"Solution.h"
#include"Union_Find_Set.h"
class ILS{
    private:
        const int localcount=10;
        int Evaluationfunc(Solution& s);
        const unsigned int equilibrium = 25;
        Graph* g;
        int bestres;
    public:
        void setGraph(Graph* g){this->g=g;}
        void run();
        int getResult(){return bestres;};
};