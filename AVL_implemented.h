#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "AVLTree.h"
using namespace std;


///--------------------------------- FUNCTIONS -------------------------------------///

string getOriginal(string fname, int line)
{
	ifstream read;
	string data;
	//string path = "C:\\1. Kainat\\FAST\\3rd_Semester\\Data Structures\\Final Project\\datafiles\\";
	//path += fname;
	read.open(fname, ios::in);
	if (read.is_open())
		//cout << "hello!";
		for (int i = 0; i < line; i++)
		{
			getline(read, data, '\n');
		}
	return data;
}

void searchData(treeNode<string>* r, string key)
{
	string data;
	string fname;
	int line_no = 0;
	AVL<string> bst;
	treeNode<string>* n;
	linkNode<string>* l;
	bst.root = r;
	n = bst.searchTree(key);
	if (n)
	{
		l = n->list.head;
		while (l)
		{

			//l = n->list.head;
			fname = l->filename;
			line_no = l->line;
			data = getOriginal(fname, line_no);
			cout << data << " " << fname << " " << line_no << endl << endl;
			l = l->next;
		}
	}
}

string deleter(string fname, int line)
{
	ifstream read;
	string data;
	string temp;
	string path = "";
	path += fname;
	read.open(path);
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

void writeFile(string fname, string data)
{
	fstream write;
	string path = "";
	path += fname;
	write.open(path);
	write << data;
}

void deleteData(treeNode<string>* r, string key)
{
	string data;
	string fname;
	int line_no = 0;
	AVL<string> bst;
	treeNode<string>* n;
	linkNode<string>* l;
	bst.root = r;
	n = bst.searchTree(key);
	l = n->list.head;
	int i = 0;
	while (l)
	{
		fname = l->filename;
		line_no = l->line;
		//line_no -= i;
		data = deleter(fname, line_no);
		writeFile(fname, data);
		l = l->next;
		i++;
	}
}

string updater(string fname, int line, string field, int choice, string input)
{
	string y = "Year", cn113 = "113 Cause Name", cn = "Cause Name", s = "State", d = "Deaths", adr = "Age - adjusted Death Rate";
	ifstream read;
	string data;
	string main_data;
	string temp;
	string original;
	original = getOriginal(fname, line);
	int b = 0;
	if (choice > 3)
	{
		choice++;
	}
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

void update(treeNode<string>* r, string key, string field)
{
	fstream read;
	string data;
	string fname;
	int index;
	int line_no = 0;
	AVL<string> bst;
	treeNode<string>* n;
	linkNode<string>* l;
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
		fname = l->filename;
		line_no = l->line;
		cout << endl << endl;
		data = updater(fname, line_no, field, choice, input);
		writeFile(fname, data);
		l = l->next;
	}
	std::cin.clear();
	std::cin.ignore();
}

//-------------------------------------------------------
//   to store tree data in file in level order traversal
//-------------------------------------------------------
void AVL_writingTree(treeNode<string>* n, string path)
{
	fstream write;
	write.open(path, ios::app);

	//if (write.is_open())
	//	cout << "HUA! KUCH HUA" << endl << endl;
	linkNode<string>* kuchHai;
	treeNode<string>* temp;
	temp = n;
	kuchHai = temp->list.head;
	Queues<treeNode<string>*> q;
	q.enqueue(n);
	while (!q.isEmpty())
	{
		temp = q.dequeue();
		kuchHai = temp->list.head;
		while (kuchHai)
		{
			write << kuchHai->data;
			write << ",";
			write << kuchHai->filename;
			write << ",";
			write << kuchHai->line;
			write << endl;
			kuchHai = kuchHai->next;
		}
		if (temp->leftChild)
			q.enqueue(temp->leftChild);
		if (temp->rightChild)
			q.enqueue(temp->rightChild);
	}
}


treeNode<string>* AVL_read(string field, string path)
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
	AVL<string> bst;
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
			if (line1 != "\0")
				bst.root = bst.AVLinsertion(line1, fname, lno, bst.root);
			if (index != 7)
			{
				getline(myFile, line);
				lno++;
			}
		}
		else
			t++;
	}
	return bst.root;
}

treeNode<string>* ID_extractToTree(AVL<string>& idTree) {
	ifstream readlevelorder;
	string pathway = "AVL.txt";
	readlevelorder.open(pathway, ios::in);		//opened file containing level order of IDs

	string arrOfIDnameLINE[3];
	int i = 0;
	while (readlevelorder.good()) {
		getline(readlevelorder, arrOfIDnameLINE[0], ',');
		getline(readlevelorder, arrOfIDnameLINE[1], ',');
		getline(readlevelorder, arrOfIDnameLINE[2], '\n');
		int i = 0;
		int line_num = 0;
		while (arrOfIDnameLINE[2][i] != '\0')
		{
			line_num = line_num * 10 + (arrOfIDnameLINE[2][i] - 48);
			i++;
		}
		if (arrOfIDnameLINE[1] != "NCHS_-Leading_Causes_of_Death_United_States_1.csv")
		{

		}
		idTree.root = idTree.AVLinsertion(arrOfIDnameLINE[0], arrOfIDnameLINE[1], line_num, idTree.root);
		i++;
	}
	readlevelorder.close();
	//idTree.levelTraversal();
	return idTree.root;
}
void AVL_range(treeNode<string>* root, string from_range, string to_range)
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
		searchData(root, count);
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

///---------------------------------------------------------------------------------///
