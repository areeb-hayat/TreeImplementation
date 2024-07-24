#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "RBTree.h"
using namespace std;


void RB_writingTree(RBNode<string>* n, string path)
{
	fstream write;
	write.open(path, ios::app);

	//if (write.is_open())
	//	cout << "HUA! KUCH HUA" << endl << endl;
	RB_LLNode<string>* kuchHai;
	RBNode<string>* temp;
	temp = n;
	kuchHai = temp->list.head;
	RB_Queue<RBNode<string>*> q;
	q.enqueue(n);
	while (!q.isEmpty())
	{
		temp = q.dequeue()->data;
		kuchHai = temp->list.head;
		while (kuchHai)
		{
			write << kuchHai->data;
			write << " ";
			write << kuchHai->file_name;
			write << " ";
			write << kuchHai->line_no;
			write << endl;
			kuchHai = kuchHai->next;
		}
		if (temp->left)
			q.enqueue(temp->left);
		if (temp->right)
			q.enqueue(temp->right);
	}
}

RBNode<string>* RB_read(string field, string path)
{
	int lno = 1;
	string fname = path;
	string* array_str = new string[100];
	ifstream myFile;
	string line;
	int i = 0;
	int index = 1;
	myFile.open(path);
	while (myFile.good())
	{
		string line1;
		if (index != 7)
			getline(myFile, line1, ',');
		else
			getline(myFile, line1);
		if (line1 == field)
		{
			break;
		}
		index++;
	}

	myFile.close();
	myFile.open(path);
	getline(myFile, line);
	lno++;
	RBTree<string> rb;
	int t = 1;
	while (myFile.good())
	{
		string line1;
		string line2;

		if (t == 3)
		{
			getline(myFile, line1, ',');
			lno++;
			int check = 0;
			int open = 0;
			int close = 0;
			while (line1[check] != '\0')
			{
				if (line1[check] == '(')
				{
					open++;
				}
				else
				{
					if (line1[check] == ')')
					{
						close++;
					}
				}
				check++;
			}
			if (open != close)
			{
				getline(myFile, line2, ',');
				line1 += ",";
				line1 += line2;
			}
		}
		else
		{
			if (t != 7)
			{
				getline(myFile, line1, ',');
			}
			else
			{
				getline(myFile, line1);
			}
		}

		if (t == index)
		{
			t = 1;
			//cout << line1 << endl;
			rb.insert(line1, fname, lno);
			if (index != 7)
			{
				getline(myFile, line);
				lno++;
			}
		}
		else
			t++;
	}
	return rb.root;
}

RBNode<string>* RB_retrievingTree(string fname)
{
	RBTree<string> newTree;
	fstream read;
	read.open(fname);

	//if (read.is_open())
	//	cout << "dekho dekho, phirse hua";

	string val;
	string file;
	int line;
	while (!read.eof())
	{
		read >> val;
		read >> file;
		read >> line;

		newTree.insert(val, file, line);
	}
	return newTree.root;
}

string RB_getOriginal(string fname, int line)
{
	ifstream read;
	string data;
	read.open(fname);
	for (int i = 0; i < line; i++)
	{
		getline(read, data, '\n');
	}
	return data;
}

void RB_searchData(RBNode<string>* r, string key)
{
	string data;
	string fname;
	int line_no = 0;
	RBTree<string> bst;
	RBNode<string>* n;
	RB_LLNode<string>* l;
	bst.root = r;
	n = bst.searchTree(key);
	l = n->list.head;
	while (l)
	{
		fname = l->file_name;
		line_no = l->line_no;
		data = RB_getOriginal(fname, line_no);
		cout << data << " " << fname << " " << line_no << endl << endl;
		l = l->next;
	}
}

string RB_deleter(string fname, int line)
{
	ifstream read;
	string data;
	string temp;
	read.open(fname);
	int i = 1;
	while (!read.eof())
	{
		if (i == line)
		{
			getline(read, temp);
			data += " ";
			data += "\n";
			i++;
		}
		else
		{
			getline(read, temp);
			data += temp;
			data += "\n";
			i++;
		}
	}
	return data;
}

void RB_writeFile(string fname, string data)
{
	fstream write;
	write.open(fname);
	write << data;
}

void RB_deleteData(RBNode<string>* r, string key)
{
	string data;
	string fname;
	int line_no = 0;
	RBTree<string> bst;
	RBNode<string>* n;
	RB_LLNode<string>* l;
	bst.root = r;
	n = bst.searchTree(key);
	l = n->list.head;
	int i = 0;
	while (l)
	{
		fname = l->file_name;
		line_no = l->line_no;
		//line_no -= i;
		data = RB_deleter(fname, line_no);
		RB_writeFile(fname, data);
		l = l->next;
		i++;
	}
	//bst.deleteNode(key);
}

string RB_updater(string fname, int line, string field, int choice, string input)
{
	string y = "Year", cn113 = "113 Cause Name", cn = "Cause Name", s = "State", d = "Deaths", adr = "Age - adjusted Death Rate";
	ifstream read;
	string data;
	string main_data;
	string temp;
	string original;
	original = RB_getOriginal(fname, line);
	int b = 0;
	for (int j = 0; j < choice; j++)
	{
		while (original[b] != ',' && original[b] != '\0')
		{
			data += original[b];
			b++;
		}
		data += original[b];
		b++;
	}
	data += input;
	data += ',';
	while (original[b] != ',' && original[b] != '\0')
		b++;
	b++;
	while (original[b] != '\0')
	{
		data += original[b];
		b++;
	}
	data += "\0";

	read.open(fname);
	int i = 1;
	while (!read.eof())
	{
		if (i == line)
		{
			getline(read, temp);
			main_data += data;
			main_data += "\n";
			i++;
		}
		else
		{
			getline(read, temp);
			temp += "\n";
			main_data += temp;
			i++;
		}
	}
	return main_data;
}


void RB_update(RBNode<string>* r, string key, string field)
{
	fstream read;
	string data;
	string fname;
	int index;
	int line_no = 0;
	RBTree<string> bst;
	RBNode<string>* n;
	RB_LLNode<string>* l;
	bst.root = r;
	int choice = 0;
	string input;

	cout << "Please choose the field you want to change" << endl;
	if (field == "ID")
	{
		cout << "\t1. Year" << endl;
		cout << "\t2. 113 Cause Name" << endl;
		cout << "\t3. Cause Name" << endl;
		cout << "\t4. State" << endl;
		cout << "\t5. Deaths" << endl;
		cout << "\t6. Age-adjusted Death Rate" << endl << endl;
		cin >> choice;
	}
	if (field == "Year")
	{
		cout << "\t1. ID" << endl;
		cout << "\t2. 113 Cause Name" << endl;
		cout << "\t3. Cause Name" << endl;
		cout << "\t4. State" << endl;
		cout << "\t5. Deaths" << endl;
		cout << "\t6. Age-adjusted Death Rate" << endl << endl;
		cin >> choice;
		if (choice == 1)
			choice = 0;
	}
	if (field == "113 Cause Name")
	{
		cout << "\t1. ID" << endl;
		cout << "\t2. Year" << endl;
		cout << "\t3. Cause Name" << endl;
		cout << "\t4. State" << endl;
		cout << "\t5. Deaths" << endl;
		cout << "\t6. Age-adjusted Death Rate" << endl << endl;
		cin >> choice;
		if (choice <= 2)
			choice--;
	}
	if (field == "Cause Name")
	{
		cout << "\t1. ID" << endl;
		cout << "\t2. Year" << endl;
		cout << "\t3. 113 Cause Name" << endl;
		cout << "\t4. State" << endl;
		cout << "\t5. Deaths" << endl;
		cout << "\t6. Age-adjusted Death Rate" << endl << endl;
		cin >> choice;
		if (choice <= 3)
			choice--;
	}
	if (field == "State")
	{
		cout << "\t1. ID" << endl;
		cout << "\t2. Year" << endl;
		cout << "\t3. 113 Cause Name" << endl;
		cout << "\t4. Cause Name" << endl;
		cout << "\t5. Deaths" << endl;
		cout << "\t6. Age-adjusted Death Rate" << endl << endl;
		cin >> choice;
		if (choice <= 4)
			choice--;
	}
	if (field == "Deaths")
	{
		cout << "\t1. ID" << endl;
		cout << "\t2. Year" << endl;
		cout << "\t3. 113 Cause Name" << endl;
		cout << "\t4. Cause Name" << endl;
		cout << "\t5. Deaths" << endl;
		cout << "\t6. Age-adjusted Death Rate" << endl << endl;
		cin >> choice;
		if (choice <= 5)
			choice--;
	}
	if (field == "Age-adjusted Death Rate")
	{
		cout << "\t1. ID" << endl;
		cout << "\t2. Year" << endl;
		cout << "\t3. 113 Cause Name" << endl;
		cout << "\t4. Cause Name" << endl;
		cout << "\t5. Deaths" << endl;
		cout << "\t6. Age-adjusted Death Rate" << endl << endl;
		cin >> choice;
		if (choice <= 6)
			choice--;
	}
	cout << "Enter new value for this field: ";
	cin >> input;

	n = bst.searchTree(key);
	l = n->list.head;
	while (l) {
		fname = l->file_name;
		line_no = l->line_no;
		cout << endl << endl;
		data = RB_updater(fname, line_no, field, choice, input);
		RB_writeFile(fname, data);
		l = l->next;
	}
}

void RB_range(RBNode<string>* root, string from_range, string to_range)
{
	//convert to int
	int range_start;
	int range_end;
	int i = 0;
	while (from_range[i] != '\0')
	{
		i++;
	}
	range_start = from_range[0] - 48;
	for (int j = 1; j < i; j++)
	{
		range_start *= 10;
		range_start += (from_range[j] - 48);
	}
	i = 0;
	while (to_range[i] != '\0')
	{
		i++;
	}
	range_end = to_range[0] - 48;
	for (int j = 1; j < i; j++)
	{
		range_end *= 10;
		range_end += (to_range[j] - 48);
	}
	//to int end
	int difference = range_end - range_start;
	if (difference <= 0)
		cout << "ERROR" << endl;
	string count = from_range;
	int temp;
	for (int d = 0; d <= difference; d++)
	{
		RB_searchData(root, count);
		cout << endl << endl;
		i = 0;
		while (count[i] != '\0')
		{
			i++;
		}
		temp = count[0] - 48;
		for (int j = 1; j < i; j++)
		{
			temp *= 10;
			temp += (count[j] - 48);
		}
		temp += 1;
		count = to_string(temp);
	}
}
