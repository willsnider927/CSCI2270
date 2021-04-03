#include <iostream>
#include <fstream>
#include "MovieTree.hpp"

using namespace std;

LLMovieNode* getLLMovieNode(int r, std::string t, int y, float q)
{
	LLMovieNode* lmn =new LLMovieNode();
	lmn->ranking = r;
	lmn->title=t;
	lmn->year =y;
	lmn->rating =q;
	lmn->next =NULL;
	return lmn;
}

/* ------------------------------------------------------ */
MovieTree::MovieTree()
{
	root = NULL;
}

/* ------------------------------------------------------ */
void inorderTraversalHelper(TreeNode * root) {
		if (root == NULL) {
			return;
		}

		inorderTraversalHelper(root->leftChild);
		cout << root->titleChar << " ";
		inorderTraversalHelper(root->rightChild);
}

void MovieTree::inorderTraversal() {
	inorderTraversalHelper(root);
	cout << endl;
}

/* ------------------------------------------------------ */
TreeNode* searchCharHelper(TreeNode* curr, char key)
{
    if (curr == NULL)
        return curr;
    else if(curr->titleChar == key)
        return curr;
    else if (curr->titleChar > key)
        return searchCharHelper(curr->leftChild, key);
    else
        return searchCharHelper(curr->rightChild, key);
}

TreeNode* MovieTree::searchCharNode(char key)
{
    return searchCharHelper(root, key);
}

//My code:
/* ------------------------------------------------------ */
void _showMovieCollection(TreeNode * t) { //helper function for showMovieCollection
	if(!t) return;
	_showMovieCollection(t->leftChild); //printing alphabetically is inOrder traversal
	if (t->head) {
		cout << "Movies starting with letter: " << t->titleChar << endl;
		for (LLMovieNode* m = t->head; m; m = m->next) {
			cout << " >> " << m->title << " " << m->rating << endl;
		}
	}
	_showMovieCollection(t->rightChild);
}

void MovieTree::showMovieCollection() {
	_showMovieCollection(root);
}

/* ------------------------------------------------------ */
void _insertMovie(TreeNode* &curr, TreeNode* prev, TreeNode* t) { //helper function for insertMovie
	if (!curr) { //found where it goes
		curr = t;
		t->parent = prev;
		return;
	}
	else {
		if (t->titleChar < curr->titleChar) _insertMovie(curr->leftChild, curr, t);
		else _insertMovie(curr->rightChild, curr, t);
	}
}

void MovieTree::insertMovie(int ranking, string title, int year, float rating) {
	LLMovieNode* m = getLLMovieNode(ranking, title, year, rating);
	TreeNode* t = searchCharNode(title[0]);
	if (t) {
		LLMovieNode* curr = t->head;
		LLMovieNode* prev = curr;
		while (curr) { //iterate until position to be inserted is found or it goes at the end
			if (curr->title < m->title) {
				prev = curr;
				curr = curr->next;
			}
			else {
				m->next = curr;
				if (prev == curr) { //check for if list had one element
					t->head = m;
					return;
				}
				else {
					prev->next = m;
					return;
				}
			}
		}
		if (prev == NULL) t->head = m; //case: adding back to an already empty TreeNode
		else prev->next = m; //case when m is last alphabetically
		m->next = NULL;
		return;
	}
	TreeNode* node = new TreeNode(); //case if first movie to start with letter
	node->head = m;
	node->titleChar = title[0];
	_insertMovie(root, nullptr, node);
}

/* ------------------------------------------------------ */

void MovieTree::removeMovieRecord(string title) {
	TreeNode* t = searchCharNode(title[0]);
	if (t) { //has to find the treenode
		LLMovieNode* prev = t->head;
		if (!prev) { //case, head null
			cout << "Movie not found." << endl;
			return;
		}
		if (title == prev->title) { //case, head == movie
			t->head = prev->next;
			delete prev;
			prev = 0;
			return;
		}
		for (LLMovieNode* curr = prev->next; curr; curr = curr->next) { //case, somewhere else in list
			if (curr->title == title) {
				prev->next = curr->next;
				delete curr;
				curr = 0;
				return;
			}
			prev = curr;
		}
	}
	cout << "Movie not found." << endl;
}

/* ------------------------------------------------------ */

void MovieTree::leftRotation(TreeNode* curr) { 
	if (!curr->rightChild) {
		return;
	}
	TreeNode* currRight = curr->rightChild;
	if (root == curr) {
		root = currRight;
	 	curr->rightChild = root->leftChild;
		root->leftChild = curr;
		if (curr->rightChild) curr->rightChild->parent = curr;
		curr->parent = root;
		root->parent = 0;
		return;
	}
	TreeNode* Parent = curr->parent;
	if (Parent->leftChild == curr) Parent->leftChild = currRight;
	else Parent->rightChild = currRight;
	curr->rightChild = currRight->leftChild;
	currRight->leftChild = curr;
	currRight->parent = curr->parent;
	curr->parent = currRight;
	if (curr->rightChild) curr->rightChild->parent = curr;
}

/* ------------------------------------------------------ */
void _delNode(TreeNode* curr) {
	if (!curr) return;
	_delNode(curr->leftChild);
	_delNode(curr->rightChild);
	LLMovieNode* prevM = curr->head;
	LLMovieNode* m = curr->head;
	while(m) {
		m = m->next;
		delete prevM;
		prevM = m;
	}
	delete curr;
	curr = 0;
}

MovieTree::~MovieTree() {
	_delNode(root);
}
