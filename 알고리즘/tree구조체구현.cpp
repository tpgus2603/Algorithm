#include<iostream>
#include<string>
#include<queue>
#include<vector>
#include<stack>
using namespace std;

struct node { //구조체로 구현 
	string position;
	std::vector<node*>children;  //adj
	node(const std::string& pos) :position(pos){} 
};
struct tree {
	node* root = nullptr;
	tree(const std::string& pos) {
		root = new node(pos);
	}
	bool addSub(const string& parent, const string& sub) { 
		auto pNode = find(root, parent);
		if (!pNode) return false;
		pNode->children.push_back(new node(sub)); 
		return true;
	}
	static void PreOrderPrint(node* root) {  
		if (root == nullptr)   
			return;
		cout << root->position << " " << endl;
		for (auto child : root->children)
			PreOrderPrint(child);
	}
	static void PostOrderPrint(node* root) { 
		if (root == nullptr)
			return;
		for (auto child : root->children)  
			PreOrderPrint(child);
		cout << root->position << " " << endl;

	}
	static void InOrderPrint(node* root) {
		if (root == nullptr)
			return;
		auto child = root->children.begin();
		InOrderPrint(*child);  
		cout << root->position<<" " << endl;
		InOrderPrint(*(child + 1));  
	}
	static node* LevelPrint(node* root) { //brethfirst
		if (!root)return nullptr;
		queue<node*> q;
		q.push(root);
		while (!q.empty()) {
			const auto node = q.front();  
			q.pop();
			cout << node->position << " " << endl;
			for (auto child : node->children)
				q.push(child);
		}
	}
	static node* depthFirstPrint(node * root) {  
		if (!root)return nullptr;
		stack<node*> s;
		s.push(root);
		while (!s.empty()) {
			const auto node = s.top();
			s.pop();
			cout << node->position << " " << endl;
			for (auto child : node->children)
				s.push(child);
		}

	}
	static node* find(node* root, const std::string& pos) {
		if (root == nullptr)
			return nullptr;
		if (root->position.compare(pos) == 0)
			return root;
		for (auto child : root->children) {
			auto found = find(child, pos);
			if (found) return found;
		}
		return nullptr;
	}
	
};
int main() {
	tree bt("a");
	bt.addSub("a", "b");	bt.addSub("a", "c");
	bt.addSub("b", "d"); 	bt.addSub("b", "h");;
	bt.addSub("d", "e");
	bt.addSub("d", "f");
	bt.addSub("h", "g");
	bt.addSub("h", "i");
	bt.addSub("i", "k");
	bt.addSub("i", "j");
	//bt.LevelPrint(bt.root);
	bt.depthFirstPrint(bt.root);


}