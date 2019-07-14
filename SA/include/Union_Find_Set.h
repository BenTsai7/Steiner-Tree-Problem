#include<map>
//used by Kruskal
class Union_Find_Set{
    private:
        std::map<int,int> mapIndex;
        int nodenum;
        int* set;
        int getMapIndex(int a);
    public:
        Union_Find_Set(bool* nodeset,int setsize); //must initial with node set
        int find(int a);
        bool exist(int a);
        bool join(int a,int b);
        ~Union_Find_Set();
};