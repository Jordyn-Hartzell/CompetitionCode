/* started out hello world.
 * it will finish as my determinant.
 * the goal is to use MPI to help
 * with that process.
 */

/* need to work through:
 * https://software.intel.com/en-us/articles/beginning-hybrid-mpiopenmp-development
 */

/* current compile notes:
 * download files with wget morpheus.mcs.utulsa.edu/~papama/hpc/m0016x0016.bin
 * mpicc -g -Wall -fopenmp -o mpi_det_1.exe mpi_det_1.c -lm
 * time mpiexec -n 2 ./mpi_det_1.exe
 */

#include <stdio.h>
#include <string.h>
#include <mpi.h>
#include <stdlib.h>
/* now we are going to try to get omp.
 *
 */

//#include <omp.h>
//int nthreads = 2;
//int required = 4;
//int* provided;

#include <math.h> // lets me use fabs to find the absolute value of a double.
// math.h should also let me take the log of a number.

const int MAX_STRING = 100;
int nodeCounter = 0; /*Index to work throgh my MPI messages.*/
int rowDistributionCounter;


/* add a character holder to hold my input binary file name.*/
char inputDataFileName[50];

//#define ARRAYSIZE 16
//#define FileNameString "m0016x0016.bin"
//m0016x0016.bin, det=3.346535e-04, log(abs(det))=-3.475405e+00

//#define ARRAYSIZE 32
//#define FileNameString "m0032x0032.bin"
//m0032x0032.bin, det=-2.633256e-01, log(abs(det))=-5.795069e-01

//#define ARRAYSIZE 64
//#define FileNameString "m0064x0064.bin"
//m0064x0064.bin, det=3.788989e+07, log(abs(det))=7.578523e+00
// output for 64 was correct, but was taking about 9 seconds to complete.

//#define ARRAYSIZE 128
//#define FileNameString "m0128x0128.bin"
//m0128x0128.bin, det=-3.725889e+38 log(abs(det))=3.857123e+01
// got correct answer, and only took about 4 seconds at school.
// correct answer on pi cluster with 8 nodes in 2.275 seconds.

//#define ARRAYSIZE 512
//#define FileNameString "m0512x0512.bin"
//m0512x0512.bin, det=-1.908922e+304, log(abs(det))=3.042808e+02,

//#define ARRAYSIZE 1000
//#define FileNameString "m1000x1000.bin"
//m1000x1000.bin. det=+inf, log(abs(det))=7.431221e+02
// ran on 8 nodes on pi cluster in 19.546 seconds.

//#define ARRAYSIZE 2000
//#define FileNameString "m2000x2000.bin"
//m2000x2000.bin. det=+inf, log(abs(det))=1.786385e+03
// ran on 8 pi nodes in 1 min 26.902 seconds.

#define ARRAYSIZE 4000
#define FileNameString "m4000x4000.bin"
//m4000x4000.bin. det=-inf, log(abs(det))=1.786385e+03
// did not run on pi cluster.
// susspect mpi message too large...

//#define ARRAYSIZE 5000
//#define FileNameString "m5000x5000.bin"
//m5000x5000.bin, det=-inf,log(abs(det))=5.464118e+03

/* define an array pointer for us to keep our big set of numbers.*/
double* arrayPointer; 



/*Prototype custom methods.*/
void readInMatrix();
void printMatrix(); // used to print off the matrix as it currently stands.
//void makeUpperTriangularMatrix(); // use this to make the upper triangular matrix.

int main(void)
{
	char	greeting[MAX_STRING];
	int 	comm_sz; /* Number of Processes */
	int 	my_rank; /* My process rank */

	
	//MPI_Init_thread(NULL, NULL, required, &provided);
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	
	// set everyone up to have a place to hold the data.
	arrayPointer = (double*)malloc(ARRAYSIZE * ARRAYSIZE * sizeof(double));

	if (my_rank == 0)
	{
		printf("Greetings from trying to read in matrix.\n");
		readInMatrix();
		//printMatrix();
		printf("Broadcast the matrix out to everyone.\n");
	}
	// Distribute pivot row to all nodes using a collective communication of broadcast.
	for(rowDistributionCounter = 0; rowDistributionCounter < ARRAYSIZE; rowDistributionCounter++)
	{
		// old message too long at 4 and 5 k long.
		//MPI_Bcast((arrayPointer + rowDistributionCounter * ARRAYSIZE), ARRAYSIZE, MPI_DOUBLE, 0, MPI_COMM_WORLD);
		// try to split in half.
		//MPI_Bcast((arrayPointer + rowDistributionCounter * ARRAYSIZE), (ARRAYSIZE/2), MPI_DOUBLE, 0, MPI_COMM_WORLD);
		//MPI_Bcast((arrayPointer + rowDistributionCounter * ARRAYSIZE + ARRAYSIZE/2), 
		//	  (ARRAYSIZE/2), MPI_DOUBLE, 0, MPI_COMM_WORLD);
		// try to split in 4.
		MPI_Bcast((arrayPointer + rowDistributionCounter * ARRAYSIZE), (ARRAYSIZE/4), MPI_DOUBLE, 0, MPI_COMM_WORLD);
		MPI_Bcast((arrayPointer + rowDistributionCounter * ARRAYSIZE + ARRAYSIZE/4), (ARRAYSIZE/4), MPI_DOUBLE, 0, MPI_COMM_WORLD);
		MPI_Bcast((arrayPointer + rowDistributionCounter * ARRAYSIZE + ARRAYSIZE/2), (ARRAYSIZE/4), MPI_DOUBLE, 0, MPI_COMM_WORLD);
		MPI_Bcast((arrayPointer + rowDistributionCounter * ARRAYSIZE + 3*ARRAYSIZE/4), (ARRAYSIZE/4), MPI_DOUBLE, 0, MPI_COMM_WORLD);
	}
	// Distribute individual rows as needed
	//if (my_rank == 0)
	//{
	//	for(rowDistributionCounter = 1; rowDistributionCounter < ARRAYSIZE; rowDistributionCounter++)
	//	{
	//		MPI_Send(
	//			(arrayPointer + rowDistributionCounter * ARRAYSIZE),
	//			 ARRAYSIZE, 
	//			MPI_DOUBLE, 
	//			rowDistributionCounter%comm_sz, 
	//			1, 
	//			MPI_COMM_WORLD);
	//	}
	//}
	
	// revieve individual rows as needed.
	//if (my_rank != 0)
	//{
	//	for(rowDistributionCounter = 1; rowDistributionCounter < ARRAYSIZE; rowDistributionCounter++)
	//	{
	//		if (my_rank == rowDistributionCounter%comm_sz)	
	//		{
	//			MPI_Recv(
	//				(arrayPointer + rowDistributionCounter * ARRAYSIZE),
	//			 	ARRAYSIZE, 
	//				MPI_DOUBLE, 
	//				0,
	//				1, 
	//				MPI_COMM_WORLD,
	//				MPI_STATUS_IGNORE);
	//		}
	//	}
	//}
	
	// make an upper triangular matrix
	//makeUpperTriangularMatrix();
	if (my_rank == 0)
	{
		printf("Start forming the upper triangular.\n");
	}
	
	
	int columnToGetZeros = 0;
	int rowToWorkOn = 0;
	double rowReductionConstant = 0;
	int columnCounter = 0;
	for(columnToGetZeros = 0; columnToGetZeros <(ARRAYSIZE-1); columnToGetZeros++)
	{
		
		for(rowToWorkOn = (columnToGetZeros+1); rowToWorkOn < ARRAYSIZE; rowToWorkOn++)
		{
			if (my_rank == rowToWorkOn%comm_sz)	
			{
				rowReductionConstant =
					*(arrayPointer + rowToWorkOn * ARRAYSIZE + columnToGetZeros )
					/ *(arrayPointer + columnToGetZeros * ARRAYSIZE + columnToGetZeros );
				
//#pragma omp parallel for	
				for(columnCounter = columnToGetZeros; columnCounter < ARRAYSIZE; columnCounter++)
				{
					*(arrayPointer + rowToWorkOn * ARRAYSIZE + columnCounter )
						= *(arrayPointer + rowToWorkOn * ARRAYSIZE + columnCounter )
						- rowReductionConstant *
						*(arrayPointer + columnToGetZeros * ARRAYSIZE + columnCounter );
				}
			}
			
		}
		// transmit the next pivot row.
		MPI_Bcast((arrayPointer + (columnToGetZeros + 1) * ARRAYSIZE), (ARRAYSIZE/4), MPI_DOUBLE, (columnToGetZeros+1)%comm_sz, MPI_COMM_WORLD);
		MPI_Bcast((arrayPointer + (columnToGetZeros + 1) * ARRAYSIZE + ARRAYSIZE/4), (ARRAYSIZE/4), MPI_DOUBLE, (columnToGetZeros+1)%comm_sz, MPI_COMM_WORLD);
		MPI_Bcast((arrayPointer + (columnToGetZeros + 1) * ARRAYSIZE + ARRAYSIZE/2), (ARRAYSIZE/4), MPI_DOUBLE, (columnToGetZeros+1)%comm_sz, MPI_COMM_WORLD);
		MPI_Bcast((arrayPointer + (columnToGetZeros + 1) * ARRAYSIZE + 3*ARRAYSIZE/4), (ARRAYSIZE/4), MPI_DOUBLE, (columnToGetZeros+1)%comm_sz, MPI_COMM_WORLD);
		
	}
	
	if (my_rank == 0)
	{
		printf("Done forming the upper triangular.\n");
	}
	
	// work the diagonal to get the det and log abs det.
	if (my_rank == 0)
	{
		double logOfAbsOfDiagonalHolder;
		double diagonalHolder;
		int diagonalAddress;
		double diagonalMultiplier = 1;
		double addAsWeGoLogAbsDet = 0;
		for(diagonalAddress = 0; diagonalAddress < ARRAYSIZE; diagonalAddress++)
		{
			diagonalHolder =*(arrayPointer + diagonalAddress * ARRAYSIZE + diagonalAddress);
			//printf("Diagonal number %d is %f.\n", diagonalAddress, diagonalHolder);
			logOfAbsOfDiagonalHolder = log10(fabs(diagonalHolder));
			//printf("The log of the absolute value of %f is %f.\n", diagonalHolder, logOfAbsOfDiagonalHolder);
			diagonalMultiplier = diagonalMultiplier * diagonalHolder;
			//printf("The diagonal multiplied all together is: %e.\n",diagonalMultiplier);
			addAsWeGoLogAbsDet = addAsWeGoLogAbsDet + logOfAbsOfDiagonalHolder;
			//printf("Add as we go of the log of the abs of the det is %e.\n", addAsWeGoLogAbsDet);
		}
		printf("\nLast output: The diagonal multiplied all together is: %e.\n",diagonalMultiplier);
		printf("Last output: Add as we go of the log of the abs of the det is %e.\n", addAsWeGoLogAbsDet);
		
	}

	
	
	// Greetings from our nodes right before the end of main.
	if (my_rank != 0)
	{
		
		sprintf(greeting, "Goodbye from process %d of %d!", 
			my_rank, comm_sz);
		MPI_Send(greeting, strlen(greeting)+1, MPI_CHAR, 0, 0, 
			MPI_COMM_WORLD);
	} else 
	{
		printf("Goodbye from process %d of %d!\n", my_rank,
			comm_sz);
		for(nodeCounter = 1; nodeCounter < comm_sz; nodeCounter++)
		{
			MPI_Recv(greeting, MAX_STRING, MPI_CHAR, nodeCounter,
				0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			printf("%s\n", greeting);
		}
	}
	MPI_Finalize();
	return 0;
}/*main*/

// make an upper triangular matrix
//void makeUpperTriangularMatrix()
//{
	//}/*makeUpperTriangularMatrix()*/

void readInMatrix()
{
	printf("Greetings from inside the read in matrix function.\n");
	
	// malloc now handled in main to get an array location for everyone."
	//arrayPointer = (double *)malloc(ARRAYSIZE * ARRAYSIZE * sizeof(double));
	
	// make a for loop inside a for loop to build a placeholder for 
	// all the zeros.
	int rowCounter;
	int columnCounter;
	for(rowCounter = 0; rowCounter < ARRAYSIZE; rowCounter++)
	{
		for( columnCounter = 0; columnCounter < ARRAYSIZE; columnCounter++)
		{
			*(arrayPointer + rowCounter * ARRAYSIZE + columnCounter ) = 0;
		}
	}

	sprintf(inputDataFileName, FileNameString);
	printf("Reading array file %s of size %dx%d\n", inputDataFileName, ARRAYSIZE, ARRAYSIZE);

	FILE *inputDataFile = fopen(inputDataFileName,"rb");

	for(rowCounter = 0; rowCounter < ARRAYSIZE; rowCounter++)
	{
		for( columnCounter = 0; columnCounter < ARRAYSIZE; columnCounter++)
		{
			fread((arrayPointer + rowCounter * ARRAYSIZE + columnCounter),
				sizeof(double),1,inputDataFile);
		}
	}
	printf("Finished reading array file %s of size %dx%d\n", inputDataFileName, ARRAYSIZE, ARRAYSIZE);
	printf("Farewell from the readInMatrixFunction.\n");
	return;
}/*readInMatrix*/

void printMatrix()
{
	printf("\nPrint matrix to a file as function call.\n");
	// we use the FILE library to declare a pointer
	// to our file.
	FILE *outputCsvFile;
	// open our file, give it a name, and append our results to the end.
	outputCsvFile = fopen("PrintOffMatrixPointer.csv","a+");
	fprintf(outputCsvFile, "\nPrinting FromFunction Call \n"); // add one one so we can separate our matrices.
	// loop through the matrix
	int rowCounter;
	int columnCounter;
	for(rowCounter = 0; rowCounter <ARRAYSIZE; rowCounter++)
	{
		for(columnCounter = 0; columnCounter < ARRAYSIZE; columnCounter++)
		{
			// print to the command line.
			//printf("\t%f",*(arrayPointer + rowCounter * ARRAYSIZE + columnCounter));
			// print to a file.
			fprintf(outputCsvFile, "%f,", *(arrayPointer + rowCounter * ARRAYSIZE + columnCounter));
			//			fprintf(myfile, "%f, %f, %f, %f, %f, %f\n",
		}
		//printf("\n");
fprintf(outputCsvFile, "\n");
