
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

int FindComma(string str) {
	int count = 0;
    int IndexComma = 0;
    for(int i=0; i<str.size(); i++) {
        char c = str[i];
        if(c==',' && count==0) {
            IndexComma = i;
        }
        if(c=='(') count++;
        if(c==')') count--;
    }
    //cout << IndexComma << endl;
    return IndexComma;
}

node* ScanInput(string str) {
	bool isNegation = false;
	if(str[0]=='!') {
		isNegation = true;
		str = str.substr(1);
	}
	if(str.find(',') != string::npos) {
		string str1 = str.substr(1,str.size()-2);// Removing the outer brackets
		int CommaPos = FindComma(str1);
		string LeftString = str1.substr(0,CommaPos);
		string RightString = str1.substr(CommaPos+1);
		//cout << LeftString << " " << RightString << endl;
		node* LeftTree, *RightTree;
		//if(LeftString[0]='(') {
		LeftTree = ScanInput(LeftString);
		//if(RightString[0] = '(') {
		RightTree = ScanInput(RightString);
		node* parent = new node(LeftTree, RightTree, isNegation);
		return parent;	
	}
	else {
		assert(str.size()==1);
		//cout << str[0] << endl;
		node* parent = new node(str[0],isNegation);
		return parent;
	}
}

vector<node*> parts;

void makeList(node* a){
	if(a->isLeaf && a->leaf=='f'){
		parts.push_back(a);
		return;
	}
	else if(a->isLeaf){
		//cout<<"HE "<<a->isNegation<<endl;
		a->isNegation = !(a->isNegation);
		//cout<<"HE "<<a->isNegation<<endl;
		parts.push_back(a);
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
	//cout<<"IS "<<a->isNegation<<endl;
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
    //str = "((p,q),((!p,q),q))";
    //cin >> str;
    node* tree;
    tree = ScanInput(str);
    makeList(tree);
    //cout << nodeToString(tree) << endl;
    for(int i=0; i<parts.size(); i++) {
    	cout << nodeToString(parts[i]) << endl;
    }
}

