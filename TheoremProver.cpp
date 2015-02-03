#include <bits/stdc++.h>
using namespace std;

struct node{
	node* left;
	node* right;
	char leaf;
	bool isLeaf;
	bool isNegation;

	node(node* a,node* b, bool isNegation ){
		left=a;
		right=b;
		isLeaf=false;
		this->isNegation = isNegation;
	}

	node(char a, bool isNegation){
		leaf=a;
		isLeaf=true;
		this->isNegation = isNegation;
	}

	node(){}
};

int FindChar(string str, char token) {
	int count = 0;
	int IndexChar = 0;
	for(int i=0; i<str.size(); i++) {
		char c = str[i];
		if(c==token && count==0) {
			IndexChar = i;
		}
		if(c=='(') count++;
		if(c==')') count--;
	}
	//cout << IndexComma << endl;
	return IndexChar;
}

node* ScanInput(string str) {
	bool isNegation = false;
	node* parent;
	if(str[0]=='!') {
		isNegation = true;
		str = str.substr(1);
	}

	if(str.size()!=1 && FindChar(str.substr(1,str.size()-2),',')) {
		string str1 = str.substr(1,str.size()-2);// Removing the outer brackets
		int CommaPos = FindChar(str1,',');
		string LeftString = str1.substr(0,CommaPos);
		string RightString = str1.substr(CommaPos+1);
		//cout << LeftString << " " << RightString << endl;
		node* LeftTree, *RightTree;
		//if(LeftString[0]='(') {
		LeftTree = ScanInput(LeftString);
		//if(RightString[0] = '(') {
		RightTree = ScanInput(RightString);
		parent = new node(LeftTree, RightTree, isNegation);
		//return parent;	
	}
	
	else if(str.size()!=1 && FindChar(str.substr(1,str.size()-2),'v')){
		string str1 = str.substr(1,str.size()-2);// Removing the outer brackets
		int OrPos = FindChar(str1,'v');
		string LeftString = str1.substr(0,OrPos);
		string RightString = str1.substr(OrPos+1);
		node* LeftTree, *RightTree;
		LeftTree = ScanInput(LeftString); //a
		RightTree = ScanInput(RightString); //b, should compute a V b = ((a,f),b)
		node* tempFalse=new node('f',false);
		node* tempLeft=new node(LeftTree,tempFalse,false);
		parent = new node(tempLeft, RightTree, isNegation);		
		//return parent;	
	}

	else if(str.size()!=1 && FindChar(str.substr(1,str.size()-2),'^')){
		string str1 = str.substr(1,str.size()-2);// Removing the outer brackets
		int AndPos = FindChar(str1,'^');
		string LeftString = str1.substr(0,AndPos);
		string RightString = str1.substr(AndPos+1);
		node* LeftTree, *RightTree;
		LeftTree = ScanInput(LeftString); //a
		RightTree = ScanInput(RightString); //b, should compute a ^ b = ((a,(b,f)),f)
		node* tempFalse=new node('f',false);
		node* tempLR=new node(RightTree,tempFalse,false);
		node* tempL=new node(LeftTree,tempLR,false);
		node* tempFalse2=new node('f',false);
		parent = new node(tempL, tempFalse2, isNegation);		
		//return parent;	
	}

	else {
		assert(str.size()==1);
		parent = new node(str[0],isNegation);
		//return parent;
	}

	if(isNegation){
		node* tempFalse = new node('f',false);
		parent->isNegation=false;
		node* returnNode = new node(parent, tempFalse, false);
	}

	else return parent;

}

vector<node*> parts;

void makeList(node* a){
	if(a->isLeaf && a->leaf=='f'){
		parts.push_back(a);
		return;
	}
	else if(a->isLeaf){
		a->isNegation = !(a->isNegation);
		if(!a->isNegation) {parts.push_back(a);}
		else {
			node* tempFalse = new node('f',false);
			a->isNegation=false;
			node* temp = new node(a,tempFalse,false);  
			parts.push_back(temp);
		}
		node* temp=new node('f',false);
		parts.push_back(temp);
		return;
	}
	parts.push_back(a->left);
	makeList(a->right);
	return;
}

string nodeToString(node* a){
	string temp="";
	if(a->isNegation){temp='~';}
	if(a->isLeaf){temp+=a->leaf;}
	else{
		string temp1=nodeToString(a->left);
		string temp2=nodeToString(a->right);
		temp+='('+temp1+','+temp2+')';
	}
	return temp;
}

int main(int argc, char* argv[]) {
	string str;
	str = argv[1];
	node* tree;
	tree = ScanInput(str);
	makeList(tree);
	for(int i=0; i<parts.size(); i++) {
		cout << nodeToString(parts[i]) << endl;
	}
}

