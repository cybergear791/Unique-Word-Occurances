//LAb 6 
//created by Nick Flouty
// Counts the occurances of each unqiue word in a text.txt

#include "BST.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <ctime>
using namespace std;

bool isValid(char input) {
	if (isalpha(input) || isdigit(input) || input == '-' || input == '\'' || input==' ')
		return true;
	return false;
}

struct BinaryNode {
	vector<vector<string>> linenumbers;
	int line = 0;
};

BinarySearchTree<string> buildTree()
{
	string name;
	cout << "Enter the name of the input text file: ";
	cin >> name;
	ifstream file;
	file.open(name.c_str());
	string line;
	vector<vector<string>> output2;
	BinaryNode linecount;
	vector<vector<bool>> check;
	int counter = 0;

	while (getline(file, line))
	{
		string word;
		
		linecount.line++;
		char temp;
		vector<string> output;
		vector<string> linetest;
		vector<bool> checky;
		for (int i = 0; i < line.size(); i++)
		{
			while (isValid(line[i]))
			{
				temp = line[i];
				word += temp;	//while it a valid char it pushes each character of a word into a string
				i++;
			}//end while
		}//end for
		 //cout << word;

		string temp2;
		istringstream lineStream(word);
		while (lineStream >> temp2)
		{
			checky.push_back(false);
			output.push_back(temp2);
			linetest.push_back(to_string(linecount.line));
			counter++;

		}
		check.push_back(checky);
		linecount.linenumbers.push_back(linetest);
		output2.push_back(output);
	}//end while
	//**********************************************************

	clock_t cl = clock();
	BinarySearchTree<string> Tree;
	Tree.insert(output2[0][0], linecount.linenumbers[0][0]);
	for (int i = 0; i < output2.size(); ++i)
	{
		for (int j = 0; j < output2[i].size(); ++j)
		{
			if ((!Tree.contains(output2[i][j])) & (check[i][j]==false))
			{
				check[i][j] = true;
				Tree.insert(output2[i][j], linecount.linenumbers[i][j]);
			}
			else //if there is already the same word in the tree
			{	
				for (int w = 0; w < output2.size(); ++w)
				{
					for (int r = 0; r < output2[w].size(); ++r)
					{
						if ((output2[i][j] == output2[w][r]) & (check[w][r] ==false)) //go through the rest of the file and check for that word and if it has already been checked?
						{
							check[w][r] = true;
							Tree.insert(output2[i][j], linecount.linenumbers[i][j]);
						}
					}
				}
			}
		}	
	} 
	cl = clock() - cl;
	cout << "Total number of words: " << counter << endl;
	cout << "Total number of distinct words: " << Tree.size(Tree.getRoot()) << endl;
	cout << "Time Taken to build index using BST is: " << cl / (double)CLOCKS_PER_SEC << " seconds" << endl;
	cout << "Height of Tree is: " << Tree.height(Tree.getRoot()) << endl;
	//*****************************************************
	bool quit = false;
	while (!quit)
	{
		int in;
		cout <<endl<< "Options: (1) display index, (2) search, (3) save index, (4) quit" << endl;
		cin >> in;
		if (in == 1)
		{
			Tree.printTree();
		}
		else if (in == 2)	
		{
			string word;
			cout << "Search word: ";
			cin >> word;
			Tree.findWord(word);
		}
		else if (in == 3)	//finish
		{
			string file;
			cout << "Enter a file name in which to store index: ";
			cin >> file;
			ofstream fname(file);
			Tree.printTree(fname);
		}
		else if (in == 4)
			quit = true;
	}
	return Tree;
}//End function

int main() {
	
	buildTree();
	
	//system("PAUSE");
	return 0;
}