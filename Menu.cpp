#include <iostream>
#include <fstream>
#include <string>
#include "RB_implemented.h"
#include "RBTree.h"
#include "BTree.h"
#include "B_implemented.h"
#include "BTreeReading_Extraction.h"
#include "AVLTree.h"
#include "AVL_implemented.h"

using namespace std;

int main() {
	
	int tree_choice;
	cout << "\t\t\tWELCOME TO DATABASE SYSTEM\n\n\n";
	cout << "\tPlease select your choice of Tree: \n";
	cout << "1. AVL Tree\n2. Red-Black Tree\n3. B-Tree\n";
	cin >> tree_choice;
	
	while (tree_choice < 1 || tree_choice > 3)
	{
		cout << "Invalid Input, Please enter valid Tree type: ";
		cin >> tree_choice;
	}

	// AVL TREE
	if (tree_choice == 1)
	{
		AVL<string> bst;
		string choice;
		cout << "\t \t AVL Tree" << endl;
		cout << "Enter 1 if you want to make new Tree" << endl;
		cout << "Enter 2 if you want to Extract Tree from File" << endl;
		cout << ": ";
		cin >> choice;

		if (choice == "1")
		{
			char fileNum = '1';
			int count = 1;
			string field;
			cout << "Enter Field of Which You want to Construct Tree: ";
			cin >> field;
			fstream DBfile;
			string pathToDB = "";
			pathToDB = "ID";
			pathToDB += "AVL.txt";
			DBfile.open(pathToDB.c_str(), ios::app);
			DBfile << field << endl;
			DBfile.close();
			//string field;
			int querry_choice;
			string path = "AVL.txt";
			string fname = "NCHS_-_Leading_Causes_of_Death__United_States_";
			AVL<string> avl;
			AVL<string>* n;
			for (int i = 1; i <= 10; i++)
			{
				string temp_str = fname;
				string temp = to_string(i);
				temp += ".csv";
				temp_str += temp;
				fname = temp_str;
				avl.root = AVL_read(field, fname);
				string write_file = "AVL.txt";
				AVL_writingTree(avl.root, write_file);
				fname = "NCHS_-_Leading_Causes_of_Death__United_States_";
				//cout << avl.root->list.head->data << endl;
			}
		}
		if (choice == "2")
		{
			ID_extractToTree(bst);
			string queryChoice;
			string contChoice;

			do
			{
				cout << "Enter 1 if You want to Perform Search Query" << endl;
				cout << "Enter 2 if You want to Perform Range Query" << endl;
				cout << "Enter 3 if You want to Perform Update Query" << endl;
				cout << "Enter 4 if You want to Perform Delete Query" << endl;
				cout << ": ";
				cin >> queryChoice;
				string key;
				string key1;

				if (queryChoice == "1")
				{

					cout << "Enter Key to Search in Tree: ";
					cin >> key;
					searchData(bst.root, key);
				}
				if (queryChoice == "2")
				{
					cout << "Enter Starting Key For Range: ";
					cin >> key;
					cout << "Enter Ending key For Range: ";
					cin >> key1;
					AVL_range(bst.root, key, key1);
				}
				if (queryChoice == "3")
				{
					cout << "Enter Key to Update in Tree: ";
					cin >> key;
					update(bst.root, key, "ID");
				}
				if (queryChoice == "4")
				{
					cout << "Enter Key to Delete in Tree: ";
					cin >> key;
					deleteData(bst.root, key);
				}
				cout << "Enter -1 To terminate: ";
				cin >> contChoice;
			} while (contChoice != "-1");
		}
	}

	// RED-BLACK TREE
	else if (tree_choice == 2)
	{
		string field;
		string choice;
		int choice1;
		string id_path = "ID_RB.txt";
		string path = "RBTree.txt";
		cout << "\t \t Reb-Black Tree" << endl;
		cout << "Enter 1 if you want to make new Tree" << endl;
		cout << "Enter 2 if you want to Extract Tree from File" << endl;
		cout << ": ";
		cin >> choice1;
		RBTree<string> RB;
		RBNode<string>* n;
		int querry_choice;
		if (choice1 == 1)
		{
			cout << "Please enter the field to base your tree upon: ";
			cin >> field;
			cout << endl;
			fstream read_id;
			read_id.open(id_path);
			read_id << field;
			string fname = "NCHS_-_Leading_Causes_of_Death__United_States_";
			for (int i = 1; i <= 10; i++)
			{
				string temp_str = fname;
				string temp = to_string(i);
				temp += ".csv";
				temp_str += temp;
				fname = temp_str;
				RB.root = RB_read(field, fname);
				RB_writingTree(RB.root, path);
				fname = "NCHS_-_Leading_Causes_of_Death__United_States_";
			}
		}

		RB.root = RB_retrievingTree(path);
		fstream id_read;
		id_read.open(id_path);
		id_read >> field;
		//cout << "\tData has been extracted and saved in File & in the Tree\n\n";

		bool cont = true;
		while (cont == true)
		{
			cout << "Please select your choice of actions: \n";
			cout << "\t1. Search Data\n\t2. Delete Data\n\t3.Update Data\n\t4. Range Search\n";
			cin >> querry_choice;
			while (querry_choice < 1 || querry_choice > 4)
			{
				cout << "Invalid Input, Please enter valid Tree type: ";
				cin >> tree_choice;
			}
			if (querry_choice == 1)
			{
				string search;
				cout << "Enter the key you want to search: ";
				cin >> search;
				RB_searchData(RB.root, search);
			}
			else if (querry_choice == 2)
			{
				string del;
				cout << "Enter the key you want to delete: ";
				cin >> del;
				RB_deleteData(RB.root, del);
			}
			else if (querry_choice == 3)
			{
				string upd;
				cout << "Enter the key you want to update: ";
				cin >> upd;
				RB_update(RB.root, upd, field);
			}
			else if (querry_choice == 4)
			{
				string start;
				string end;
				cout << "Enter the key you want to start search from: ";
				cin >> start;
				cout << "Enter the key you want to end search at: ";
				cin >> end;
				RB_range(RB.root, start, end);
			}
			char cont_choice;
			cout << "Do you wish to perform another Querry (Y/N): ";
			cin >> cont_choice;
			while (cont_choice != 'Y' && cont_choice != 'y' && cont_choice != 'N' && cont_choice != 'n')
			{
				cout << "Invalid Input, Please enter Y/N: ";
				cin >> cont_choice;
			}
			if (cont_choice == 'Y' || cont_choice == 'y')
				cont_choice = true;
			else 
				cont_choice = false;
		}
	}

	//B-TREE
	else if (tree_choice == 3)
	{
		string choice;
		string field = "ID";
		string cont;
		string print1;
		int order = 0;

		cout << "\t\tBtree" << endl << endl;
		cin.ignore();
		cin.clear();
		do
		{
			do
			{
				cout << "Enter 1 if you want to Create a Btree" << endl;
				cout << "Enter 2 if you want to Extract Tree From File to Perform Operations on It" << endl;
				getline(cin, choice);
			} while (choice != "1" && choice != "2");
			if (choice == "1")
			{
				string path = "NCHS_-Leading_Causes_of_DeathUnited_States";
				cout << "Enter Field: ";
				getline(cin, field);
				string val;
				cout << "Enter Order of Btree" << endl;
				getline(cin, val);
				int value = 0;
				int i = 0;
				while (val[i] != '\0')
				{
					value = value * 10 + (val[i] - 48);
					i++;
				}
				i = 1;
				char number = '1';
				fstream outfile;
				outfile.open("BTree.txt", ios::out | ios::app);
				outfile << val << endl;
				outfile << field << endl;
				outfile.close();

				while (i <= 9)
				{
					path = "NCHS_-_Leading_Causes_of_Death__United_States_";
					path += number;
					path += ".csv";
					BTreeRead(field, value, val, path);
					i++;
					number++;

				}
				path = "NCHS_-_Leading_Causes_of_Death__United_States_10.csv";
				BTreeRead(field, value, val, path);
				cout << "Tree has Generated and Saved in File" << endl;
			}
			if (choice == "2")
			{
				ifstream myFile;
				myFile.open("BTree.txt");
				string line2;
				getline(myFile, line2, '\n');
				getline(myFile, field, '\n');
				int i = 0;
				int line_num = 0;
				myFile.close();
				while (line2[i] != '\0')
				{
					line_num = line_num * 10 + (line2[i] - 48);
					i++;
				}
				BTree<string> b1(line_num);
				string query;
				BTree<string>* tree = BTreeExtract(b1);
				order = tree->order;
				cout << "Tree has Been Extracted From File" << endl;
				string keyval;
				string keyval1;

				cout << "Enter 1 for Search Query" << endl;
				cout << "Enter 2 for Range Query" << endl;
				cout << "Enter 3 for Update Query" << endl;
				cout << "Enter 4 for Delete Query" << endl;
				cout << "Your Choice: " << endl;
				getline(cin, query);
				if (query == "1")
				{
					cout << "Enter Key Value: ";
					getline(cin, keyval);
					BTreeSearchData(b1.root, keyval, order);
				}
				if (query == "2")
				{
					int val1 = 0;
					int val2 = 0;
					int i = 0;
					cout << "Enter Key Value for Start of Range: ";
					getline(cin, keyval);
					while (keyval[i] != '\0')
					{
						val1 = val1 * 10 + (keyval[i] - 48);
						i++;
					}
					i = 0;
					cout << "Enter Key Value for END of Range: ";
					getline(cin, keyval1);
					while (keyval1[i] != '\0')
					{
						val2 = val2 * 10 + (keyval1[i] - 48);
						i++;
					}
					val2 = val2 - val1;
					int temp = 0;
					int temp1 = 0;
					for (int i = 0; i <= val2; i++)
					{
						BTreeSearchData(b1.root, keyval, order);
						val1++;
						temp = val1;
						keyval = "\0";
						while (temp != 0)
						{
							temp1 = (temp1 * 10) + temp % 10;
							temp /= 10;
						}
						while (temp1 != 0)
						{
							keyval += (temp1 % 10) + 48;
							temp1 /= 10;
						}
					}
					cin.ignore();
					cin.clear();
				}
				if (query == "3")
				{
					cout << "Enter Key Value: ";
					getline(cin, keyval);
					BTreeUpdate(b1.root, keyval, field, order);
				}
				if (query == "4")
				{
					cout << "Enter Key Value: ";
					getline(cin, keyval);
					BTreeDeleteData(b1.root, keyval, order);
					cout << endl << "Successfully Deleted" << endl;
				}
				cout << "Do you want to print it (Y/N): ";
				getline(cin, print1);
				if (print1 == "Y")
				{
					b1.root->traverse();

				}

			}

			cout << "Do You want to Perform another operation?" << endl << "Enter -1 to terminate: ";
			getline(cin, cont);
		} while (cont != "-1");
	}

	return 0;
}