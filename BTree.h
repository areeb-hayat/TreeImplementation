#pragma once
#include<iostream>
#include<string>
#include<fstream>
using namespace std;
template <class T>
class BTreeLLNode
{
public:
	T data;
	string filename;
	int line_no;
	BTreeLLNode* next;

	BTreeLLNode()
	{
		data = 0;
		next = NULL;
	}

	BTreeLLNode(T d, BTreeLLNode* n)
	{
		data = d;
		next = n;
	}

	BTreeLLNode(T d)
	{
		data = d;
		next = NULL;
	}

	void setData(T d)
	{
		data = d;
	}

	void setNext(BTreeLLNode* n)
	{
		next = n;
	}

	T getData()
	{
		return data;
	}

	BTreeLLNode* getNext()
	{
		return next;
	}

};
template <class T>
class BTreeSLinkedList {

public:

	BTreeLLNode<T>* head;


	BTreeSLinkedList()
	{
		head = NULL;
	}
	void insert(T data, string filename1, int line_no1)
	{
		BTreeLLNode <T>* n = new BTreeLLNode<T>(data);
		n->filename = filename1;
		n->line_no = line_no1;
		n->next = NULL;
		if (head == NULL)
		{
			head = n;
		}
		else
		{
			BTreeLLNode <T>* temp = head;
			while (temp->next != NULL)
			{
				temp = temp->next;
			}
			temp->next = n;
		}
	}
	void insertAtHead(T data)
	{
		BTreeLLNode <T>* n = new BTreeLLNode<T>(data);
		n->next = NULL;
		if (head == NULL)
		{
			head = n;
		}
		else
		{
			n->next = head;
			head = n;
		}
	}
	void InsertAtIndex(T data, int count)
	{
		BTreeLLNode <T>* n = new BTreeLLNode<T>(data);
		n->next = NULL;
		if (head == NULL)
		{
			head = n;
		}
		else
		{
			BTreeLLNode <T>* ptr = head;
			int i = 0;
			while (i < count && ptr)
			{
				ptr = ptr->next;
				i++;
			}
			if (ptr == NULL)
			{
				ptr = n;
			}
			else
			{
				BTreeLLNode <T>* temp;
				temp = ptr;
				ptr = n;
				n->next = temp;
			}
		}
	}
	T search(T d)
	{
		if (head)
		{
			BTreeLLNode <T>* ptr = head;
			int i = 0;
			while (ptr)
			{

				if (ptr->data == d)
				{
					return i;
				}
				ptr = ptr->next;
				i++;
			}
		}
	}
	void update(int count, T data)
	{
		if (head)
		{
			BTreeLLNode <T>* ptr = head;
			int i = 0;
			while (i < count)
			{
				ptr = ptr->next;
				i++;
			}
			ptr->data = data;
		}
	}
	void remove(T d)
	{
		if (head)
		{
			BTreeLLNode <T>* ptr = head;
			while (ptr->next)
			{
				if ((ptr->next)->data == d)
				{
					break;
				}
				ptr = ptr->next;
			}
			BTreeLLNode <T>* temp;
			if (ptr->next)
				temp = (ptr->next)->next;
			delete ptr->next;
			ptr->next = temp;
		}
	}
	void print()
	{
		if (head)
		{
			BTreeLLNode <T>* ptr = head;
			while (ptr)
			{
				cout << ptr->data << " " << ptr->filename << " " << ptr->line_no << endl;
				ptr = ptr->next;
			}
		}
	}
	bool isEmpty()
	{
		if (head == NULL)
		{
			return true;
		}
		return false;
	}
	void mergeLists(BTreeSLinkedList obj)
	{
		BTreeLLNode <T>* ptr1 = obj.head;
		BTreeLLNode <T>* ptr2 = this->head;
		int size = 0;
		while (ptr1)
		{
			ptr1 = ptr1->next;
			size++;
		}
		ptr1 = obj.head;
		int i = 0;
		while (i < size)
		{
			this->insert(ptr1->data);
			ptr1 = ptr1->next;
			i++;
		}
		int sorted = 0;
		while (ptr2)
		{
			ptr2 = ptr2->next;
			size++;
		}
		ptr2 = this->head;
		i = 0;
		int j = 0;
		T value;
		while (j < size)
		{
			i = 0;
			ptr2 = this->head;
			while (i < size && ptr2->next)
			{
				if (ptr2->data > ptr2->next->data)
				{
					value = ptr2->data;
					ptr2->data = ptr2->next->data;
					ptr2->next->data = value;
				}
				ptr2 = ptr2->next;
				i++;
			}
			j++;
		}

	}

};
template <class T>
class BNode
{

public:
	T* keys;
	BTreeSLinkedList<T>** duplicates;
	int degree;
	string* filename;
	int* line_num;
	BNode<T>** Children;
	int n;
	bool is_leaf;
	BNode(int degree1, bool is_leaf1)
	{
		degree = degree1;
		is_leaf = is_leaf1;
		keys = new T[2 * degree - 1];
		Children = new BNode * [2 * degree];
		filename = new string[2 * degree];
		line_num = new int[2 * degree]{ 0 };
		duplicates = new BTreeSLinkedList<T>*[2 * degree];
		for (int i = 0; i < (2 * degree - 1); i++)
		{
			duplicates[i] = new BTreeSLinkedList<T>;
		}
		n = 0;
	}
	void insertNonFull(T k, string file_name, int line_no)
	{

		int i = n - 1;

		if (is_leaf == true)
		{
			while (i >= 0 && keys[i] > k)
			{

				keys[i + 1] = keys[i];
				filename[i + 1] = filename[i];
				line_num[i + 1] = line_num[i];
				duplicates[i + 1] = duplicates[i];
				duplicates[i] = new BTreeSLinkedList<T>;

				i--;
			}

			keys[i + 1] = k;
			filename[i + 1] = file_name;
			line_num[i + 1] = line_no;
			n = n + 1;


		}
		else
		{

			while (i >= 0 && keys[i] > k)
				i--;

			if (Children[i + 1]->n == 2 * degree - 1)
			{
				splitChild(i + 1, Children[i + 1], file_name, line_no);
				if (keys[i + 1] < k)
					i++;
			}
			Children[i + 1]->insertNonFull(k, file_name, line_no);
		}
	}

	void splitChild(int i, BNode* y, string file_name, int line_no)
	{

		BNode* z = new BNode(y->degree, y->is_leaf);
		z->n = degree - 1;
		for (int j = 0; j < degree - 1; j++)
		{
			z->keys[j] = y->keys[j + degree];
			z->filename[j] = y->filename[j + degree];
			z->line_num[j] = y->line_num[j + degree];
			z->duplicates[j] = y->duplicates[j + degree];
		}

		if (y->is_leaf == false)
		{
			for (int j = 0; j < degree; j++)
			{
				z->Children[j] = y->Children[j + degree];

			}

		}


		y->n = degree - 1;

		for (int j = n; j >= i + 1; j--)
		{
			Children[j + 1] = Children[j];

		}


		Children[i + 1] = z;


		for (int j = n - 1; j >= i; j--)
		{
			keys[j + 1] = keys[j];
			filename[j + 1] = filename[j];
			line_num[j + 1] = line_num[j];
			duplicates[j + 1] = duplicates[j];
		}


		keys[i] = y->keys[degree - 1];
		filename[i] = y->filename[degree - 1];
		line_num[i] = y->line_num[degree - 1];
		duplicates[i] = y->duplicates[degree - 1];

		n = n + 1;
	}

	void storeInFile()
	{
		fstream outfile;
		outfile.open("BTree.txt", ios::out | ios::app);

		int i;
		for (i = 0; i < n; i++)
		{

			if (is_leaf == false)
				Children[i]->storeInFile();
			//cout << keys[i] << " " << filename[i] << " " << line_num[i] << " " << endl;
			outfile << keys[i] << "," << filename[i] << "," << line_num[i] << endl;
			if (duplicates[i]->head)
			{
				BTreeLLNode <T>* ptr = duplicates[i]->head;
				while (ptr)
				{
					outfile << ptr->data << "," << ptr->filename << "," << ptr->line_no << endl;
					ptr = ptr->next;
				}
			}
		}

		if (is_leaf == false)
			Children[i]->storeInFile();
		outfile.close();
	}
	void traverse()
	{
		fstream outfile;
		outfile.open("BTree.txt", ios::out | ios::app);

		int i;
		for (i = 0; i < n; i++)
		{

			if (is_leaf == false)
				Children[i]->traverse();
			cout << keys[i] << " " << filename[i] << " " << line_num[i] << " " << endl;
			if (duplicates[i]->head)
			{
				BTreeLLNode <T>* ptr = duplicates[i]->head;
				while (ptr)
				{
					cout << ptr->data << "," << ptr->filename << "," << ptr->line_no << endl;
					ptr = ptr->next;
				}
			}

			//outfile << keys[i] << " " << filename[i] << " " << line_num[i] << endl;

		}
		if (is_leaf == false)
			Children[i]->traverse();
		outfile.close();
	}
	BNode<T>* search(T k)
	{

		int i = 0;
		while (i < n && k > keys[i])
			i++;
		if (keys[i] == k)
		{
			return this;
		}
		if (is_leaf == true)
			return NULL;
		return Children[i]->search(k);
	}
	BNode<T>* InsertDuplicate(T k, string file_name1, int line_no1)
	{

		int i = 0;
		while (i < n && k > keys[i])
			i++;
		if (keys[i] == k)
		{
			duplicates[i]->insert(k, file_name1, line_no1);
			return this;
		}
		if (is_leaf == true)
			return NULL;
		return Children[i]->InsertDuplicate(k, file_name1, line_no1);
	}

};
template <class T>
class BTree
{

public:
	BNode<T>* root;
	int order;
	string key_Field;

	BTree(int _order)
	{
		root = NULL;  order = _order;
	}


	void traverse()
	{
		if (root != NULL)
			root->traverse();
	}
	void storeInFile()
	{
		if (root != NULL)
			root->storeInFile();
	}

	BNode<T>* search(T k)
	{
		if (root == NULL)
		{
			return NULL;
		}
		else
		{
			return root->search(k);
		}

	}
	BNode<T>* InsertDuplicates(T k, string file, int line)
	{
		if (root == NULL)
		{
			return NULL;
		}
		else
		{
			return root->InsertDuplicate(k, file, line);
		}
	}


	void insert(T k, string file_name1, int line_no1)
	{
		if (root == NULL)
		{

			root = new BNode<T>(order, true);
			root->keys[0] = k;
			root->filename[0] = file_name1;
			root->line_num[0] = line_no1;
			root->n = 1;
		}
		else
		{

			if (root->n == 2 * order - 1)
			{

				BNode<T>* s = new BNode<T>(order, false);


				s->Children[0] = root;



				s->splitChild(0, root, file_name1, line_no1);


				int i = 0;
				if (s->keys[0] < k)
					i++;
				s->Children[i]->insertNonFull(k, file_name1, line_no1);


				root = s;

			}
			else
				root->insertNonFull(k, file_name1, line_no1);
		}
	}
};