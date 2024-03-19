#include <stdio.h>
#include <string.h>
#include <math.h>
// Yo if you see this commit then I am officially a git bash demon. Like  this was probably the most complicated thing that I've ever done
// This is a massive change can you like work?
// Some changes here
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
void Question1_LandAverageTemperatures(float TemperatureData[][8]){
	// Note: Start is 120

	double AverageYearlyTemperature = 0.0;
	int CurrentYear = 1759;
	int MonthsElapsed = 0; 
	for(int rows = 120; rows < 3200; rows++){
		
		double CurrentTemperature = TemperatureData[rows][0];

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
	float tDataArr[3200][8];
	
	/* dArr contains the date column of the spreadsheet. The dates are
	 * preserved as strings. cTitleArr contains the column titles. The
	 * titles are stored as strings.*/ 
	char dArrStor[3200][11], *cTitleArr[9];
	
	getcTitle(cTitleArr, gloTempData, token, out);
	getTempData(dArrStor, tDataArr, gloTempData, token, out);
	for (short i = 0; i < 3200; i++)
	{
		fprintf(out, "%s\n", &dArrStor[i][0]);
	}
	

	// Question 1
	Question1_LandAverageTemperatures(tDataArr); 
	
	
	
	fclose(gloTempData);
	
	return (0);
}
