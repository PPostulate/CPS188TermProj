#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define DataLen 3192

//Function to get the column header values.
void getcTitle (char *cTitleArr[], FILE* gloTempData, char *token, FILE *out)
{
	char cTitle[300];
	//Gets the column headers as one string.
	fgets(cTitle, 300, gloTempData);
	//Store the first header as a token.
	token = strtok(cTitle, ",");
	//Loop to put all the headers in an array.
	for (short i = 0; token != NULL; i++)
	{
		//Puts the current token in the column title array.
		cTitleArr[i] = token;
		//Move to next header.
		token = strtok (NULL, ",");
	}
}

//Function to get the data from the csv.
void getTempData (char dArrStor[][11], float tDataArr[][8], FILE *gloTempData, char *token, FILE *out)
{
	//Decalare array to store a line of the csv
	char line[200];
	//Loop until the end of the csv is reached.
	for (short i = 0; fgets(line, 200, gloTempData); i++)
	{
		//Places a token (region of a line seprated by a comma), into the token char*.
		token = strtok(line, ",");
		//Loops until all of the tokens in a line of the csv are parsed.
		for (short j = 0; token != NULL; j++) 
		{
			//Switch to decide to store given value in a char array or float array.
			switch (j)
			{
				/*The first token of any line is the date which is stored as a string since, it
				* is not strictly numerical.*/
				case 0:
					//Date is stored in the dArrStor.
					strncpy(dArrStor[i], token, 10);
					break;
				//All other tokens in a line are stored in the tDataArr since they are all numerical.
				default:
					/*Index of j is offset by one since the switch case begins at one but
					* the index of the data should start at zero.*/
					tDataArr[i][j-1] = atof(token);
					break;
					
			}
			//Move to next token.
			token = strtok (NULL, ",");
		}
	}
}


//Question 1
// Finds the average land temperatures between 1760 to 2015
void Question1_LandAverageTemperatures(float TemperatureDatas[][8],char Date[][11],double DataOut[]) {
	// Note: Start is 120

	double AverageYearlyTemperature = 0.0;
	int LengthOfDataOut = 0; 
	int CurrentYear = 1759;
	int MonthsElapsed = 0; 
	short count = 1;
	for(int rows = 120; rows < 3196; rows++, count++){
		
		double CurrentTemperature = TemperatureDatas[rows][0];

		// Adds the current temperature and sums it up
		AverageYearlyTemperature += CurrentTemperature;
		MonthsElapsed += 1; 

		// Every 12 months
		if(MonthsElapsed % 12 == 0){
			
			CurrentYear += 1; 
			AverageYearlyTemperature /= 12.0;

			// Outputs the results
			DataOut[LengthOfDataOut] = AverageYearlyTemperature;

			// Increments the length of the data out
			LengthOfDataOut += 1;

			// Reset
			AverageYearlyTemperature = 0.0;
		}
	}
	

}


//Question 2 
/**
 * Calculates the average temperature between two seperate start and end years 
 * @param TemperatureData The temperature data array 
 * @param Date The date array
 * @param StartYear The start year [inclusive]
 * @param EndYear The end year [exclusive]
*/
double Question2_CalculateLandAverageTemperature(float TemperatureData[][8], char Date[][11], char* StartYear, char* EndYear){
	double AverageYearlyTemperature = 0.0;
	int MonthsElapsed = 0;
	int StartCount = 0; 

	for(int rows = 0; rows < 3192; rows++){
		
		if(strncmp(Date[rows],StartYear,4) == 0){
			StartCount = 1;
		}

		// Checks if the current year is still the same and it adds the temperature for that year 
		if((strncmp(Date[rows],EndYear,4) != 0) && StartCount == 1){
			MonthsElapsed++; 
			AverageYearlyTemperature += TemperatureData[rows][0];
		}
		else if(strncmp(Date[rows],EndYear,4) == 0 && StartCount == 1){
			// Stops the loop 
			break; 
		}
	} 


	// Returns the average 
	return AverageYearlyTemperature/MonthsElapsed;

}


//Question 3 
/**
 * Calculates the average temperature for each month between 1900 and 2015
*/
void Question3_CalculateMonthlyAverageTemperatures(float TemperatureData[][8], float monthAvgTemp[12]) {
	for (short i = 0; i < 1392; i++)
	{
		switch (i % 12)
			{
			case 1:
				monthAvgTemp[0] += TemperatureData[1800 + i][0];
				break;
			case 2:
				monthAvgTemp[1] += TemperatureData[1800 + i][0];
				break;
			case 3:
				monthAvgTemp[2] += TemperatureData[1800 + i][0];
				break;
			case 4:
				monthAvgTemp[3] += TemperatureData[1800 + i][0];
				break;
			case 5:
				monthAvgTemp[4] += TemperatureData[1800 + i][0];
				break;
			case 6:
				monthAvgTemp[5] += TemperatureData[1800 + i][0];
				break;
			case 7:
				monthAvgTemp[6] += TemperatureData[1800 + i][0];
				break;
			case 8:
				monthAvgTemp[7] += TemperatureData[1800 + i][0];
				break;
			case 9:
				monthAvgTemp[8] += TemperatureData[1800 + i][0];
				break;
			case 10:
				monthAvgTemp[9] += TemperatureData[1800 + i][0];
				break;
			case 11:
				monthAvgTemp[10] += TemperatureData[1800 + i][0];
				break;
			case 0:
				monthAvgTemp[11] += TemperatureData[1800 + i][0];
				break;
			default:
				printf("Switch goofed");
				break;
			}
	}
	for (short j = 0; j < 12; j++)
	{
		monthAvgTemp[j] = monthAvgTemp[j] / 116;
	}
	
}


// Question 4 + Question 5
/**
 * Finds the hottest month and the coldest month in an given year
*/
void Question4_FindHottestAndColdestMonth(float TemperatureData[][8], char Date[][11]){

	char HottestDate[11];
	double HottestTemperature = 0.0;

	char ColdestDate[11];
	double ColdestTemperature = 0.0;

	// Goes through the entire temperature data per month and finds the hottest and coldest month
	for(int i = 0; i < DataLen; i++){
		if(TemperatureData[i][0] > HottestTemperature){
			HottestTemperature = TemperatureData[i][0];
			strncpy(HottestDate,Date[i],11);
		}
		else if(TemperatureData[i][0] < ColdestTemperature){
			ColdestTemperature = TemperatureData[i][0];
			strncpy(ColdestDate,Date[i],11);
		}
	}

	// Outputs the results

	// Question 5
	printf("Hottest Month: %s | %lf\n",HottestDate,HottestTemperature);
	printf("Coldest Month: %s | %lf\n",ColdestDate,ColdestTemperature);

}


// Question 6 
/**
 * Generates the GNUPlot for the data in the 
*/
void Question6_GenerateGNUPlotFromData(float TemperatureData[][8], char Date[][11], double* AverageTemperatures){
	// Outputs the data to a file
	FILE *GNUPlotData = fopen("GNUPlotData.txt","w");
	int CurrentIndex = 0; 
	for(int i = 120; i < 3195; i++){
		if(i % 12 == 0 && Date[i][0] != '\0'){
			fprintf(GNUPlotData,"%s %lf\n",Date[i + 11],AverageTemperatures[CurrentIndex]);
			CurrentIndex += 1;
		}
	}

	fclose(GNUPlotData);
}


//Question 7 
/**
 * Generates the GNUPlot data for the land average temperatures for the 19th and 20th century
*/
void Question7_PlotTemperaturesFrom19To20Century(double LandAverageTemperatures[], char Dates[][11]){
	// Loops through the land average temperatures from the 19th and 20th century

	// Start Index for 19th century is 41
	// End Index for 19th century is 140
	
	FILE *GNUPlotData = fopen("Question_7_Data.txt","w");

	// Combines the 19th and 20th century data into one file 
	float CombinedTemperatureData[1200][8];
	char CombinedDates[1200][11];

	// Calculates the land average temperatures for the 19th century
	for(int i = 41; i <= 140; i++){
		CombinedTemperatureData[i - 41][0] = LandAverageTemperatures[i];

	}

	// Start Index for the 20th century is 141
	// End Index for the 20th century is 240
	for(int i = 141; i <= 240; i++){
		CombinedTemperatureData[i - 141][1] = LandAverageTemperatures[i];

	}

	fprintf(GNUPlotData,"#Year 19th Century  20th Century\n");
	// Loops through all the merged data and reads it into a file 
	for(int i = 0; i < 100; i++){
		fprintf(GNUPlotData,"%d %f %f\n",i+1,CombinedTemperatureData[i][0],CombinedTemperatureData[i][1]);
	}

	fclose(GNUPlotData);


}

//Question 8
void Q8AverageTemp(float tDataArr[][8]) {
	FILE* q8plot;
	q8plot = fopen("q8output.txt", "w");	
	//Declare and intialize arrays for average, max, and min yearly temperatures.
	float avgTempArr[166] = { 0 }, avgMaxTemp[166] = { 0 }, avgMinTemp[166] = { 0 };
	//Outer loop iterates for each year.
	for (short i = 0; i <= 165; i++)
	{
		//Inner loop to iterate for each month in a year.
		for (short j = 0; j < 12; j++)
		{
			/*Index of the data array is determined by finding an offset from the csv
			* and then iterating through each month by the counter j, and ofsetting by 
			* a year by multiplying i by 12.*/
			avgTempArr[i] += tDataArr[1200 + 12 * i + j][0];
			avgMaxTemp[i] += tDataArr[1200 + 12 * i + j][2];
			avgMinTemp[i] += tDataArr[1200 + 12 * i + j][4];
		}
		//Calculating average of current year
		avgTempArr[i] /= 12;
		avgMaxTemp[i] /= 12;
		avgMinTemp[i] /= 12;
		//Outputting to a text file with columns for year, average, max, and min.
		fprintf(q8plot, "%-8hd%-20f%-20f%f\n", 1850 + i, avgTempArr[i], avgMaxTemp[i], avgMinTemp[i]);
	}
	fclose(q8plot);
}

//Question 9 calculation function (Find avg min and max for a century.)
void Q9multiPlotCalc(float tDataArr[][8], float avgTempCent[], float maxTempCent[], float minTempCent[], short i, short cent)
{
	/*Using the current index based on the loop in Q9Multiplot, the index of the data array is determined.
	* This index is used to add the current land temperature to the sum, compare the current max temp to
	* the index one, and compare the current min temp to the index one.*/
	avgTempCent[cent] += tDataArr[i][0];
	maxTempCent[cent] = (maxTempCent[cent] < tDataArr[i][2]) ? tDataArr[i][2] : maxTempCent[cent];
	minTempCent[cent] = (minTempCent[cent] > tDataArr[i][4]) ? tDataArr[i][4] : minTempCent[cent];
}

//Question 9 formatting function
void Q9multiPlot(float tDataArr[][8])
{
	FILE* q9out;
	q9out = fopen("q9data.txt", "w");
	/*Declare and intialize arrays for the average, min, and max temperatures.
	* max and min are initialized with values that are low/high inorder to start the
	* comparison process.*/
	float avgTempCent[3] = { 0 }, maxTempCent[3] = { 0 }, minTempCent[3] = { 1000 };
	short count = 0;
	//Loop for the 19th century, bounds based on rows of the csv.
	for (short i = 1212; i <= 1811; i++, count++)
	{
		//Function Q9multiPlotCalc is called to determine the average, min, and max.
		Q9multiPlotCalc(tDataArr, avgTempCent, maxTempCent, minTempCent, i, 0);
	}
	//Divide sum of temperatures by number of iterations to find average.
	avgTempCent[0] /= count;
	//Output a row of data for the 19th century.
	fprintf(q9out, "%-15s%-10f%-10f%f", "\"19th Century\"", avgTempCent[0], maxTempCent[0], minTempCent[0]);
	
	//Reset the iteration counter.
	count = 0;
	//Loop for the 20th century, bounds based on rows of the csv.
	for (short i = 1812; i <=  3011; i++, count++)
	{
		//Function Q9multiPlotCalc is called to determine the average, min, and max.
		Q9multiPlotCalc(tDataArr, avgTempCent, maxTempCent, minTempCent, i, 1);
	}
	//Divide sum of temperatures by number of iterations to find average.
	avgTempCent[1] /= count;
	//Output a row of data for the 20th century.
	fprintf(q9out, "\n%-15s%-10f%-10f%f", "\"20th Century\"", avgTempCent[1], maxTempCent[1], minTempCent[1]);
	//Reset the iteration counter.
	count = 0;
	//Loop for the 21st century, bounds based on rows of the csv.
	for (short i = 3012; i <= DataLen - 1; i++, count++)
	{
		//Function Q9multiPlotCalc is called to determine the average, min, and max.
		Q9multiPlotCalc(tDataArr, avgTempCent, maxTempCent, minTempCent, i, 2);
	}
	//Divide sum of temperatures by number of iterations to find average.
	avgTempCent[2] /= count;
	//Output a row of data for the 19th century.
	fprintf(q9out, "\n%-15s%-10f%-10f%f", "\"21st Century\"", avgTempCent[2], maxTempCent[2], minTempCent[2]);
}

//Question 10 average temp and deviation calculation
void Q10Calc(float tDataArr[][8], float avgMonTemp[], float monTempDev[], short mon)
{
	//Loop to iterate through each year between 2000 and 2015 inclusive.
	for (short i = 0; i <= 15; i++)
	{
		/* Sum of the average temp and deviation is calculated by using the row offset
		* and adding 12 times the counter variable i. This iteration is also offset by
		* the counter from Q10Format: "mon". This allows the calcuation for each month.*/
		avgMonTemp[mon] += tDataArr[3000 + i*12 + mon][0];
		monTempDev[mon] += tDataArr[3000 + i*12 + mon][1];
	}
	//Averages are calculated by dividing the sum by the iterations (number of years).
	avgMonTemp[mon] /= 16;
	monTempDev[mon] /= 16;
}


//Question 10 format funciton
void Q10Format(float tDataArr[][8])
{
	FILE* Q10Output;
	Q10Output = fopen("q10data.txt", "w");
	//Declare arrays for the average monthly temperatures and the average deviation.
	float avgMonTemp[12] = { 0 }, monTempDev[12] = { 0 };
	//Array of month names for formatting output.
	char* monName[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
	/*Loop to calculate the average temperature and deviation for a given month.
	* Iterates 12 times for each month of the year.*/
	for (short i = 0; i < 12; i++)
	{
		//Call Q10Calc to find the average temp and deviation.
		Q10Calc(tDataArr, avgMonTemp, monTempDev, i);
		//Output the month name, calculated average temperature, and deviation.
		fprintf(Q10Output, "%-15s%-15f%f\n", monName[i], avgMonTemp[i], monTempDev[i]);
	}
}

/*Question 11 function to find the yearly average of the ocean & land average
* temperatures*/
void Q11OceanLandCalc(float tDataArr[][8], float oceanLandAvgTemp[256])
{
	/*Outer loop to iterate once every year.i increases by twelve each iteration.
	* j increases by one for the index of the average array.*/
	for (short i = 1200, j = 0; i < DataLen; i += 12, j++)
	{
		//Nested loop to find the sum of the temperatures for a given year.
		for (short k = 0; k < 12; k++)
		{
			/*Index of tDataArr is determined based on the index of i which increases by
			* twelve each loop. k iterates once each time of the inner loop which gets 
			* through all twelve months of the year. */
			oceanLandAvgTemp[j] += tDataArr[i + k][6];
		}
		oceanLandAvgTemp[j] /= 12;
	}
}


//Question 11 format function
void Q11Format(float tDataArr[][8], double landAvgTemp[])
{
	FILE* q11out;
	q11out = fopen("q11data.txt", "w");
	//Declare a array for the yearly average temperatures of the land and ocean average temperatures.
	float oceanLandAvgTemp[256] = { 0 };
	//Function call to determine the averages for oceanLandAvgTemp.
	Q11OceanLandCalc(tDataArr, oceanLandAvgTemp);
	
	for (short i = 0; i < 2015 - 1849; i++)
	{
		//Output year, yearly land temp, and yearly ocean & land temp.
		fprintf(q11out, "%-10hd%-10f%f\n", i+1850, landAvgTemp[i+ 1850-1760], oceanLandAvgTemp[i]);
	}
}


int main (void)
{

		FILE* gloTempData;
		FILE* out;
		gloTempData = fopen("GlobalTemperatures.csv", "r");
		out = fopen("output.txt", "w");
		char* token = "";

		// Temperature data array 
		float TemperatureData[DataLen][8];
		// Array for the average monthly land temperatures.
		float monthAvgTemp[12] = { 0 };

		/* Array "Dates" contains the date column of the spreadsheet. The dates are
		* preserved as strings. cTitleArr contains the column titles. The
		* titles are stored as strings.*/
		char Dates[3200][11] = { 0 }, * cTitleArr[9];

		getcTitle(cTitleArr, gloTempData, token, out);
		getTempData(Dates, TemperatureData, gloTempData, token, out);



	// Question 1
	double LandAverageTemperatures[256];
	Question1_LandAverageTemperatures(TemperatureData,Dates, LandAverageTemperatures);

	// Question 2
		double Temperatures1760 = Question2_CalculateLandAverageTemperature(TemperatureData,Dates,"1760","1800");

		double Temperatures1800 = Question2_CalculateLandAverageTemperature(TemperatureData,Dates,"1800","1900");

		double Temperatures1900 = Question2_CalculateLandAverageTemperature(TemperatureData,Dates,"1900","2000");

		double Temperatures2000 = Question2_CalculateLandAverageTemperature(TemperatureData,Dates,"2000","2016");

	// Question 3
	Question3_CalculateMonthlyAverageTemperatures(TemperatureData, monthAvgTemp);
	
	// Question 4 + Question 5
	Question4_FindHottestAndColdestMonth(TemperatureData,Dates);

	//Question 6
	Question6_GenerateGNUPlotFromData(TemperatureData,Dates,LandAverageTemperatures);

	//Question 7
	Question7_PlotTemperaturesFrom19To20Century(TemperatureData, Dates);

	//Question 8
	Q8AverageTemp(TemperatureData);

	//Question 9
	Q9multiPlot(TemperatureData);

	//Question 10
	Q10Format(TemperatureData);

	//Question 11
	Q11Format(TemperatureData, LandAverageTemperatures);



	

	fclose(gloTempData);
	
	return (0);
}
