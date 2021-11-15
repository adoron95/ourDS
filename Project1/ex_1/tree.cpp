#include "tree.h"



Node* Tree::search(Node* p, string val, Node*& parent)
{
	if (!p || (p->isLeaf && p->value != val))
		return nullptr;
	if (p->value == val) {
		parent = p;
		return p;
	}
	Node* temp = nullptr;
	for (list<Answer*>::iterator i = p->answersList.begin(); i != p->answersList.end(); i++) {
		if ((*i)->son->value == val)
		{
			parent = p;
			return (*i)->son;
		}
		temp = (search((*i)->son, val, parent));
		if (temp)
			return temp;
	}
	return temp;
}

bool Tree::searchAndPrint(Node* p, string val)
{
	Node* parent;
	Node* temp = search(p, val, parent);
	if (!temp) { return false; }
	if (parent != temp) {
		cout << temp->value << "->";
		searchAndPrint(p, parent->value);
	}
	else
	{
		cout << temp->value;
	}
	return true;
}

void Tree::print(Node* p, int level)
{
	if (!p)return;
	for (int i = 0; i < level; i++) {
		cout << "\t";
	}
	cout << p->value << endl;
	if (p->isLeaf) {
		return;
	}
	for (list<Answer*>::iterator it = p->answersList.begin(); it != p->answersList.end(); it++) {
		for (int i = 0; i < level; i++) {
			cout << "\t";
		}
		cout << ":" << (*it)->ans << endl;
		print((*it)->son, level + 1);
	}
}

void Tree::process(Node* p)
{
	if (!(p->isLeaf)) {
		cout << p->value << endl;
		string help;
		cin >> help;
		for (list<Answer*>::iterator it = p->answersList.begin(); it != p->answersList.end(); it++)
		{
			if (help == (*it)->ans)
			{
				process((*it)->son);
				return;
			}
		}
	}
	else
		cout << p->value << endl;
}

void Tree::deleteAllSubTree(Node* t)
{
	if (t->isLeaf) {
		delete t;
		return;
	}
	while (!(t->answersList.empty())) {
		deleteAllSubTree(t->answersList.back()->son);
		t->answersList.pop_back();
	}
	t->isLeaf = true;
}

void Tree::addRoot(string newval)
{
	if (root)
	{
		deleteAllSubTree(root);
	}
	root = new Node(newval);
}

bool Tree::addSon(string fatherquestion, string newanswer, string newval)
{
	Node* father;
	Node* t;
	father = search(root, fatherquestion, t);
	if (father == nullptr)
		return false;
	Answer* temp = new Answer(newanswer, new Node(newval));
	father->answersList.push_back(temp);
	father->isLeaf = false;
	return true;
}

string Tree::printToString(Node* p)
{
	string str;
	if (!p)return "\0";
	str = "(" + p->value;
	if (p->isLeaf) {
		return str + ")";
	}
	for (list<Answer*>::iterator it = p->answersList.begin(); it != p->answersList.end(); it++) {
		str += "(" + (*it)->ans + printToString((*it)->son) + ")";
	}
	return str + ")";
}

void Tree::deleteSubTree(string val)
{
	Node* parent;
	Node* temp = search(root, val, parent);
	if (temp == parent) {
		deleteAllSubTree(temp);
		return;
	}
	if (temp) {
		parent->removeSonValue(val);
		if (parent->answersList.empty())
			parent->isLeaf = true;
	}
}

void Node::removeSonValue(string v)
{
	for (list<Answer*>::iterator it = answersList.begin(); it != answersList.end(); it++) {
		if ((*it)->son->value == v) {
			Tree::deleteAllSubTree((*it)->son);
			answersList.remove(*it);
			break;
		}
	}
}
