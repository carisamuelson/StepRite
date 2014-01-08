/*
This file contains the algorithms developed by Dr.
Rob LeGrand.   Copyright 2012, MedHab LLC 
*/

#include <climits>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <vector>
#include <fstream>
#include <float.h>


#include "lib.cpp"

using namespace std;

#define PITCH	data[ACCEL2_X], data[ACCEL2_Z], 'x', 'z', leg
#define ROLL	data[ACCEL2_Y], data[ACCEL2_Z], 'z', 'x', leg
#define YAW		data[ACCEL2_X], data[ACCEL2_Y], 'x', 'y', leg

//constants for the location in the arrays for
//the data
const int ACCEL1_X = 5;
const int ACCEL1_Y = 6;
const int ACCEL1_Z = 7;
const int ACCEL2_X = 5;
const int ACCEL2_Y = 6;
const int ACCEL2_Z = 7;

//number of rows per second
const int RPS = 25;
//the start of the data (first row with data is row 10)
//old data starts at 13
const int DATA_START = 10;

const double PI = 3.141592653589;

//Dr. LeGrands debug boolean
const bool PRINT_DEBUG_INFO = false;

// Cari's boolean, set to true if you want a detailed graph file output
const bool OUTPUT_GRAPH_FILE = false;

/*converts radians into degrees */
double RadiansToDegrees(double radians)
{
	return radians * (180/PI);
}

/* get the offset for the axis */
double GetOffset(char axis, string leg)
{
	double xOffset, yOffset, zOffset;
	xOffset = yOffset = zOffset = 0.0;
	switch(axis)
	{
		case 'x' : return leg=="left" ? xOffset : xOffset;
		case 'y' : return leg=="left" ? yOffset : yOffset;
		case 'z' : return leg=="left" ? zOffset : zOffset;
		default  : return 0;
	}
}

/* this takes two data points from a file, adds in their offsets, and
generates a value in degrees */
/* as per: http://blog.mattandanne.org/2006/10/beware-of-atan2-excel-vs-cc-be-aware.html
 Beware of ATAN2: Excel vs C/C++
Be aware when copying formulae between Excel and C/C++. 
For example, the Excel version of ATAN2 accepts two parameters X & Y receptively. 
On the other hand, ATAN2 in the C Math library accepts two parameters Y & X! 
So if you blindly copy, the equation will work but be 90 degrees out of phase!! 
*/
double DegreesFromOffset(double data1, double data2, char axis1, char axis2, string leg)
{

	double ret1 = abs(atan2(data1 - GetOffset(axis1, leg), data2 - GetOffset(axis2, leg)));
	ret1 = abs(atan2(data1, data2));
	ret1 = abs(atan2(data2, data1));
	
	ret1 = RadiansToDegrees(ret1);
	
	ret1-=90;
	
	ret1=abs(ret1);

	// DCT: no longer using ret, using ret1 to correct after doing various real-data tests
	//double ret = (RadiansToDegrees(atan2(data1 - GetOffset(axis1, leg), data2 - GetOffset(axis2, leg))));
	
	
	// FIXME Is there any reason for this step?
//	if(ret < 0)
//		ret *= -1;
	// An angle's quadrant and sign should probably be fixed separately for each specific exercise.  See below.

	return ret1;
}

double CalculateDegrees(double * data, int exCode, string leg)
{
	switch(exCode)
	{
		// For now, just deciding in which plane the movement is--not worrying at all about major v. minor
		// axes or any signs.  So, for now, there are only three possibilities: xy, xz and yz.  If there
		// is no apparent plane of motion, neither for hip (accelerometer 1) nor for foot (accelerometer
		// 2), just return 0.  These are based on RHL's best judgement and may need to be adjusted based
		// on real data and real experts.

		// Update (2 July 2012): RHL fixed the following according to data gathered at ASU the week of 20 June 2012:
		//    AF15 AF20 AF21 AF22 AF27 AF42 AF45 HK24 HK26 HK27 HK28
		//    HK29 HK30 HK31 HK44 HK55 HK57 HK58 HK59 HK76 HK80
		// The formulae for those exercises should now be correct for both legs.
		// Note: The subject 002 data for AF22 must really be for a different exercise, maybe AF20?

		// ankle/foot
		case 25 : return 0; // -DegreesFromOffset(data[ACCEL2_Y], data[ACCEL2_Z], 'y', 'z', leg); // AF15
		case 15 : return  DegreesFromOffset(PITCH); // AF20
//		{
//		double deg = abs(DegreesFromOffset(data[ACCEL2_X], data[ACCEL2_Z], 'y', 'z', leg)) > 180 ?
//						 abs(DegreesFromOffset(data[ACCEL2_X], data[ACCEL2_Z], 'y', 'z', leg)) - 90:
//						 abs(DegreesFromOffset(data[ACCEL2_X], data[ACCEL2_Z], 'y', 'z', leg)); // AF20
//						 //cout << "deg: " << deg << endl;
//						 return deg;
//						 break;
//						 }
		case 16 : return  DegreesFromOffset(PITCH); // AF21
		case 17 : return  DegreesFromOffset(PITCH); // AF22
		case 26 : return  DegreesFromOffset(PITCH); // AF26
		case 18 : return  DegreesFromOffset(PITCH); // AF27
		case 19 : return  DegreesFromOffset(PITCH); // AF28
		case 20 : return  abs(DegreesFromOffset(YAW)); // AF29
		case 21 : return  abs(DegreesFromOffset(YAW)); // AF30
		// case 22 : return  0; // AF42 (no significant rotational motion)
		case 22: return abs(DegreesFromOffset(PITCH)); // AF42 // DCT
//		case 23 : return -DegreesFromOffset(data[ACCEL2_Y], data[ACCEL2_Z], 'y', 'z', leg); // AF45 (seems to work very well with leg data)
		case 23 : return abs(DegreesFromOffset(PITCH)); // AF45 (perhaps should work better with hip data)
		case 24 : return  abs(DegreesFromOffset(PITCH)); // AF46

		// hip/knee (both part 1 and strength)
		case 27 : return  abs(DegreesFromOffset(PITCH)); // HK8
		case 42 : return  0;                                                                // HK32 (significant motion only in y)
		case 43 : return  0;                                                                // HK33 (significant motion only in z)
		case 44 : return  abs(DegreesFromOffset(PITCH));									// HK34
		case 45 : return  abs(DegreesFromOffset(ROLL));										// HK35
		case 46 : return  abs(DegreesFromOffset(ROLL));										// HK36
		case 47 : return  abs(DegreesFromOffset(PITCH));									// HK37
		case 48 : return  abs(DegreesFromOffset(PITCH));									// HK38
		case 49 : return  abs(DegreesFromOffset(PITCH));									// HK39
		case 50 : return  abs(DegreesFromOffset(PITCH));									// HK40

		case 51 : return  abs(DegreesFromOffset(PITCH)); // HK41
		case 52 : return  abs(DegreesFromOffset(PITCH)); // HK42
		case 57 : return  abs(DegreesFromOffset(PITCH));									// HK48
		case 64 : return  abs(DegreesFromOffset(PITCH));									// HK61
		case 65 : return  abs(DegreesFromOffset(PITCH));									// HK63
		case 66 : return  abs(DegreesFromOffset(YAW));										// HK66 (motion in y as well, but seems less)
		case 67 : return  abs(DegreesFromOffset(PITCH));									// HK67
		case 68 : return  abs(DegreesFromOffset(PITCH));									// HK68

		case 56 : return  0;                                                                // HK47 (significant motion only in y)

	  //case    : return  DegreesFromOffset(data[ACCEL2_X], data[ACCEL2_Z], 'x', 'z', leg); // HK16 FIXME not in the database!
		case 28 : return  abs(DegreesFromOffset(PITCH));									// HK17
		case 29 : return  abs(DegreesFromOffset(PITCH));									// HK18
		case 30 : return  abs(DegreesFromOffset(PITCH));									// HK19
		case 31 : return  abs(DegreesFromOffset(PITCH));									// HK20
		case 32 : return  DegreesFromOffset(ROLL);											// HK21
		case 33 : return  DegreesFromOffset(ROLL);											// HK22

		case 34 : return  abs(DegreesFromOffset(PITCH));									// HK23
		case 35 : return  abs(DegreesFromOffset(PITCH));									// HK24
		case 36 : return  abs(DegreesFromOffset(ROLL));										// HK 26
		case 37 : return  abs(DegreesFromOffset(ROLL));										// HK 27

//		case 36 : return  DegreesFromOffset(data[ACCEL2_X], data[ACCEL2_Z], 'x', 'z', leg); // HK26
		//case 36 : return leg == "left" ?                                                    // HK26
		//                  DegreesFromOffset(data[ACCEL2_X], data[ACCEL2_Z], 'x', 'z', leg) :
		//                 -DegreesFromOffset(data[ACCEL2_X], data[ACCEL2_Z], 'x', 'z', leg);
		//case 37 : return leg == "left" ?                                                    // HK27
		//                 -DegreesFromOffset(data[ACCEL2_Y], data[ACCEL2_Z], 'x', 'z', leg) :
		//                  DegreesFromOffset(data[ACCEL2_Y], data[ACCEL2_Z], 'x', 'z', leg);

		case 38 : return  abs(DegreesFromOffset(PITCH));									// HK28
		case 39 : return  abs(DegreesFromOffset(PITCH));									// HK29
		case 40 : return  abs(DegreesFromOffset(PITCH));									// HK30 (motion in x as well, but seems less)
		case 41 : return  abs(DegreesFromOffset(PITCH));									// HK31 (motion in x as well, but seems less)	
		case 53 : return  abs(DegreesFromOffset(PITCH));									// HK43
		case 54 : return  abs(DegreesFromOffset(PITCH));									// HK44
		case 55 : return  abs(DegreesFromOffset(PITCH));									// HK45	
//		case    : return  0;                                                                // HK49 (no significant motion) FIXME not in the database!

		case 58 : return  abs(DegreesFromOffset(PITCH));									// HK55
		case 59 : return  abs(DegreesFromOffset(PITCH));									// HK56
		case 60 : return  abs(DegreesFromOffset(PITCH));									// HK57
		case 61 : return  abs(DegreesFromOffset(ROLL));									// HK58
		case 62 : return  abs(DegreesFromOffset(ROLL));									// HK59
		//case 61 : return leg == "left" ?                                                    // HK58
		//                  DegreesFromOffset(data[ACCEL2_X], data[ACCEL2_Z], 'x', 'z', leg) :
		//                 -DegreesFromOffset(data[ACCEL2_X], data[ACCEL2_Z], 'x', 'z', leg);
		//case 62 : return leg == "left" ?                                                    // HK59 (data seem very noisy)
		//                 -DegreesFromOffset(data[ACCEL2_X], data[ACCEL2_Z], 'x', 'z', leg) :
		//                  DegreesFromOffset(data[ACCEL2_X], data[ACCEL2_Z], 'x', 'z', leg);
		case 63 : return  abs(DegreesFromOffset(PITCH));									// HK60
		
		case 69 : return  abs(DegreesFromOffset(PITCH));// HK75
		case 70 : return  abs(DegreesFromOffset(PITCH));// HK76
		case 71 : return  abs(DegreesFromOffset(PITCH));// HK77
		case 72 : return  abs(DegreesFromOffset(PITCH));// HK78
		case 73 : return  abs(DegreesFromOffset(PITCH));// HK79
		case 74 : return  abs(DegreesFromOffset(PITCH));// HK80

		// lower extremity
		case 75 : return  abs(DegreesFromOffset(PITCH));// LE4
		case 76 : return  abs(DegreesFromOffset(PITCH));// LE5
		case 77 : return  abs(DegreesFromOffset(PITCH));// LE6
		case 78 : return  0;                                                                // LE11 (significant motion only in z)
		case 79 : return  0;                                                                // LE12 (significant motion only in z)

		case 80 : return  abs(DegreesFromOffset(PITCH)); // LE32 (motion in x as well, but seems less)
		case 81 : return  abs(DegreesFromOffset(PITCH)); // LE33 (motion in x as well, but seems less)
		case 82 : return  abs(DegreesFromOffset(PITCH)); // LE34 (motion in x as well, but seems less)

		case 83 : return  abs(DegreesFromOffset(PITCH)); // LE37
		case 84 : return  abs(DegreesFromOffset(PITCH)); // LE45
		case 85 : return  abs(DegreesFromOffset(PITCH)); // LE46
		case 86 : return  abs(DegreesFromOffset(ROLL)); // LE47

		case 87 : return  abs(DegreesFromOffset(PITCH)); // LE49
		case 88 : return  abs(DegreesFromOffset(PITCH)); // LE50
		case 89 : return  abs(DegreesFromOffset(ROLL)); // LE51
		
		case 99 : return  abs(DegreesFromOffset(YAW)); // LE51

		// anything else
		default : return 0;
	}
}

/* a compare function for sorting used in
doctor LeGrand's algorithm. */
int compFunc(const void *num1, const void *num2)
{
	double n1 = *(double *) num1;
	double n2 = *(double *) num2;
	if (n1 < n2)
	{
		return -1;
	}
	if (n1 > n2)
	{
		return 1;
	}
	return  0;
}
/* Doctor LeGrand smoothed the data to help even
out the noise generated from the data collector */
void SmoothData(double *data, int numData, int radius = 1)
{
	double *smoothedData;
	int whichDatum, howFar, weight, totalWeight;
	if (radius > 0)
	{
		smoothedData = (double *) malloc(numData * sizeof(double));
		for (whichDatum = 0; whichDatum < numData; ++whichDatum)
		{
			smoothedData[whichDatum] = (radius + 1) * data[whichDatum];
			totalWeight = radius + 1;
			for (howFar = 1, weight = radius; weight > 0; ++howFar, --weight)
			{
				if (howFar <= whichDatum)
				{
					smoothedData[whichDatum] += weight * data[whichDatum - howFar];
					totalWeight += weight;
				}
				if (whichDatum + howFar < numData)
				{
					smoothedData[whichDatum] += weight * data[whichDatum + howFar];
					totalWeight += weight;
				}
			}
			smoothedData[whichDatum] /= totalWeight;
		}
		for (whichDatum = 0; whichDatum < numData; ++whichDatum)
		{
			data[whichDatum] = smoothedData[whichDatum];
		}
		free(smoothedData);
	}
}

/* Dr. LeGrand's algorithm to determine the threshold markers for
an exercise */
double GetThreshold(double * data, int d_size, double baselineClusterTightnessFactor = 1.0, double fixedBaseline = DBL_MAX, bool snapDataToBaseline = false)
{
	double baselineClusterMean, repClusterMean;
	double baselineClusterTotal, repClusterTotal;
	double averageDatum, bestThreshold, error, totalSquaredError;
	double averageTotalSquaredError, bestTotalSquaredError, medianTotalSquaredError;
	int numData = d_size, cutoffIndex, whichDatum;
	int bestCutoffIndex, medianCutoffIndex, averageCutoffIndex;

	// Sort the data array, smallest to largest.  Leave the original array alone.
	double *sortedData = (double *) malloc(numData * sizeof(double));
	memcpy(sortedData, data, numData * sizeof(double));
	qsort(sortedData, numData, sizeof(double), &compFunc);

	// Initialize the cluster totals.
	baselineClusterTotal = repClusterTotal = 0.0;
	for (whichDatum = 0; whichDatum < numData; ++whichDatum)
	{
		// If all data less than baseline can be assumed to be effectively baseline, snap them to.
		if (snapDataToBaseline && sortedData[whichDatum] < fixedBaseline)
		{
			sortedData[whichDatum] = fixedBaseline;
		}
		repClusterTotal += sortedData[whichDatum];
	}
	averageDatum = repClusterTotal / numData;

	// If baselineClusterTightnessFactor isn't positive, just return average as the threshold.
	if (baselineClusterTightnessFactor <= 0.0)
	{
		if (PRINT_DEBUG_INFO)
		{
			printf("DEBUG using average as threshold\n");
			printf("DEBUG    numData: %d\n", numData);
			printf("DEBUG    average: %.10lf\n", averageDatum);
		}
		return averageDatum;
	}

	// Try all possible baseline/rep cutoff points and find the best one, the one that minimizes the total squared error.
	// This code assumes that baseline data are LESS than rep data.
	bestTotalSquaredError = DBL_MAX;
	for (cutoffIndex = 1; cutoffIndex < numData; ++cutoffIndex)
	{
		// Baseline cluster is indices 0 through cutoffIndex - 1.
		// Rep cluster is indices cutoffIndex through numData - 1.
		baselineClusterTotal += sortedData[cutoffIndex - 1];
		repClusterTotal -= sortedData[cutoffIndex - 1];
		baselineClusterMean = (fixedBaseline < DBL_MAX) ? fixedBaseline : baselineClusterTotal / cutoffIndex;
		repClusterMean = repClusterTotal / (numData - cutoffIndex);
		totalSquaredError = 0.0;
		for (whichDatum = 0; whichDatum < numData; ++whichDatum)
		{
			error = sortedData[whichDatum] - (whichDatum < cutoffIndex ? baselineClusterMean : repClusterMean);
			totalSquaredError += (whichDatum < cutoffIndex ? baselineClusterTightnessFactor : 1.0) * error * error;
		}
		if (totalSquaredError < bestTotalSquaredError)
		{
			bestTotalSquaredError = totalSquaredError;
			bestCutoffIndex = cutoffIndex;
		}
		if (cutoffIndex == numData / 2)
		{
			medianTotalSquaredError = totalSquaredError;
			medianCutoffIndex = cutoffIndex;
		}
		if (sortedData[cutoffIndex - 1] < averageDatum)
		{
			averageTotalSquaredError = totalSquaredError;
			averageCutoffIndex = cutoffIndex;
		}
	}
	bestThreshold = (sortedData[bestCutoffIndex - 1] + sortedData[bestCutoffIndex]) / 2.0;

	if (PRINT_DEBUG_INFO)
	{
		printf("DEBUG baselineClusterTightnessFactor: %.3lf\n", baselineClusterTightnessFactor);
		printf("DEBUG    numData: %d\n", numData);
		printf("DEBUG    best threshold: %.10lf\n", bestThreshold);
		printf("DEBUG    median: %.10lf\n", (sortedData[numData / 2 - 1] + sortedData[numData / 2]) / 2.0);
		printf("DEBUG    average: %.10lf\n", averageDatum);
		printf("DEBUG    best:    baseline cluster: %.10lf through %.10lf\n", sortedData[0], sortedData[bestCutoffIndex - 1]);
		printf("DEBUG                  rep cluster: %.10lf through %.10lf\n", sortedData[bestCutoffIndex], sortedData[numData - 1]);
		printf("DEBUG        bestTotalSquaredError: %.10lf\n", bestTotalSquaredError);
		printf("DEBUG    median:  baseline cluster: %.10lf through %.10lf\n", sortedData[0], sortedData[medianCutoffIndex - 1]);
		printf("DEBUG                  rep cluster: %.10lf through %.10lf\n", sortedData[medianCutoffIndex], sortedData[numData - 1]);
		printf("DEBUG      medianTotalSquaredError: %.10lf\n", medianTotalSquaredError);
		printf("DEBUG    average: baseline cluster: %.10lf through %.10lf\n", sortedData[0], sortedData[averageCutoffIndex - 1]);
		printf("DEBUG                  rep cluster: %.10lf through %.10lf\n", sortedData[averageCutoffIndex], sortedData[numData - 1]);
		printf("DEBUG     averageTotalSquaredError: %.10lf\n", averageTotalSquaredError);
	}
	free(sortedData);

	// Return the best threshold found.
	return bestThreshold;
}

/*
This function actually does the calculations for the range of motion
exercises.  It implements Dr. LeGrand's smoothing algorithm, his
GetThreshold algorithm and then determines the averages of each rep.
remember to free the returned structure*/
double * RangeOfMotionCalculations(double ** arr, int num_elements, string leg, int exCode)
{

	//declare and initialize variables
	const int num_degrees = num_elements - DATA_START;
	double minRange = DBL_MAX;
	double maxRange = 0;
	double avgRange = 0;
	double rep_min = 60, rep_max = 0, rep_avg = 0;
	bool repStarted = false;
	int reps = 0;
	double degrees[num_degrees];
	double deg = 0;
	double rep_length = 0;
	double reppiness;
	double totalReppinessThisRep = 0.0;
	const int minTotalReppiness = RPS / 2;
	double avgAngleThisRep = 0.0;
	double repStartThreshold, repFullCreditThreshold, repPartialCreditThreshold, repEndThreshold;
	for(int i = DATA_START, j=0; i < num_elements; i++,j++)
	{
		deg = CalculateDegrees(arr[i], exCode, leg);

		degrees[j] = deg;
	}
	
	ofstream myfile;
	ostringstream os;
	os.clear();
	os.str("");
	os << exCode << "-" << num_elements << "-" << leg << ".csv";
	//cout << "FILE NAME " << os.str() << endl; //debugging
	string filestring = os.str();
	myfile.open(filestring.c_str());
	
	int numcols = 10;
	string outfile[num_degrees+1][numcols];
	
	outfile[0][0] = "AccelX";
	outfile[0][1] = "AccelY";
	outfile[0][2] = "AccelZ";
	outfile[0][3] = "DegRough";
	outfile[0][4] = "Rep";
	outfile[0][5] = "DegSmooth";
	
	for (int i = 1; i < num_degrees; i++ ) // put accelx, accely, and accelz in generated file
	{
		os.clear();
		os.str("");
		os << arr[i+10][5];
		outfile[i][0] =  os.str();
		
		os.clear();
		os.str("");
		os << arr[i+10][6];
		outfile[i][1] = os.str();
		
		os.clear();
		os.str("");
		os << arr[i+10][7];
		outfile[i][2] = os.str();
		
		os.clear();
		os.str("");
		os << degrees[i];
		outfile[i][3] = os.str();
		
	}
	


	// RHL step 1 to increase robustness:
	// Smooth out the data in the degrees array before beginning analysis.
	// smoothingRadius can be adjusted to fine-tune rep detection.
//	const int smoothingRadius = 0;
	const int smoothingRadius = minTotalReppiness / 2;
	if (PRINT_DEBUG_INFO)
	{
		printf("DEBUG smoothing radius: %d\n", smoothingRadius);
	}
	SmoothData(degrees, num_degrees, smoothingRadius);
	
	for (int i = 0; i < num_degrees; i++)
	{
	os.clear();
		os.str("");
		os << degrees[i];
		outfile[i+1][5] = os.str();
	}

	// RHL step 2 to increase robustness:
	// Use a clustering approach to determine
	//  - thresholds for starting and ending a rep.
	//  - thresholds for determining how much time credit to give a potential rep.
	// The third parameter in each call to GetThreshold() can be adjusted to fine-tune rep detection.
	repStartThreshold         = GetThreshold(degrees, num_degrees,  0.5);   // relatively high (close to rep)
	repFullCreditThreshold    = GetThreshold(degrees, num_degrees,  0.025); // threshold for full time credit for rep qualification
	repPartialCreditThreshold = GetThreshold(degrees, num_degrees,  2.0);   // threshold for any time credit at all
	repEndThreshold           = GetThreshold(degrees, num_degrees, 10.0);   // relatively low (close to baseline)
//	repStartThreshold = repFullCreditThreshold = repPartialCreditThreshold = repEndThreshold = GetThreshold(degrees, num_degrees, 0.0); // just gives average for comparison purposes

	for(int i = 0; i < num_degrees; i++)
	{
	
		os.clear();
		os.str("");
		os << (repStarted ? 100 : 0);
		outfile[i+1][4] = os.str();
	
		if(degrees[i] > (repStarted ? repEndThreshold : repStartThreshold))
		{
			if(!repStarted)
			{
				repStarted = true;
				reps++;
				if (PRINT_DEBUG_INFO)
				{
					printf("DEBUG starting rep at %d\nDEBUG ", i);
				}
			}

			rep_length++;

			// How much does this angle deserve to be counted in a rep?  Is it fully reppy, sorta reppy or not reppy at all?
			reppiness = degrees[i] > repFullCreditThreshold ? 1.0 : degrees[i] > repPartialCreditThreshold ? 0.5 : 0.0;
			// For rep-detection purposes, only give full credit above repFullCreditThreshold; give no credit below repPartialCreditThreshold.
			totalReppinessThisRep += reppiness;
			// Use reppiness as this angle's weight when calculating the average angle of this rep.
			avgAngleThisRep += reppiness * degrees[i];

			if (PRINT_DEBUG_INFO)
			{
				printf(reppiness >= 1.0 ? "#" : reppiness > 0.0 ? "+" : ".");
			}
		}else
		{
			if(repStarted)
			{
				if(totalReppinessThisRep > minTotalReppiness)
				{
					// Use average angle of rep just ended.
					avgAngleThisRep /= totalReppinessThisRep;
					if (avgAngleThisRep > maxRange)
					{
						maxRange = avgAngleThisRep;
					}
					if (avgAngleThisRep < minRange)
					{
						minRange = avgAngleThisRep;
					}
					avgRange += avgAngleThisRep;

					//divide rep_length by the number of data points per second
					rep_length /= RPS;

					if(rep_length > rep_max)
						rep_max = rep_length;
					if(rep_length < rep_min)
						rep_min = rep_length;
					rep_avg += rep_length;

					if (PRINT_DEBUG_INFO)
					{
						printf("\nDEBUG   ending rep at %d   *\n", i);
					}
				}else
				{
					reps--;
					if (PRINT_DEBUG_INFO)
					{
						printf("\nDEBUG    giving up at %d\n", i);
					}
				}
				repStarted = false;
				avgAngleThisRep = 0.0;
				rep_length = 0;
				totalReppinessThisRep = 0.0;
			}
		}
	}

	if(repStarted)
	{
		if(totalReppinessThisRep > minTotalReppiness)
		{
			// Use average angle of rep just ended.
			avgAngleThisRep /= totalReppinessThisRep;
			if (avgAngleThisRep > maxRange)
			{
				maxRange = avgAngleThisRep;
			}
			if (avgAngleThisRep < minRange)
			{
				minRange = avgAngleThisRep;
			}
			avgRange += avgAngleThisRep;

			//divide rep_length by the number of data points per second
			rep_length /= RPS;

			if(rep_length > rep_max)
				rep_max = rep_length;
			if(rep_length < rep_min)
				rep_min = rep_length;
			rep_avg += rep_length;

			if (PRINT_DEBUG_INFO)
			{
				printf("\nDEBUG   ending rep at %d   *\n", num_degrees);
			}
		}else
		{
			reps--;
			if (PRINT_DEBUG_INFO)
			{
				printf("\nDEBUG    giving up at %d\n", num_degrees);
			}
		}
		repStarted = false;
		avgAngleThisRep = 0.0;
		rep_length = 0;
		totalReppinessThisRep = 0.0;
	}

	if (reps > 0)
	{
		avgRange /= reps;
		rep_avg /= reps;
	}
	else
	{
		minRange = maxRange = avgRange = 0.0;
		rep_min = rep_max = rep_avg = 0.0;
	}

	double *ret = (double *) malloc(sizeof(double) * 8);

	ret[0] = minRange;
	ret[1] = maxRange;
	ret[2] = avgRange;
	ret[3] = rep_min;
	ret[4] = rep_max;
	ret[5] = rep_avg;
	ret[6] = reps;
	ret[7] = num_degrees;
	
	
	for (int i = 0; i < num_degrees; i++)
	{
		for (int j = 0; j < numcols; j++)
		{
			myfile << outfile[i][j] << ",";
		}
		myfile << "0" << endl;
	}
	myfile.close();

	return ret;
}



int main(int argc, char *argv[]) 
{
	
	if (argc != 4)
	{
		cout << "usage: ./wrapper leftFileName rightFileName exercise_id" << endl;
		return 0;
	}
	
	char * leftFile = argv[1]; 
	char * rightFile = argv[2];
	int exercise_id = atoi(argv[3]);
	
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
	
	//cout << "num_elements: " << num_elements << endl;
	
	double * rom_calcs_left = RangeOfMotionCalculations(lcsv, num_elements, "left", exercise_id);
	double * rom_calcs_right = RangeOfMotionCalculations(rcsv, num_elements, "right", exercise_id);

	cout << rom_calcs_left[0] << endl; // minRange;
	cout << rom_calcs_left[1] << endl; // maxRange;
	cout << rom_calcs_left[2] << endl; // avgRange;
	cout << rom_calcs_left[3] << endl; // rep_min;
	cout << rom_calcs_left[4] << endl; // rep_max;
	cout << rom_calcs_left[5] << endl; // rep_avg;
	cout << rom_calcs_left[6] << endl; // reps;
	cout << rom_calcs_left[7] << endl; // num_degrees;
	
	cout << rom_calcs_right[0] << endl; // minRange;
	cout << rom_calcs_right[1] << endl; // maxRange;
	cout << rom_calcs_right[2] << endl; // avgRange;
	cout << rom_calcs_right[3] << endl; // rep_min;
	cout << rom_calcs_right[4] << endl; // rep_max;
	cout << rom_calcs_right[5] << endl; // rep_avg;
	cout << rom_calcs_right[6] << endl; // reps;
	cout << rom_calcs_right[7] << endl; // num_degrees;
	
	//get the force from each sensor
	double * sensors = ForcePerSensor(lcsv, rcsv, num_elements);
	
	//printf("Finished range of motion calculations\n");
	//printf("Range Left  - Avg: %0.2f Min: %0.2f Max: %0.2f\n",rom_calcs_left[2], rom_calcs_left[0], rom_calcs_left[1]);
	//printf("Range Right - Avg: %0.2f Min: %0.2f Max: %0.2f\n",rom_calcs_right[2], rom_calcs_right[0], rom_calcs_right[1]);
	//printf("Force Left  - LF1: %0.2f LF2: %0.2f LF3: %0.2f LF4: %0.2f\n",sensors[0],sensors[1], sensors[2], sensors[3]);
	//printf("Force Right - RF1: %0.2f RF2: %0.2f RF3: %0.2f RF4: %0.2f\n",sensors[4],sensors[5], sensors[6], sensors[7]);

	//cout << sensors[0] << endl; // LF1;
	//cout << sensors[1] << endl; // LF2;
	//cout << sensors[2] << endl; // LF3;
	//cout << sensors[3] << endl; // LF4;
	//cout << sensors[4] << endl; // RF1;
	//cout << sensors[5] << endl; // RF2;
	//cout << sensors[6] << endl; // RF3;
	//cout << sensors[7] << endl; // RF4;	
	
	free(rom_calcs_left);
	free(rom_calcs_right);
	free(sensors);
	
	return 0;
}
