#include <stdio.h>
#include <string.h>
#include <math.h>
// Yo if you see this commit then I am officially a git bash demon. Like  this was probably the most complicated thing that I've ever done
// This is a massive change can you like work?
// Some changes here
void getcTitle (char *cTitleArr[], FILE* gloTempData)
{
	char cTitle[300], *token;
	fgets(cTitle, 300, gloTempData);
	token = strtok(cTitle, ",");
	for (short i = 0; token != NULL; i++)
	{
		cTitleArr[i] = token;
		printf("%s\n", cTitleArr[i]);
		token = strtok (NULL, ",");
	}
}

void getTempData (char *dArr[], float tDataArr[][8], FILE *gloTempData)
{
	char line[100], *token;
	for (short i = 0; fgets(line, 100, gloTempData); i++)
	{
		token = strtok(line, ",");
		for (short j = 0; token != NULL; j++) 
		{
			switch (j)
			{
				case 0:
					dArr[i] = token;
					printf("%s\n", dArr[i]);
					break;
				
				default:
					tDataArr[i][j-1] = atof(token);
					printf("%f\n", tDataArr[i][j-1]);
					break;
					
			}
			token = strtok (NULL, ",");
		}
	}
}
// hi, this is a test commit
int main (void)
{
	FILE *gloTempData;
	gloTempData = fopen("GlobalTemperatures.csv","r");
	/* tDataArr contains the numerical data in the spreadsheet stored as
	 * floats. The array is two dimensional; [row#][column#]. Note that
	 * the row # in the array doesn't match the spreadsheet row #.*/
	
	float tDataArr[3200][8];
	
	/* dArr contains the date column of the spreadsheet. The dates are
	 * preserved as strings. cTitleArr contains the column titles. The
	 * titles are stored as strings.*/ 
	char *dArr[3200], *cTitleArr[9];
	
	getcTitle(cTitleArr, gloTempData);
	getTempData(dArr, tDataArr, gloTempData);
	//for (short i = 0; i < 3200; i++)
	//{
		//printf("%s\n", dArr[i]);
	//}
	
	
	fclose(gloTempData);
	
	return (0);
}
