#include <bits/stdc++.h>
using namespace std;

struct node;
//int getHeuristic(node);
map<string, node*> indexToNode;
map<string,string> parent;
list<node*> openList,closedList;
string startString,goalString;

struct node{
    string index;
    int g;
    int h;
    node(string s,int g){
        index=s;
        this->g=g;
        h=getHeuristic();
    }
    node() {};
    
    /*
    int getHeuristic(){  //Not in their positions
        int count=0;
        for(int i=0;i<9;i++){
            int positionInIndex=find(index.begin(),index.end(),goalString[i])-index.begin();
            if(i!=positionInIndex)count++;
        }
        return count;
    }
	*/
    
    /*
    int getHeuristic(){  //Manhattan Distances
        int count=0;
        for(int i=0;i<9;i++){
            int positionInIndex=find(index.begin(),index.end(),goalString[i])-index.begin();
            count+=abs(positionInIndex%3 - i%3);
            count+=abs(positionInIndex/3 - i/3);
        }
        return count;
    }*/
    

    /*
    int getHeuristic(){  //Own Heuristic
        int count=0;
        for(int i=0;i<9;i++){
            int positionInIndex=find(index.begin(),index.end(),goalString[i])-index.begin();
            if(positionInIndex%3 != i%3){count++;}
            if(positionInIndex/3 != i/3){count++;}
        }
        return count;
    }*/
	

	/*
	int getHeuristic(){  //Manhattan Distances
        return 0;
    }*/
    
        
    int getHeuristic(){
    	int count=0;
    	for (int i=0;i<9;i++){
    		for(int j=i+1;j<9;j++){
	            int positionInIndexi=find(index.begin(),index.end(),goalString[i])-index.begin();    			
	            int positionInIndexj=find(index.begin(),index.end(),goalString[j])-index.begin();
	            if( (positionInIndexi/3 == positionInIndexj/3) && (positionInIndexi/3==i/3) 
	            	&& (positionInIndexj/3==j/3) && (positionInIndexi%3>positionInIndexj%3) ){
	            		count+=2;
	            }
	            else if( (positionInIndexi%3 == positionInIndexj%3) && (positionInIndexi%3==i%3) 
	            	&& (positionInIndexj%3==j%3) && (positionInIndexi/3>positionInIndexj/3) ){
	            		count+=2;
	            }    		
    		}
    	}
    	return count;
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


void addChildren(node* parentNode){
    list<string> childrenIndices = successors(parentNode->index);
    for(list<string>::iterator it=childrenIndices.begin(); it!=childrenIndices.end(); it++) {
    	//assert(abs(parentNode->h - ))
        string childIndex = *it;
        int tempG = parentNode->g + 1;
        if(indexToNode.find(childIndex) == indexToNode.end()) {
            node *n = new node(childIndex, tempG);
            //assert(abs(parentNode->h - n->h) <1);
            indexToNode[childIndex] = n;
            parent[childIndex] = parentNode->index;
            openList.push_back(n);
        }
        else { //Already found
            if(indexToNode[childIndex]->g > tempG) { //New cost is less than old cost
                indexToNode[childIndex]->g = tempG;
                parent[childIndex] = parentNode->index;
                //Newly added
            	
            	//assert(abs(parentNode->h - indexToNode[childIndex]->h) <1);   
                /*            
                if(find(closedList.begin(),closedList.end(),indexToNode[childIndex])!=closedList.end()){ // If in closed list
                	//cout<<"CAME"<<endl;
                	typeof(closedList.begin()) it = find(closedList.begin(),closedList.end(),indexToNode[childIndex]);
                	openList.push_back(*it);
                	closedList.remove(*it);
                } 
				*/
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
    startString = "214783569";
    node* start;
    node temp(startString,0); //g for start is 0
    start = &temp;
    goalString = "123456789";
    node* goal;

    if(reachable(startString))cout<<"Reachable"<<endl;
    else {cout<<"Not Reachable"<<endl; return 0;}
    
    node temp2(goalString,0); //Defining g for goal to be 0 for now
    goal = &temp2;
    start->h=start->getHeuristic();
    openList.push_back(start);
    
    list<node*>::iterator current; 
    
    int expandedNodeCount = 0;
    while(openList.size() != 0) {
        current = minNode(openList);
    //    cout<< (*current)->index <<endl;
        if((*current)->index == goal->index) {
            break; // TODO
        }
        openList.remove(*current);
        closedList.push_back(*current);
        addChildren(*current);
        expandedNodeCount++;

    }
	

    string temp3 = goal->index;
    while(temp3 != start->index) {
        temp3 = parent[temp3];
        cout << temp3 << endl;
    }
    printf("No. of expanded nodes is %d\n",expandedNodeCount);
	
}
