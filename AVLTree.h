#pragma once
#include "iostream"
#include "string"
#include <fstream>
using namespace std;

template <typename T>
class linkNode {
public:
	T data;
	string filename;
	int line;
	linkNode* next;

	linkNode() {
		//data = 0;
		next = NULL;
	}
	linkNode(T d, string name, int l) {
		data = d;
		filename = name;
		line = l;
		next = NULL;
	}
};

template <typename T>
class LinkedList {

public:
	linkNode<T>* head;
	LinkedList() {
		head = NULL;
	}
	bool isEmpty() {	//checking if list is empty
		if (head == NULL)
			return true;
		else
			return false;
	}

	/*void InsertAtHead(T d) {
		linkNode<T>* temp = new linkNode<T>(d);
		if (isEmpty()) {
			temp->next = NULL;
			head = temp;
		}
		else {
			temp->next = head;
			head = temp;
		}
	}*/

	void InsertAtTail(T d, string file, int l) {
		linkNode<T>* temp = new linkNode<T>;
		temp->data = d;
		temp->filename = file;
		temp->line = l;
		if (isEmpty()) {
			temp->next = NULL;
			head = temp;
		}
		else {
			linkNode<T>* t = head;
			while (t->next != NULL)
				t = t->next;
			t->next = temp;
			temp->next = NULL;
		}
	}

	//void InsertAtIndex(T val, int index) {
	//	linkNode<T>* toinsert = new linkNode<T>(val);
	//	int count = 0;
	//	if (head == NULL) {
	//		toinsert->next = NULL;
	//		head = toinsert;
	//		//head = toinsert;
	//	}
	//	linkNode<T>* temp = head;
	//	while (temp != NULL) {
	//		if (count == index) {
	//			toinsert->next = temp->next;	//inserting node at next position
	//			temp->next = toinsert;
	//			return;
	//		}
	//		count++;
	//		temp = temp->next;
	//	}
	//}

	void Update(T data, int index) {
		linkNode<T>* updated = new linkNode<T>(data);
		int count = 0;
		if (head == NULL) {
			head = updated;
			updated->next = NULL;
		}
		linkNode<T>* temp = head;
		while (temp != NULL) {
			if (count == index) {
				temp->data = data;
			}
			count++;
			temp = temp->next;
		}
	}

	void Remove(T d) {
		linkNode<T>* temp = head;
		linkNode<T>* t = NULL;
		if (temp->data == d) {
			t = temp->next;
			delete temp;
			return;
		}
		while (temp->next != NULL) {
			if (temp->next->data == d)
				break;
			temp = temp->next;
		}
		if (temp->next != NULL) {
			t = temp->next->next;
		}
		delete temp->next;
		temp->next = t;
		return;
	}

	void printList() {
		linkNode<T>* t = head;
		while (t != NULL) {
			cout << t->data << " -> ";
			t = t->next;
		}
		cout << "NULL\n";
		//cout << endl;
	}

	void emptyList() {
		this->~LinkedList();
	}

	~LinkedList() {
		linkNode<T>* currNode = head;
		linkNode<T>* nextNode = NULL;
		while (currNode != NULL)
		{
			nextNode = currNode->next;
			delete currNode; // destroy the current node
			currNode = nextNode;
		}
		head = NULL;
	}
};

///---------------------------------------------------------------------------------///

template <typename T>
class Node {
public:
	T data;
	Node* next;

	Node() {
		data = 0;
		next = NULL;
	}
	Node(T d) {
		data = d;
		next = NULL;
	}
};

template <typename T>
class Queues {
public:
	Node<T>* head;	//elements delete from hed
	Node<T>* tail;	//elements added at tail

	Queues() {
		head = NULL;
		tail = NULL;
	}

	bool isEmpty() {	//checking if list is empty
		if (head == NULL)
			return true;
		else
			return false;
	}

	void enqueue(T d) {	//Insert At Tail
		Node<T>* temp = new Node<T>(d);
		if (isEmpty()) {
			temp->next = NULL;
			head = temp;
			tail = temp;
		}
		else {
			tail->next = temp;
			tail = temp;
		}
	}

	T dequeue() {	//remove from head
		if (isEmpty()) {
			cout << "Queue empty, nothing to dequeue.\n";
		}
		else {

			Node<T>* temp = head;
			Node<T>* extra1 = new Node<T>;
			extra1->data = head->data;
			extra1->next = head->next;
			head = head->next;
			delete temp;
			return extra1->data;
		}
	}

	T front() {
		if (isEmpty()) {
			cout << "Empty Queue.\n";
			return 0;
		}
		else
			return head->data;
	}

	void printQueue() {
		Node<T>* t = head;
		while (t != NULL) {
			cout << t->data << " -> ";
			t = t->next;
		}
		cout << "NULL\n";
	}

	void emptyQueue() {
		this->~Queues();
	}

	~Queues() {
		Node<T>* currNode = head;
		Node<T>* nextNode = NULL;
		while (currNode != NULL)
		{
			nextNode = currNode->next;
			delete currNode; // destroy the current node
			currNode = nextNode;
		}
		head = NULL;
	}
};


template <typename T>
class treeNode {
public:
	//T index;
	//string filename;
	//int line;
	LinkedList<T> list;
	treeNode<T>* rightChild;
	treeNode<T>* leftChild;
	int height;

	treeNode() {
		leftChild = NULL;
		rightChild = NULL;
		height = -1;
		list.head = NULL;
	}
	treeNode(T d, string name, int l) {
		list.InsertAtTail(d, name, l);
		leftChild = NULL;
		rightChild = NULL;
		height = 0;
	}
};

template <typename T>
class AVL {//binary search tree
public:
	treeNode<T>* root;

	AVL() {
		root = NULL;
	}

	int heightOfNode(treeNode<T>* temp)
	{
		if (temp == NULL) //meaning leaf node
			return -1;
		else
			return temp->height;
	}

	int greaterHeight(int left, int right)
	{
		if (left > right)
			return left;
		else
			return right;
	}

	int getBalance(treeNode<T>* N)
	{
		if (N == NULL)
			return 0;
		return heightOfNode(N->leftChild) - heightOfNode(N->rightChild);
	}

	treeNode<T>* LL(treeNode<T>* tree) {
		treeNode<T>* newR;
		newR = tree->rightChild; // K1: node whose balance factor is violated
		tree->rightChild = newR->leftChild;
		newR->leftChild = tree;
		int h1 = heightOfNode(tree->leftChild);
		int h2 = heightOfNode(tree->rightChild);
		tree->height = greaterHeight(h1, h2) + 1;
		newR->height = greaterHeight(heightOfNode(newR->rightChild), tree->height) + 1;
		return newR; /* New root */
	}

	treeNode<T>* RR(treeNode<T>* tree) {
		treeNode<T>* newR;
		newR = tree->leftChild; // K1: node whose balance factor is violated
		tree->leftChild = newR->rightChild;
		newR->rightChild = tree;
		int h1 = heightOfNode(tree->leftChild);
		int h2 = heightOfNode(tree->rightChild);
		tree->height = greaterHeight(h1, h2) + 1;
		newR->height = greaterHeight(heightOfNode(newR->leftChild), tree->height) + 1;
		return newR; /* New root */
	}

	treeNode<T>* LR(treeNode<T>* tree)
	{
		tree->rightChild = RR(tree->rightChild);
		return LL(tree);
	}

	treeNode<T>* RL(treeNode<T>* tree)
	{
		tree->leftChild = LL(tree->leftChild);
		return RR(tree);
	}

	bool retrieve(T d) {
		treeNode<T>* temp = root;
		while (temp) {
			if (temp->index == d)
				return true;
			else if (d < temp->index)
				temp = temp->leftChild;
			else if (d > temp->index)
				temp = temp->rightChild;
		}
		return false;
	}

	treeNode<T>* AVLinsertion(T d, string name, int l, treeNode<T>* r)
	{
		//reaching here meaning value not duplicated
		//treeNode<T>* toinsert = new treeNode<T>(d, name, l);
		treeNode<T>* temp = r;
		if (r == NULL) {	//meaning tree empty rn
			r = new treeNode<T>;
			r->list.InsertAtTail(d, name, l);
		}
		else if (d < r->list.head->data)
		{
			r->leftChild = AVLinsertion(d, name, l, r->leftChild);
			if (heightOfNode(r->leftChild) - heightOfNode(r->rightChild) == 2)
			{
				if (d < r->leftChild->list.head->data)
					r = RR(r);
				else
					r = RL(r);
			}
		}
		else if (d > r->list.head->data)
		{
			r->rightChild = AVLinsertion(d, name, l, r->rightChild);
			if (heightOfNode(r->rightChild) - heightOfNode(r->leftChild) == 2)
			{
				if (d > r->rightChild->list.head->data)
					r = LL(r);
				else
					r = LR(r);
			}
		}
		else if (d == r->list.head->data)
		{
			r->list.InsertAtTail(d, name, l);
		}
		r->height = greaterHeight(heightOfNode(r->leftChild), heightOfNode(r->rightChild)) + 1;
		return r;
	}//insert ftn end

	treeNode<T>* searchTree(T d) {
		treeNode<T>* temp = root;
		while (temp) {
			if (temp->list.head->data == d)
				return temp;
			else if (d < temp->list.head->data)
				temp = temp->leftChild;
			else if (d > temp->list.head->data)
				temp = temp->rightChild;
		}
		return NULL;
	}

	void inorder(treeNode<T>* t1) {
		treeNode<T>* temp = t1;
		if (temp != NULL) {
			inorder(temp->leftChild);
			linkNode<T>* l = temp->list.head;
			while (l)
			{
				cout << l->data << " ";
				cout << l->filename << " ";
				cout << l->line << " ";
				cout << endl;
				l = l->next;
			}
			cout << endl;
			inorder(temp->rightChild);
		}
	}

	void postorder(treeNode<T>* t1) {
		treeNode<T>* temp = t1;
		if (temp != NULL) {
			postorder(temp->leftChild);
			postorder(temp->rightChild);
			linkNode<T>* l = temp->list.head;
			while (l)
			{
				cout << l->data << " ";
				l = l->next;
			}
			cout << endl;
		}
	}

	void preorder(treeNode<T>* t1) {
		treeNode<T>* temp = t1;
		if (temp != NULL) {
			linkNode<T>* l = temp->list.head;
			while (l)
			{
				cout << l->data << " ";
				l = l->next;
			}
			cout << endl;
			preorder(temp->leftChild);
			preorder(temp->rightChild);
		}
	}

	//void levelTraversal() {
	//	Queues<treeNode<T>*> q1;
	//	treeNode<T>* temp = root;
	//	q1.enqueue(temp);
	//	treeNode<T>* val;
	//	int count = 1;
	//	while (!q1.isEmpty()) {	//run while loop until queue is empty
	//		val = q1.dequeue()->data;
	//		if (count == 1010)
	//		{
	//			cout << endl;
	//		}
	//		cout << val->index << "   " << val->filename << "   " << val->line << endl;
	//		if (val->leftChild)
	//			q1.enqueue(val->leftChild);
	//		if (val->rightChild)
	//			q1.enqueue(val->rightChild);
	//		count++;
	//	}
	//}

	T findMin() {
		treeNode<T>* temp = root;
		int minimum = 0;
		while (temp) {
			minimum = temp->list.head->data;
			temp = temp->leftChild;
		}
		return minimum;
	}

	treeNode<T>* minValueNode(treeNode<T>* node)
	{
		treeNode<T>* current = node;

		while (current->leftChild != NULL)
			current = current->leftChild;

		return current;
	}

	//treeNode<T>* deletionAVL(treeNode<T>* root, T valToDelete)
	//{
	//	if (root == NULL)
	//		return root;

	//	if (valToDelete < root->index)
	//		root->leftChild = deletionAVL(root->leftChild, valToDelete);

	//	else if (valToDelete > root->index)
	//		root->rightChild = deletionAVL(root->rightChild, valToDelete);

	//	//valToDelete found!!
	//	else
	//	{
	//		// node with only one child or no child 
	//		if ((root->leftChild == NULL) || (root->rightChild == NULL))
	//		{
	//			treeNode<T>* temp;
	//			if (root->leftChild != NULL)
	//				temp = root->leftChild;
	//			else if (root->rightChild != NULL)
	//				temp = root->rightChild;
	//			else
	//				temp = root->leftChild;
	//			// No child case 
	//			if (temp == NULL)
	//			{
	//				temp = root;
	//				root = NULL;
	//			}
	//			else // One child case 
	//				root = temp; // Copy the contents of 
	//							   // the non-empty child 
	//			//free(temp);
	//			delete temp;
	//		}
	//		else
	//		{
	//			// node with two children: Get the inorder 
	//			// successor (smallest in the right subtree) 
	//			treeNode<T>* temp;
	//			temp = minValueNode(root->leftChild);
	//			root->index = temp->index;
	//			root->leftChild = deletionAVL(root->leftChild, temp->index);
	//		}
	//	}

	//	// If the tree empty
	//	// then return 
	//	if (root == NULL)
	//		return root;

	//	// STEP 2: UPDATE HEIGHT OF THE CURRENT NODE 
	//	root->height = 1 + max(heightOfNode(root->leftChild), heightOfNode(root->rightChild));

	//	// STEP 3: GET THE BALANCE FACTOR OF 
	//	// THIS NODE (to check whether this 
	//	// node became unbalanced) 
	//	int balance = getBalance(root);

	//	// If this node becomes unbalanced, 
	//	// then there are 4 cases 

	//	// Left Left Case 
	//	if (balance > 1 && getBalance(root->leftChild) >= 0)
	//		return RR(root);

	//	// Left Right Case 
	//	if (balance > 1 && getBalance(root->leftChild) < 0)
	//		return RL(root);

	//	// Right Right Case 
	//	if (balance < -1 && getBalance(root->rightChild) <= 0)
	//		return LL(root);

	//	// Right Left Case 
	//	if (balance < -1 && getBalance(root->rightChild) > 0)
	//		return LR(root);

	//	return root;
	//}

};

///---------------------------------------------------------------------------------///
