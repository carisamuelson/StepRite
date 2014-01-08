#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <sstream>
#include <ctime>

#include "lib.cpp"

using namespace std;
void doCompensation(char * leftFile, char * rightFile, long difference, long epoch);


int main(int argc, char *argv[]) 
{
	
	if (argc != 4)
	{
		cout << "usage: ./wrapper leftFileName rightFileName difference" << endl;
		return 0;
	}
	
	char * leftFile = argv[1];  //"tc_i1_eid1-lf0.csv";
	char * rightFile = argv[2]; //"tc_i1_eid1-rf0.csv";
	long difference = atol(argv[3]);  //500;
	long epoch = time(NULL);

	doCompensation(leftFile, rightFile, difference, epoch);

	return 0;
}



inline std::string to_string (long t)
{
	std::stringstream ss;
	ss << t;
	return ss.str();
}

void doCompensation(char * leftFile, char * rightFile, long difference, long epoch)
{
	const char * sfile1 = leftFile;
	const char * sfile2 = rightFile;
	string leftData = "", rightData = "";

	readFile(sfile1, leftData);
	readFile(sfile2, rightData);
	
	if(leftData == "" || rightData == "")
		return;
	
	vector<string> leftRows = split(leftData, '\n'), rightRows = split(rightData, '\n');
	vector<vector<string> > leftCSV, rightCSV;
	unsigned int size = leftRows.size();
	for(unsigned int i = 0; i < size; i++)
	{
		leftCSV.push_back(split(leftRows[i],','));
	}
	
	size = rightRows.size();
	for(unsigned int i = 0; i < size; i++)
	{
		rightCSV.push_back(split(rightRows[i],','));
	}
	
	//remove the unwanted stuff from the left file
	for(int i = difference/10 + 1; i > 1; i--)
	{
		leftCSV.erase(leftCSV.begin() + i);
	}
	
	//align epoch times
	size = leftCSV.size();
	for(unsigned int i = 2, j = 0; i < size; j++,i++)
	{
		leftCSV[i][0] = to_string(epoch + j/100);
	}
	
	size = rightCSV.size();
	for(unsigned int i = 2, j = 0; i < size; j++,i++)
	{
		rightCSV[i][0] = to_string(epoch + j/100);
	}
	
	printCSV(sfile1, leftCSV);
	printCSV(sfile2, rightCSV);
}