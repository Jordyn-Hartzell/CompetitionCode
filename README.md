# CompetitionCode


// Standard library included with the file.
#include <stdio.h>
#include <stdlib.h>
#include <math.h> // lets me use fabs to find the absolute value of a double.
// math.h should also let me take the log of a number.

/* Import the time header file so we can time our function calls.
 * Allows use of clock_t number type, clock() function call,
 * and CLOCKS_PER_SEC $
 */
#include <time.h>

/* Reading in data using online code from University of Tulsa.
 * Using their code for a starting point.
 * Just trying to get something to work...
 */

//#define ARRAYSIZE 16 // Starting out small.
#define ARRAYSIZE 1000 // Starting out small.

/* We are going to use a pointer and not a variable.
 * This will allow us to use Malloc.
 */
double *arrayPointer; // define a pointer to hold our array.

/* prototype custom function calls. */
void readDataFromDotBinIntoMatrix ();
void makeUpperTriangularFunction ();
double multiplyDiagonalAndReturnAnswer ();
//void printMatrix(); // used to print off the matrix as it currently stands.


int main(void) {
	puts("!!!Hello Class!!!"); /* prints !!!Hello Class!!! */

	/* Read in the data from the .bin file */
	readDataFromDotBinIntoMatrix();

	/* Make an upper triangular matrix */
	makeUpperTriangularFunction ();

	/* Multiply the diagonal to produce the determinant. */
	double determinant = 0;
    determinant = multiplyDiagonalAndReturnAnswer ();

    printf("\n\nThe diagonal multiplied all together is: %e.\n",determinant);

    double absoluteValueOfDeterminant = 0;
    absoluteValueOfDeterminant = fabs(determinant);
    printf("The absolute value of the determinant is: %e.\n",absoluteValueOfDeterminant);

    double logOfAbsoluteValueOfDeterminant = 0;
    logOfAbsoluteValueOfDeterminant = log10(absoluteValueOfDeterminant);
    printf("The log of the absolute value of the determinant is: %e.\n",logOfAbsoluteValueOfDeterminant);

	// now we let our free our memory again.
	// #14 Free our memory array
	// googled: c programming free memory
	// found: https://www.codingunit.com/c-tutorial-the-fun$
	// free(ptr_one);
	free(arrayPointer);
	return 0;
}  /* main */

void makeUpperTriangularFunction ()
{
	printf("Hello from make upper triangular function.\n");
	// print the matrix to a csv file.
	//printMatrix();

	// from old code:
	//	for(j=i+1;j<size;j++){
	//		tmp1 = *(matrix+size*j+i) / *(matrix+size*i+i);
	//		for(k=i;k<size;k++){
	//			*(matrix+size*j+k) = *(matrix+size*j+k)-*(matrix + size*i+k)*tmp1;
	//		}
	//	}

	// Loop through the columns we need to fix.

	/*
	 * Our pattern for using the pointer is to start out with the
	 * arrayPointer address.
	 * Then we add to that the number of rows times the array size.
	 * This gives us the offset from the beginning of the vector to grab
	 * our current row.
	 * Next we add our column address as an additional offset.
	 * This should park us right at the number we are looking for.
	 */

	double rowReductionConstant = 0;

	for(int columnToGetZeros = 0; columnToGetZeros <(ARRAYSIZE-1); columnToGetZeros++)
	{
		//printf("We need to get zeros in column %d\n.", columnToGetZeros);

		// in each column, we will need to work through each of the rows.
		for(int rowToWorkOn = (columnToGetZeros+1); rowToWorkOn < ARRAYSIZE; rowToWorkOn++)
		{
			//printf("\tWe will work on row %d\n.", rowToWorkOn);
			//printf("\t\tWe will subtract from %d a constant times row %d\n", rowToWorkOn, columnToGetZeros);
			//printf("\t\t\tThat constant is [row, column] [%d, %d] divided by [row, column] [%d, %d]\n",
			//rowToWorkOn, columnToGetZeros, columnToGetZeros, columnToGetZeros);

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
		// print the matrix to a csv file.
		//printMatrix();
	}

	// print the matrix to a csv file.
	//printMatrix();
} /* makeUpperTriangularFunction */


void readDataFromDotBinIntoMatrix ()
{
	printf("Hello from read in data call.\n");

	// Let us begin by doing a copy and paste from the code online.
	// from: http://morpheus.mcs.utulsa.edu/%7Epapama/hpc/

	/* from University of Tulsa website:
	 * m0016x0016.bin
	 * det=3.346535e-04
	 * log(abs(det))=-3.475405e+00
	 */


	// Going to do some refactoring to use a pointer.
	/* Use malloc to set aside memory for our array.
	 * We have a pointer
	 * We write an address to it
	 * That address will store doubles.
	 * We use malloc to give us that address.
	 * We ask malloc to give us a memory chuck
	 * That has enough elements for our matrix,
	 * which is the size of our array squared.
	 * Each element needs to be the big enough
	 * to hold a double.*/
	// arrayPointer = (double *)malloc(numberOfRows * numberOfColumns * sizeof(double));
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

	char inputDataFileName[50];

	// open file
	//sprintf(inputDataFileName,"m0016x0016.bin");
	/* from University of Tulsa website:
		 * m0016x0016.bin
		 * det=3.346535e-04
		 * log(abs(det))=-3.475405e+00
		 */
	sprintf(inputDataFileName,"m1000x1000.bin");
	/* from University of Tulsa website:
		 * m0016x0016.bin
		 * det=5.948068e+292
		 * log(abs(det))=2.927744e+02
		 * and from my notes:
		 * The diagonal multiplied all together is: 5.948068e+292.
		 */

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


double multiplyDiagonalAndReturnAnswer ()
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
	double diagonalMultiplierVariableDouble = 1; // This is the multiplication identity.
	for(int diagonalAddress = 0; diagonalAddress < ARRAYSIZE; diagonalAddress++)
	{
		diagonalMultiplierVariableDouble = diagonalMultiplierVariableDouble *
				*(arrayPointer + diagonalAddress * ARRAYSIZE + diagonalAddress );

	}
	//printf("\n\nThe diagonal multiplied all together is: %e.\n",diagonalMultiplierVariableDouble);
	/*double logOfAbsOfDet;
	// doing a manual absolute value function because the linker only recognizes the first math library call.
	if(diagonalMultiplierVariableDouble<0)
	{
		// if it is less than zero flip its sign.
		logOfAbsOfDet = -1 * diagonalMultiplierVariableDouble;
	}
	else
	{
		// else leave it alone.
		logOfAbsOfDet = 1 * diagonalMultiplierVariableDouble;
	}
			//(diagonalMultiplierVariableDouble);
	logOfAbsOfDet = log(logOfAbsOfDet);*/
	//printf("\nThis provides a log of the absolute value of the determinant of: %e.\n", logOfAbsOfDet);
	/* from University of Tulsa website:
		 * m0016x0016.bin
		 * det=3.346535e-04
		 * log(abs(det))=-3.475405e+00
		 */
	return diagonalMultiplierVariableDouble;
} /* multiplyDiagonalAndReturnAnswer */


void printMatrix()
{
	
	//printf("\nPrint matrix to a file as function call.\n");
	// we use the FILE library to declare a pointer
	// to our file.
	FILE *outputCsvFile;
	// open our file, give it a name, and append our results to the end.
	outputCsvFile = fopen("PrintOffMatrixPointer.csv","a+");
	fprintf(outputCsvFile, "\nPrinting FromFunction Call \n"); // add one one so we can separate our matrices.
	// loop through the matrix
	for(int rowCounter = 0; rowCounter <ARRAYSIZE; rowCounter++)
	{
		for(int columnCounter = 0; columnCounter < ARRAYSIZE; columnCounter++)
		{
			// print to the command line.
			//printf("\t%f",*(arrayPointer + rowCounter * ARRAYSIZE + columnCounter));
			// print to a file.
			fprintf(outputCsvFile, "%f,", *(arrayPointer + rowCounter * ARRAYSIZE + columnCounter));
			//			fprintf(myfile, "%f, %f, %f, %f, %f, %f\n",
		}
		//printf("\n");
		fprintf(outputCsvFile, "\n");
	}
	fclose(outputCsvFile);

} /* printMatrix */
