#pragma once
#include <iostream>
#include<fstream>
#include <string>
//#include"RB_implemented.h"
using namespace std;

template <class T>
class RB_LLNode
{

public:
	T data;
	RB_LLNode<T>* next;
	string file_name;
	int line_no;

	RB_LLNode()
	{
		//data = "\0";
		next = NULL;
	}

};

template <class T>
class RB_SLinkedList {

public:

	RB_LLNode<T>* head;


	RB_SLinkedList()
	{
		head = NULL;
	}

	void insert(T d, string file, int line) {
		RB_LLNode <T>* n = new RB_LLNode<T>;
		n->data = d;
		n->file_name = file;
		n->line_no = line;
		n->next = NULL;
		if (head == NULL)
		{
			head = n;
		}
		else
		{
			RB_LLNode <T>* temp;
			temp = head;
			while (temp->next)
			{
				temp = (temp->next);
			}
			temp->next = n;
		}
	}
	void print()
	{
		RB_LLNode<T>* temp;
		temp = head;
		while (temp)
		{
			cout << temp->data << " ";
			if (temp->data == -1)
				cout << endl;
			temp = temp->next;
		}
		cout << endl;
	}
};

template <class T>
class RB_QNode
{
public:
	T data;
	RB_QNode<T>* next;

	RB_QNode()
	{
		data = 0;
		next = NULL;
	}

	RB_QNode(T d, RB_QNode<T>* n)
	{
		data = d;
		next = n;
	}

	RB_QNode(T d)
	{
		data = d;
		next = NULL;
	}

};

template <class T>
class RB_Queue
{
public:
	RB_QNode<T>* front;
	RB_QNode<T>* rear;

	RB_Queue()
	{
		front = NULL;
		rear = NULL;
	}

	bool isEmpty()
	{
		if (front == NULL)
			return true;
		return false;
	}

	void enqueue(T d) {
		RB_QNode <T>* n = new RB_QNode<T>;
		n->data = d;
		n->next = NULL;
		if (front == NULL)
		{
			front = n;
			rear = n;
		}
		else
		{
			rear->next = n;
			rear = n;
		}
	}

	RB_QNode<T>* dequeue()
	{
		RB_QNode <T>* temp = new RB_QNode<T>;
		temp = front;
		front = front->next;
		return temp;
	}

	T Front()
	{
		return front->data;
	}

	void print()
	{
		RB_QNode <T>* temp = new RB_QNode<T>;
		temp = front;
		while (temp)
		{
			cout << temp->data << " ";
			temp = temp->next;
		}
		cout << endl << endl;
	}
};


template <class T>
class RBNode {
public:
	RB_SLinkedList<T> list;
	RBNode<T>* parent;
	RBNode<T>* left;
	RBNode<T>* right;
	bool color; // true for Red, false for Black
};

template <class T>
class RBTree {
public:
	RBNode<T>* root;
	RBNode<T>* TNULL;

	RBTree() {
		TNULL = new RBNode<T>;
		TNULL->color = 0;
		TNULL->left = nullptr;
		TNULL->right = nullptr;
		root = TNULL;
	}

	void preOrder(RBNode<T>* root) {
		if (root != TNULL) {
			RB_LLNode<T>* temp = root->list.head;
			while (temp)
			{
				cout << temp->data << " ";
				cout << temp->file_name << " ";
				cout << temp->line_no << endl;
				temp = temp->next;
			}
			preOrder(root->left);
			preOrder(root->right);
		}
	}

	void inOrder(RBNode<T>* root) {
		if (root != TNULL) {
			inOrder(root->left);
			RB_LLNode<T>* temp = root->list.head;
			while (temp)
			{
				cout << temp->data << " ";
				cout << temp->file_name << " ";
				cout << temp->line_no << endl;
				temp = temp->next;
			}
			inOrder(root->right);
		}
	}

	void postOrder(RBNode<T>* root) {
		if (root != TNULL) {
			postOrder(root->left);
			postOrder(root->right);
			RB_LLNode<T>* temp = root->list.head;
			while (temp)
			{
				cout << temp->data << " ";
				cout << temp->file_name << " ";
				cout << temp->line_no << endl;
				temp = temp->next;
			}
		}
	}

	RBNode<T>* searchTreeHelper(RBNode<T>* RBNode, T key) {
		if (RBNode == TNULL || key == RBNode->list.head->data) {
			return RBNode;
		}

		if (key < RBNode->list.head->data) {
			return searchTreeHelper(RBNode->left, key);
		}
		return searchTreeHelper(RBNode->right, key);
	}

	RBNode<T>* searchTree(T k) {
		return searchTreeHelper(this->root, k);
	}

	void rbTransplant(RBNode<T>* u, RBNode<T>* v) {
		if (u->parent == nullptr) {
			root = v;
		}
		else if (u == u->parent->left) {
			u->parent->left = v;
		}
		else {
			u->parent->right = v;
		}
		v->parent = u->parent;
	}

	void deleteNode(T key) {
		RBNode<T>* RBN = root;
		RBNode<T>* z = TNULL;
		RBNode<T>* x, * y;
		while (RBN != TNULL) {
			if (RBN->list.head->data == key) {
				z = RBN;
			}

			if (RBN->list.head->data <= key) {
				RBN = RBN->right;
			}
			else {
				RBN = RBN->left;
			}
		}

		if (z == TNULL) {
			cout << "Couldn't find key in the tree" << endl;
			return;
		}

		y = z;
		int y_original_color = y->color;
		if (z->left == TNULL) {
			x = z->right;
			rbTransplant(z, z->right);
		}
		else if (z->right == TNULL) {
			x = z->left;
			rbTransplant(z, z->left);
		}
		else {
			y = minimum(z->right);
			y_original_color = y->color;
			x = y->right;
			if (y->parent == z) {
				x->parent = y;
			}
			else {
				rbTransplant(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}

			rbTransplant(z, y);
			y->left = z->left;
			y->left->parent = y;
			y->color = z->color;
		}
		delete z;
		if (y_original_color == 0) {
			RBNode<T>* s;
			while (x != root && x->color == 0) {
				if (x == x->parent->left) {
					s = x->parent->right;
					if (s->color == 1) {
						// case 3.1
						s->color = 0;
						x->parent->color = 1;
						leftRotate(x->parent);
						s = x->parent->right;
					}

					if (s->left->color == 0 && s->right->color == 0) {
						// case 3.2
						s->color = 1;
						x = x->parent;
					}
					else {
						if (s->right->color == 0) {
							// case 3.3
							s->left->color = 0;
							s->color = 1;
							rightRotate(s);
							s = x->parent->right;
						}

						// case 3.4
						s->color = x->parent->color;
						x->parent->color = 0;
						s->right->color = 0;
						leftRotate(x->parent);
						x = root;
					}
				}
				else {
					s = x->parent->left;
					if (s->color == 1) {
						// case 3.1
						s->color = 0;
						x->parent->color = 1;
						rightRotate(x->parent);
						s = x->parent->left;
					}

					if (s->right->color == 0 && s->right->color == 0) {
						// case 3.2
						s->color = 1;
						x = x->parent;
					}
					else {
						if (s->left->color == 0) {
							// case 3.3
							s->right->color = 0;
							s->color = 1;
							leftRotate(s);
							s = x->parent->left;
						}

						// case 3.4
						s->color = x->parent->color;
						x->parent->color = 0;
						s->left->color = 0;
						rightRotate(x->parent);
						x = root;
					}
				}
			}
			x->color = 0;
		}
	}


	RBNode<T>* minimum(RBNode<T>* RBNode) {
		while (RBNode->left != TNULL) {
			RBNode = RBNode->left;
		}
		return RBNode;
	}

	void leftRotate(RBNode<T>* x) {
		RBNode<T>* y = x->right;
		x->right = y->left;
		if (y->left != TNULL) {
			y->left->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			this->root = y;
		}
		else if (x == x->parent->left) {
			x->parent->left = y;
		}
		else {
			x->parent->right = y;
		}
		y->left = x;
		x->parent = y;
	}

	void rightRotate(RBNode<T>* x) {
		RBNode<T>* y = x->left;
		x->left = y->right;
		if (y->right != TNULL) {
			y->right->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			this->root = y;
		}
		else if (x == x->parent->right) {
			x->parent->right = y;
		}
		else {
			x->parent->left = y;
		}
		y->right = x;
		x->parent = y;
	}

	void insert(T key, string fname, int line) {
		RBNode<T>* RBN = new RBNode<T>;
		RBN->parent = nullptr;
		RBN->list.insert(key, fname, line);
		RBN->left = TNULL;
		RBN->right = TNULL;
		RBN->color = 1; // new RBNode must be red

		RBNode<T>* y = nullptr;
		RBNode<T>* x = this->root;

		while (x != TNULL) {
			y = x;
			if (RBN->list.head->data < x->list.head->data) {
				x = x->left;
			}
			else if (RBN->list.head->data > x->list.head->data) {
				x = x->right;
			}
			else if (RBN->list.head->data == x->list.head->data)
				break;
		}

		RBN->parent = y;
		if (y == nullptr) {
			root = RBN;
		}
		else if (RBN->list.head->data < y->list.head->data) {
			y->left = RBN;
		}
		else if (RBN->list.head->data > y->list.head->data) {
			y->right = RBN;
		}
		else {
			y->list.insert(RBN->list.head->data, RBN->list.head->file_name, RBN->list.head->line_no);
		}

		if (RBN->parent == nullptr) {
			RBN->color = 0;
			return;
		}

		if (RBN->parent->parent == nullptr) {
			return;
		}

		// Fix the tree

		RBNode<T>* u, * k;
		k = RBN;
		while (k->parent->color == 1) {
			if (k->parent == k->parent->parent->right) {
				u = k->parent->parent->left; // uncle
				if (u->color == 1) {
					// case 3.1
					u->color = 0;
					k->parent->color = 0;
					k->parent->parent->color = 1;
					k = k->parent->parent;
				}
				else {
					if (k == k->parent->left) {
						// case 3.2.2
						k = k->parent;
						rightRotate(k);
					}
					// case 3.2.1
					k->parent->color = 0;
					k->parent->parent->color = 1;
					leftRotate(k->parent->parent);
				}
			}
			else {
				u = k->parent->parent->right; // uncle

				if (u->color == 1) {
					// mirror case 3.1
					u->color = 0;
					k->parent->color = 0;
					k->parent->parent->color = 1;
					k = k->parent->parent;
				}
				else {
					if (k == k->parent->right) {
						// mirror case 3.2.2
						k = k->parent;
						leftRotate(k);
					}
					// mirror case 3.2.1
					k->parent->color = 0;
					k->parent->parent->color = 1;
					rightRotate(k->parent->parent);
				}
			}
			if (k == root) {
				break;
			}
		}
		root->color = 0;
	}
};
