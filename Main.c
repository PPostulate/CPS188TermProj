#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define DataLen 3192


void getcTitle (char *cTitleArr[], FILE* gloTempData, char *token, FILE *out)
{
	char cTitle[300];
	fgets(cTitle, 300, gloTempData);
	token = strtok(cTitle, ",");
	for (short i = 0; token != NULL; i++)
	{
		cTitleArr[i] = token;
		//fprintf(out, "%s\n", cTitleArr[i]);
		token = strtok (NULL, ",");
	}
}

void getTempData (char dArrStor[][11], float tDataArr[][8], FILE *gloTempData, char *token, FILE *out)
{
	char line[200];
	for (short i = 0; fgets(line, 200, gloTempData); i++)
	{
		token = strtok(line, ",");
		for (short j = 0; token != NULL; j++) 
		{
			switch (j)
			{
				case 0:
					strncpy(dArrStor[i], token, 10);
					//fprintf(out, "%s\n", dArr[i]);
					break;
				
				default:
					tDataArr[i][j-1] = atof(token);
					break;
					
			}
			token = strtok (NULL, ",");
		}
	}
}


//Question 1
// Finds the average land temperatures between 1760 to 2015
void Question1_LandAverageTemperatures(float TemperatureDatas[][8],char Date[][11],double *DataOut){
	// Note: Start is 120

	double AverageYearlyTemperature = 0.0;
	int LengthOfDataOut = 0; 
	int CurrentYear = 1759;
	int MonthsElapsed = 0; 

	for(int rows = 120; rows < 3196; rows++){
		
		double CurrentTemperature = TemperatureDatas[rows][0];

		// Adds the current temperature and sums it up
		AverageYearlyTemperature += CurrentTemperature;
		MonthsElapsed += 1; 

		// Every 12 months
		if(MonthsElapsed % 12 == 0){
			
			CurrentYear += 1; 
			AverageYearlyTemperature /= 12.0;

			// Outputs the results
			printf("%d %s %lf\n",LengthOfDataOut,Date[rows],AverageYearlyTemperature);
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
			//printf("%s | %d\n",Date[rows],rows);
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
	//printf("%f\n", TemperatureData[3199][0]);
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
		//printf("%f\n", monthAvgTemp[j]);
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
		//printf("%lf\n",CalculatedTemperatureData[i]);
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

void Question7_PlotTemperaturesFrom19To20Century(double LandAverageTemperatures[]){
	// Loops through the land average temperatures from the 19th and 20th century 
	printf("%lf",LandAverageTemperatures[40]);

}

int main (void)
{
	FILE *gloTempData;
	FILE *out; 
	gloTempData = fopen("GlobalTemperatures.csv","r");
	out = fopen("output.txt", "w");
	/* tDataArr contains the numerical data in the spreadsheet stored as
	 * floats. The array is two dimensional; [row#][column#]. Note that
	 * the row # in the array doesn't match the spreadsheet row #.*/
	char *token = "thing";

	// Temperature data array 
	float TemperatureData[DataLen][8];
	
	float monthAvgTemp[12] = { 0 };
	
	/* dArr contains the date column of the spreadsheet. The dates are
	 * preserved as strings. cTitleArr contains the column titles. The
	 * titles are stored as strings.*/ 
	char Dates[3200][11], *cTitleArr[9];
	
	getcTitle(cTitleArr, gloTempData, token, out);
	getTempData(Dates, TemperatureData, gloTempData, token, out);
	for (short i = 0; i < 3200; i++)
	{
		//fprintf(out, "%s\n", &Dates[i][0]);
	}

	// Question 1
	double LandAverageTemperatures[256];
	Question1_LandAverageTemperatures(TemperatureData,Dates,LandAverageTemperatures); 

	// Question 2
	// double Temperatures1760 = Question2_CalculateLandAverageTemperature(TemperatureData,Dates,"1760","1800");
	// printf("%lf\n",Temperatures1760); 

	// double Temperatures1800 = Question2_CalculateLandAverageTemperature(TemperatureData,Dates,"1800","1900");
	// printf("%lf\n",Temperatures1800);

	// double Temperatures1900 = Question2_CalculateLandAverageTemperature(TemperatureData,Dates,"1900","2000");
	//  printf("%lf\n",Temperatures1900);

	// double Temperatures2000 = Question2_CalculateLandAverageTemperature(TemperatureData,Dates,"2000","2016");
	// printf("%lf\n",Temperatures2000);

	// Question 3
	//Question3_CalculateMonthlyAverageTemperatures(TemperatureData, monthAvgTemp);


	// Question 4 + Question 5
	//Question4_FindHottestAndColdestMonth(TemperatureData,Dates);


	//Question 6
	//Question6_GenerateGNUPlotFromData(TemperatureData,Dates,LandAverageTemperatures);

	// Question 7
	Question7_PlotTemperaturesFrom19To20Century(LandAverageTemperatures);


	fclose(gloTempData);
	
	return (0);
}
