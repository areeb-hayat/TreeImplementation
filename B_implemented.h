#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include"BTree.h"
using namespace std;

string BTreegetOriginal(string fname, int line)
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
string BTreegetOriginalUpdate(string fname, int line)
{
	ifstream read;
	string data;
	read.open(fname);
	for (int i = 0; i <= line; i++)
	{
		getline(read, data, '\n');
	}
	return data;
}

void BTreeSearchData(BNode<string>* r, string key, int ord)
{
	string data = "Not Found";
	BTreeSLinkedList<string> s1;
	string fname;
	int line_no = 0;
	BTree<string> bst(ord);
	BNode<string>* n;
	bst.root = r;
	n = bst.search(key);
	int index = 0;
	for (int i = 0; i < ((2 * ord) - 1); i++)
	{
		if (n && n->keys[i] == key)
		{
			index = i;
			break;
		}
	}
	if (n)
	{
		fname = n->filename[index];
		line_no = n->line_num[index];
		data = BTreegetOriginal(fname, line_no);
		cout << endl << endl << data << endl;
		if (n->duplicates[index]->head)
		{
			BTreeLLNode <string>* ptr = n->duplicates[index]->head;
			while (ptr)
			{
				data = BTreegetOriginal(ptr->filename, ptr->line_no);
				cout << data << endl;
				ptr = ptr->next;
			}

		}

	}
	if (n == NULL)
	{
		cout << endl << endl << data << endl << endl;
	}
}
string BTreeDeleter(string fname, int line)
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
			data += "";
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
void BTreeWriteFile(string fname, string data)
{
	fstream write;
	write.open(fname);
	write << data;
}
void BTreeDeleteData(BNode<string>* r, string key, int order)
{
	string data;
	string fname;
	int line_no = 0;
	BTree<string> bst(order);
	BNode<string>* n;
	bst.root = r;
	BTreeLLNode<string>* l;
	n = bst.search(key);
	int index = 0;
	for (int i = 0; i < ((2 * order) - 1); i++)
	{
		if (n && n->keys[i] == key)
		{
			index = i;
			break;
		}
	}
	if (n)
	{
		//int moveback = 1;
		fname = n->filename[index];
		line_no = n->line_num[index];
		data = BTreeDeleter(fname, line_no);
		BTreeWriteFile(fname, data);
		l = n->duplicates[index]->head;
		while (l) {
			fname = l->filename;
			line_no = l->line_no;
			//line_no = line_no - moveback;
			//cout << endl << endl;
			data = BTreeDeleter(fname, line_no);
			BTreeWriteFile(fname, data);
			l = l->next;
			//moveback++;
		}
	}
}
string BTreeUpdater(string fname, int line, string field, int choice, string input)
{
	string y = "Year", cn113 = "113 Cause Name", cn = "Cause Name", s = "State", d = "Deaths", adr = "Age - adjusted Death Rate";
	ifstream read;
	string data;
	string main_data;
	string temp;
	string original;
	original = BTreegetOriginalUpdate(fname, line);
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
	int i = 0;
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


void BTreeUpdate(BNode<string>* r, string key, string field, int order)
{
	fstream read;
	string data;
	string fname;
	int index = 0;
	int line_no = 0;
	BTree<string> bst(order);
	BNode<string>* n;
	BTreeLLNode<string>* l;
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
	n = bst.search(key);
	index = 0;
	for (int i = 0; i < ((2 * order) - 1); i++)
	{
		if (n && n->keys[i] == key)
		{
			index = i;
			break;
		}
	}

	if (n)
	{
		fname = n->filename[index];
		line_no = n->line_num[index];
		line_no--;
		data = BTreeUpdater(fname, line_no, field, choice, input);
		BTreeWriteFile(fname, data);
		l = n->duplicates[index]->head;
		while (l) {
			fname = l->filename;
			line_no = l->line_no;
			line_no--;
			//cout << endl << endl;
			data = BTreeUpdater(fname, line_no, field, choice, input);
			BTreeWriteFile(fname, data);
			l = l->next;
		}
	}
}