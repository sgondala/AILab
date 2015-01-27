#include <bits/stdc++.h>
using namespace std;

struct node;
//int getHeuristic(node);
map<string, node*> indexToNode;
map<string,string> parent;
list<node*> openList,closedList;
string startString,goalString;

map<string, node*> indexToNodeRev;
map<string,string> parentRev;
list<node*> openListRev,closedListRev;

struct node{
    string index;
    int g;
    int h;
    node(string s,int g,bool p){
        index=s;
        this->g=g;
        h=getHeuristic(p);
    }
    node() {};
    
    int getHeuristic(bool p){  //Manhattan Distances P is true for straight thing
        int count=0;
        for(int i=0;i<9;i++){
            int positionInIndex;
            if(p) {positionInIndex=find(index.begin(),index.end(),goalString[i])-index.begin();}
            else {positionInIndex=find(index.begin(),index.end(),startString[i])-index.begin();}
            count+=abs(positionInIndex%3 - i%3);
            count+=abs(positionInIndex/3 - i/3);
        }
        return 0;
    }
    
};

void swap(string &s, int i, int j) {
    char temp = s[i];
    s[i] = s[j];
    s[j] = temp;
}

list<string> successors(string s) {
    list<string> ret;
    int blankSpace = s.find('9');
    if(blankSpace%3 != 0) { // Left Move
        string temp = s;
        swap(temp, blankSpace, blankSpace-1);
        ret.push_back(temp);
    }
    if(blankSpace%3 != 2) { // Right Move
        string temp = s;
        swap(temp, blankSpace, blankSpace+1);
        ret.push_back(temp);
    }
    if(blankSpace/3 != 0) { // Up Move
        string temp = s;
        swap(temp, blankSpace, blankSpace-3);
        ret.push_back(temp);
    }
    if(blankSpace/3 != 2) { // Down Move
        string temp = s;
        swap(temp, blankSpace, blankSpace+3);
        ret.push_back(temp);
    }
    return ret;
}


void addChildren(node* parentNode,bool p){
    list<string> childrenIndices = successors(parentNode->index);
    for(list<string>::iterator it=childrenIndices.begin(); it!=childrenIndices.end(); it++) {
        string childIndex = *it;
        int tempG = parentNode->g + 1;

        if(p){
        if(indexToNode.find(childIndex) == indexToNode.end()) {
            node *n = new node(childIndex, tempG, true);
            indexToNode[childIndex] = n;
            parent[childIndex] = parentNode->index;
            openList.push_back(n);
        }
        else { //Already found
            if(indexToNode[childIndex]->g > tempG) { //New cost is less than old cost
                indexToNode[childIndex]->g = tempG;
                parent[childIndex] = parentNode->index;
                //Newly added
                if(find(closedList.begin(),closedList.end(),indexToNode[childIndex])!=closedList.end()){ // If in closed list
                	typeof(closedList.begin()) it = find(closedList.begin(),closedList.end(),indexToNode[childIndex]);
                	openList.push_back(*it);
                	closedList.remove(*it);
                } 

            }
        }
        }

        else{

        if(indexToNodeRev.find(childIndex) == indexToNodeRev.end()) {
            node *n = new node(childIndex, tempG, false);
            indexToNodeRev[childIndex] = n;
            parentRev[childIndex] = parentNode->index;
            openListRev.push_back(n);
        }
        else { //Already found
            if(indexToNodeRev[childIndex]->g > tempG) { //New cost is less than old cost
                indexToNodeRev[childIndex]->g = tempG;
                parentRev[childIndex] = parentNode->index;
                //Newly added
                if(find(closedListRev.begin(),closedListRev.end(),indexToNodeRev[childIndex])!=closedListRev.end()){ // If in closed list
                    typeof(closedListRev.begin()) it = find(closedListRev.begin(),closedListRev.end(),indexToNodeRev[childIndex]);
                    openListRev.push_back(*it);
                    closedListRev.remove(*it);
                } 

            }
        }


        }

    }
}


list<node*>::iterator minNode(list<node*> &l){
    list<node*>::iterator ret=l.begin();
    for(list<node*>::iterator it = l.begin(); it!=l.end(); it++) {
        node* New = *it;
        node* Old = *ret;
        if(Old->g + Old->h > New->g + New->h) ret=it;
    }
    return ret;
}

bool reachable(string s)
{
  int count = 0;
  for(int i = 0; i < s.length() - 1; i++)
    for(int j = i+1; j < s.length(); j++)
      if(s[i] > s[j])
        count++;
 
  
  //cout<<count<<endl;

  int temp=find(s.begin(),s.end(),'9')-s.begin();
  int manDist=abs(temp/3 - 8/3) + abs(temp%3 - 8%3);
  
  //cout<<manDist<<endl;

  return (manDist+count)%2==0;
  //else if(manDist%2==1 && count%2==1) return true;
  

}

int main() {
    //Assuming input format is startString, goalString
    //startString = "214783569";

    startString = "123456798";
    node* start;
    node temp(startString,0,true); //g for start is 0
    start = &temp;
    goalString = "123456789";
    node* goal;

    if(reachable(startString))cout<<"Reachable"<<endl;
    else {cout<<"Not Reachable"<<endl; return 0;}
    
    node temp2(goalString,0,true); //Defining g for goal to be 0 for now
    goal = &temp2;
    start->h=start->getHeuristic(true);

    node* startRev;
    node tempRev(goalString,0,false); //g for start is 0
    startRev = &tempRev;
    node* goalRev;
    node temp2Rev(startString,0,false); //Defining g for goal to be 0 for now
    goalRev = &temp2Rev;
    startRev->h=startRev->getHeuristic(false);    

    //cout<<start->index<<endl;

    openList.push_back(start);
    openListRev.push_back(startRev);
    
    list<node*>::iterator current,currentRev; 
    
    int expandedNodeCount = 0, expandedNodeCountRev = 0;
    
    bool foundAll=false;
    while(openList.size() != 0) {
        current = minNode(openList);
        currentRev = minNode(openListRev);

        //cout<<(*current) ->index<<" "<< (*currentRev) ->index<<endl;
    //    cout<< (*current)->index <<endl;
    //    if((*current)->index == goal->index) {
    //        break; // TODO
    //    }

        openList.remove(*current);
        closedList.push_back(*current);
        addChildren(*current, true);
        expandedNodeCount++;
        
        openListRev.remove(*currentRev);
        closedListRev.push_back(*currentRev);
        addChildren(*currentRev, false);
        expandedNodeCountRev++;

        //cout<<"i"<<endl; 

        for(typeof(closedList.begin()) itTemp=closedList.begin(); itTemp!=closedList.end(); itTemp++){
            for(typeof(closedListRev.begin()) itTempRev=closedListRev.begin(); itTempRev!=closedListRev.end(); itTempRev++){
                if( (*itTemp)->index == (*itTempRev)->index ){
                    cout<<(*itTemp)->index<<endl; foundAll = true; break;
                }
            }
        }

        if(foundAll) break;

    }
	
/*
    string temp3 = goal->index;
    while(temp3 != start->index) {
        temp3 = parent[temp3];
        cout << temp3 << endl;
    }
    cout<<"!@#"<<endl; */
    printf("No. of expanded nodes is %d\n",expandedNodeCount+expandedNodeCountRev);
	
}
