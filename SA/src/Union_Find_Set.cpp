#include"Union_Find_Set.h"
Union_Find_Set::Union_Find_Set(bool* nodeset,int setsize){
    nodenum=0;
    for(int i=0;i<setsize;++i){
        if(nodeset[i]){
            mapIndex.insert(std::map<int,int>::value_type(i,nodenum));//map nonsequence index to sequence
            ++nodenum;
        }
    }
    set = new int[nodenum];
    for(int i=0;i<nodenum;++i) set[i]=i;
}

Union_Find_Set::~Union_Find_Set(){
    delete []set;
}

int Union_Find_Set::getMapIndex(int a){
    int index=-1;
    std::map<int,int>::iterator iter = mapIndex.find(a);
    if(iter!=mapIndex.end()) index=iter->second;
    return index;
}

int Union_Find_Set::find(int a){
    while(a != set[a]) {a=set[a];}
    return a;
}

bool Union_Find_Set::join(int a,int b){
    int indexa=getMapIndex(a),indexb=getMapIndex(b);//not exist in solution
    if(indexa==-1||indexb==-1) return false;
    int roota = find(indexa);
    int rootb = find(indexb);
    if(roota == rootb) return false; //they are already in the same block
    set[roota] = rootb;
    return true; //join success
}
bool Union_Find_Set::exist(int a){
    return getMapIndex(a)!=-1;
}