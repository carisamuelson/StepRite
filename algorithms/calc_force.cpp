#include <iostream>
#include <cstdio>
#include <cstdlib>

#include "lib.cpp"

double * ForceCalculations(double ** lcsv, double ** rcsv, int num_elements, int weight, int target);
double * ForcePerSensor(double ** lcsv, double ** rcsv, int num_elements);


using namespace std;

int main(int argc, char *argv[]) 
{
	
	if (argc != 3)
	{
		cout << "usage: ./wrapper leftFileName rightFileName" << endl;
		return 0;
	}
	
	char * leftFile = argv[1]; 
	char * rightFile = argv[2];
	
	int target = 0;
	int weight = 100;
	int num_elements = 0;
	
	const char * sfile1 = leftFile;
	const char * sfile2 = rightFile;
	string leftData = "", rightData = "";

	readFile(sfile1, leftData);
	readFile(sfile2, rightData);
	
	int left_elements = 0, right_elements = 0;
	double ** lcsv = SplitFile(leftData, &left_elements);
	double ** rcsv = SplitFile(rightData, &right_elements);
	
	num_elements = left_elements < right_elements ? left_elements : right_elements;
	
	ForceCalculations(lcsv, rcsv, num_elements, weight, target);
	ForcePerSensor(lcsv, rcsv, num_elements);
	
	
	return 0;
}

/* Copyright 2012, MedHab LLC */

/* Calculates information for the force dashboard.  the calculation returns the average, minimum,
maximum, # of times over max, # of times under min for each leg and the total number of elements.
remember to free the returned structure when finished */
double * ForceCalculations(double ** lcsv, double ** rcsv, int num_elements, int weight, int target)
{
	double minimum_weight = (target-5) * weight / 100;
	double maximum_weight = (target+5) * weight / 100;
	double left_total = 0, right_total = 0, total = 0, left_actual = 0, right_actual = 0;
	int left_over_max = 0, left_under_min = 0;
	int right_over_max = 0, right_under_min = 0;
	bool left_still_over = false, left_still_under = false;
	bool right_still_over = false, right_still_under = false;
	double left_average = 0, left_minimum = weight, left_maximum = 0;
	double right_average = 0, right_minimum = weight, right_maximum = 0;

	int data_start = 2;
	for(int i = data_start; i < num_elements; i++)
	{
		//compute totals for each leg and the overall total
		left_total = lcsv[i][1] + lcsv[i][2] + lcsv[i][3] + lcsv[i][4];
		right_total = rcsv[i][1] + rcsv[i][2] + rcsv[i][3] + rcsv[i][4];
		total = left_total + right_total;
		
		//compute actual on each leg
		left_actual = left_total/total;
		right_actual = right_total/total;

		left_average += left_actual;
		right_average += right_actual;

		if(left_actual < left_minimum)
			left_minimum = left_actual;
		
		if(right_actual < right_minimum)
			right_minimum = right_actual;

		if(left_actual > left_maximum)
			left_maximum = left_actual;
		
		if(right_actual > right_maximum)
			right_maximum = right_actual;

		//add over/under MAX/MIN here
		if(left_actual > maximum_weight && !left_still_over)
		{
			left_over_max++;
			left_still_over = true;
		}else if(left_still_over)
			left_still_over = false;

		if(left_actual < minimum_weight && !left_still_under)
		{
			left_under_min++;
			left_still_under = true;
		}else if(left_still_under)
			left_still_under = false;

		if(right_actual > maximum_weight && !right_still_over)
		{
			right_over_max++;
			right_still_over = true;
		}else if(right_still_over)
			right_still_over = false;

		if(right_actual < minimum_weight && !right_still_under)
		{
			right_under_min++;
			right_still_under = true;
		}else if(right_still_under)
			right_still_under = false;
	}

	left_average /= num_elements;
	right_average /= num_elements;

	//create a dynamic array to return to the calling function
	double * ret = (double *)malloc(sizeof(double) * 11);

	ret[0] = left_average;
	ret[1] = left_minimum;
	ret[2] = left_maximum;
	ret[3] = left_over_max;
	ret[4] = left_under_min;
	ret[5] = right_average;
	ret[6] = right_minimum;
	ret[7] = right_maximum;
	ret[8] = right_over_max;
	ret[9] = right_under_min;
	ret[10] = num_elements;
	
	cout << left_average << endl;
	cout << left_maximum << endl;
	cout << right_average << endl;
	cout << right_maximum << endl;
	cout << num_elements << endl;
	
	return ret;
}
