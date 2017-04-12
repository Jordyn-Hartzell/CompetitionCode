/*
 ============================================================================
 Name        : det.c
 Author      : Jeremy Evert
 Version     :
 Copyright   : MIT License
 Description : Hello World in C, Ansi-style
 ============================================================================
 */


/** Jeremy's code to find determinants, version one for c.
 * Once upon a time, we wanted to compete in the Oklahoma
 * High Performance Computing competition. The team has done a great
 * job getting money to buy clusters and putting clusters together.
 * They have done a good job of setting up the clusters. But the
 * program to make the clusters do the thing has been lacking. However,
 * part of the reason for this is a lack of quality educational leadership.
 * To be more specific, Jeremy didn't show them how to do it. This is in the
 * short term. In the long term, Jeremy didn't help them learn how to do it.
 * So in order to do number two, we must work on number one. And this is the
 * code that helps Jeremy think through how to do it.
 *
 * The goal on this code is to make everything mostly modular.
 * This should make it easier to tweak the code later and make it run faster.
 * Key word there is should. It could also make the code into spaghetti.
 * It will be interesting.
 *
 * I am going to use the main function to lay out the major steps.
 *
 * Then I am going to go use custom functions to go lay out the
 * key parts of those steps.
 *
 * Then I am going to go start to do the thing.
 *
 * Then I am going to try to do it better...
 *
 * All of this is easier said than done.
 * For each little component, I am going to do a function call.
 * I plan on using a pointer to my data.
 * I don't plan on the functions returning anything.
 * I plan on them doing the work inside the function.
 *
 */

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

/* now we are going to try to get omp.
 *
 */
#include <omp.h>
int nthreads = 4;

/* Reading in data using online code from University of Tulsa.
 * Using their code for a starting point.
 * Just trying to get something to work...
 */

char inputDataFileName[50]; // declares the array to hold our binary input file name.

//#define ARRAYSIZE 5024
//#define FileNameString "m5024x5024.bin"
//m5024x5024.bin, det=+inf,log(abs(det))=5.494860e+03
/*
 * The diagonal multiplied all together is: inf.
Rounded to a double, this is: inf.
Add as we go of the log of the abs of the det is 5.494860e+03.
The log of the absolute value of the determinant is: inf.
Time taken: 566.523253.
 */

// tried to change optimization from none up to optimize most.
// We will see how this changes the time to go.
/*
 *The diagonal multiplied all together is: inf.
Rounded to a double, this is: inf.
Add as we go of the log of the abs of the det is 5.494860e+03.
The log of the absolute value of the determinant is: inf.
Time taken: 159.053656.
Note: this uses
make all
Building file: ../src/det.c
Invoking: GCC C Compiler
gcc -O3 -g3 -Wall -c -fmessage-length=0 -fopenmp -MMD -MP -MF"src/det.d" -MT"src/det.d" -o "src/det.o" "../src/det.c"
 */


#define ARRAYSIZE 5000
#define FileNameString "m5000x5000.bin"
//m5000x5000.bin, det=-inf,log(abs(det))=5.464118e+03
/*
 * The diagonal multiplied all together is: -inf.
The log of the absolute value of the determinant is: inf.
Time taken: 534.599812. So nearly 9 minutes to get the wrong answer...
 */

/*
 * Turn on openMP and optimizations.
 *The diagonal multiplied all together is: -inf.
Rounded to a double, this is: -inf.
Add as we go of the log of the abs of the det is 5.464118e+03.
The log of the absolute value of the determinant is: inf.
Time taken: 424.519161.
 */

//#define ARRAYSIZE 4000
//#define FileNameString "m4000x4000.bin"
//m4000x4000.bin,det=-inf, log(abs(det))=4.176335e+03

/*
 * The diagonal multiplied all together is: -2.162817e+4176.
The log of the absolute value of the determinant is: 4.176335e+03.
Time taken: 286.576013.
 */

//#define ARRAYSIZE 3000
//#define FileNameString "m3000x3000.bin"
//m3000x3000.bin, det=-inf, log(abs(det))=2.945781e+03
/*result
 * The diagonal multiplied all together is: -6.034397e+2945.
The log of the absolute value of the determinant is: 2.945781e+03.
Time taken: 111.713879.
 */

/*
 * Now we add openMP:
 * The diagonal multiplied all together is: -6.034397e+2945.
Rounded to a double, this is: -inf.
Add as we go of the log of the abs of the det is 2.945781e+03.
The log of the absolute value of the determinant is: 2.945781e+03.
Time taken: 275.466254.
 */

/* turning on optimize most in the project settings and openMP.
 * The diagonal multiplied all together is: -6.034397e+2945.
Rounded to a double, this is: -inf.
Add as we go of the log of the abs of the det is 2.945781e+03.
The log of the absolute value of the determinant is: 2.945781e+03.
Time taken: 114.347693.
 */

//#define ARRAYSIZE 2048
//#define FileNameString "m2048x2048.bin"
//m2048x2048.bin, det=+inf, log(abs(det))=1.838927e+03, time:
// note: with current code, this is getting a log value that is too large.
// I am going to see if I can use a long double to keep track.
/*
 * output now:
 * The diagonal multiplied all together is: 8.459398e+1838.
 * The log of the absolute value of the determinant is: 1.838927e+03.
 * Time taken: 30.564942.
 */

/* after adding openMP:
 * The diagonal multiplied all together is: 8.459398e+1838.
Rounded to a double, this is: inf.
Add as we go of the log of the abs of the det is 1.838927e+03.
The log of the absolute value of the determinant is: 1.838927e+03.
Time taken: 109.525889.
 */

//#define ARRAYSIZE 512
//#define FileNameString "m0512x0512.bin"
//m0512x0512.bin, det=-1.908922e+304, log(abs(det))=3.042808e+02, time: 0.582746, 0.555018, 0.557018, 0.527063

//#define ARRAYSIZE 496 // Starting out small.
//#define FileNameString "m0496x0496.bin"
// m0496x0496.bin, det=5.948068e+292, log(abs(det))=2.927744e+02, time: 0.537939, 0.567946, 0.564027

/* after adding openMP:
 * The diagonal multiplied all together is: 5.948068e+292.
Rounded to a double, this is: 5.948068e+292.
Add as we go of the log of the abs of the det is 2.927744e+02.
The log of the absolute value of the determinant is: 2.927744e+02.
Time taken: 2.489351.
 */

//#define ARRAYSIZE 16 // Starting out small.
//#define FileNameString "m0016x0016.bin"
//m0016x0016.bin, det=3.346535e-04, log(abs(det))=-3.475405e+00, Time taken: 0.000624.

/* after adding openMP:
 * The diagonal multiplied all together is: 3.346535e-04.
Rounded to a double, this is: 3.346535e-04.
Add as we go of the log of the abs of the det is -3.475405e+00.
The log of the absolute value of the determinant is: -3.475405e+00.
Time taken: 0.175008.
 */

/* We are going to use a pointer and not a variable.
 * This will allow us to use Malloc.
 */
double *arrayPointer; // define a pointer to hold our array.

/* We will use the variable diagonalMultiplerVariableDouble
 * to keep track of all of our values along the diagonal
 * of our upper triangular matrix as we multiply them together.
 * The multiplication identity is 1.
 * This means our variable will take on whatever value it
 * is multiplied by.
 *
 * The variable diagonalMultiplierVariableDouble
 * is also the determinant when it is complete.
 * Because this will often be a large positive or negative
 * number, we will also record the log of the absolute value of
 * the number.
 */
long double diagonalMultiplierVariableLongDouble = 1;
long double logOfAbsoluteValueOfDeterminant = 0;

/* I am going to try to add the log of the determinats
 * as I go instead of multiplying the numbers in the first
 * place.
 * So with the old variables, I would do
 * 10 * 10 * 10 = 1,000.
 * But the log of 10 is 1.
 * and the log of 1,000 is 3.
 * So I need to do
 * log(10) + log(10) + log(10).
 *
 */
double addAsWeGoLogAbsDet = 0;

/*
 * We want to keep track of how long each of these processes take.
 * To do this, we will use the time.h header.
 * This allows us to use clock_t, clock(), and CLOCKS_PER_SEC.
 */
double time_taken;

/* prototype custom function calls. */
void readDataFromDotBinIntoMatrix ();
void makeUpperTriangularFunction ();
void multiplyDiagonalAndReturnAnswer ();
//void printMatrix(); // used to print off the matrix as it currently stands.


int main(void) {
	puts("!!!Hello Class!!!"); /* prints !!!Hello Class!!! */

	/* Read in the data from the .bin file */
	readDataFromDotBinIntoMatrix();

	// set up the clock, using tools from the time.h library.
	clock_t timeOfProcessInProcessorCycles;
	timeOfProcessInProcessorCycles = clock(); // start the clock running.

	/* Make an upper triangular matrix */
	makeUpperTriangularFunction ();

	/* Multiply the diagonal to produce the determinant. */
	multiplyDiagonalAndReturnAnswer ();

	// use tools from the library to get the clock time.
	timeOfProcessInProcessorCycles = clock() - timeOfProcessInProcessorCycles;
	time_taken = ((double)timeOfProcessInProcessorCycles)/CLOCKS_PER_SEC; // in seconds
	printf("Time taken: %f.\n",time_taken);

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
			// trying to get openMP to work.
			// http://www.openmp.org/wp-content/uploads/omp-hands-on-SC08.pdf
			//m0016x0016.bin, det=3.346535e-04, log(abs(det))=-3.475405e+00, Time taken: 0.000624.
#pragma omp parallel for
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
	 * m0016x0016.bin, det=3.346535e-04, log(abs(det))=-3.475405e+00
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

	//char inputDataFileName[50];

	// open file
	//sprintf(inputDataFileName,"m0016x0016.bin");
	/* from University of Tulsa website:
	 * m0016x0016.bin, det=3.346535e-04, log(abs(det))=-3.475405e+00
	 */
	//sprintf(inputDataFileName,"m0496x0496.bin");
	sprintf(inputDataFileName,FileNameString);
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
	/* from University of Tulsa website:
	 * m0016x0016.bin
	 * det=3.346535e-04
	 * log(abs(det))=-3.475405e+00
	 */
	printf("\nThe diagonal multiplied all together is: %Le.\n",diagonalMultiplierVariableLongDouble);
	printf("Rounded to a double, this is: %e.\n",(double)diagonalMultiplierVariableLongDouble);
	printf("Add as we go of the log of the abs of the det is %e.\n", addAsWeGoLogAbsDet);

	/*
	 * In the words of the great Chantz Drake, when you
	 * multiply 5,000 numbers together, you get a great
	 * number. This is going to be either positive or negative
	 * infinity.
	 * So to help with this, sometimes they find
	 * the log of the value.
	 * Because you can only find the log of positive numbers
	 * you will need to find the absolute value first.
	 * So we need two functions to help us.
	 * To find the absolute value of a double, we use
	 * fabs, as abs is the absolute value of ints.
	 * Next we need the base 10 log. This is log10.
	 * However, to make these make sense to the compiler,
	 * we have to include the math.h library.
	 * However, we also have to include the math library in
	 * the linker.
	 * To do this, you could tell the code
	 * gcc -o det.exe det.c -lm
	 * However, to get this built into the eclipse
	 * environment, go to
	 * project
	 * 	properties
	 * 	 c/c++ build
	 * 	  gcc c linker
	 * 	   libraries
	 * and where it says libraies (-l)
	 * we need to add an m.
	 * And then bob is your uncle...
	 *
	 * Later on I hit a wall about 2048.
	 * then I tried to use a long double for my diagonal.
	 * to do a long double abs, use fabsl.
	 * I alson need to do log10l
	 */

	logOfAbsoluteValueOfDeterminant = log10l(fabsl(diagonalMultiplierVariableLongDouble));

	printf("The log of the absolute value of the determinant is: %Le.\n",logOfAbsoluteValueOfDeterminant);

	//long double tryFabf = log10l(fabsf(diagonalMultiplierVariableDouble));
	//printf("The log of the absolute value fabsf of the determinant is: %Le.\n",tryFabf);

	return;
} /* multiplyDiagonalAndReturnAnswer */


//void printMatrix()
//{
/*
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
 */
//} /* printMatrix */
