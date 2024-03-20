#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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
void Question1_LandAverageTemperatures(float TemperatureDatas[][8]){
	// Note: Start is 120

	double AverageYearlyTemperature = 0.0;
	int CurrentYear = 1759;
	int MonthsElapsed = 0; 
	for(int rows = 120; rows < 3200; rows++){
		
		double CurrentTemperature = TemperatureDatas[rows][0];

		// Adds the current temperature and sums it up
		AverageYearlyTemperature += CurrentTemperature;
		MonthsElapsed += 1; 

		// Every 12 months
		if(MonthsElapsed % 12 == 0){
			
			
			CurrentYear += 1; 
			AverageYearlyTemperature /= 12.0;

			// Outputs the results
			printf("%lf\n",AverageYearlyTemperature);

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
	float TemperatureData[3200][8];
	
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
	//Question1_LandAverageTemperatures(TemperatureData); 

	// Question 2
	double Temperatures1760 = Question2_CalculateLandAverageTemperature(TemperatureData,Dates,"1760","1800");
	printf("%lf\n",Temperatures1760); 

	double Temperatures1800 = Question2_CalculateLandAverageTemperature(TemperatureData,Dates,"1800","1900");
	printf("%lf\n",Temperatures1800);

	double Temperatures1900 = Question2_CalculateLandAverageTemperature(TemperatureData,Dates,"1900","2000");
	 printf("%lf\n",Temperatures1900);

	double Temperatures2000 = Question2_CalculateLandAverageTemperature(TemperatureData,Dates,"2000","2016");
	printf("%lf\n",Temperatures2000);

	fclose(gloTempData);
	
	return (0);
}
