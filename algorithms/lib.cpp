#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <sstream>
#include <ctime>

using namespace std;

/* a helper function to split a data file into rows and columns */
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) 
{
	std::stringstream ss(s);
	std::string item;
	while(std::getline(ss, item, delim)) 
	{
		elems.push_back(item);
	}
	
	return elems;
}
/* same as above */
std::vector<std::string> split(const std::string &s, char delim) 
{
	std::vector<std::string> elems;
	return split(s, delim, elems);
}

/* this makes use of the two split functions above to return a
2D array containing the data 
remember to free the returned structure*/
double ** SplitFile(string data, int * elements)
{
	//splits the rows of the data file
	vector<string> rows = split(data,'\n');

	unsigned int size = rows.size();

	vector< vector<string> > csv;
	//splits each row into columns
	for(unsigned int i = 0; i < size; i++)
	{
		csv.push_back(split(rows[i], ','));
	}
	//pushes them into a 2d double array
	double ** arr = (double **)malloc(sizeof(double) * size);
	for(unsigned int i = 0; i < size; i++)
	{
		unsigned int c_size = csv[i].size();
		arr[i] = (double *)malloc(sizeof(double) * c_size);
		for(unsigned int j = 0; j < c_size; j++)
		{
			arr[i][j] = strtod(csv[i][j].c_str(), NULL);
		}
	}
	
	*elements = size;
	return arr;
}

void printCSV(string file, vector<vector<string> > & csv)
{
	ofstream fout;
	fout.open(file.c_str());
	unsigned int size = csv.size();
	for(unsigned int i = 0; i < size; i++)
	{
		int col_size = csv[i].size();
		for(int j = 0; j < col_size; j++)
		{
			if(j==0)
				fout << csv[i][j];
			else
				fout << "," << csv[i][j];
		}
		fout << "\n";
	}
	fout.close();
}

void readFile(string file, string & ret)
{
	FILE * f1;
	f1 = fopen(file.c_str(), "r");
	
	if(f1 == NULL)
	{
		return;
	}
	
	fseek(f1, 0, SEEK_END);
	size_t len = ftell(f1);
	rewind(f1);
	
	char * temp = (char *)malloc(len);
	
	fread(temp, 1, len, f1);
	
	fclose(f1);
	
	ret = temp;
	
	free(temp);
}


/* gets the amount of force on each sensor.  This is used with the rom
dashboard to make sure a patient is doing the exercise correctly 
remember to free the returned structure*/
double * ForcePerSensor(double ** lcsv, double ** rcsv, int num_elements)
{

	ofstream myfile;
	ostringstream os;
	os.clear();
	os.str("");
	os << "force_output" << ".csv";
	string filestring = os.str();
	myfile.open(filestring.c_str());
	
	int data_start = 3;

	//create and initialize variables
	double * sensors = (double *)malloc(sizeof(double) * 8);
	double lf1, lf2, lf3, lf4, rf1, rf2, rf3, rf4;
	lf1 = lf2 = lf3 = lf4 = rf1 = rf2 = rf3 = rf4 = 0.0f;
	double total = 0.0f;
	//for each row, get the amount of force per sensor.
	
	int numcols = 20;
	int numrows = 500;
	string outfile[numrows][numcols];
	outfile[0][0] = "l1";
	outfile[0][1] = "l2";
	outfile[0][2] = "l3";
	outfile[0][3] = "l4";
	outfile[0][4] = "r1";
	outfile[0][5] = "r2";
	outfile[0][6] = "r3";
	outfile[0][7] = "r4";
	outfile[0][8] = "total";
	outfile[0][9] = "lp1";
	outfile[0][10] = "lp2";
	outfile[0][11] = "lp3";
	outfile[0][12] = "lp4";
	outfile[0][13] = "rp1";
	outfile[0][14] = "rp2";
	outfile[0][15] = "rp3";
	outfile[0][16] = "rp4";
	
	for(int i = data_start, k = 1; i < num_elements; i++, k++)
	{
	
	if ( k < numrows )
	{
	os.clear();
	os.str("");
	os <<  lcsv[i][1];
	outfile[k][0] = os.str();
	
		os.clear();
	os.str("");
	os <<  lcsv[i][2];
	outfile[k][1] = os.str();
	
		os.clear();
	os.str("");
	os <<  lcsv[i][3];
	outfile[k][2] = os.str();
	
		os.clear();
	os.str("");
	os <<  lcsv[i][4];
	outfile[k][3] = os.str();
	
		os.clear();
	os.str("");
	os <<  rcsv[i][1];
	outfile[k][4] = os.str();
	
		os.clear();
	os.str("");
	os <<  rcsv[i][2];
	outfile[k][5] = os.str();
	
		os.clear();
	os.str("");
	os <<  rcsv[i][3];
	outfile[k][6] = os.str();
	
		os.clear();
	os.str("");
	os <<  rcsv[i][4];
	outfile[k][7] = os.str();
	}
	
	
		total = lcsv[i][1] + lcsv[i][2] + lcsv[i][3] + lcsv[i][4] + rcsv[i][1] + rcsv[i][2] + rcsv[i][3] + rcsv[i][4];
		
		lf1 += lcsv[i][1]/total * 100;
		lf2 += lcsv[i][2]/total * 100;
		lf3 += lcsv[i][3]/total * 100;
		lf4 += lcsv[i][4]/total * 100;

		rf1 += rcsv[i][1]/total * 100;
		rf2 += rcsv[i][2]/total * 100;
		rf3 += rcsv[i][3]/total * 100;
		rf4 += rcsv[i][4]/total * 100;
		
				if ( k < numrows )
				{
				os.clear();
				os.str("");
				os <<  total;
				outfile[k][8] = os.str();

				os.clear();
				os.str("");
				os <<  lf1;
				outfile[k][9] = os.str();

				os.clear();
				os.str("");
				os <<  lf2;
				outfile[k][10] = os.str();

				os.clear();
				os.str("");
				os <<  lf3;
				outfile[k][11] = os.str();

				os.clear();
				os.str("");
				os <<  lf4;
				outfile[k][12] = os.str();

				os.clear();
				os.str("");
				os <<  rf1;
				outfile[k][13] = os.str();

				os.clear();
				os.str("");
				os <<  rf2;
				outfile[k][14] = os.str();

				os.clear();
				os.str("");
				os <<  rf3;
				outfile[k][15] = os.str();

				os.clear();
				os.str("");
				os <<  rf4;
				outfile[k][16] = os.str();

				}
		
	}
	//average them out by the number of elements
	lf1 /= (num_elements - data_start);
	lf2 /= (num_elements - data_start);
	lf3 /= (num_elements - data_start);
	lf4 /= (num_elements - data_start);

	rf1 /= (num_elements - data_start);
	rf2 /= (num_elements - data_start);
	rf3 /= (num_elements - data_start);
	rf4 /= (num_elements - data_start);

	sensors[0] = lf1; sensors[1] = lf2; sensors[2] = lf3; sensors[3] = lf4;
	sensors[4] = rf1; sensors[5] = rf2; sensors[6] = rf3; sensors[7] = rf4;
	
	cout << lf1 << endl;
	cout << lf2 << endl;
	cout << lf3 << endl;
	cout << lf4 << endl;
	cout << rf1 << endl;
	cout << rf2 << endl;
	cout << rf3 << endl;
	cout << rf4 << endl;
	
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < numcols; j++)
		{
			myfile << outfile[i][j] << ",";
		}
		myfile << "0" << endl;
	}
	myfile.close();

	return sensors;
}