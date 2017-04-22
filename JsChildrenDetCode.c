#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

int nthreads = 4;

// declaration to hold binary input file
char inputDataFileName[50];


#define ARRAYSIZE 5000
#define FileNameString "m5000x5000.bin"

// create pointer to hold array
double *arrayPointer; 


// establish variables to track multiplication of diagonal (determinant) and log of absolute determinant
long double diagonalMultiplierVariableLongDouble = 1;
double addAsWeGoLogAbsDet = 0;

// initialize method calls 
void readDataFromDotBinIntoMatrix ();
void makeUpperTriangularFunction ();
void multiplyDiagonalAndReturnAnswer ();

int main(void) {

	// call method to read data from bin file
	readDataFromDotBinIntoMatrix();

	// call method to perform Gaussian elimination
	makeUpperTriangularFunction ();

	// call method to find determinant and log of determinant
	multiplyDiagonalAndReturnAnswer ();

	// free memory from pointer address
	free(arrayPointer);
	return 0;
}  // end main

// function to create upper triangle of 0's
void makeUpperTriangularFunction ()
{
	
	// initialize variables for row reduction
	double rowReductionConstant = 0;
	int columnToGetZeros = 0;
	int rowToWorkOn = 0;

	// work through columns
	for(columnToGetZeros = 0; columnToGetZeros <(ARRAYSIZE-1); columnToGetZeros++)
	{

		// work through each row
		for(rowToWorkOn = (columnToGetZeros+1); rowToWorkOn < ARRAYSIZE; rowToWorkOn++)
		{
			rowReductionConstant =
					*(arrayPointer + rowToWorkOn * ARRAYSIZE + columnToGetZeros )
					/ *(arrayPointer + columnToGetZeros * ARRAYSIZE + columnToGetZeros );

	int columnCounter = 0;			
// use a pragma to initiate openMP			
#pragma omp parallel for private(columnCounter)

			for(columnCounter = 0; columnCounter < ARRAYSIZE; columnCounter++)
			{
				*(arrayPointer + rowToWorkOn * ARRAYSIZE + columnCounter )
							= *(arrayPointer + rowToWorkOn * ARRAYSIZE + columnCounter )
							- rowReductionConstant *
							*(arrayPointer + columnToGetZeros * ARRAYSIZE + columnCounter );
			}
		}
	}

} // end makeUpperTriangular


// method to read bin file into array
void readDataFromDotBinIntoMatrix ()
{


	// use malloc to assign array
	arrayPointer = (double *)malloc(ARRAYSIZE * ARRAYSIZE * sizeof(double));
	
	// set the array to zeros
	for(int rowCounter = 0; rowCounter <ARRAYSIZE; rowCounter++)
	{
		for(int columnCounter = 0; columnCounter < ARRAYSIZE; columnCounter++)
		{
			*(arrayPointer + rowCounter * ARRAYSIZE + columnCounter ) = 0;
		}
	}

	sprintf(inputDataFileName,FileNameString);
	
	// open file
	FILE *inputDataFile=fopen(inputDataFileName,"rb");

	// read data from file
	for(int rowCounter = 0; rowCounter <ARRAYSIZE; rowCounter++)
	{
		for(int columnCounter = 0; columnCounter < ARRAYSIZE; columnCounter++)
		{
			fread((arrayPointer + rowCounter * ARRAYSIZE + columnCounter),sizeof(double),1,inputDataFile);
		}
	}

} // end readDataFromDotBinIntoMatrix


void multiplyDiagonalAndReturnAnswer ()
{
	
	// iterate through diagonals of array
	for(int diagonalAddress = 0; diagonalAddress < ARRAYSIZE; diagonalAddress++)
	{
		// mutiply diagonal nums
		diagonalMultiplierVariableLongDouble = diagonalMultiplierVariableLongDouble *
				(long double)*(arrayPointer + diagonalAddress * ARRAYSIZE + diagonalAddress );
		
		// take log of diagonal num and add to total
		addAsWeGoLogAbsDet = addAsWeGoLogAbsDet +
				log10(fabs(*(arrayPointer + diagonalAddress * ARRAYSIZE + diagonalAddress )));
	}

	// output results	
	printf("\nThe diagonal multiplied all together is: %Le.\n",diagonalMultiplierVariableLongDouble);
	printf("Rounded to a double, this is: %e.\n",(double)diagonalMultiplierVariableLongDouble);
	printf("Add as we go of the log of the abs of the det is %e.\n", addAsWeGoLogAbsDet);

	return;
} // end multiplyDiagonalAndReturnAnswer

