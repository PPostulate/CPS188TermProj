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


void getTempData (char *dArr[], char dArrStor[][11], float tDataArr[][8], FILE *gloTempData, char *token, FILE *out)
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
					for (short k = 0; k < 10; k++) 
					{
						dArrStor[i][k] = *(token + k);
					}
					dArrStor[i][10] = '\0';
					dArr[i] = &dArrStor[i][0];
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
// hi, this is a test commit
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
	float tDataArr[3200][8];
	
	/* dArr contains the date column of the spreadsheet. The dates are
	 * preserved as strings. cTitleArr contains the column titles. The
	 * titles are stored as strings.*/ 
	char dArrStor[3200][11], *dArr[3200], *cTitleArr[9];
	
	getcTitle(cTitleArr, gloTempData, token, out);
	getTempData(dArr, dArrStor, tDataArr, gloTempData, token, out);
	for (short i = 0; i < 3200; i++)
	{
		fprintf(out, "%s\n", dArr[i]);
	}
	
	
	fclose(gloTempData);
	
	return (0);
}
