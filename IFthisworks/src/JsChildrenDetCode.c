#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
int nthreads = 4;

char inputDataFileName[50]; // declares the array to hold our binary input file name.


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
//void printMatrix();


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

	/*
	 * Our pattern for using the pointer is to start out with the
	 * arrayPointer address.
	 * Then we add to that the number of rows times the array size.
	 * This gives us the offset from the beginning of the vector to grab
	 * our current row.
	 * Next we add our column address as an additional offset.
	 * This should park us right at the number we are looking for.
	 */
	
	// initialize variable for row reduction
	double rowReductionConstant = 0;

	// work through columns
	for(int columnToGetZeros = 0; columnToGetZeros <(ARRAYSIZE-1); columnToGetZeros++)
	{

		// work through each row
		for(int rowToWorkOn = (columnToGetZeros+1); rowToWorkOn < ARRAYSIZE; rowToWorkOn++)
		{
			//printf("\tWe will work on row %d\n.", rowToWorkOn);
			//printf("\t\tWe will subtract from %d a constant times row %d\n", rowToWorkOn, columnToGetZeros);
			//printf("\t\t\tThat constant is [row, column] [%d, %d] divided by [row, column] [%d, %d]\n",
			//rowToWorkOn, columnToGetZeros, columnToGetZeros, columnToGetZeros);
			
			//*********************************************************************************************************
			rowReductionConstant =
					*(arrayPointer + rowToWorkOn * ARRAYSIZE + columnToGetZeros )
					/ *(arrayPointer + columnToGetZeros * ARRAYSIZE + columnToGetZeros );
			//printf("\tWe will work on row %d\n.", rowToWorkOn);
			//printf("\t\tWe will subtract from %d a constant, %f, times row %d\n", rowToWorkOn, rowReductionConstant, columnToGetZeros);
			//printf("\t\t\tThat constant is [%d, %d]/[%d, %d], or %f.\n",
			//	rowToWorkOn, columnToGetZeros, columnToGetZeros, columnToGetZeros, rowReductionConstant);

			/* now we apply the multiplication.
			 * We will work across the entire row to work on.
			 * Our new row will be our old row minus the row
			 * number which happens to be the same number as the
			 * column we are trying to turn into zeros.
			 * We will use a for loop for now for this process.
			 * Later, we can use a openMP parallel for loop.
			 */
// use a pragma to initiate openMP			
#pragma omp parallel for

			//
			for(int columnCounter = 0; columnCounter < ARRAYSIZE; columnCounter++)
			{
				*(arrayPointer + rowToWorkOn * ARRAYSIZE + columnCounter )
							= *(arrayPointer + rowToWorkOn * ARRAYSIZE + columnCounter )
							- rowReductionConstant *
							*(arrayPointer + columnToGetZeros * ARRAYSIZE + columnCounter );
			}




		}
		// here we should be done with the first pass.
		// Before moving on, I want to print off the matrix and see how it is doing.
		
	}
//**************************************************************************************************************
} // end makeUpperTriangular


// method to read bin file into array
void readDataFromDotBinIntoMatrix ()
{


	// use malloc to assign array
	arrayPointer = (double *)malloc(ARRAYSIZE * ARRAYSIZE * sizeof(double));
	// here, our array pointer is called arrayPointer.
	// our type is double.
	// our size is number of rows times the number of columns times the size of doubles.
	// we have ARRAYSIZE because we will always use a square matrix.


	// set the array to zeros
	for(int rowCounter = 0; rowCounter <ARRAYSIZE; rowCounter++)
	{
		for(int columnCounter = 0; columnCounter < ARRAYSIZE; columnCounter++)
		{
			/* Where the array starts
			 * plus our row counter times the number of elements in our array
			 * plus our column counter
			 * is set to zero.
			 */
			*(arrayPointer + rowCounter * ARRAYSIZE + columnCounter ) = 0;
		}
	}

	// read in array to pointer memory allocated space full of zeros.

	//char inputDataFileName[50];

	// open file
	//sprintf(inputDataFileName,"m0016x0016.bin");
	
	//sprintf(inputDataFileName,"m0496x0496.bin");
	sprintf(inputDataFileName,FileNameString);
	
	printf("Reading array file %s of size %dx%d\n",inputDataFileName,ARRAYSIZE,ARRAYSIZE);
	//Open file
	FILE *inputDataFile=fopen(inputDataFileName,"rb");
	//Read elelements

	for(int rowCounter = 0; rowCounter <ARRAYSIZE; rowCounter++)
	{
		for(int columnCounter = 0; columnCounter < ARRAYSIZE; columnCounter++)
		{
			/* Where the array starts
			 * plus our row counter times the number of elements in our array
			 * plus our column counter
			 * is set to zero.
			 */
			//*( arrayPointer + rowCounter * ARRAYSIZE + columnCounter ) = 0;
			fread((arrayPointer + rowCounter * ARRAYSIZE + columnCounter),sizeof(double),1,inputDataFile);
		}
	}

	// print the matrix to a csv file.
	//printMatrix();

	printf("Finished reading array file %s of size %dx%d\n",inputDataFileName,ARRAYSIZE,ARRAYSIZE);

} /* readDataFromDotBinIntoMatrix */


void multiplyDiagonalAndReturnAnswer ()
{
	printf("Hello from multiply diagonal and return answer function.\n");

	/*
	 * For this exercise, we will multiply across the diagonal.
	 * We will start at [0,0] and multiply it by [1,1].
	 * We could use an openMP reduction for this later on.
	 * For now, we will just do it with a for loop.
	 *
	 * To access this number, we begin with the address of the arrayPointer.
	 * We add to that the row we want times the array size.
	 * This is the offset to get us onto the row we want to work on.
	 * Then we add to that the number of columns we want to go over.
	 * That parks us at the number we want to grab.
	 */

	for(int diagonalAddress = 0; diagonalAddress < ARRAYSIZE; diagonalAddress++)
	{
		diagonalMultiplierVariableLongDouble = diagonalMultiplierVariableLongDouble *
				(long double)*(arrayPointer + diagonalAddress * ARRAYSIZE + diagonalAddress );

		/* Now we try to add as we go.
		 *
		 */

		addAsWeGoLogAbsDet = addAsWeGoLogAbsDet +
				log10(fabs(*(arrayPointer + diagonalAddress * ARRAYSIZE + diagonalAddress )));
	}

	//printf("\nThis provides a log of the absolute value of the determinant of: %e.\n", logOfAbsOfDet);
	
	printf("\nThe diagonal multiplied all together is: %Le.\n",diagonalMultiplierVariableLongDouble);
	printf("Rounded to a double, this is: %e.\n",(double)diagonalMultiplierVariableLongDouble);
	printf("Add as we go of the log of the abs of the det is %e.\n", addAsWeGoLogAbsDet);


	
	

	return;
} /* multiplyDiagonalAndReturnAnswer */

