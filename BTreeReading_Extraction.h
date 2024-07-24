#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include"BTree.h"
#include"B_implemented.h"


using namespace std;
void BTreeRead(string field, int value, string order_val, string path)
{
	string* array_str = new string[100];
	ifstream myFile;
	string line;
	int i = 0;
	int index = 1;
	//string path = "NCHS_-Leading_Causes_of_Death_United_States_1.csv";
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
	int t = 1;

	BTree<string> b1(value);
	int lineNo = 2;
	int files = 1;
	int count = 0;
	while (count < 1)
	{
		while (myFile.good())
		{
			string line1;
			string line2;


			if (t == 3)
			{
				getline(myFile, line1, ',');
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
					lineNo++;
				}
			}


			if (t == index)
			{
				t = 1;
				if (line1 != "")
				{
					if (b1.search(line1) == NULL)
					{
						b1.insert(line1, path, lineNo);
					}
					else
					{
						b1.InsertDuplicates(line1, path, lineNo);
					}
				}
				if (index != 7)
					getline(myFile, line);
				lineNo++;

			}
			else
				t++;
		}
		path[46] += files;
		if (path[46] == ':')
		{
			path = "NCHS_-Leading_Causes_of_Death_United_States_10.csv";
		}
		myFile.close();
		myFile.open(path);
		getline(myFile, line);
		lineNo = 1;
		t = 1;
		count++;
	}
	//b1.traverse();

	b1.storeInFile();
	myFile.close();
}

BTree<string>* BTreeExtract(BTree<string>& b1)
{
	ifstream myFile;
	myFile.open("BTree.txt");
	string key;
	string line2;
	string filename;
	string line_no;
	getline(myFile, line2, '\n');
	int i = 0;
	int line_num = 0;
	while (line2[i] != '\0')
	{
		line_num = line_num * 10 + (line2[i] - 48);
		i++;
	}
	getline(myFile, line2, '\n');
	//BTree<string> b1(line_num);
	line_num = 0;
	i = 0;

	while (myFile.good())
	{
		getline(myFile, key, ',');
		int check = 0;
		int open = 0;
		int close = 0;
		while (key[check] != '\0')
		{
			if (key[check] == '(')
			{
				open++;
			}
			else
			{
				if (key[check] == ')')
				{
					close++;
				}
			}
			check++;
		}
		if (open != close)
		{
			getline(myFile, line2, ',');
			key += ",";
			key += line2;
		}
		getline(myFile, filename, ',');
		getline(myFile, line_no, '\n');
		while (line_no[i] != '\0')
		{
			line_num = line_num * 10 + (line_no[i] - 48);
			i++;
		}
		if (key != "" && key != " ")
		{
			if (b1.search(key) == NULL)
			{
				b1.insert(key, filename, line_num);
			}
			else
			{
				b1.InsertDuplicates(key, filename, line_num);
			}
		}
		//getline(myFile, key);
		line_num = 0;
		i = 0;
	}
	//b1.traverse();
	return &b1;
}