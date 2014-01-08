///////////////////////////////////////////
// dist.c 
// 
// TMAC - The University of Texas at Arlington
// 
// Version 131204
//
// Delivered to MedHab, LLC
//
// Walking/Running gait analysis -- computes stride time/distance from accel/gyro signals 
//
// Original algorithm coded in MATLAB by Raul Fernandez
// C port written by Juan Paramo
//
///////////////////////////////////////////

// included libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// constants 

// -------------------------------------------------------------------------------
const int FILE_TYPE = 0; // exercise type (0 -> WALKING, 1-> RUNNING)
const int SAMPLE_FREQ = 50; // raw data sampling frequency in Hz (50 Hz -> WALKING, 100 Hz -> RUNNING)
// -------------------------------------------------------------------------------

const int STANDSTILL_SEC = 2; // sec's required standing still prior to motion 
const double G = 9.80665; // international standard for gravity constant
const double PI = 3.14159; // standard for PI
const int HEADER_LINES = 3; // number of header lines in sensor data file 

const char *INIT_FILENAME_EXT = ".ini"; // initialization fixed to .ini
const char *INPUT_FILENAME_EXT = ".csv"; // input fixed to .csv
const char *OUTPUT_FILENAME_EXT = ".out"; // output fixed to .out

const int FILTERAPPLY = 0; // // apply filter selection (0-> bypass filter, 1-> apply filter) 
const char *FILEIDL = "-lf"; // left foot file id
const char *FILEIDR = "-rf"; // right foot file id 
const int OUTPUTTYPE = 0; // step time output type (0 -> ACCEL BASED, 1-> FORCE BASED)
const int OPTIMIZATION = 0; // optimization based on final velocity (0 -> none 1 -> gyro offset 2 -> stride offset)
const int OUTPUTADD = 0; // walking stride information (0 -> none, 1 -> walking) 

// structures
struct data // input data structure defined 
{
	int dTime; // time (ms) - member 0
	double dGyroX; // gyroscope y  - member 1
	double dAccelX; // accel x - member 2
	double dAccelY; // accel y - member 3
	double dAccelZ; // accel z - member 4
	double dAccelT;	// total acceleration - member 5
	int nFs1; // force sensor 1 - member 6
	int nFs2; // force sensor 2 - member 7
	int nFs3; // force sensor 3 - member 8
	int nFs4; // force sensor 4  - member 9
	int nFsf; // force sensor front sum (nFs1 + nFs2) - member 10
	int nFsr; // force sensor rear sum (nFs3 + nFs4) - member 11
	int nFst; // force sensor total sum - member 12
}; 

struct stride // stride structure defined 
{
	int nStride; // stride number 
	int nStart; // data index of start of a stride
	int nPeak; // data index of accel total peak of a stride
	int nStop; // data index of stop of a stride
	
	double dStrideTimeSwing; // stride time midstance in sec
	double dStrideTime; // stride time stride in sec
	double dStride; // stride distance in inches
	double dStrideMaxForceBall; // max force value of the stride on the ball of the foot
	double dStrideMaxForceHeel; // max force value of the stride on the heel of the foot
	double dStrideMaxForce; // max total force value of the stride 
};

struct strideForce
{
	int nStride; // stride number
	int nGroundContact; // data index for ground contact of a stride
};

// function prototypes
// -------------------------------------------------------------------------------
int bgets(char * o_buffer, int size, char ** i_buffer); // buffer streaming function 
void DistRead(char * strRunID, char * strFileName, char * strInputBuffer, struct data ** idata, int * nDataLineRead); // read raw sensor data and dynamically allocate and assign to sensor data structure (data converted to engineering units)
void DistInit(struct data ** idata, int nDataLineRead, double * dAccelTQuiescentOffset, double * dGyroXQuiescentOffset, double * dFstMaximum, double * dFstMinimum, double * dFstQuiescent); // calculate standstill offsets and force thresholds
void DistOutInit(char * strInitFileName, double dAccelTQuiescentOffsetL, double dGyroYQuiescentOffsetL, double dFstMaximumL, double dFstMinimumL, double dFstQuiescentL, double dAccelTQuiescentOffsetR, double dGyroYQuiescentOffsetR, double dFstMaximumR, double dFstMinimumR, double dFstQuiescentR); // initialization output for exercise
void DistGet(char * strInputBuffer, double * dAccelTQuiescentOffsetL, double * dGyroXQuiescentOffsetL, double * dFstMaximumL, double * dFstMinimumL, double * dFstQuiescentL, double * dAccelTQuiescentOffsetR, double * dGyroXQuiescentOffsetR, double * dFstMaximumR, double * dFstMinimumR, double * dFstQuiescentR); // get quiescent offsets and force thresholds
void DistProc(struct data ** idata, int nDataLineRead, double dGyroXQuiescentOffset); // apply gyro offset and filter sensor data
void DistDisc(struct data ** idata, struct stride ** istride, struct strideForce ** istrideForce, int nDataLineRead, double dAccelTQuiescentOffset, double dFstMaximum, double dFstMinimum, double dFstQuiescent, int * nStrideCount, int * nStrideForcePeaks); // discretize raw data into individual strides
void DistAvg(double dArray[], int nMax, double * dMedian, double * dIQRMean); // median and interquartile mean calculation 
void DistAlgo(struct stride ** istride, struct data ** idata, int nStride, double dSamplePeriod); // distance algorithm for a particular Stride within a data set
void DistOutAvg(char * strOutputFileName, double dIQRAvgStrideTimeL, double dIQRAvgStrideSwingTimeL, double dIQRAvgStrideDistanceL, double dIQRAvgStrideForceL, double dFstMaximumL, int nDataLineReadL, double dIQRAvgStrideTimeR, double dIQRAvgStrideSwingTimeR, double dIQRAvgStrideDistanceR, double dIQRAvgStrideForceR, double dFstMaximumR, int nDataLineReadR, double dIQRAvgStepTimeLR, double dIQRAvgStepTimeRL); // statistical output for exercise
void DistOut(char * strOutputFileName, struct stride ** istride, int nStrideCount, double dIQRAvgStrideDistance, double dIQRAvgStrideTime); // distance output for each stride
// -------------------------------------------------------------------------------
void AccelTMagnitude(struct data ** idata, int nMax); // calculate and assign total acceleration magnitude 
double dStandStillOffset(struct data ** idata, int nMax, int nPrm); // return standstill offset average of data structure member collection 
void OffsetApply(struct data ** idata, int nMax, double dOffset, int nPrm); // apply offset to corresponding data structure member collection
void FilterApply(struct data ** idata, int nMax, int nPrm); // build filtered array
// -------------------------------------------------------------------------------
void AccelTAbsoluteValue(struct data ** idata, int nMax); // convert to absolute value total acceleration collection 
int nCompareFunction(const void *a,const void *b); // compare functions for quick sort 
int dCompareFunction(const void *a,const void *b);
// -------------------------------------------------------------------------------
void FillArray(struct data ** idata, double * dArray, int nStart, int nMax, int nPrm); // fill array with corresponding data
double dMean (double dArray[], int nMax); // return mean of array
double dTrapz(double dArray[], int nIndex); // return incremental trapezoidal area
// -------------------------------------------------------------------------------

// data file pointer
FILE * fid;

// init file pointer
FILE * fnd;

// output file pointer
FILE * fod;

///////////////////////////////////////////
// main function - receives output text file name from command line
///////////////////////////////////////////
int main(int argc, char *argv[]) 
{
	int nIndexI = 0; // general indeces
	int nIndexJ = 0;
	struct data * idataL; // structure instances declaration
	struct data * idataR;
	struct stride * istrideL;
	struct stride * istrideR;
	struct strideForce * istrideForceL;
	struct strideForce * istrideForceR;

	char *strFileName = ""; // file name specified by user
	int nFileNameSize = 0;  // extension size variable for file name
	char *strInitFileName = ""; // standstill data file
	int nInitFileNameSizeExt = 0; // extension size variable for ini file .ini
	char *strInputFileName = ""; // raw data source for exercise with multiple strides 
	char *strInputFileNameExt = ""; // input file extension 
	int nInputFileIDSizeExt = 0; // extension size variables for input file FILEID: "lf" or "rf"
	int nInputFileRunIDSizeExt = 0; // RUNID: "0,1,2,..."
	int nInputFileNameSizeExt = 0; // ".csv"
	char *strOutputFileName = ""; // output file name for statistical results
	int nOutputFileNameSizeExt = 0; // extension size variable for output file .out
	
	double dSamplePeriod = 0; // sample period in sec 
	
	long lInputFileLength = 0; // data file length
	char *strInputFileBuffer; // data file stream buffer
	char *strRunID = ""; // run ID ("0" --> standstill data or !0" --> exercise data)

	int nIndexEpoch = 0; // index for epoch synch

	// LEFT
	int nDataLineReadL = 0; // number of data lines read in each iteration 
	int nStartEpochL = 0; // epoch start time 
	double dAccelTQuiescentOffsetL = 0; // total acceleration quiescent offset 
	double dGyroXQuiescentOffsetL = 0; // gyro x quiescent offset
	double dFstMaximumL = 0; // total force standstill threshold 
	double dFstMinimumL = 0; // total force minimum threshold
	double dFstQuiescentL = 0; // total force quiescent threshold 
	int nStrideCountL = 0; // number of strides found 
	int nStrideForcePeaksL = 0; // number of strides force peaks 
	
	double *dArrayStrideTimeL; // result array containing stride time values
	double dStrideTimeMedianL = 0; // stride time median 
	double dIQRAvgStrideTimeL = 0;  // average interquartile stride time

	double *dArrayStrideSwingTimeL; // result array containing stride swing time values
	double dStrideSwingTimeMedianL = 0; // stride swing time median 
	double dIQRAvgStrideSwingTimeL = 0;  // average interquartile stride swing time

	double *dArrayStrideDistanceL;
	double dStrideDistanceMedianL = 0; // stride distance median 
	double dIQRAvgStrideDistanceL = 0;  // average interquartile stride distance

	double *dArrayStrideForceL;
	double dStrideForceMedianL = 0; // stride force median 
	double dIQRAvgStrideForceL = 0;  // average interquartile stride force

	// RIGHT
	int nDataLineReadR = 0; // number of data lines read in each iteration 
	int nStartEpochR = 0; // epoch start time 
	double dAccelTQuiescentOffsetR = 0; // total acceleration quiescent offset 
	double dGyroXQuiescentOffsetR = 0; // gyro x quiescent offset
	double dFstMaximumR = 0; // total force standstill threshold 
	double dFstMinimumR = 0; // total force minimum threshold
	double dFstQuiescentR = 0; // total force quiescent threshold 
	int nStrideCountR = 0; // number of strides found 
	int nStrideForcePeaksR = 0; // number of strides force peaks

	double *dArrayStrideTimeR; // result array containing stride time values
	double dStrideTimeMedianR = 0; // stride time median 
	double dIQRAvgStrideTimeR = 0;  // average interquartile stride time

	double *dArrayStrideSwingTimeR; // result array containing stride swing time values
	double dStrideSwingTimeMedianR = 0; // stride swing time median 
	double dIQRAvgStrideSwingTimeR = 0;  // average interquartile stride swing time

	double *dArrayStrideDistanceR;
	double dStrideDistanceMedianR = 0; // stride distance median 
	double dIQRAvgStrideDistanceR = 0;  // average interquartile stride distance

	double *dArrayStrideForceR;
	double dStrideForceMedianR = 0; // stride force median 
	double dIQRAvgStrideForceR = 0;  // average interquartile stride force

	// LR
	double *dArrayTimeLR; // step time differences between left to right 
	double *dArrayTimeRL; // step time differences between right to left 
	int nTimeIndex = 0; // general index for step time differences
	double dAvgStepTimeLR = 0;  // average step time differences LR & RL 
	double dAvgStepTimeRL = 0;
	
	double *dArrayTimeLRSorted; // sorted step time differences between left to right 
	double *dArrayTimeRLSorted; // sorted step time differences between right to left 
	double dTimeLRMedian = 0; // LR step time difference median 
	double dTimeRLMedian = 0; // LR step time difference median 
	double dIQRAvgStepTimeLR = 0;  // average interquartile step time differences LR & RL 
	double dIQRAvgStepTimeRL = 0;
		
	// check if file name and runID were not specified 
	if (argc <= 2)
	{
		// end application 
		return 0;
	}

	// calculate sample period
	dSamplePeriod = 1/(double)SAMPLE_FREQ;

	// get file name from command line 
	strFileName = argv[1];
	
	// get file name size 
	nFileNameSize = strlen(strFileName);

	// get run ID from command line to differentiate standstill or exercise data processing ("0" --> standstill data or "#" --> exercise data)
	strRunID = argv[2];
	
	// check if it is standstill data
	if (*strRunID == '0') 
	{
		goto standstill;
	}
	// check if it is exercise data
	else 
	{
		goto exercise;
	}	

standstill:
	
	// LEFT
	// get input file ID extension size 
	nInputFileIDSizeExt =  strlen(FILEIDL);

	// get input run ID extension size
	nInputFileRunIDSizeExt = strlen(strRunID);

	// get input file extension size
	nInputFileNameSizeExt = strlen(INPUT_FILENAME_EXT);

	// allocate memory input file name extension string, example: "-lf" + "0" + ".csv"
	strInputFileNameExt = (char *) calloc((nInputFileIDSizeExt + nInputFileRunIDSizeExt + nInputFileNameSizeExt), sizeof(char));
	
	// build input file extension
	strcpy(strInputFileNameExt, FILEIDL);
	strInputFileNameExt = strncat(strInputFileNameExt, strRunID, nInputFileRunIDSizeExt);
	strInputFileNameExt = strncat(strInputFileNameExt, INPUT_FILENAME_EXT, nInputFileNameSizeExt);

	// get total input file extension size
	nInputFileNameSizeExt = strlen(strInputFileNameExt);

	// allocate memory input file name string
	strInputFileName = (char *) calloc((nFileNameSize + nInputFileNameSizeExt), sizeof(char));

	// build input file name
	strcpy(strInputFileName, strFileName);
	strInputFileName = strncat(strInputFileName, strInputFileNameExt, nInputFileNameSizeExt);

	//open the file and put the data into a buffer
	fid = fopen(strInputFileName,"r");

	// check if data file exists
	if (fid == NULL)
	{
		return 0; // file not found, terminate app
	}

	fseek(fid,0,SEEK_END);
	lInputFileLength = ftell(fid);
	rewind(fid);
	strInputFileBuffer = (char *)malloc(lInputFileLength);
	fread(strInputFileBuffer, 1, lInputFileLength, fid);
	fclose(fid);

	// read raw data and convert it to engineering units
	DistRead(strRunID, strInputFileName, strInputFileBuffer, &idataL, &nDataLineReadL);

	// get offsets and force thresholds
	DistInit(&idataL, nDataLineReadL, &dAccelTQuiescentOffsetL, &dGyroXQuiescentOffsetL, &dFstMaximumL, &dFstMinimumL, &dFstQuiescentL);

	// RIGHT 
	// get input file ID extension size 
	nInputFileIDSizeExt =  strlen(FILEIDR);

	// get input run ID extension size
	nInputFileRunIDSizeExt = strlen(strRunID);

	// get input file extension size
	nInputFileNameSizeExt = strlen(INPUT_FILENAME_EXT);

	// allocate memory input file name extension string, example: "-rf" + "0" + ".csv"
	strInputFileNameExt = (char *) calloc((nInputFileIDSizeExt + nInputFileRunIDSizeExt + nInputFileNameSizeExt), sizeof(char));
	
	// build input file extension
	strcpy(strInputFileNameExt, FILEIDR);
	strInputFileNameExt = strncat(strInputFileNameExt, strRunID, nInputFileRunIDSizeExt);
	strInputFileNameExt = strncat(strInputFileNameExt, INPUT_FILENAME_EXT, nInputFileNameSizeExt);

	// get total input file extension size
	nInputFileNameSizeExt = strlen(strInputFileNameExt);

	// allocate memory input file name string
	strInputFileName = (char *) calloc((nFileNameSize + nInputFileNameSizeExt), sizeof(char));

	// build input file name
	strcpy(strInputFileName, strFileName);
	strInputFileName = strncat(strInputFileName, strInputFileNameExt, nInputFileNameSizeExt);

	//open the file and put the data into a buffer
	fid = fopen(strInputFileName,"r");

	// check if data file exists
	if (fid == NULL)
	{
		return 0; // file not found, terminate app
	}

	fseek(fid,0,SEEK_END);
	lInputFileLength = ftell(fid);
	rewind(fid);
	strInputFileBuffer = (char *)malloc(lInputFileLength);
	fread(strInputFileBuffer, 1, lInputFileLength, fid);
	fclose(fid);

	// read raw data and convert it to engineering units
	DistRead(strRunID, strInputFileName, strInputFileBuffer, &idataR, &nDataLineReadR);

	// get offsets and force thresholds
	DistInit(&idataR, nDataLineReadR, &dAccelTQuiescentOffsetR, &dGyroXQuiescentOffsetR, &dFstMaximumR, &dFstMinimumR, &dFstQuiescentR);

	// check if standstill total acceleration is within boundaries
	if (dAccelTQuiescentOffsetL != 9999)
	{
		// get init file extension size
		nInitFileNameSizeExt = strlen(INIT_FILENAME_EXT);

		// allocate memory init file name string
		strInitFileName = (char *) calloc((nFileNameSize + nInitFileNameSizeExt), sizeof(char));

		// build init file name (throw away last character)
		strncpy(strInitFileName, strFileName, nFileNameSize);
		
		// build init file name
		strInitFileName = strncat(strInitFileName, INIT_FILENAME_EXT, nInitFileNameSizeExt);

		// output initialization parameters for exercise
		DistOutInit(strInitFileName, dAccelTQuiescentOffsetL, dGyroXQuiescentOffsetL, dFstMaximumL, dFstMinimumL, dFstQuiescentL, dAccelTQuiescentOffsetR, dGyroXQuiescentOffsetR, dFstMaximumR, dFstMinimumR, dFstQuiescentR);
	}
	
	goto done;

exercise:

	// get init file extension size
	nInitFileNameSizeExt = strlen(INIT_FILENAME_EXT);

	// allocate memory init file name string
	strInitFileName = (char *) calloc((nFileNameSize + nInitFileNameSizeExt), sizeof(char));

	// build init file name (throw away last character)
	strncpy(strInitFileName, strFileName, nFileNameSize);

	// build init file name
	strInitFileName = strncat(strInitFileName, INIT_FILENAME_EXT, nInitFileNameSizeExt);

	// open init file 
	fnd = fopen(strInitFileName,"r");

	// check if init file exists
	if (fnd == NULL)
	{
		return 0; // file not found, terminate app
	}

	//put the data into a buffer
	fseek(fnd,0,SEEK_END);
	lInputFileLength = ftell(fnd);
	rewind(fnd);
	strInputFileBuffer = (char *)malloc(lInputFileLength);
	fread(strInputFileBuffer, 1, lInputFileLength, fnd);
	fclose(fnd);

	// get quiescent offsets and force thresholds
	DistGet(strInputFileBuffer, &dAccelTQuiescentOffsetL, &dGyroXQuiescentOffsetL, &dFstMaximumL, &dFstMinimumL, &dFstQuiescentL, &dAccelTQuiescentOffsetR, &dGyroXQuiescentOffsetR, &dFstMaximumR, &dFstMinimumR, &dFstQuiescentR);

	// LEFT
	// get input file ID extension size 
	nInputFileIDSizeExt =  strlen(FILEIDL);

	// get input run ID extension size
	nInputFileRunIDSizeExt = strlen(strRunID);

	// get input file extension size
	nInputFileNameSizeExt = strlen(INPUT_FILENAME_EXT);

	// allocate memory input file name extension string, example: "-lf" + "1" + ".csv"
	strInputFileNameExt = (char *) calloc((nInputFileIDSizeExt + nInputFileRunIDSizeExt + nInputFileNameSizeExt), sizeof(char));
	
	// build input file extension
	strcpy(strInputFileNameExt, FILEIDL);
	strInputFileNameExt = strncat(strInputFileNameExt, strRunID, nInputFileRunIDSizeExt);
	strInputFileNameExt = strncat(strInputFileNameExt, INPUT_FILENAME_EXT, nInputFileNameSizeExt);

	// get total input file extension size
	nInputFileNameSizeExt = strlen(strInputFileNameExt);

	// allocate memory input file name string
	strInputFileName = (char *) calloc((nFileNameSize + nInputFileNameSizeExt), sizeof(char));

	// build input file name
	strcpy(strInputFileName, strFileName);
	strInputFileName = strncat(strInputFileName, strInputFileNameExt, nInputFileNameSizeExt);

	//open the file and put the data into a buffer
	fid = fopen(strInputFileName,"r");

	// check if data file exists
	if (fid == NULL)
	{
		return 0; // file not found, terminate app
	}

	fseek(fid,0,SEEK_END);
	lInputFileLength = ftell(fid);
	rewind(fid);
	strInputFileBuffer = (char *)malloc(lInputFileLength);
	fread(strInputFileBuffer, 1, lInputFileLength, fid);
	fclose(fid);
	
	// read raw data and convert it to engineering units
	DistRead(strRunID, strInputFileName, strInputFileBuffer, &idataL, &nDataLineReadL);

	// apply gyro x offset and filter data
	DistProc(&idataL, nDataLineReadL, dGyroXQuiescentOffsetL);
	
	// RIGHT 
	// get input file ID extension size 
	nInputFileIDSizeExt =  strlen(FILEIDR);

	// get input run ID extension size
	nInputFileRunIDSizeExt = strlen(strRunID);

	// get input file extension size
	nInputFileNameSizeExt = strlen(INPUT_FILENAME_EXT);

	// allocate memory input file name extension string, example: "-rf" + "1" + ".csv"
	strInputFileNameExt = (char *) calloc((nInputFileIDSizeExt + nInputFileRunIDSizeExt + nInputFileNameSizeExt), sizeof(char));
	
	// build input file extension
	strcpy(strInputFileNameExt, FILEIDR);
	strInputFileNameExt = strncat(strInputFileNameExt, strRunID, nInputFileRunIDSizeExt);
	strInputFileNameExt = strncat(strInputFileNameExt, INPUT_FILENAME_EXT, nInputFileNameSizeExt);

	// get total input file extension size
	nInputFileNameSizeExt = strlen(strInputFileNameExt);

	// allocate memory input file name string
	strInputFileName = (char *) calloc((nFileNameSize + nInputFileNameSizeExt), sizeof(char));

	// build input file name
	strcpy(strInputFileName, strFileName);
	strInputFileName = strncat(strInputFileName, strInputFileNameExt, nInputFileNameSizeExt);

	//open the file and put the data into a buffer
	fid = fopen(strInputFileName,"r");

	// check if data file exists
	if (fid == NULL)
	{
		return 0; // file not found, terminate app
	}

	fseek(fid,0,SEEK_END);
	lInputFileLength = ftell(fid);
	rewind(fid);
	strInputFileBuffer = (char *)malloc(lInputFileLength);
	fread(strInputFileBuffer, 1, lInputFileLength, fid);
	fclose(fid);

	// read raw data and convert it to engineering units
	DistRead(strRunID, strInputFileName, strInputFileBuffer, &idataR, &nDataLineReadR);

	// apply gyro x offset and filter data
	DistProc(&idataR, nDataLineReadR, dGyroXQuiescentOffsetR);

	// get starting epoch for both feet 
	nStartEpochL = (idataL)[0].dTime;
	nStartEpochR = (idataR)[0].dTime;

	// calculate epoch difference between feet and reassign data structure accordingly
	if (nStartEpochL > nStartEpochR)
	{
		// get epoch time index 
		while ((idataR)[nIndexJ].dTime != nStartEpochL)
		{
			nIndexJ = nIndexJ + 1;
		}

		// save epoch index
		nIndexEpoch = nIndexJ;

		// reset index
		nIndexJ = 0;

		// redefine structure based on epoch time index
		for (nIndexI = nIndexEpoch; nIndexI < nDataLineReadR; nIndexI++)
		{
			// reassign values to structure 
			(idataR)[nIndexJ].dTime = (idataR)[nIndexI].dTime;
			(idataR)[nIndexJ].dGyroX = (idataR)[nIndexI].dGyroX;
			(idataR)[nIndexJ].dAccelX = (idataR)[nIndexI].dAccelX;
			(idataR)[nIndexJ].dAccelY = (idataR)[nIndexI].dAccelY;
			(idataR)[nIndexJ].dAccelZ = (idataR)[nIndexI].dAccelZ;
			(idataR)[nIndexJ].dAccelT = (idataR)[nIndexI].dAccelT;
			(idataR)[nIndexJ].nFs1 = (idataR)[nIndexI].nFs1; 
			(idataR)[nIndexJ].nFs2 = (idataR)[nIndexI].nFs2; 
			(idataR)[nIndexJ].nFs3 = (idataR)[nIndexI].nFs3; 
			(idataR)[nIndexJ].nFs4 = (idataR)[nIndexI].nFs4; 
			(idataR)[nIndexJ].nFsf = (idataR)[nIndexI].nFsf; 
			(idataR)[nIndexJ].nFsr = (idataR)[nIndexI].nFsr; 
			(idataR)[nIndexJ].nFst = (idataR)[nIndexI].nFst; 

			// update indeces for next iteration 
			nIndexJ = nIndexJ + 1;
		}
	
		// update number of data lines read
		nDataLineReadR = nDataLineReadR - nIndexEpoch;

		// update structure reallocating for discarded data
		(idataR) = (struct data *)realloc((idataR), (nDataLineReadR) *sizeof(struct data));
	}
	else 
	{
		if (nStartEpochR > nStartEpochL)
		{
			// get epoch time index 
			while ((idataL)[nIndexJ].dTime != nStartEpochR)
			{
				nIndexJ = nIndexJ + 1;
			}

			// save epoch index
			nIndexEpoch = nIndexJ;
	
			// reset index
			nIndexJ = 0;

			// redefine structure based on epoch time index
			for (nIndexI = nIndexEpoch; nIndexI < nDataLineReadL; nIndexI++)
			{
				// reassign values to structure 
				(idataL)[nIndexJ].dTime = (idataL)[nIndexI].dTime;
				(idataL)[nIndexJ].dGyroX = (idataL)[nIndexI].dGyroX;
				(idataL)[nIndexJ].dAccelX = (idataL)[nIndexI].dAccelX;
				(idataL)[nIndexJ].dAccelY = (idataL)[nIndexI].dAccelY;
				(idataL)[nIndexJ].dAccelZ = (idataL)[nIndexI].dAccelZ;
				(idataL)[nIndexJ].dAccelT = (idataL)[nIndexI].dAccelT;
				(idataL)[nIndexJ].nFs1 = (idataL)[nIndexI].nFs1; 
				(idataL)[nIndexJ].nFs2 = (idataL)[nIndexI].nFs2; 
				(idataL)[nIndexJ].nFs3 = (idataL)[nIndexI].nFs3; 
				(idataL)[nIndexJ].nFs4 = (idataL)[nIndexI].nFs4; 
				(idataL)[nIndexJ].nFsf = (idataL)[nIndexI].nFsf; 
				(idataL)[nIndexJ].nFsr = (idataL)[nIndexI].nFsr; 
				(idataL)[nIndexJ].nFst = (idataL)[nIndexI].nFst; 

				// update indeces for next iteration 
				nIndexJ = nIndexJ + 1;
			}
	
			// update number of data lines read
			nDataLineReadL = nDataLineReadL - nIndexEpoch;

			// update structure reallocating for discarded data
			(idataL) = (struct data *)realloc((idataL), (nDataLineReadL) *sizeof(struct data));
		}
	}
	
	// LEFT
	// discretize raw data into individual strides
	DistDisc(&idataL, &istrideL, &istrideForceL, nDataLineReadL, dAccelTQuiescentOffsetL, dFstMaximumL, dFstMinimumL, dFstQuiescentL, &nStrideCountL, &nStrideForcePeaksL);
	
	// RIGHT
	// discretize raw data into individual strides
	DistDisc(&idataR, &istrideR, &istrideForceR, nDataLineReadR, dAccelTQuiescentOffsetR, dFstMaximumR, dFstMinimumR, dFstQuiescentR, &nStrideCountR, &nStrideForcePeaksR);
	
	// if strides are found, run the algorithm against each stride and output measurements
	if ((nStrideCountL != 0) && (nStrideCountR != 0)) 
	{
		// force based output
		if ((OUTPUTTYPE == 1) && (nStrideForcePeaksL != 0) && (nStrideForcePeaksR != 0))
		{
			goto force;
		}
		// accel based output
		else 
		{
			goto accel;
		}	

accel:
		// calculate step time differences between each feet (left to right)
		for (nIndexI = 0; nIndexI < nStrideCountL; nIndexI++)
		{
			for(nIndexJ = 0; nIndexJ < nStrideCountR; nIndexJ++)
			{
				// check for next stop index from right foot
				if (istrideR[nIndexJ].nStop > istrideL[nIndexI].nStop)
				{
					// increase index 
					nTimeIndex = nTimeIndex + 1;

					// allocate memory based on time index
					if (nTimeIndex == 1)
					{
						dArrayTimeLR = (double *) calloc(nTimeIndex, sizeof(double));
					}
					else
					{
						// reallocate memory besed on new identified number of valid stride starts
						dArrayTimeLR = (double *) realloc(dArrayTimeLR, nTimeIndex*sizeof(double));
					}

					// assign time difference to array 
					dArrayTimeLR[nTimeIndex-1] = (double)(istrideR[nIndexJ].nStop - istrideL[nIndexI].nStop) * dSamplePeriod;

					// exit loop
					break;
				}
			}
		}
		
		// get step time difference mean 
		dAvgStepTimeLR = dMean(dArrayTimeLR,nTimeIndex);

		// allocate memory based on time index
		dArrayTimeLRSorted = (double *) calloc(nTimeIndex, sizeof(double));

		// copy time array for sorting purposes
		for (nIndexI = 0; nIndexI < nTimeIndex; nIndexI++)
		{
			dArrayTimeLRSorted[nIndexI] = dArrayTimeLR[nIndexI];
		}

		// quick sort of time array in ascending order 
		qsort(dArrayTimeLRSorted, nTimeIndex, sizeof(double), dCompareFunction);

		// calculate median and interquartile mean 
		DistAvg(dArrayTimeLRSorted, nTimeIndex, &dTimeLRMedian, &dIQRAvgStepTimeLR);

		// reset time difference index
		nTimeIndex = 0;

		// calculate step time differences between each feet (right to left)
		for (nIndexI = 0; nIndexI < nStrideCountR; nIndexI++)
		{
			for(nIndexJ = 0; nIndexJ < nStrideCountL; nIndexJ++)
			{
				// check for next stop index from left foot
				if (istrideL[nIndexJ].nStop > istrideR[nIndexI].nStop)
				{
					// increase index 
					nTimeIndex = nTimeIndex + 1;

					// allocate memory based on time index
					if (nTimeIndex == 1)
					{
						dArrayTimeRL = (double *) calloc(nTimeIndex, sizeof(double));
					}
					else
					{
						// reallocate memory besed on new identified number of valid stride starts
						dArrayTimeRL = (double *) realloc(dArrayTimeRL, nTimeIndex*sizeof(double));
					}

					// assign time difference to array 
					dArrayTimeRL[nTimeIndex-1] =  (double)(istrideL[nIndexJ].nStop - istrideR[nIndexI].nStop) * dSamplePeriod;

					// exit loop
					break;
				}
			}
		}

		// get step time difference mean 
		dAvgStepTimeRL = dMean(dArrayTimeRL,nTimeIndex);

		// allocate memory based on time index
		dArrayTimeRLSorted = (double *) calloc(nTimeIndex, sizeof(double));

		// copy time array for sorting purposes
		for (nIndexI = 0; nIndexI < nTimeIndex; nIndexI++)
		{
			dArrayTimeRLSorted[nIndexI] = dArrayTimeRL[nIndexI];
		}

		// quick sort of time array in ascending order 
		qsort(dArrayTimeRLSorted, nTimeIndex, sizeof(double), dCompareFunction);

		// calculate median and interquartile mean 
		DistAvg(dArrayTimeRLSorted, nTimeIndex, &dTimeRLMedian, &dIQRAvgStepTimeRL);

		// jump to distance calculation
		goto algorithm;

force:
		// calculate step time differences between each feet (left to right)
		for (nIndexI = 0; nIndexI < nStrideForcePeaksL; nIndexI++)
		{
			for(nIndexJ = 0; nIndexJ < nStrideForcePeaksR; nIndexJ++)
			{
				// check for next stop index from right foot
				if (istrideForceR[nIndexJ].nGroundContact > istrideForceL[nIndexI].nGroundContact)
				{
					// increase index 
					nTimeIndex = nTimeIndex + 1;

					// allocate memory based on time index
					if (nTimeIndex == 1)
					{
						dArrayTimeLR = (double *) calloc(nTimeIndex, sizeof(double));
					}
					else
					{
						// reallocate memory besed on new identified number of valid stride starts
						dArrayTimeLR = (double *) realloc(dArrayTimeLR, nTimeIndex*sizeof(double));
					}

					// assign time difference to array 
					dArrayTimeLR[nTimeIndex-1] = (double)(istrideForceR[nIndexJ].nGroundContact - istrideForceL[nIndexI].nGroundContact) * dSamplePeriod;

					// exit loop
					break;
				}
			}
		}
		
		// get step time difference mean 
		dAvgStepTimeLR = dMean(dArrayTimeLR,nTimeIndex);

		// allocate memory based on time index
		dArrayTimeLRSorted = (double *) calloc(nTimeIndex, sizeof(double));

		// copy time array for sorting purposes
		for (nIndexI = 0; nIndexI < nTimeIndex; nIndexI++)
		{
			dArrayTimeLRSorted[nIndexI] = dArrayTimeLR[nIndexI];
		}

		// quick sort of time array in ascending order 
		qsort(dArrayTimeLRSorted, nTimeIndex, sizeof(double), dCompareFunction);

		// calculate median and interquartile mean 
		DistAvg(dArrayTimeLRSorted, nTimeIndex, &dTimeLRMedian, &dIQRAvgStepTimeLR);
		
		// reset time difference index
		nTimeIndex = 0;

		// calculate step time differences between each feet (right to left)
		for (nIndexI = 0; nIndexI < nStrideForcePeaksR; nIndexI++)
		{
			for(nIndexJ = 0; nIndexJ < nStrideForcePeaksL; nIndexJ++)
			{
				// check for next stop index from left foot
				if (istrideForceL[nIndexJ].nGroundContact > istrideForceR[nIndexI].nGroundContact)
				{
					// increase index 
					nTimeIndex = nTimeIndex + 1;

					// allocate memory based on time index
					if (nTimeIndex == 1)
					{
						dArrayTimeRL = (double *) calloc(nTimeIndex, sizeof(double));
					}
					else
					{
						// reallocate memory besed on new identified number of valid stride starts
						dArrayTimeRL = (double *) realloc(dArrayTimeRL, nTimeIndex*sizeof(double));
					}

					// assign time difference to array 
					dArrayTimeRL[nTimeIndex-1] =  (double)(istrideForceL[nIndexJ].nGroundContact - istrideForceR[nIndexI].nGroundContact) * dSamplePeriod;

					// exit loop
					break;
				}
			}
		}

		// get step time difference mean 
		dAvgStepTimeRL = dMean(dArrayTimeRL,nTimeIndex);

		// allocate memory based on time index
		dArrayTimeRLSorted = (double *) calloc(nTimeIndex, sizeof(double));

		// copy time array for sorting purposes
		for (nIndexI = 0; nIndexI < nTimeIndex; nIndexI++)
		{
			dArrayTimeRLSorted[nIndexI] = dArrayTimeRL[nIndexI];
		}

		// quick sort of time array in ascending order 
		qsort(dArrayTimeRLSorted, nTimeIndex, sizeof(double), dCompareFunction);

		// calculate median and interquartile mean 
		DistAvg(dArrayTimeRLSorted, nTimeIndex, &dTimeRLMedian, &dIQRAvgStepTimeRL);
				
algorithm:
		
		// reset index
		nIndexJ = 0;

		// LEFT
		for (nIndexI = 1; nIndexI < nStrideCountL-1; nIndexI++)
		{
			// run algorithm for each stride
			DistAlgo(&istrideL, &idataL, nIndexI, dSamplePeriod);

			// increment index 
			nIndexJ = nIndexJ + 1;
			
			// allocate dynamically array based on interval index
			if (nIndexJ == 1)
			{
				dArrayStrideTimeL = (double *) calloc(nIndexJ, sizeof(double));
				dArrayStrideSwingTimeL = (double *) calloc(nIndexJ, sizeof(double));
				dArrayStrideDistanceL = (double *) calloc(nIndexJ, sizeof(double));
				dArrayStrideForceL = (double *) calloc(nIndexJ, sizeof(double));
			}
			else
			{
				// reallocate memory for subsequent passes
				dArrayStrideTimeL = (double *) realloc(dArrayStrideTimeL, nIndexJ*sizeof(double));
				dArrayStrideSwingTimeL = (double *) realloc(dArrayStrideSwingTimeL, nIndexJ*sizeof(double));
				dArrayStrideDistanceL = (double *) realloc(dArrayStrideDistanceL, nIndexJ*sizeof(double));
				dArrayStrideForceL = (double *) realloc(dArrayStrideForceL, nIndexJ*sizeof(double));
			}

			// assign count to array interval 
			dArrayStrideTimeL[nIndexJ-1] = (istrideL)[nIndexI].dStrideTime;
			dArrayStrideSwingTimeL[nIndexJ-1] = (istrideL)[nIndexI].dStrideTimeSwing;
			dArrayStrideDistanceL[nIndexJ-1] = (istrideL)[nIndexI].dStride;
			dArrayStrideForceL[nIndexJ-1] = (istrideL)[nIndexI].dStrideMaxForce;
		}

		// quick sort of time array in ascending order 
		qsort(dArrayStrideTimeL, nIndexJ, sizeof(double), dCompareFunction);

		// calculate median and interquartile mean for stride time  
		DistAvg(dArrayStrideTimeL, nIndexJ, &dStrideTimeMedianL, &dIQRAvgStrideTimeL);

		// quick sort of time array in ascending order 
		qsort(dArrayStrideSwingTimeL, nIndexJ, sizeof(double), dCompareFunction);

		// calculate median and interquartile mean for stride swing time  
		DistAvg(dArrayStrideSwingTimeL, nIndexJ, &dStrideSwingTimeMedianL, &dIQRAvgStrideSwingTimeL);

		// quick sort of time array in ascending order 
		qsort(dArrayStrideDistanceL, nIndexJ, sizeof(double), dCompareFunction);

		// calculate median and interquartile mean for stride distance  
		DistAvg(dArrayStrideDistanceL, nIndexJ, &dStrideDistanceMedianL, &dIQRAvgStrideDistanceL);
		
		// quick sort of time array in ascending order 
		qsort(dArrayStrideForceL, nIndexJ, sizeof(double), dCompareFunction);

		// calculate median and interquartile mean for stride force  
		DistAvg(dArrayStrideForceL, nIndexJ, &dStrideForceMedianL, &dIQRAvgStrideForceL);

		// reset index
		nIndexJ = 0;

		// RIGHT
		for (nIndexI = 1; nIndexI < nStrideCountR-1; nIndexI++)
		{
			// run algorithm for each stride
			DistAlgo(&istrideR, &idataR, nIndexI, dSamplePeriod);

			// increment index 
			nIndexJ = nIndexJ + 1;

			// allocate dynamically array based on interval index
			if (nIndexJ == 1)
			{
				dArrayStrideTimeR = (double *) calloc(nIndexJ, sizeof(double));
				dArrayStrideSwingTimeR = (double *) calloc(nIndexJ, sizeof(double));
				dArrayStrideDistanceR = (double *) calloc(nIndexJ, sizeof(double));
				dArrayStrideForceR = (double *) calloc(nIndexJ, sizeof(double));
			}
			else
			{
				// reallocate memory for subsequent passes
				dArrayStrideTimeR = (double *) realloc(dArrayStrideTimeR, nIndexJ*sizeof(double));
				dArrayStrideSwingTimeR = (double *) realloc(dArrayStrideSwingTimeR, nIndexJ*sizeof(double));
				dArrayStrideDistanceR = (double *) realloc(dArrayStrideDistanceR, nIndexJ*sizeof(double));
				dArrayStrideForceR = (double *) realloc(dArrayStrideForceR, nIndexJ*sizeof(double));
			}

			// assign count to array interval 
			dArrayStrideTimeR[nIndexJ-1] = (istrideR)[nIndexI].dStrideTime;
			dArrayStrideSwingTimeR[nIndexJ-1] = (istrideR)[nIndexI].dStrideTimeSwing;
			dArrayStrideDistanceR[nIndexJ-1] = (istrideR)[nIndexI].dStride;
			dArrayStrideForceR[nIndexJ-1] = (istrideR)[nIndexI].dStrideMaxForce;
		}

		// quick sort of time array in ascending order 
		qsort(dArrayStrideTimeR, nIndexJ, sizeof(double), dCompareFunction);

		// calculate median and interquartile mean for stride time  
		DistAvg(dArrayStrideTimeR, nIndexJ, &dStrideTimeMedianR, &dIQRAvgStrideTimeR);

		// quick sort of time array in ascending order 
		qsort(dArrayStrideSwingTimeR, nIndexJ, sizeof(double), dCompareFunction);

		// calculate median and interquartile mean for stride swing time  
		DistAvg(dArrayStrideSwingTimeR, nIndexJ, &dStrideSwingTimeMedianR, &dIQRAvgStrideSwingTimeR);

		// quick sort of time array in ascending order 
		qsort(dArrayStrideDistanceR, nIndexJ, sizeof(double), dCompareFunction);

		// calculate median and interquartile mean for stride distance  
		DistAvg(dArrayStrideDistanceR, nIndexJ, &dStrideDistanceMedianR, &dIQRAvgStrideDistanceR);
		
		// quick sort of time array in ascending order 
		qsort(dArrayStrideForceR, nIndexJ, sizeof(double), dCompareFunction);

		// calculate median and interquartile mean for stride force  
		DistAvg(dArrayStrideForceR, nIndexJ, &dStrideForceMedianR, &dIQRAvgStrideForceR);
		
		// get output file extension size
		nOutputFileNameSizeExt = strlen(OUTPUT_FILENAME_EXT);

		// allocate memory output file name string
		strOutputFileName = (char *) calloc((nFileNameSize + nOutputFileNameSizeExt), sizeof(char));

		// build output file name
		strcpy(strOutputFileName, strFileName);
		strOutputFileName = strncat(strOutputFileName, OUTPUT_FILENAME_EXT, nOutputFileNameSizeExt);

		// output statistical exercise data to file only if strides have been found 
		DistOutAvg(strOutputFileName, dIQRAvgStrideTimeL, dIQRAvgStrideSwingTimeL, dIQRAvgStrideDistanceL, dIQRAvgStrideForceL, dFstMaximumL, nDataLineReadL, dIQRAvgStrideTimeR, dIQRAvgStrideSwingTimeR, dIQRAvgStrideDistanceR, dIQRAvgStrideForceR, dFstMaximumR, nDataLineReadR, dIQRAvgStepTimeLR, dIQRAvgStepTimeRL);

		// output stride data to file
		if ((FILE_TYPE == 0) && (OUTPUTADD == 1)) 
		{
			DistOut(strOutputFileName, &istrideL, nStrideCountL, dIQRAvgStrideDistanceL, dIQRAvgStrideTimeL);
			DistOut(strOutputFileName, &istrideR, nStrideCountR, dIQRAvgStrideDistanceR, dIQRAvgStrideTimeR);
		}
				
		// deallocate memory
		free(istrideL);
		free(istrideR);

		if ((nStrideForcePeaksL != 0) && (nStrideForcePeaksR != 0))
		{
			free(istrideForceL);
			free(istrideForceR);
		}	
	}

done:

	// deallocate memory
	free(strInputFileBuffer);
	free(idataL);
	free(idataR);

	return 0;
}

//--------------------------------------------------------------------------------
///////////////////////////////////////////
// buffer streaming function - replacement for fgets
///////////////////////////////////////////
int bgets(char * o_buffer, int size, char ** i_buffer)
{
	char * pch;
	int length = 0;

	pch = (char *)memchr((*i_buffer), '\n', strlen((*i_buffer)));

	if(pch == NULL)
		return 2;

	length = pch - (*i_buffer) + 1;
	
	if(length > size)
		return 1;

	memcpy(o_buffer, (*i_buffer), length);

	(*i_buffer) = (*i_buffer) + length;

	return 0;
}

///////////////////////////////////////////
// read raw sensor data and dynamically allocate and assign to sensor data structure (data converted to engineering units)
///////////////////////////////////////////
void DistRead(char * strRunID, char * strFileName, char * strInputBuffer, struct data ** idata, int * nDataLineRead)
{
	int nIndexI = 0; // general indeces
	int nIndexJ = 0;
	int nIndexEpoch = 0; // index for first epoch change
	char strFootID; // foot ID ("r/R" --> right foot or "l/L" --> left foot)
	char strHeader[1000]; // header line size set to max of 1000
	char strDataLine[1000]; // data line size set to max of 1000
	double dGyroX, dGyroY, dGyroZ, dAccelX, dAccelY, dAccelZ; // sensor data file read line variables
	int nTime, nFs1, nFs2, nFs3, nFs4;
	int b_error = 0;

	// check antepenultimate in the file name ("r\R" --> right foot or "l\L" --> left foot)
	strFootID = strFileName[strlen(strFileName)-7];

	// ignore first x header lines (+ first data line -> usually 0s) in data sensor file 
	for (nIndexI = 0; nIndexI < HEADER_LINES; nIndexI++)
	{
		b_error = bgets((char *)&strHeader, 1000, &strInputBuffer);
	}
	
	// reset index
	nIndexI = 0;

	// assign sensor data file values to data structure 
	while (!b_error) 
	{
		// increment number of data lines counter 
		*nDataLineRead = *nDataLineRead + 1;

		if ((*nDataLineRead) == 1)
		{
			// dynamically allocate data structure 
			(*idata) = (struct data *) calloc(*nDataLineRead, sizeof(struct data));
		}
		else
		{
			// reallocate memory besed on new identified number of valid stride stops
			(*idata) = (struct data *) realloc((*idata), (*nDataLineRead)*sizeof(struct data));
		}

		// get data line from sensor data file 
		b_error = bgets((char *)&strDataLine, 1000, &strInputBuffer);
		sscanf(strDataLine,"%d%*c %d%*c %d%*c %d%*c %d%*c %lf%*c %lf%*c %lf%*c %lf%*c %lf%*c %lf%*\n", &nTime, &nFs1, &nFs2, &nFs3, &nFs4, &dGyroX, &dGyroY, &dGyroZ, &dAccelX, &dAccelY, &dAccelZ);
		
		// assign time stamp 
		(*idata)[nIndexI].dTime = nTime; 

		// assign force values
		(*idata)[nIndexI].nFs1 = nFs1; // force sensor 1
		(*idata)[nIndexI].nFs2 = nFs2; // force sensor 2
		(*idata)[nIndexI].nFs3 = nFs3; // force sensor 3
		(*idata)[nIndexI].nFs4 = nFs4; // force sensor 4
		(*idata)[nIndexI].nFsf = nFs1 + nFs2; // force sensor front sum (nFs1 + nFs2)
		(*idata)[nIndexI].nFsr = nFs3 + nFs4; // force sensor rear sum (nFs3 + nFs4)
		(*idata)[nIndexI].nFst = nFs1 + nFs2 + nFs3 + nFs4; // force sensor total sum 

		// check if it is a right or left foot data, default is left foot
		if ((strFootID == 'l') || (strFootID == 'L')) // (multiply by a factor -1 --> accel x
		{
			// right foot  - assign extracted data value to corresponding structure member (AX, AY)
			(*idata)[nIndexI].dAccelX = (-1 * G * dAccelX)/65536; // accel X in g; convert to m/s^2
			(*idata)[nIndexI].dAccelY = (G * dAccelY)/65536; // accel Y in g; convert to m/s^2
		}
		else 
		{
			// left foot - assign extracted data value to corresponding structure member (AX, AY)
			(*idata)[nIndexI].dAccelX = (-1 * G * dAccelX)/65536; // accel X in g; convert to m/s^2
			(*idata)[nIndexI].dAccelY = (G * dAccelY)/65536; // accel Y in g; convert to m/s^2
		}

		// assign GX to corresponding structure member
		(*idata)[nIndexI].dGyroX = dGyroX / 65536; // gyro Y in deg/s 

		// assign AZ to corresponding structure member
		(*idata)[nIndexI].dAccelZ = (-1 * G * dAccelZ)/65536; // accel Z in g; convert to m/s^2
		
		// update index for next iteration 
		nIndexI = nIndexI + 1;
	}

	// correct number of data lines read  
	*nDataLineRead = *nDataLineRead - 1;

	if (*strRunID == '0')
	{
		goto skip; // skip epoch synch
	}

	// traverse entire structure looking for first change of epoch time
	for (nIndexI = 0; nIndexI < *nDataLineRead; nIndexI++)
	{
		if ((*idata)[nIndexI].dTime > (*idata)[1].dTime)
		{
			// change found, break from loop
			break;
		}
	}

	// save epoch index
	nIndexEpoch = nIndexI;

	// redefine structure based on epoch time index
	for (nIndexI = nIndexEpoch; nIndexI < *nDataLineRead; nIndexI++)
	{
		// reassign values to structure 
		(*idata)[nIndexJ].dTime = (*idata)[nIndexI].dTime;
		(*idata)[nIndexJ].dGyroX = (*idata)[nIndexI].dGyroX;
		(*idata)[nIndexJ].dAccelX = (*idata)[nIndexI].dAccelX;
		(*idata)[nIndexJ].dAccelY = (*idata)[nIndexI].dAccelY;
		(*idata)[nIndexJ].dAccelZ = (*idata)[nIndexI].dAccelZ;
		(*idata)[nIndexJ].nFs1 = (*idata)[nIndexI].nFs1; 
		(*idata)[nIndexJ].nFs2 = (*idata)[nIndexI].nFs2; 
		(*idata)[nIndexJ].nFs3 = (*idata)[nIndexI].nFs3; 
		(*idata)[nIndexJ].nFs4 = (*idata)[nIndexI].nFs4; 
		(*idata)[nIndexJ].nFsf = (*idata)[nIndexI].nFsf; 
		(*idata)[nIndexJ].nFsr = (*idata)[nIndexI].nFsr; 
		(*idata)[nIndexJ].nFst = (*idata)[nIndexI].nFst; 

		// update index
		nIndexJ = nIndexJ + 1;
	}
	
	// update number of data lines read
	*nDataLineRead = *nDataLineRead - nIndexEpoch;

	// update structure reallocating for discarded data
	(*idata) = (struct data *)realloc((*idata), (*nDataLineRead) *sizeof(struct data));

skip:
	;
}
//--------------------------------------------------------------------------------

// -------------------------------------------------------------------------------
///////////////////////////////////////////
// calculate standstill offsets and force thresholds
///////////////////////////////////////////
void DistInit(struct data ** idata, int nDataLineRead, double * dAccelTQuiescentOffset, double * dGyroXQuiescentOffset, double * dFstMaximum, double * dFstMinimum, double * dFstQuiescent)
{
	int nIndexI = 0; // general indeces
	int nIndexJ = 0;
	int nStandstillIndex = 0; // index for standstill period end

	double dAccelTBase = G; // total accel baseline 1g
	double dAccelTRange = 20; // total accel range in percent 20% 

	int nForceMax = 0; // max total force value
	int nForceMinInt = 0; // total force interval limits & increment 
	int nForceMaxInt = 2;
	int nForceIncrement = 2; 
	
	int nIntCount = 0;  // total force interval count 
	int *nArrayIntCount; // result array containing total force interval counts
	int nArrayIntCountSize = 0;

	int nIntSum = 0; // total force interval sum
	int *nArrayIntSum; // result array containing total force interval sums

	// initialize force total max value
	nForceMax = (*idata)[1].nFst;

	// find max force value in entire total force data structure 
	for (nIndexI = 0; nIndexI < nDataLineRead; nIndexI++)
	{
		if ((*idata)[nIndexI].nFst > nForceMax)
		{
			// update force max 
			nForceMax = (*idata)[nIndexI].nFst;
		}
	}

	// traverse data structure and count number of data points inside total force intervals
	while (nForceMaxInt <= nForceMax)
	{
		for (nIndexI = 0; nIndexI < nDataLineRead; nIndexI++)
		{
			// check if total force value is inside intervals
			if (((*idata)[nIndexI].nFst > nForceMinInt) && ((*idata)[nIndexI].nFst < nForceMaxInt))
			{
				// update interval count
				nIntCount = nIntCount + 1;

				// update interval sum
				nIntSum = nIntSum + (*idata)[nIndexI].nFst;
			}
		}
		
		// update interval index 
		nIndexJ = nIndexJ + 1;

		// allocate dynamically array based on interval index
		if (nIndexJ == 1)
		{
			nArrayIntCount = (int *) calloc(nIndexJ, sizeof(int));
			nArrayIntSum = (int *) calloc(nIndexJ, sizeof(int));
		}
		else
		{
			// reallocate memory for subsequent passes
			nArrayIntCount = (int *) realloc(nArrayIntCount, nIndexJ*sizeof(int));
			nArrayIntSum = (int *) realloc(nArrayIntSum, nIndexJ*sizeof(int));
		}

		// assign count to corresponding array  
		nArrayIntCount[nIndexJ-1] = nIntCount;

		// assign sum to corresponding array  
		nArrayIntSum[nIndexJ-1] = nIntSum;

		// update force intervals
		nForceMinInt = nForceMinInt + nForceIncrement;
		nForceMaxInt = nForceMaxInt + nForceIncrement;

		// reset interval count & sum
		nIntCount = 0;
		nIntSum = 0;
	}

	// save array interval count size
	nArrayIntCountSize = nIndexJ;

	// look for first drop in array interval count to locate first total force valley
	for (nIndexI = 0; nIndexI < nArrayIntCountSize - 1; nIndexI++)
	{
		if (nArrayIntCount[nIndexI+1] >= nArrayIntCount[nIndexI])
		{
		}
		else // if there is drop, break from loop
		{
			break;
		}
	}

	// find minimum force threshold
	*dFstMinimum = (double)(nArrayIntSum[nIndexI]) / (double)(nArrayIntCount[nIndexI]);

	// standstill index calculation 
	nStandstillIndex = STANDSTILL_SEC * SAMPLE_FREQ;

	// get total force quiescent sum 
	for (nIndexI = 0; nIndexI < nStandstillIndex; nIndexI++)
	{
		*dFstQuiescent = *dFstQuiescent + (*idata)[nIndexI].nFst;
	}

	// calculate total force quiescent avg 
	*dFstQuiescent = *dFstQuiescent/nStandstillIndex;

	// assign standstill force threshold - between max force and quiescent avg
	*dFstMaximum = *dFstQuiescent + ((double)nForceMax - *dFstQuiescent)/2;
	
	// compute total acceleration magnitude
	AccelTMagnitude(idata, nStandstillIndex);

	// average quiescent total acceleration at standstill
	*dAccelTQuiescentOffset = dStandStillOffset(idata, nStandstillIndex, 5); // at (struct member 5)

	// check average quiescent total acceleration against % boundary of base value (1g)
	if (*dAccelTQuiescentOffset < (dAccelTBase - dAccelTBase*(dAccelTRange/100)))
	{
		// average quiescent total acceleration not within boundaries
		goto failed; // do not create init file 
	}
	else 
	{
		if (*dAccelTQuiescentOffset > (dAccelTBase + dAccelTBase*(dAccelTRange/100)))
		{
			// average quiescent total acceleration not within boundaries
			goto failed; // do not create init file 
		}		
	}

	// calculate standstill gyro offset 
	*dGyroXQuiescentOffset = dStandStillOffset(idata, nStandstillIndex, 1); // gx (struct member 1)

	// return to main function 
	return;

failed:

	*dAccelTQuiescentOffset = 9999;
}

///////////////////////////////////////////
// initialization output for exercise 
///////////////////////////////////////////
void DistOutInit(char * strInitFileName, double dAccelTQuiescentOffsetL, double dGyroXQuiescentOffsetL, double dFstMaximumL, double dFstMinimumL, double dFstQuiescentL, double dAccelTQuiescentOffsetR, double dGyroXQuiescentOffsetR, double dFstMaximumR, double dFstMinimumR, double dFstQuiescentR)
{
	// open init file 
	fnd = fopen(strInitFileName,"w");
	
	// write to file
	fprintf(fnd, "%%\n");
	fprintf(fnd, "%% MedHab gait algorithm initialization file\n");
	fprintf(fnd, "%%\n");
	fprintf(fnd, "%% Numbers below contain the following information\n");
	fprintf(fnd, "%% -LF total acceleration standstill offset (units: m/s^2)\n");
	fprintf(fnd, "%% -LF gyro x standstill offset (units: deg/s)\n");
	fprintf(fnd, "%% -LF total force standstill threshold (units: counts)\n");
	fprintf(fnd, "%% -LF total force maximum threshold (units: counts)\n");
	fprintf(fnd, "%% -LF total force minimum threshold (units: counts)\n");
	fprintf(fnd, "%% -RF total acceleration standstill offset (units: m/s^2)\n");
	fprintf(fnd, "%% -RF gyro x standstill offset (units: deg/s)\n");
	fprintf(fnd, "%% -RF total force standstill threshold (units: counts)\n");
	fprintf(fnd, "%% -RF total force maximum threshold (units: counts)\n");
	fprintf(fnd, "%% -RF total force minimum threshold (units: counts)\n");
	fprintf(fnd, "%%\n");

	fprintf(fnd, "%lf\n", dAccelTQuiescentOffsetL);
	fprintf(fnd, "%lf\n", dGyroXQuiescentOffsetL);
	fprintf(fnd, "%lf\n", dFstQuiescentL);
	fprintf(fnd, "%lf\n", dFstMaximumL);
	fprintf(fnd, "%lf\n", dFstMinimumL);

	fprintf(fnd, "%lf\n", dAccelTQuiescentOffsetR);
	fprintf(fnd, "%lf\n", dGyroXQuiescentOffsetR);
	fprintf(fnd, "%lf\n", dFstQuiescentR);
	fprintf(fnd, "%lf\n", dFstMaximumR);
	fprintf(fnd, "%lf\n", dFstMinimumR);
	
	// close init file
	fclose(fnd);
}
// -------------------------------------------------------------------------------

// -------------------------------------------------------------------------------
///////////////////////////////////////////
// get quiescent offsets and force thresholds 
///////////////////////////////////////////
void DistGet(char * strInputBuffer, double * dAccelTQuiescentOffsetL, double * dGyroXQuiescentOffsetL, double * dFstMaximumL, double * dFstMinimumL, double * dFstQuiescentL, double * dAccelTQuiescentOffsetR, double * dGyroXQuiescentOffsetR, double * dFstMaximumR, double * dFstMinimumR, double * dFstQuiescentR)
{
	int nIndex = 0; // general index
	int nHeaderLines = 15; // number of header lines in init file
	char strHeader[1000]; // header line size set to max of 1000
	char strDataLine[1000]; // data line size set to max of 1000
	double dAccelOffset, dGyroXOffset;
	double dFMaxOffset, dFMinOffset, dFStandStillOffset;

	// ignore first header lines in init file 
	for (nIndex = 0; nIndex < nHeaderLines; nIndex++)
	{
		bgets((char *)&strHeader, 1000, &strInputBuffer);
	}

	// get data lines from init file
	// LEFT
	bgets((char *)&strDataLine, 1000, &strInputBuffer);
	sscanf(strDataLine,"%lf%*c", &dAccelOffset);

	bgets((char *)&strDataLine, 1000, &strInputBuffer);
	sscanf(strDataLine,"%lf%*c", &dGyroXOffset);

	bgets((char *)&strDataLine, 1000, &strInputBuffer);
	sscanf(strDataLine,"%lf%*c", &dFStandStillOffset);

	bgets((char *)&strDataLine, 1000, &strInputBuffer);
	sscanf(strDataLine,"%lf%*c", &dFMaxOffset);

	bgets((char *)&strDataLine, 1000, &strInputBuffer);
	sscanf(strDataLine,"%lf%*c", &dFMinOffset);

	*dAccelTQuiescentOffsetL = dAccelOffset;
	*dGyroXQuiescentOffsetL = dGyroXOffset;
	*dFstQuiescentL = dFStandStillOffset;
	*dFstMaximumL = dFMaxOffset;
	*dFstMinimumL = dFMinOffset;

	// RIGHT
	bgets((char *)&strDataLine, 1000, &strInputBuffer);
	sscanf(strDataLine,"%lf%*c", &dAccelOffset);

	bgets((char *)&strDataLine, 1000, &strInputBuffer);
	sscanf(strDataLine,"%lf%*c", &dGyroXOffset);

	bgets((char *)&strDataLine, 1000, &strInputBuffer);
	sscanf(strDataLine,"%lf%*c", &dFStandStillOffset);

	bgets((char *)&strDataLine, 1000, &strInputBuffer);
	sscanf(strDataLine,"%lf%*c", &dFMaxOffset);

	bgets((char *)&strDataLine, 1000, &strInputBuffer);
	sscanf(strDataLine,"%lf%*c", &dFMinOffset);

	*dAccelTQuiescentOffsetR = dAccelOffset;
	*dGyroXQuiescentOffsetR = dGyroXOffset;
	*dFstQuiescentR = dFStandStillOffset;
	*dFstMaximumR = dFMaxOffset;
	*dFstMinimumR = dFMinOffset;
}

///////////////////////////////////////////
// apply offsets and filter sensor data
///////////////////////////////////////////
void DistProc(struct data ** idata, int nDataLineRead, double dGyroXQuiescentOffset)
{
	// compute total acceleration magnitude
	AccelTMagnitude(idata, nDataLineRead);
	
	//  apply standstill offset to gyro 
	OffsetApply(idata, nDataLineRead, dGyroXQuiescentOffset, 1);

	// check apply filter selection
	if (FILTERAPPLY == 1)  
	{
		// apply filter to gyro and all accelerations
		FilterApply(idata, nDataLineRead, 1); // gx
		FilterApply(idata, nDataLineRead, 2); // accel x
		FilterApply(idata, nDataLineRead, 3); // accel y
		FilterApply(idata, nDataLineRead, 4); // accel z
		FilterApply(idata, nDataLineRead, 5); // accel t
		FilterApply(idata, nDataLineRead, 10); // Fsf
		FilterApply(idata, nDataLineRead, 11); // Fsr
		FilterApply(idata, nDataLineRead, 12); // Fst
	}	
}

///////////////////////////////////////////
// discretize raw data into individual strides
///////////////////////////////////////////
void DistDisc(struct data ** idata, struct stride ** istride, struct strideForce ** istrideForce, int nDataLineRead, double dAccelTQuiescentOffset, double dFstMaximum, double dFstMinimum, double dFstQuiescent, int * nStrideCount, int * nStrideForcePeaks)
{
	int nIndexI = 0; // general indeces
	int nIndexJ = 0; 
	int nIndexK = 0; 
	int nIndexL = 0;

	double dAccelMax = 0;  // total accel max 
	double dAccelMinInt = 0; // total accel intervals & increment 
	double dAccelMaxInt = 0.25 * G;
	double dAccelIncrement = 0.25 * G; 

	int nStrideIndex = 0; // number of strides counted
	int *nArrayStrideStart; // result array containing stride start index
	int *nArrayStridePeak; // result array containing stride accel total peak index
	int *nArrayStrideStop; // result array containing stride index stop
	int nStrideStartIndex = 0; // general index for array of stride starts
	int nStrideStopIndex = 0; // general index for array of stride stops
	int nStridePhase = 1; // phase within stride look ahead search
	
	int nIntCount = 0;  // total accel valley interval count 
	int *nArrayIntCount; // result array containing total accel interval counts
	int nArrayIntCountSize = 0;

	double dSumAccel = 0;  // total accel valley sum 
	double *dArraySumAccel; // result array containing total accel interval sums
	int nArraySumAccelSize = 0;

	int nAccelValleyIndex = 0; // accel valley index & interval limits
	double dAccelValleyMinInt = 0; 
	double dAccelValleyMaxInt = 0; 
	int *nArrayAccelBinary; // result binary array for data inside accel valley 

	int nConsecutivePointsPlatos = 0; // number of consecutive points in plato
	int nPlatoCount = 0; // number of platos found
	int *nArrayPlatoWidth; // result array containing plato widths
	int *nArrayPlatoWidthSorted; // sorted array plato widths

	int nConsecutivePointsGap = 0; // number of consecutive points in accel valley gaps
	int nConsecutivePointsPlato = 0; // number of consecutive points proceding accel valley gaps
	int nGapCount = 0; // number of gaps found
	int *nArrayGapWidth; // result array containing gap widths
	int *nArrayGapWidthSorted; // sorted array gap widths

	double dMedianIndex = 0; // median index 

	int nMedianPlatoWidth = 0; // plato width median 
	
	int nMedianGapWidth = 0; // gap width median 
	int *nArrayGapWithDiff; // result array containing gap width differences 
	
	int nMedianAbsDev = 0; // median absolute deviation 
	double *dArrayModifiedZScore; // result array containing modified z score values for each gap width
	
	int nGapCountAdj = 0; // adjusted gap count (after outlier elimination)
	int *nArrayGapWidthAdj; // adjusted array gap widths (after outlier elimination)

	int nSum = 0; // cumulative sum for mean calculation
	
	double dGapWidthAvg = 0; // gap width mean 
	double dDiff = 0; // cumulative diff for std dev calculation 
	double dGapWidthStdDev = 0; // gap width std dev 
	
	double dLeftFence = 0; // gap width lower fence for outlier elimination 
	double dRightFence = 0; // gap width upper fence 
	
	int nPlatoWidthMin = 0; // plato width min  
	int nGapWidthMin = 0; // gap width min  
	
	double dAccelPeak = 0; // stride total accel max
	
	int nStrideForceIndex = 0; // number of strides counted
	int *nArrayStrideForcePeak; // result array containing stride force peak index
	int nStrideForcePhase = 1; // phase within stride force look ahead search

	// check if exercise is walking or running and assign corresponding interval parameters 
	// walking total accel profile contains more regular drops into valley interval, as such interval limits must be narrow
	if (FILE_TYPE == 0) 
	{
		dAccelMaxInt = 0.1 * G;
		dAccelIncrement = 0.1 * G; 	
	}
	else
	{
		dAccelMaxInt = 0.25 * G;
		dAccelIncrement = 0.25 * G; 	
	}

	// zero out accel total data structure member collection
	OffsetApply(idata, nDataLineRead, dAccelTQuiescentOffset, 5);

	// convert to absolute value accel total data structure member collection for ease of handling 
	AccelTAbsoluteValue(idata, nDataLineRead);

	// initialize accel total max value
	dAccelMax = (*idata)[1].dAccelT;

	// find max accel value in entire accel total data structure 
	for (nIndexI = 0; nIndexI < nDataLineRead; nIndexI++)
	{
		if ((*idata)[nIndexI].dAccelT > dAccelMax)
		{
			// update accel max 
			dAccelMax = (*idata)[nIndexI].dAccelT;
		}
	}

	// traverse data structure and count number of data points inside accel total intervals
	while (dAccelMaxInt <= dAccelMax)
	{
		for (nIndexI = 0; nIndexI < nDataLineRead; nIndexI++)
		{
			// check if accel total value is inside intervals
			if (((*idata)[nIndexI].dAccelT > dAccelMinInt) && ((*idata)[nIndexI].dAccelT < dAccelMaxInt))
			{
				// keep count of number of points within search window
				nIntCount = nIntCount + 1;

				// keep sum to obtain average
				dSumAccel = dSumAccel + (*idata)[nIndexI].dAccelT;
			}
		}
		
		// update interval index 
		nIndexJ = nIndexJ + 1;

		// allocate dynamically array based on interval index
		if (nIndexJ == 1)
		{
			nArrayIntCount = (int *) calloc(nIndexJ, sizeof(int));
			dArraySumAccel = (double *) calloc(nIndexJ, sizeof(double));
		}
		else
		{
			// reallocate memory for subsequent passes
			nArrayIntCount = (int *) realloc(nArrayIntCount, nIndexJ*sizeof(int));
			dArraySumAccel = (double *) realloc(dArraySumAccel, nIndexJ*sizeof(double));
		}

		// assign count to array interval 
		nArrayIntCount[nIndexJ-1] = nIntCount;
		dArraySumAccel[nIndexJ-1] = dSumAccel;

		// update accel intervals
		dAccelMinInt = dAccelMinInt + dAccelIncrement;
		dAccelMaxInt = dAccelMaxInt + dAccelIncrement;

		// reset interval count 
		nIntCount = 0;
		dSumAccel = 0;
	}

	// save array interval count size
	nArrayIntCountSize = nIndexJ;

	// look for first drop in array interval count to locate first accel total valley
	for (nIndexI = 0; nIndexI < nArrayIntCountSize - 1; nIndexI++)
	{
		if (nArrayIntCount[nIndexI+1] >= nArrayIntCount[nIndexI])
		{
		}
		else // if there is drop, break from loop
		{
			break;
		}
	}

	// save accel total valley index 
	nAccelValleyIndex = nIndexI;

	// get accel valley intervals 
	dAccelValleyMinInt = nAccelValleyIndex * dAccelIncrement;
	dAccelValleyMaxInt = nAccelValleyIndex * dAccelIncrement + dAccelIncrement;

	// initialize binary array
	nArrayAccelBinary = (int *) calloc(nDataLineRead, sizeof(int));

	// assemble binary array of points inside accel total valley interval 
	for (nIndexI = 0; nIndexI < nDataLineRead; nIndexI++)
	{
		// check if accel total is inside interval 
		if ((*idata)[nIndexI].dAccelT <= dAccelValleyMaxInt)
		{
			// inside, assign a 1 
			nArrayAccelBinary[nIndexI] = 1;
		}
		else
		{
			// outside, assign a 0
			nArrayAccelBinary[nIndexI] = 0;
		}
	}
	
	// eliminate single point valleys (false drops)
	for (nIndexI = 0; nIndexI < nDataLineRead - 2; nIndexI++)
	{
		if ((nArrayAccelBinary[nIndexI] == 1) && (nArrayAccelBinary[nIndexI + 1] == 0) && (nArrayAccelBinary[nIndexI + 2] == 1))
		{
			nArrayAccelBinary[nIndexI + 1] = 1;
		}
	}

	// eliminate two point valleys (false drops)
	for (nIndexI = 0; nIndexI < nDataLineRead - 3; nIndexI++)
	{
		if ((nArrayAccelBinary[nIndexI] == 1) && (nArrayAccelBinary[nIndexI + 1] == 0) && (nArrayAccelBinary[nIndexI + 2] == 0) && (nArrayAccelBinary[nIndexI + 3] == 1))
		{
			nArrayAccelBinary[nIndexI + 1] = 1;
			nArrayAccelBinary[nIndexI + 2] = 1;
		}
	}

	// eliminate single point peaks (false highs)
	for (nIndexI = 0; nIndexI < nDataLineRead - 2; nIndexI++)
	{
		if ((nArrayAccelBinary[nIndexI] == 0) && (nArrayAccelBinary[nIndexI + 1] == 1) && (nArrayAccelBinary[nIndexI + 2] == 0))
		{
			nArrayAccelBinary[nIndexI + 1] = 0;
		}
	}

	// check if exercise is walking or running
	if (FILE_TYPE == 0) 
	{
		goto walking;		
	}
	else
	{
		goto running;
	}

	//
	// walking 
	//
walking:

	// get accel total plato widths
	for (nIndexI = 1; nIndexI < nDataLineRead - 1; nIndexI++)
	{
		// check for plato entry point 
		if ((nArrayAccelBinary[nIndexI-1] == 0) && (nArrayAccelBinary[nIndexI] == 1))
		{
			// update counts 
			nConsecutivePointsPlatos = 1;
			nPlatoCount = nPlatoCount + 1;

			// continue traversing binary array until current plato is done or end of data
			for (nIndexJ = nIndexI + 1; nIndexJ < nDataLineRead; nIndexJ++)
			{
				// as soon a 0 is found stop counting consecutive points 
				if (nArrayAccelBinary[nIndexJ] == 0)
				{
					break;
				}
				else
				{
					// update number of consecutive points @ current plato
					nConsecutivePointsPlatos = nConsecutivePointsPlatos + 1;
				}
			}

			// check for unfinished gap at the end of array - ignore it 
			if (nIndexJ < nDataLineRead)
			{
			}
			else
			{
				// ignore last gap 
				nPlatoCount = nPlatoCount - 1;

				// next iteration  
				continue;
			}

			// allocate dynamically array based on gap count
			if (nPlatoCount == 1)
			{
				nArrayPlatoWidth = (int *) calloc(nPlatoCount, sizeof(int));
			}
			else
			{
				// reallocate memory for subsequent passes
				nArrayPlatoWidth = (int *) realloc(nArrayPlatoWidth, nPlatoCount*sizeof(int));
			}

			// assign plato width to corresponding array location 
			nArrayPlatoWidth[nPlatoCount - 1] = nConsecutivePointsPlatos;
		}
	}

	// allocate dynamically array based on plato count  
	nArrayPlatoWidthSorted = (int *) calloc(nPlatoCount, sizeof(int));

	// copy array for sorting 
	for (nIndexI = 0; nIndexI < nPlatoCount; nIndexI++)
	{
		nArrayPlatoWidthSorted[nIndexI] = nArrayPlatoWidth[nIndexI];
	}

	// quick sort of plato width array in ascending order 
	qsort(nArrayPlatoWidthSorted, nPlatoCount, sizeof(int), nCompareFunction);

	// calculate median index based on number of platos found
	dMedianIndex = ((nPlatoCount + 1)/2);

	// check platos count to calculate median 
	if (nPlatoCount % 2 != 0)
	{
		// odd number of platos 
		nMedianPlatoWidth = nArrayPlatoWidthSorted[(int)(dMedianIndex - 1)];
	}
	else
	{
		// even number of platos - avg left and right values next to median index 
		nMedianPlatoWidth = (nArrayPlatoWidthSorted[(int)floor(dMedianIndex - 1)] + nArrayPlatoWidthSorted[(int)ceil(dMedianIndex - 1)])/2;
	}

	// assign minimum plato thickness 
	nPlatoWidthMin = floor(nMedianPlatoWidth);

	// eliminate platos at binary array with less than min number of consecutive points
	for (nIndexI = 1; nIndexI < nDataLineRead; nIndexI++)
	{
		// check first gap to plato entry  
		if ((nArrayAccelBinary[nIndexI-1] == 0) && (nArrayAccelBinary[nIndexI] == 1))
		{
			// keep track of data points in plato
			nConsecutivePointsPlatos = 1;
			for (nIndexJ = nIndexI + 1; nIndexJ < nDataLineRead; nIndexJ++)
			{
				// as soon 0 is found stop counting consecutive points 
				if (nArrayAccelBinary[nIndexJ] == 0)
				{
					break;
				}
				else
				{
					nConsecutivePointsPlatos = nConsecutivePointsPlatos + 1;
				}
			}

			// check for unfinished gap at the end of array  
			if (nIndexJ < nDataLineRead)
			{
			}
			else
			{
				// next iteration  
				continue;
			}

			// eliminate platos with not enough number of consecutive points
			if (nConsecutivePointsPlatos < nPlatoWidthMin)
			{
				for (nIndexL = nIndexI; nIndexL <= (nIndexI + nConsecutivePointsPlatos); nIndexL++)
				{
					// check for end of data file  
					if (nIndexL < nDataLineRead)
					{
					}
					else
					{
						// next iteration  
						break;
					}

					nArrayAccelBinary[nIndexL] = 0;			
				}

				// rewind main loop index 
				nIndexI = nIndexI - 1;
			}
		}
	}

	// traverse binary array and find step indeces
	for (nIndexI = 0; nIndexI < nDataLineRead; nIndexI++)
	{
		// look ahead for 1 to 0 transition = exit point from accel total valley
		if ((nStridePhase == 1) && (nArrayAccelBinary[nIndexI] == 1) && (nArrayAccelBinary[nIndexI+1] == 0))
		{
			// increment stride count
			nStrideIndex = nStrideIndex + 1;

			// increment stride start index
			nStrideStartIndex = nStrideStartIndex + 1;

			// allocate dynamically array based on stride index
			if (nStrideIndex == 1)
			{
				nArrayStrideStart = (int *) calloc(nStrideIndex, sizeof(int));
			}
			else
			{
				// reallocate memory besed on new identified number of valid stride starts
				nArrayStrideStart = (int *) realloc(nArrayStrideStart, nStrideIndex*sizeof(int));
			}

			// assign index
			nArrayStrideStart[nStrideIndex-1] = nIndexI;

			// now looking for stride stop  
			nStridePhase = 2; 
		}

		// look ahead for 0 to 1 transition = entry point from accel total valley
		if ((nStridePhase == 2) && (nArrayAccelBinary[nIndexI] == 0) && (nArrayAccelBinary[nIndexI+1] == 1))
		{
			// increment stride start index
			nStrideStopIndex = nStrideStopIndex + 1;

			// allocate dynamically array based on stride index
			if (nStrideIndex == 1)
			{
				nArrayStrideStop = (int *) calloc(nStrideIndex, sizeof(int));
			}
			else
			{
				// reallocate memory besed on new identified number of valid stride stops
				nArrayStrideStop = (int *) realloc(nArrayStrideStop, nStrideIndex*sizeof(int));
			}

			// assign index
			nArrayStrideStop[nStrideIndex-1] = nIndexI;

			// now looking for beginning of next stride 
			nStridePhase = 1;
		}
	}

	goto stride;

running:

	//
	// running 
	//

	// get accel total gap widths
	for (nIndexI = 1; nIndexI < nDataLineRead - 1; nIndexI++)
	{
		// check for gap entry point 
		if ((nArrayAccelBinary[nIndexI-1] == 1) && (nArrayAccelBinary[nIndexI] == 0))
		{
			// update counts 
			nConsecutivePointsGap = 1;
			nGapCount = nGapCount + 1;

			// continue traversing binary array until current gap is done or end of data
			for (nIndexJ = nIndexI + 1; nIndexJ < nDataLineRead; nIndexJ++)
			{
				// as soon a 1 is found stop counting consecutive points 
				if (nArrayAccelBinary[nIndexJ] == 1)
				{
					break;
				}
				else
				{
					// update number of consecutive points @ current gap
					nConsecutivePointsGap = nConsecutivePointsGap + 1;
				}
			}

			// check for unfinished gap at the end of array - ignore it 
			if (nIndexJ < nDataLineRead)
			{
			}
			else
			{
				// ignore last gap 
				nGapCount = nGapCount - 1;

				// next iteration  
				continue;
			}

			// allocate dynamically array based on gap count
			if (nGapCount == 1)
			{
				nArrayGapWidth = (int *) calloc(nGapCount, sizeof(int));
			}
			else
			{
				// reallocate memory for subsequent passes
				nArrayGapWidth = (int *) realloc(nArrayGapWidth, nGapCount*sizeof(int));
			}

			// assign plato width to corresponding array location 
			nArrayGapWidth[nGapCount - 1] = nConsecutivePointsGap;
		}
	}
	
	//
	// outlier detection 
	//

	// allocate dynamically array based on gap count  
	nArrayGapWidthSorted = (int *) calloc(nGapCount, sizeof(int));

	// copy array for sorting 
	for (nIndexI = 0; nIndexI < nGapCount; nIndexI++)
	{
		nArrayGapWidthSorted[nIndexI] = nArrayGapWidth[nIndexI];
	}

	// quick sort of gap width array in ascending order 
	qsort(nArrayGapWidthSorted, nGapCount, sizeof(int), nCompareFunction);

	// calculate median index based on number of gaps found
	dMedianIndex = ((nGapCount + 1)/2);

	// check gap count to calculate median 
	if (nGapCount % 2 != 0)
	{
		// odd number of gaps 
		nMedianGapWidth = nArrayGapWidthSorted[(int)(dMedianIndex - 1)];
	}
	else
	{
		// even number of gaps - avg left and right values next to median index 
		nMedianGapWidth = (nArrayGapWidthSorted[(int)floor(dMedianIndex - 1)] + nArrayGapWidthSorted[(int)ceil(dMedianIndex - 1)])/2;
	}

	// allocate dynamically array based on gap count  
	nArrayGapWithDiff = (int *) calloc(nGapCount, sizeof(int));

	// assign difference between gap and gap median 
	for (nIndexI = 0; nIndexI < nGapCount; nIndexI++)
	{
		nArrayGapWithDiff[nIndexI] = abs(nArrayGapWidthSorted[nIndexI] - nMedianGapWidth);
	}

	// quick sort of gap width array in ascending order 
	qsort(nArrayGapWithDiff, nGapCount, sizeof(int), nCompareFunction);

	// check gap count to calculate median 
	if (nGapCount % 2 != 0)
	{
		// odd number of gaps 
		nMedianAbsDev = nArrayGapWithDiff[(int)(dMedianIndex - 1)];
	}
	else
	{
		// even number of gaps  - avg left and right values next to median index 
		nMedianAbsDev = (nArrayGapWithDiff[(int)floor(dMedianIndex - 1)] + nArrayGapWithDiff[(int)ceil(dMedianIndex - 1)])/2;
	}

	// allocate dynamically array based on gap count  
	dArrayModifiedZScore  = (double *) calloc(nGapCount, sizeof(double));

	// calculate modified z score for each gap width 
	for (nIndexI = 0; nIndexI < nGapCount; nIndexI++)
	{
		dArrayModifiedZScore[nIndexI] = (0.6745 * (nArrayGapWidth[nIndexI] - nMedianGapWidth)) / nMedianAbsDev;

		// check if calculated score is inside threshold 
		if (abs(dArrayModifiedZScore[nIndexI]) < 3.5)
		{
			// keep count 
			nGapCountAdj = nGapCountAdj + 1;

			// allocate dynamically array based on adjusted gap count
			if (nGapCountAdj == 1)
			{
				nArrayGapWidthAdj = (int *) calloc(nGapCountAdj, sizeof(int));
			}
			else
			{
				// reallocate memory for subsequent passes
				nArrayGapWidthAdj = (int *) realloc(nArrayGapWidthAdj, nGapCountAdj*sizeof(int));
			}

			nArrayGapWidthAdj[nGapCountAdj - 1] = nArrayGapWidth[nIndexI];
		}
	}

	// calculate cumulative sum of adjusted gap width array 
	for (nIndexI = 0; nIndexI < nGapCountAdj; nIndexI++)
	{
		nSum = nSum + nArrayGapWidthAdj[nIndexI];
	}

	// calculate mean 
	dGapWidthAvg = ((double)nSum/(double)nGapCountAdj);

	// calculate cumulative difference 
	for (nIndexI = 0; nIndexI < nGapCountAdj; nIndexI++)
	{
		dDiff = dDiff + pow(((double)(nArrayGapWidthAdj[nIndexI]) - dGapWidthAvg), 2);
	}
	
	// calculate standard deviation 
	dGapWidthStdDev = sqrt(dDiff/(double)nGapCountAdj);

	// calculate left & right fence gap width distribution values 
	dLeftFence = dGapWidthAvg - 2 * dGapWidthStdDev;
	dRightFence = dGapWidthAvg + 2 * dGapWidthStdDev;

	// assign minimum gap thickness 
	nGapWidthMin = floor(dLeftFence);

	// eliminate platos at binary array with less than min number of consecutive points at preceding gap
	for (nIndexI = 1; nIndexI < nDataLineRead; nIndexI++)
	{
		// check first plato to gap drop 
		if ((nArrayAccelBinary[nIndexI-1] == 1) && (nArrayAccelBinary[nIndexI] == 0))
		{
			// keep track of data points in gap
			nConsecutivePointsGap = 1;
			for (nIndexJ = nIndexI + 1; nIndexJ < nDataLineRead; nIndexJ++)
			{
				// as soon 1 is found stop counting consecutive points 
				if (nArrayAccelBinary[nIndexJ] == 1)
				{
					break;
				}
				else
				{
					nConsecutivePointsGap = nConsecutivePointsGap + 1;
				}
			}

			// check for unfinished gap at the end of array  
			if (nIndexJ < nDataLineRead)
			{
			}
			else
			{
				// next iteration  
				continue;
			}

			// keep track of data points in proceding plato
			nConsecutivePointsPlato = 1;
			for (nIndexK = nIndexJ + 1; nIndexK < nDataLineRead; nIndexK++)
			{
				// as soon 0 is found stop counting consecutive points 
				if (nArrayAccelBinary[nIndexK] == 0)
				{
					break;
				}
				else
				{
					nConsecutivePointsPlato = nConsecutivePointsPlato + 1;
				}
			}

			// eliminate platos with not enough number of consecutive points on preceding gap
			if (nConsecutivePointsGap < nGapWidthMin)
			{
				for (nIndexL = nIndexI; nIndexL <= (nIndexI + nConsecutivePointsGap + nConsecutivePointsPlato); nIndexL++)
				{
					// check for end of data file  
					if (nIndexL < nDataLineRead)
					{
					}
					else
					{
						// next iteration  
						break;
					}

					nArrayAccelBinary[nIndexL] = 0;			
				}

				// rewind main loop index 
				nIndexI = nIndexI - 1;
			}
		}
	}
	
	// traverse binary array and find step indeces
	for (nIndexI = 0; nIndexI < nDataLineRead; nIndexI++)
	{
		// look ahead for 1 to 0 transition = exit point from accel total valley
		if ((nStridePhase == 1) && (nArrayAccelBinary[nIndexI] == 1) && (nArrayAccelBinary[nIndexI+1] == 0))
		{
			// increment stride count
			nStrideIndex = nStrideIndex + 1;

			// increment stride start index
			nStrideStartIndex = nStrideStartIndex + 1;

			// allocate dynamically array based on stride index
			if (nStrideIndex == 1)
			{
				nArrayStrideStart = (int *) calloc(nStrideIndex, sizeof(int));
			}
			else
			{
				// reallocate memory besed on new identified number of valid stride starts
				nArrayStrideStart = (int *) realloc(nArrayStrideStart, nStrideIndex*sizeof(int));
			}

			// assign index
			nArrayStrideStart[nStrideIndex-1] = nIndexI;

			// now looking for stride stop  
			nStridePhase = 2; 
		}

		// look ahead for 0 to 1 transition = entry point from accel total valley
		if ((nStridePhase == 2) && (nArrayAccelBinary[nIndexI] == 0) && (nArrayAccelBinary[nIndexI+1] == 1))
		{
			// increment stride start index
			nStrideStopIndex = nStrideStopIndex + 1;

			// allocate dynamically array based on stride index
			if (nStrideIndex == 1)
			{
				nArrayStrideStop = (int *) calloc(nStrideIndex, sizeof(int));
			}
			else
			{
				// reallocate memory besed on new identified number of valid stride stops
				nArrayStrideStop = (int *) realloc(nArrayStrideStop, nStrideIndex*sizeof(int));
			}

			// assign index
			nArrayStrideStop[nStrideIndex-1] = nIndexI;

			// now looking for beginning of next stride 
			nStridePhase = 1;
		}
	}

stride:

	// assign number of strides 
	*nStrideCount = nStrideIndex;

	// no strides found 
	if (*nStrideCount == 0)
	{
		return; 
	}

	// save number of strides identified 
	if (nStrideStartIndex != nStrideStopIndex)
	{
		// ignore last stride if number of start & stop do not match
		*nStrideCount = *nStrideCount - 1;
	}

	// initialize accel total peak index array
	nArrayStridePeak = (int *) calloc(*nStrideCount, sizeof(int));

	// find accel total peak index between step start & stop indeces
	for (nIndexI = 0; nIndexI < *nStrideCount; nIndexI++)
	{
		dAccelPeak = (*idata)[nArrayStrideStart[nIndexI]].dAccelT;
		for (nIndexJ = nArrayStrideStart[nIndexI]; nIndexJ <= nArrayStrideStop[nIndexI]; nIndexJ++)
		{
			if (dAccelPeak < (*idata)[nIndexJ].dAccelT)
			{
				dAccelPeak = (*idata)[nIndexJ].dAccelT;
				nArrayStridePeak[nIndexI] = nIndexJ;
			}
		}
	}

	// dynamically allocate data structure 
	(*istride) = (struct stride *)malloc((*nStrideCount) *sizeof(struct stride));

	// assign contents of start and stop arrays to stride structure
	for (nIndexI = 0; nIndexI < *nStrideCount; nIndexI++)
	{
		(*istride)[nIndexI].nStride = nIndexI;
		(*istride)[nIndexI].nStart = nArrayStrideStart[nIndexI];
		(*istride)[nIndexI].nPeak = nArrayStridePeak[nIndexI];
		(*istride)[nIndexI].nStop = nArrayStrideStop[nIndexI];
	}

	// look ahead for force peak 
	for (nIndexI = 0; nIndexI < nDataLineRead - 1; nIndexI++)
	{
		if ((nStrideForcePhase == 1) && ((*idata)[nIndexI].nFst > dFstMaximum))
		{
			// now looking for peak  
			nStrideForcePhase = 2; 
		}

		if ((nStrideForcePhase == 2) && ((*idata)[nIndexI + 1].nFst < (*idata)[nIndexI].nFst))
		{
			// increment stride index
			nStrideForceIndex = nStrideForceIndex + 1;

			// allocate dynamically array based on stride index
			if (nStrideForceIndex == 1)
			{
				nArrayStrideForcePeak = (int *) calloc(nStrideForceIndex, sizeof(int));
			}
			else
			{
				// reallocate memory besed on new identified number of valid stride starts
				nArrayStrideForcePeak = (int *) realloc(nArrayStrideForcePeak, nStrideForceIndex*sizeof(int));
			}

			// assign index
			nArrayStrideForcePeak[nStrideForceIndex-1] = nIndexI;

			// now looking for force decrease  
			nStrideForcePhase = 3; 
		}

		if ((nStrideForcePhase == 3) && ((*idata)[nIndexI].nFst < dFstQuiescent))
		{
			// look for force increase
			nStrideForcePhase = 1;
		}
	}

	// assign number of force peaks found  
	*nStrideForcePeaks = nStrideForceIndex;

	// dynamically allocate data structure 
	(*istrideForce) = (struct strideForce *)malloc((*nStrideForcePeaks) *sizeof(struct strideForce));

	// assign contents of peak arrays to stride structure
	for (nIndexI = 0; nIndexI < *nStrideForcePeaks; nIndexI++)
	{
		(*istrideForce)[nIndexI].nStride = nIndexI;
		(*istrideForce)[nIndexI].nGroundContact = nArrayStrideForcePeak[nIndexI];
	}
	
	// deallocate memory
	free(nArrayStrideStart);
	free(nArrayStridePeak);
	free(nArrayStrideStop);
	free(nArrayStrideForcePeak);
}

///////////////////////////////////////////
// median and interquartile mean calculation 
///////////////////////////////////////////
void DistAvg(double dArray[], int nMax, double * dMedian, double * dIQRMean)
{
	int nIndexI = 0; // general index
	double dMedianIndex = 0; // median index
	double dDepth = 0; // depth index
	int nLowerQuartileIndex = 0; // lower & upper quartile indeces
	int nUpperQuartileIndex = 0;
	double dSum = 0; // cumulative sum 

	// calculate median index 
	dMedianIndex = ((nMax + 1)/2);

	// check number of values to calculate median 
	if (nMax % 2 != 0)
	{
		// odd number of values 
		*dMedian = dArray[(int)(dMedianIndex - 1)];
	}
	else
	{
		// even number of values - avg left and right values next to median index 
		*dMedian = (dArray[(int)floor(dMedianIndex - 1)] + dArray[(int)ceil(dMedianIndex - 1)])/2;
	}

	// calculate median depth 
	dDepth = (floor(dMedianIndex) + 1)/2;

	// calculate lower & upper quartile indeces
	if (nMax % 2 != 0)
	{
		nLowerQuartileIndex = dDepth - 1;
		nUpperQuartileIndex = nMax - dDepth;
	}
	else
	{
		nLowerQuartileIndex = ceil(dDepth) - 1;
		nUpperQuartileIndex = nMax - ceil(dDepth);
	}

	// calculate cumulative sum based on interquartile range 
	for (nIndexI = nLowerQuartileIndex; nIndexI <= nUpperQuartileIndex; nIndexI++)
	{
		dSum = dSum + dArray[nIndexI];
	}

	// calculate interquartile mean 
	*dIQRMean = dSum / (nUpperQuartileIndex - nLowerQuartileIndex + 1);
}

///////////////////////////////////////////
// distance algorithm for a particular stride within a data set
///////////////////////////////////////////
void DistAlgo(struct stride ** istride, struct data ** idata, int nStride, double dSamplePeriod)
{
	double dIndex = 0; // general double index
	int nIndexI = 0; // general integer index
	int nIndexJ = 0; // general integer index

	int nStrideStart = 0; // stride start for integration 
	int nStridePeak = 0; // stride accel total peak index 
	int nStrideStop = 0; // stride stop for integration 
	int nStrideEnd = 0; // stride end for integration 
	int nStrideSize = 0; // stride point size 
	int nPrevStrideStop = 0; // previous stride stop 
	int nNextStrideStart = 0; // next stride start 

	double dStrideTime = 0; // stride total time in sec
	double dStrideTimeSwing = 0; // stride swing time in sec

	double *dArrayGyroX; // stride gyro x
	double *dArrayGyroXOffset; // gx with offset 
	double *dArrayAccelY; // stride acceleratio in y
	double *dArrayAccelZ; // stride acceleration in z
	
	double dPhiInitial = 0; // initial stride angle 
	double dPhiFinal = 0; // final stride angle
	double dSum = 0; // cumulative trapezoidal integration sum

	double *dArrayAccelYMidstance; // stride acceleration in y
	double *dArrayAccelYMidstanceNext; // next stride acceleration in y
	int nMidstancePointIndex = 0; // midstance stride point count 
	int nMidstanceNextPointIndex = 0; // midstance next stride point count
	double dAccelYMidstanceAvg = 0; // average stride acceleration in y
	double dAccelYMidstanceNextAvg = 0; // average next stride acceleration in y
		
	double *dArrayPhi; // stride tilt angle increments
	double *dArrayPhiRad; // stride tilt angle increments in radians
	double *dArrayAccelFoward; // stride forward acceleration increments
	double *dArrayVelocityFoward; // stride forward velocity increments
	double *dArrayDistanceFoward; // stride forward distance increments

	double dStrideMaxForceBall = 0; // max force value of the stride on the ball of the foot for each stride
	double dStrideMaxForceHeel = 0; // max force value of the stride on the heel of the foot for each stride
	double dStrideMaxForce = 0; // max total force value of the stride

	double dStride = 0; // stride stride distance

	double dGyroXOffset = 0; // gyro offset to optimize
	double dGyroXOffsetBest = 9999; // best gy offset found 
	int nStrideOffset = 0; // stride offset to optimize
	int nStrideOffsetBest = 9999; // best stride offset found
	double dVelFinalEndBest = 10000; // best end final velocity

	// get current stride information 
	nStrideStart = (*istride)[nStride].nStart; // stride start index
	nStridePeak = (*istride)[nStride].nPeak; // stride accel total peak index
	nStrideStop = (*istride)[nStride].nStop; // stride stop index
	
	// get previous & next stride information 	
	nPrevStrideStop =  (*istride)[nStride-1].nStop; // stop of previous stride
	nNextStrideStart = (*istride)[nStride+1].nStart; // start of next stride

	nStrideEnd = nStridePeak + floor((nStrideStop - nStridePeak)/3); // stride end of integration 
	nStrideSize = nStrideEnd - nStrideStart + 1; // stride point size
		
	// dynamically allocate corresponding arrays using the current stride size 
	dArrayGyroX = (double *) calloc(nStrideSize, sizeof(double));
	dArrayAccelY = (double *) calloc(nStrideSize, sizeof(double));
	dArrayAccelZ = (double *) calloc(nStrideSize, sizeof(double));

	dArrayPhi = (double *) calloc(nStrideSize, sizeof(double));
	dArrayPhiRad = (double *) calloc(nStrideSize, sizeof(double));
	dArrayAccelFoward = (double *) calloc(nStrideSize, sizeof(double));
	dArrayVelocityFoward = (double *) calloc(nStrideSize, sizeof(double));
	dArrayDistanceFoward = (double *) calloc(nStrideSize, sizeof(double));

	dArrayGyroXOffset = (double *) calloc(nStrideSize, sizeof(double));

	// swing occurs between start and stop indeces
	dStrideTimeSwing = (double) (nStrideStop - nStrideStart) / SAMPLE_FREQ;
	
	// stride time is stop of current to stop of previous
	dStrideTime = (double) (nStrideStop - nPrevStrideStop) / SAMPLE_FREQ;
	
	// dynamically allocate array from previous stop and start of current stride
	dArrayAccelYMidstance = (double *) calloc((nStrideStart - nPrevStrideStop) + 1, sizeof(double));

	// for each stride get previous stop to start of current 
	for (nIndexI = nPrevStrideStop; nIndexI <= nStrideStart; nIndexI++) 
	{
		dArrayAccelYMidstance[nMidstancePointIndex] = (*idata)[nIndexI].dAccelY; 
		nMidstancePointIndex = nMidstancePointIndex + 1;
	}

	// dynamically allocate array 
	dArrayAccelYMidstanceNext = (double *) calloc((nNextStrideStart - nStrideStop) + 1, sizeof(double));
	
	// for each stride get stop of current to next start 
	for (nIndexI = nStrideStop; nIndexI <= nNextStrideStart; nIndexI++)
	{
		dArrayAccelYMidstanceNext[nMidstanceNextPointIndex] = (*idata)[nIndexI].dAccelY;
		nMidstanceNextPointIndex = nMidstanceNextPointIndex + 1;
	}
			
	// subsequent calculations will be performed on the "motion" part of the stride - when total accel is greater than 1 G
	
	FillArray(idata, dArrayGyroX, nStrideStart, nStrideSize, 1); // stride gyro x data
	FillArray(idata, dArrayAccelY, nStrideStart, nStrideSize, 3); // stride accel y data
	FillArray(idata, dArrayAccelZ, nStrideStart, nStrideSize, 4); // stride accel z data
		
	//
	// step 2
	//

	// the initial angle is based on the average accel y readings preceding the motion
	dAccelYMidstanceAvg = dMean(dArrayAccelYMidstance, nMidstancePointIndex);
	
	// check if absolute value of accel y is less or equal to 1 to computer initial tilt angle
	if (fabs(dAccelYMidstanceAvg/G) <= 1)
	{
		dPhiInitial = asin(dAccelYMidstanceAvg/G) * (180/PI); 
	}
	else
	{
		dPhiInitial = 0;
	}

	// final angle is based on the average of accel y readings after motion 
	dAccelYMidstanceNextAvg = dMean(dArrayAccelYMidstanceNext, nMidstanceNextPointIndex);
	
	// check if absolute value of accel y is less or equal to 1 to computer final tilt angle
	if (fabs(dAccelYMidstanceNextAvg/G) <= 1)
	{
		dPhiFinal = asin(dAccelYMidstanceNextAvg/G) * (180/PI); 
	}
	else
	{
		dPhiFinal = 0;
	}

	//
	// step 3
	//
	
	// calculate initial stride value (no optimization)

	// reset cumulative integration sum
	dSum = 0;

	// find stride motion tilt angles 
	for (nIndexI = 0; nIndexI < nStrideSize; nIndexI++)
	{
		dSum = dSum + dTrapz(dArrayGyroX, nIndexI);
		dArrayPhi[nIndexI] = dPhiInitial - (dSum * dSamplePeriod); 
		dArrayPhiRad[nIndexI] = dArrayPhi[nIndexI] * (PI/180);
	}

	// forward acceleration vector resolution
	for (nIndexI = 0; nIndexI < nStrideSize; nIndexI++)
	{
		dArrayAccelFoward[nIndexI] = -1*dArrayAccelY[nIndexI]*cos(dArrayPhiRad[nIndexI]) + dArrayAccelZ[nIndexI]*sin(dArrayPhiRad[nIndexI]);
	}
	
	// reset cumulative integration sum
	dSum = 0;

	// forward velocity integration
	for (nIndexI = 0; nIndexI < nStrideSize; nIndexI++)
	{
		dSum = dSum + dTrapz(dArrayAccelFoward, nIndexI);
		dArrayVelocityFoward[nIndexI] = dSum * dSamplePeriod;
	}

	// reset cumulative integration sum
	dSum = 0;

	// forward distance integration
	for (nIndexI = 0; nIndexI < nStrideSize; nIndexI++)
	{
		dSum = dSum + dTrapz(dArrayVelocityFoward, nIndexI);
		dArrayDistanceFoward[nIndexI] = dSum * dSamplePeriod;
	}

	// final distance in inches
	dStride = dArrayDistanceFoward[nStrideSize-1] * 1000/25.4; 
	
	// check if optimization has been selected
	if (OPTIMIZATION > 0) 
	{
		goto opt;
	}
	else
	{
		goto none;
	}

opt: 
	
	switch(OPTIMIZATION)
	{
	case 1: // change gyro offset & optimize based on final velocity = 0

		// initialize offsets
		nStrideOffsetBest = 0;

		for (dIndex = -50; dIndex <= 50; dIndex += 0.1)
		{
			dGyroXOffset = dIndex; // adjust offset between -50 and 50 deg/s
				
			// apply offset to gyro x data
			for (nIndexI = 0; nIndexI < nStrideSize; nIndexI++)
			{	
				dArrayGyroXOffset[nIndexI] = dArrayGyroX[nIndexI] + dGyroXOffset;
			}
		
			// reset cumulative integration sum
			dSum = 0;

			// find stride motion tilt angles 
			for (nIndexI = 0; nIndexI < nStrideSize; nIndexI++)
			{
				dSum = dSum + dTrapz(dArrayGyroXOffset, nIndexI);
				dArrayPhi[nIndexI] = dPhiInitial - (dSum * dSamplePeriod); 
				dArrayPhiRad[nIndexI] = dArrayPhi[nIndexI] * (PI/180);
			}

			// forward acceleration vector resolution
			for (nIndexI = 0; nIndexI < nStrideSize; nIndexI++)
			{
				dArrayAccelFoward[nIndexI] = -1*dArrayAccelY[nIndexI]*cos(dArrayPhiRad[nIndexI]) + dArrayAccelZ[nIndexI]*sin(dArrayPhiRad[nIndexI]);
			}
	
			// reset cumulative integration sum
			dSum = 0;

			// forward velocity integration
			for (nIndexI = 0; nIndexI < nStrideSize; nIndexI++)
			{
				dSum = dSum + dTrapz(dArrayAccelFoward, nIndexI);
				dArrayVelocityFoward[nIndexI] = dSum * dSamplePeriod;
			}

			// remember the gyro offset that best zeroes out end velocity 
			if (fabs(dArrayVelocityFoward[nStrideSize-1]) < dVelFinalEndBest)
			{
				dVelFinalEndBest = fabs(dArrayVelocityFoward[nStrideSize-1]);
				dGyroXOffsetBest = dGyroXOffset;
			}
		}

		break;

	case 2: 

		// initialize offsets
		dGyroXOffsetBest = 0;

		for (nIndexJ = -10; nIndexJ <= 10; nIndexJ++)
		{
			// adjust stride offset 
			nStrideOffset = nIndexJ; 

			// reallocate arrays for optimization based on current stride offset 
			dArrayGyroX = (double *) realloc(dArrayGyroX, (nStrideSize + nStrideOffset)*sizeof(double));
			dArrayAccelY = (double *) realloc(dArrayAccelY, (nStrideSize + nStrideOffset)*sizeof(double));
			dArrayAccelZ = (double *) realloc(dArrayAccelZ, (nStrideSize + nStrideOffset)*sizeof(double));
			dArrayPhi = (double *) realloc(dArrayPhi, (nStrideSize + nStrideOffset)*sizeof(double));
			dArrayPhiRad = (double *) realloc(dArrayPhiRad, (nStrideSize + nStrideOffset)*sizeof(double));
			dArrayAccelFoward = (double *) realloc(dArrayAccelFoward, (nStrideSize + nStrideOffset)*sizeof(double));
			dArrayVelocityFoward = (double *) realloc(dArrayVelocityFoward, (nStrideSize + nStrideOffset)*sizeof(double));
			dArrayDistanceFoward = (double *) realloc(dArrayDistanceFoward, (nStrideSize + nStrideOffset)*sizeof(double));
		
			// fill corresponding arrays
			FillArray(idata, dArrayGyroX, nStrideStart, (nStrideSize + nStrideOffset), 1); // stride gyro x data
			FillArray(idata, dArrayAccelY, nStrideStart, (nStrideSize + nStrideOffset), 3); // stride accel y data
			FillArray(idata, dArrayAccelZ, nStrideStart, (nStrideSize + nStrideOffset), 4); // stride accel z data

			// reset cumulative integration sum
			dSum = 0;

			// find stride motion tilt angles 
			for (nIndexI = 0; nIndexI < nStrideSize + nStrideOffset; nIndexI++)
			{
				dSum = dSum + dTrapz(dArrayGyroX, nIndexI);
				dArrayPhi[nIndexI] = dPhiInitial - (dSum * dSamplePeriod); 
				dArrayPhiRad[nIndexI] = dArrayPhi[nIndexI] * (PI/180);
			}

			// forward acceleration vector resolution
			for (nIndexI = 0; nIndexI < nStrideSize + nStrideOffset; nIndexI++)
			{
				dArrayAccelFoward[nIndexI] = -1*dArrayAccelY[nIndexI]*cos(dArrayPhiRad[nIndexI]) + dArrayAccelZ[nIndexI]*sin(dArrayPhiRad[nIndexI]);
			}
	
			// reset cumulative integration sum
			dSum = 0;

			// forward velocity integration
			for (nIndexI = 0; nIndexI < nStrideSize + nStrideOffset; nIndexI++)
			{
				dSum = dSum + dTrapz(dArrayAccelFoward, nIndexI);
				dArrayVelocityFoward[nIndexI] = dSum * dSamplePeriod;
			}

			// remember the stride offset that best zeroes out end velocity 
			if (fabs(dArrayVelocityFoward[nStrideSize + nStrideOffset - 1]) < dVelFinalEndBest)
			{
				dVelFinalEndBest = fabs(dArrayVelocityFoward[nStrideSize + nStrideOffset - 1]);
				nStrideOffsetBest = nStrideOffset;
			}
		}

		break;
	}

	// reallocate arrays for results of optimization 
	dArrayGyroX = (double *) realloc(dArrayGyroX, (nStrideSize + nStrideOffsetBest)*sizeof(double));
	dArrayAccelY = (double *) realloc(dArrayAccelY, (nStrideSize + nStrideOffsetBest)*sizeof(double));
	dArrayAccelZ = (double *) realloc(dArrayAccelZ, (nStrideSize + nStrideOffsetBest)*sizeof(double));
	dArrayPhi = (double *) realloc(dArrayPhi, (nStrideSize + nStrideOffsetBest)*sizeof(double));
	dArrayPhiRad = (double *) realloc(dArrayPhiRad, (nStrideSize + nStrideOffsetBest)*sizeof(double));
	dArrayAccelFoward = (double *) realloc(dArrayAccelFoward, (nStrideSize + nStrideOffsetBest)*sizeof(double));
	dArrayVelocityFoward = (double *) realloc(dArrayVelocityFoward, (nStrideSize + nStrideOffsetBest)*sizeof(double));
	dArrayDistanceFoward = (double *) realloc(dArrayDistanceFoward, (nStrideSize + nStrideOffsetBest)*sizeof(double));
	
	// fill corresponding arrays
	FillArray(idata, dArrayGyroX, nStrideStart, (nStrideSize + nStrideOffsetBest), 1); // stride gyro x data
	FillArray(idata, dArrayAccelY, nStrideStart, (nStrideSize + nStrideOffsetBest), 3); // stride accel y data
	FillArray(idata, dArrayAccelZ, nStrideStart, (nStrideSize + nStrideOffsetBest), 4); // stride accel z data

	// apply best gy offset found 
	for (nIndexI = 0; nIndexI < (nStrideSize + nStrideOffsetBest); nIndexI++)
	{
		dArrayGyroX[nIndexI] = dArrayGyroX[nIndexI] + dGyroXOffsetBest;
	}

	// reset cumulative integration sum
	dSum = 0;

	// find stride motion tilt angles 
	for (nIndexI = 0; nIndexI < (nStrideSize + nStrideOffsetBest); nIndexI++)
	{
		dSum = dSum + dTrapz(dArrayGyroX, nIndexI);
		dArrayPhi[nIndexI] = (dPhiInitial) - (dSum*dSamplePeriod); 
		dArrayPhiRad[nIndexI] = dArrayPhi[nIndexI] * (PI/180);
	}
	
	// forward acceleration vector resolution
	for (nIndexI = 0; nIndexI < (nStrideSize + nStrideOffsetBest); nIndexI++)
	{
		dArrayAccelFoward[nIndexI] = -1*dArrayAccelY[nIndexI]*cos(dArrayPhiRad[nIndexI]) + dArrayAccelZ[nIndexI]*sin(dArrayPhiRad[nIndexI]);
	}
	
	// reset cumulative integration sum
	dSum = 0;

	// forward velocity integration
	for (nIndexI = 0; nIndexI < (nStrideSize + nStrideOffsetBest); nIndexI++)
	{
		dSum = dSum + dTrapz(dArrayAccelFoward, nIndexI);
		dArrayVelocityFoward[nIndexI] = dSum * dSamplePeriod;
	}
	
	// reset cumulative integration sum
	dSum = 0;

	// forward distance integration
	for (nIndexI = 0; nIndexI < (nStrideSize + nStrideOffsetBest); nIndexI++)
	{
		dSum = dSum + dTrapz(dArrayVelocityFoward, nIndexI);
		dArrayDistanceFoward[nIndexI] = dSum * dSamplePeriod;
	}

	dStride = dArrayDistanceFoward[nStrideSize + nStrideOffsetBest - 1] * 1000/25.4; // final distance in inches

none:
	// compute max force values considering all stride 
	for (nIndexI = nStrideStart; nIndexI <= nStrideStop; nIndexI++) 
	{
		// find the max force values of the foot 
		if (nIndexI == nStrideStart)
		{
			dStrideMaxForceBall = (*idata)[nIndexI].nFsf;
			dStrideMaxForceHeel = (*idata)[nIndexI].nFsr;
			dStrideMaxForce = (*idata)[nIndexI].nFst;
		}
		else
		{
			// ball force sensors max
			if ((*idata)[nIndexI].nFsf > dStrideMaxForceBall)
			{
				dStrideMaxForceBall = (*idata)[nIndexI].nFsf;
			}
				
			// heel force sensors max
			if ((*idata)[nIndexI].nFsr > dStrideMaxForceHeel)
			{
				dStrideMaxForceHeel = (*idata)[nIndexI].nFsr;
			}

			// total force max
			if ((*idata)[nIndexI].nFst > dStrideMaxForce)
			{
				dStrideMaxForce = (*idata)[nIndexI].nFst;
			}
		}		
	}

	// assign to stride structure calculated data
	(*istride)[nStride].dStrideTimeSwing = dStrideTimeSwing;
	(*istride)[nStride].dStrideTime = dStrideTime;
	(*istride)[nStride].dStride = dStride;

	// assign max force (ball and heel) values to stride structure
	(*istride)[nStride].dStrideMaxForceBall = dStrideMaxForceBall;
	(*istride)[nStride].dStrideMaxForceHeel = dStrideMaxForceHeel;
	(*istride)[nStride].dStrideMaxForce = dStrideMaxForce;

	// deallocate memory
	free(dArrayAccelYMidstance);
	free(dArrayAccelYMidstanceNext);
	free(dArrayGyroX);
	free(dArrayAccelY);
	free(dArrayAccelZ);
	free(dArrayPhi);
	free(dArrayPhiRad);
	free(dArrayAccelFoward);
	free(dArrayVelocityFoward);
	free(dArrayDistanceFoward);
}

///////////////////////////////////////////
// statistical output for exercise based on accel
///////////////////////////////////////////
void DistOutAvg(char * strOutputFileName, double dIQRAvgStrideTimeL, double dIQRAvgStrideSwingTimeL, double dIQRAvgStrideDistanceL, double dIQRAvgStrideForceL, double dFstMaximumL, int nDataLineReadL, double dIQRAvgStrideTimeR, double dIQRAvgStrideSwingTimeR, double dIQRAvgStrideDistanceR, double dIQRAvgStrideForceR, double dFstMaximumR, int nDataLineReadR, double dIQRAvgStepTimeLR, double dIQRAvgStepTimeRL)
{
	// LEFT
	double dClockTimeL = 0; // clock time 
	double dStrideCadenceAvgL = 0; // avg cadence 
	int nStrideCountL = 0; // stride count 
	double dStridePercentSwingAvgL = 0; // avg swing time
	double dStridePercentForceAvgL = 0; // avg force 
	
	// RIGHT
	double dClockTimeR = 0; // clock time
	double dStrideCadenceAvgR = 0; // avg cadence 
	int nStrideCountR = 0; // stride count 
	double dStridePercentSwingAvgR = 0; // avg swing time 
	double dStridePercentForceAvgR = 0; // avg force 
	
	// open output file 
	fod = fopen(strOutputFileName,"w");

	// calculate clock time based on number of data points collected and frequency
	dClockTimeL = ((double)nDataLineReadL / (double)SAMPLE_FREQ);
	dClockTimeR = ((double)nDataLineReadR / (double)SAMPLE_FREQ);
		
	// calculate avg cadence based on avg stride time
	dStrideCadenceAvgL = (60/dIQRAvgStrideTimeL);
	dStrideCadenceAvgR = (60/dIQRAvgStrideTimeR);

	// calculate number of strides based on average cadence and clock time
	nStrideCountL = (int)(dStrideCadenceAvgL * (dClockTimeL/60));
	nStrideCountR = (int)(dStrideCadenceAvgR * (dClockTimeR/60));
	
	// calculate avg percent swing time based on avg swing and total stride time
	dStridePercentSwingAvgL = (dIQRAvgStrideSwingTimeL / dIQRAvgStrideTimeL)*100;
	dStridePercentSwingAvgR = (dIQRAvgStrideSwingTimeR / dIQRAvgStrideTimeR)*100;

	// calculate avg percent stride force based on stanstill max force
	dStridePercentForceAvgL = (dIQRAvgStrideForceL/dFstMaximumL)*100;
	dStridePercentForceAvgR = (dIQRAvgStrideForceR/dFstMaximumR)*100;

	// write to file
	fprintf(fod, "%%\n");
	fprintf(fod, "%% MedHab gait algorithm output file\n");
	fprintf(fod, "%%\n");
	fprintf(fod, "%% Numbers below contain the following information\n");
	fprintf(fod, "%% -clock time (units: seconds)\n");
	fprintf(fod, "%% -avg cadence time (units: strides per minute)\n");
	fprintf(fod, "%% -number of strides (units: none)\n");
	fprintf(fod, "%% -LF avg swing time (units: percent relative to total stride time)\n");
	fprintf(fod, "%% -RF avg swing time (units: percent relative to total stride time)\n");
	fprintf(fod, "%% -LF-RF avg step time (units: seconds)\n");
	fprintf(fod, "%% -RF-LF avg step time (units: seconds)\n");
	fprintf(fod, "%% -LF avg maximum pressure (units: percent relative to standing pressure)\n");
	fprintf(fod, "%% -RF avg maximum pressure (units: percent relative to standing pressure)\n");
	fprintf(fod, "%% -LF avg stride distance (units: inches; estimated)\n");
	fprintf(fod, "%% -RF avg stride distance (units: inches; estimated)\n");
	fprintf(fod, "%%\n");
	
	fprintf(fod, "%4.1f\n", dClockTimeL);
	fprintf(fod, "%4.1f\n", dStrideCadenceAvgL);
	fprintf(fod, "%d\n", nStrideCountL);
	fprintf(fod, "%4.1f\n", dStridePercentSwingAvgL);
	fprintf(fod, "%4.1f\n", dStridePercentSwingAvgR);
	fprintf(fod, "%4.2f\n", dIQRAvgStepTimeLR);
	fprintf(fod, "%4.2f\n", dIQRAvgStepTimeRL);
	fprintf(fod, "%4.1f\n", dStridePercentForceAvgL);
	fprintf(fod, "%4.1f\n", dStridePercentForceAvgR);
	fprintf(fod, "%4.1f\n", dIQRAvgStrideDistanceL); 
	fprintf(fod, "%4.1f\n", dIQRAvgStrideDistanceR); 
	
	// close output file
	fclose(fod);
}

///////////////////////////////////////////
// distance output for each stride
///////////////////////////////////////////
void DistOut(char * strOutputFileName, struct stride ** istride, int nStrideCount, double dIQRAvgStrideDistance, double dIQRAvgStrideTime)
{
	int nIndex = 0; // general index
	int nIndexI = 0; 
	double dStrideCadence = 0; // strides per min 
	double dPercent = 30.0; // percent limit 
	double dLowStrideDistanceLimit = 0; // stride distance limits 
	double dUpStrideDistanceLimit = 0; 
	double dLowStrideTimeLimit = 0; // stride time limits 
	double dUpStrideTimeLimit = 0; 

	// calculate limits
	dLowStrideDistanceLimit = dIQRAvgStrideDistance - ((dPercent/100) * dIQRAvgStrideDistance);
	dUpStrideDistanceLimit = dIQRAvgStrideDistance + ((dPercent/100) * dIQRAvgStrideDistance);

	dLowStrideTimeLimit = dIQRAvgStrideTime - ((dPercent/100) * dIQRAvgStrideTime);
	dUpStrideTimeLimit = dIQRAvgStrideTime + ((dPercent/100) * dIQRAvgStrideTime);

	// open debug file 
	fod = fopen(strOutputFileName,"a");

	// debug file banner
	fprintf(fod, "\n");
	fprintf(fod, "Stride No   Swing(s)  Stride(s)   Stride dist(in)    Max force ball(lbf)   Max force heel(lbf)    Cadence(strides per min)\n");
	fprintf(fod, "---------   -------   --------   ----------------   -------------------   --------------------   ------------------------\n");
	
	for (nIndex = 1; nIndex < nStrideCount - 1; nIndex++)
	{
		// check if stride distance and time is within set limits 
		if (((*istride)[nIndex].dStrideTime < dLowStrideTimeLimit) || ((*istride)[nIndex].dStrideTime > dUpStrideTimeLimit) || ((*istride)[nIndex].dStride < dLowStrideDistanceLimit) || ((*istride)[nIndex].dStride > dUpStrideDistanceLimit))
		{
			continue;
		}
		else
		{
			nIndexI = nIndexI + 1;
		}

		// calculate stride cadence 
		dStrideCadence = (60/(*istride)[nIndex].dStrideTime); // strides per min 

		// print to file stride data 
		fprintf(fod, "  %2d          %4.1f         %4.1f            %4.1f                 %2.0f                     %2.0f                      %4.1f\n", (nIndexI), (*istride)[nIndex].dStrideTimeSwing, (*istride)[nIndex].dStrideTime, (*istride)[nIndex].dStride, (*istride)[nIndex].dStrideMaxForceBall, (*istride)[nIndex].dStrideMaxForceHeel, dStrideCadence);
	}
	
	// close debug file
	fclose(fod);
}

// -------------------------------------------------------------------------------

// -------------------------------------------------------------------------------
///////////////////////////////////////////
// calculate and assign total acceleration magnitude 
///////////////////////////////////////////
void AccelTMagnitude(struct data ** idata, int nMax)
{
	int nIndex = 0; // general index

	// traverse data structure calculating accel total 
	for (nIndex=0; nIndex < nMax; nIndex++)
	{
		// calculate total acceleration 
		(*idata)[nIndex].dAccelT = sqrt(pow((*idata)[nIndex].dAccelX,2) + pow((*idata)[nIndex].dAccelY,2) + pow((*idata)[nIndex].dAccelZ,2));
	}
}

///////////////////////////////////////////
// return standstill offset average of data structure member collection  
///////////////////////////////////////////
double dStandStillOffset (struct data ** idata, int nMax, int nPrm)
{
	int nIndex = 0;
	double dSum = 0;
	double dOffset = 0;

	// get data structure member sum 
	for (nIndex=0; nIndex < nMax; nIndex++)
	{
		switch(nPrm)
		{
		case 1:
			dSum = dSum + (*idata)[nIndex].dGyroX;
			break;
		case 5:
			dSum = dSum + (*idata)[nIndex].dAccelT;
			break;
		}
	}

	// get data structure member average
	dOffset = dSum/nMax;

	return dOffset;
}

//////////////////////////////////////////
// apply offset to corresponding data structure member collection
///////////////////////////////////////////
void OffsetApply (struct data ** idata, int nMax, double dOffset, int nPrm)
{
	int nIndex = 0; // general index

	// apply offset to all the data structure member collection 
	for (nIndex = 0; nIndex < nMax; nIndex++)
	{
		switch(nPrm)
		{
		case 1:
			(*idata)[nIndex].dGyroX = (*idata)[nIndex].dGyroX - dOffset;
			break;
		case 5:
			(*idata)[nIndex].dAccelT = (*idata)[nIndex].dAccelT - dOffset;
			break;
		}
	}
}

//////////////////////////////////////////
// build filtered array
///////////////////////////////////////////
void FilterApply (struct data ** idata, int nMax, int nPrm)
{
	double *dArrayFilteredData;
	int nIndex = 0;

	// dynamically allocate filtered data array with a size corresponding to number of data lines read
	dArrayFilteredData = (double *) calloc(nMax, sizeof(double));

	// build filtered data array for each data structure member, applying filter equation
	for (nIndex = 0; nIndex < nMax; nIndex++)
	{
		switch(nPrm)
		{
		case 1: // gyro x
			// initialize first element of filtered data array
			if (nIndex == 0) 
			{
				// if it is first iteration through the sensor data file, assign first point 
				dArrayFilteredData[nIndex] = (*idata)[nIndex].dGyroX;
			} 
			else 
			{
				// output (filtered) value for each gyro x is derived from current input gx, previous input gx, and previous filtered output value 
				dArrayFilteredData[nIndex] = (0.2452*(*idata)[nIndex].dGyroX) + (0.2452*(*idata)[nIndex-1].dGyroX) + (0.5094*dArrayFilteredData[nIndex-1]);
			}
			break;
		case 2: // accel x
			// initialize first element of filtered data array
			if (nIndex == 0) 
			{
				dArrayFilteredData[nIndex] = (*idata)[nIndex].dAccelX;
			} 
			else 
			{
				dArrayFilteredData[nIndex] = (0.2452*(*idata)[nIndex].dAccelX) + (0.2452*(*idata)[nIndex-1].dAccelX) + (0.5094*dArrayFilteredData[nIndex-1]);
			}
			break;
		case 3: // accel y
			// initialize first element of filtered data array
			if (nIndex == 0)
			{
				dArrayFilteredData[nIndex] = (*idata)[nIndex].dAccelY;
			} 
			else
			{
				dArrayFilteredData[nIndex] = (0.2452*(*idata)[nIndex].dAccelY) + (0.2452*(*idata)[nIndex-1].dAccelY) + (0.5094*dArrayFilteredData[nIndex-1]);
			}
				
			break;
		case 4: // accel z
			// initialize first element of filtered data array
			if (nIndex == 0)
			{
				dArrayFilteredData[nIndex] = (*idata)[nIndex].dAccelZ;
			} 
			else
			{		
				dArrayFilteredData[nIndex] = (0.2452*(*idata)[nIndex].dAccelZ) + (0.2452*(*idata)[nIndex-1].dAccelZ) + (0.5094*dArrayFilteredData[nIndex-1]);
			}
			break;
		case 5: // total accel
			// initialize first element of filtered data array
			if (nIndex == 0) 
			{
				dArrayFilteredData[nIndex] = (*idata)[nIndex].dAccelT;
			} 
			else
			{
				dArrayFilteredData[nIndex] = (0.2452*(*idata)[nIndex].dAccelT) + (0.2452*(*idata)[nIndex-1].dAccelT) + (0.5094*dArrayFilteredData[nIndex-1]);
			}
			break;
		case 10: // force sensor front sum 
			// initialize first element of filtered data array
			if (nIndex == 0) 
			{
				dArrayFilteredData[nIndex] = (*idata)[nIndex].nFsf;
			} 
			else
			{
				dArrayFilteredData[nIndex] = (0.2452*(*idata)[nIndex].nFsf) + (0.2452*(*idata)[nIndex-1].nFsf) + (0.5094*dArrayFilteredData[nIndex-1]);
			}
			break;
		case 11: // force sensor rear sum 
			// initialize first element of filtered data array
			if (nIndex == 0) 
			{
				dArrayFilteredData[nIndex] = (*idata)[nIndex].nFsr;
			} 
			else
			{
				dArrayFilteredData[nIndex] = (0.2452*(*idata)[nIndex].nFsr) + (0.2452*(*idata)[nIndex-1].nFsr) + (0.5094*dArrayFilteredData[nIndex-1]);
			}
			break;
		case 12: // force sensor total sum 
			// initialize first element of filtered data array
			if (nIndex == 0) 
			{
				dArrayFilteredData[nIndex] = (*idata)[nIndex].nFst;
			} 
			else
			{
				dArrayFilteredData[nIndex] = (0.2452*(*idata)[nIndex].nFst) + (0.2452*(*idata)[nIndex-1].nFst) + (0.5094*dArrayFilteredData[nIndex-1]);
			}
			break;
		}
	}

	// assign filtered data back to corresponding data structure member collection
	for (nIndex = 0; nIndex < nMax; nIndex++)
	{
		switch(nPrm)
		{
		case 1:
			(*idata)[nIndex].dGyroX = dArrayFilteredData[nIndex];
			break;
		case 2:
			(*idata)[nIndex].dAccelX = dArrayFilteredData[nIndex];
			break;
		case 3:
			(*idata)[nIndex].dAccelY = dArrayFilteredData[nIndex];
			break;
		case 4:
			(*idata)[nIndex].dAccelZ = dArrayFilteredData[nIndex];
			break;
		case 5:
			(*idata)[nIndex].dAccelT = dArrayFilteredData[nIndex];
			break;
		case 10:
			(*idata)[nIndex].nFsf = dArrayFilteredData[nIndex];
			break;
		case 11:
			(*idata)[nIndex].nFsr = dArrayFilteredData[nIndex];
			break;
		case 12:
			(*idata)[nIndex].nFst = dArrayFilteredData[nIndex];
			break;
		}
	}

	// deallocate memory
	free(dArrayFilteredData);
}
// -------------------------------------------------------------------------------
///////////////////////////////////////////
// convert to absolute value total acceleration collection 
///////////////////////////////////////////
void AccelTAbsoluteValue(struct data ** idata, int nMax)
{
	int nIndex = 0;

	// get absolute value for each value and assign it back to data structure member collection 
	for (nIndex = 0; nIndex < nMax; nIndex++)
	{
		(*idata)[nIndex].dAccelT = fabs((*idata)[nIndex].dAccelT);
	}
}

///////////////////////////////////////////
// quick sort compare functions 
///////////////////////////////////////////
int nCompareFunction (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}

int dCompareFunction (const void * a, const void * b)
{
	if (*(double*)a > *(double*)b) return 1;
	else if (*(double*)a < *(double*)b) return -1;
}


// -------------------------------------------------------------------------------

// -------------------------------------------------------------------------------
///////////////////////////////////////////
// fill array with corresponding data
///////////////////////////////////////////
void FillArray(struct data ** idata, double * dArray, int nStart, int nMax, int nPrm)
{
	int nIndex = 0;
	
	// fill temp array with respective data 
	for (nIndex = 0; nIndex < nMax; nIndex++)
	{
		switch(nPrm)
		{
		case 1:
			dArray[nIndex] = (*idata)[nStart].dGyroX;
			break;
		case 3:
			dArray[nIndex] = (*idata)[nStart].dAccelY;
			break;
		case 4:
			dArray[nIndex] = (*idata)[nStart].dAccelZ;
			break;
		}

		nStart = nStart + 1;
	}
}

///////////////////////////////////////////
// return mean of array  
///////////////////////////////////////////
double dMean (double dArray[], int nMax)
{
	int nIndex = 0;
	double dSum = 0;
	double dAvg = 0;

	// get sum of each array component 
	for (nIndex = 0; nIndex < nMax; nIndex++)
	{
		dSum = dSum + dArray[nIndex];
	}

	// calculate average  
	dAvg = dSum / nMax;

	return dAvg;
}

///////////////////////////////////////////
// return incremental trapezoidal area
///////////////////////////////////////////
double dTrapz(double dArray[], int nIndex)
{
	double dSum = 0;

	// get incremental sum for each trapezoid under the curve 
	if (nIndex == 0)
	{
		dSum = 0;
	}
	else
	{
		dSum = 0.5*(dArray[nIndex] + dArray[nIndex-1]);
	}
	
	return dSum;
}
// -------------------------------------------------------------------------------
