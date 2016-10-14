#include <stdio.h>
#include <stdlib.h>

// Other than at the specified locations, you are not allowed to make
// changes or insert new statements in this file

// The following include statement includes the declarations of the 
// functions that you have to write in this assignment. Including 
// the definitions allows you to use the functions in this file.

#include "answer01.h"

// At the specified location, modify this function to generate memcheck.log.2 
// Undo the changes after you have generated the log file

void printArray(int * array, int len)
{
    printf("{");
    int ind;

    // inject error
    // change "ind < len" to "ind <= len" for your valgrind output
    // change it back to "ind < len" after you have collected the required 
    // output

    for(ind = 0; ind < len; ++ind) {
	printf("%d", array[ind]);
	if(ind != len - 1) {
	    printf(", ");
	}
    }
    printf("}");
    // If we don't include a '\n' character, then we need to 
    // include this line to ensure that our output is immediately
    // printed out output.
    fflush(stdout); 
}

// Do not modify this function
// Given a filename, this function reads the entries in the file 
// into an array, and returns the array and the size of the array
// the file is assumed to store only numbers.
// The function first determines the number of numbers in the file,
// then allocates the right array size, 
// and reads all the numbers into the array.
//
int *read_in_Array(char *filename, int *arraysize)
{
   if (filename == NULL) {
      *arraysize = 0;
      return NULL;
   } 
   // we have a valid filename
   // check if the file is present, open the file for read operation

   FILE *fp = fopen(filename, "r");
   if (fp == NULL) { // the file is not present, or we don't have the permission to read the file
      fprintf(stderr, "can't open input file, return NULL array\n");
      *arraysize = 0;
      return NULL;
   }

   // check the number of lines in the file

   int n_line = 0;
   while (!feof(fp)) { 
      int read_stat;
      int dummy;
      read_stat = fscanf(fp, "%d ", &dummy);
      if (read_stat != 1) { // no number in that line, return NULL;
	 fprintf(stderr, "input file in wrong format, read_stat %d, return NULL array\n", read_stat);
	 fclose(fp);
         *arraysize = 0;
         return NULL;
      }
      n_line++;
   }
   if (fseek(fp, 0, SEEK_SET) != 0) { // unsuccessfully rewind to the beginning of file   
      fprintf(stderr, "can't rewind input file, return NULL array\n");
      fclose(fp);
      *arraysize = 0;
      return NULL;
   }
   int *array = (int *)malloc(sizeof(int) * n_line);
   if (array == NULL) { // no memory available
      fprintf(stderr, "no memory available, return NULL array\n");
      fclose(fp);
      *arraysize = 0;
      return NULL;
   }

   // now, we can fill in the array
   n_line = 0;
   while (!feof(fp)) {
      int read_stat;
      read_stat = fscanf(fp, "%d ", &(array[n_line]));
      if (read_stat != 1) { // no number in that line, return NULL;
	 fprintf(stderr, "input file in wrong format, return NULL array\n");
	 free(array);
         fclose(fp);
         *arraysize = 0;
         return NULL;
      }
      n_line++;
   }
   fclose(fp);
   *arraysize = n_line;
   return array;
}

// test function for largest_partial_sum
//
void test_largest_partial_sum(int * array, int len, int expected)
{
    printArray(array, len);
    int sum = largest_partial_sum(array, len);
    printf(". partial sum = %d, expected = %d.", sum, expected);
    if(sum != expected)
	printf(" FAIL");
    printf("\n");
}

// test function for largest_difference
void test_largest_difference(int * array, int len, int expected)
{
    printArray(array, len);
    int largestDiff = largest_difference(array, len);
    printf(". largest_difference = %d, expected difference = %d.", largestDiff, expected);
    if(largestDiff != expected)
        printf(" FAIL");
    printf("\n");
}

// test function for largest_partial_sum
//
void test_00_largest_partial_sum()
{
    printf("Testing largest_partial_sum(...)\n");

    // Here we use "static initialization" to create an array
    int array1[] = { -4, -1, 0, 1, 5, 10, 20, 21 };
    int len1 = 8;
    test_largest_partial_sum(array1, len1, 57);

    // Our functions must always work... even on empty arrays
    int array2[] = { };
    int len2 = 0;
    test_largest_partial_sum(array2, len2, 0);

    int array3[] = { 1, 4, -1, 6, -5, 4}; 
    int len3 = 6;
    test_largest_partial_sum(array3, len3, 10);

    int array4[] = { -1, -2, -3, -4 };
    int len4 = 4;
    test_largest_partial_sum(array4, len4, -1);

    // You can add more test-cases here
    // ...
    
    //NEW TEST CASE 11111111111
    int array5[] = { 0,0,0,0,0,0,0,0,0};
    int len5 = 9;
    test_largest_partial_sum(array5, len5, 0);
    
    //NEW TEST CASE 22222222222
    int array6[] = { -1, -2, -3, -4, 5, 6, 7,};
    int len6 = 7;
    test_largest_partial_sum(array6, len6, 18);

    //NEW TEST CASE 33333333333
    int array7[] = { 0, 0, 0, -4, -1, -2, -3, 0, 0 };
    int len7 = 9;
    test_largest_partial_sum(array7, len7, 0);
    
    //NEW TEST CASE 44444444444
    int array8[] = { 1, 4, -1, 6, -5, 4};
    int len8 = 6;
    test_largest_partial_sum(array8, len8, 10);

    printf("\n"); // Tidy output is easier to use
}

// you may want to write your own test function
//
void test_01_largest_difference()
{
    printf("Testing largest_difference(...)\n");
    // write your own test function
    
    // TEST CASE 11111111111111111111
    int array1[] = { 1, 4, -1, 6, -5, 4};
    int len1 = 6;
    test_largest_difference(array1, len1, 11);
    
    // TEST CASE 22222222222222222
    int array2[] = { };
    int len2 = 0;
    test_largest_difference(array2, len2, 0);
    
    // TEST CASE 333333333333333333
    int array3[] = { 1, 4, -1, 6, -5, 4, 0, 0, 0};
    int len3 = 9;
    test_largest_difference(array3, len3, 11);
    
    // TEST CASE 4444444444444444444
    int array4[] = { -1, -2, -3, -4 };
    int len4 = 4;
    test_largest_difference(array4, len4, 3);
    
    // TEST CASE 5555555555555555555
    int array5[] = { 0,0,0,0,0,0,0,0,0};
    int len5 = 9;
    test_largest_difference(array5, len5, 0);
    
    // TEST CASE 666666666666666666
    int array6[] = { -1, -2, -3, -4, 5, 6, 7};
    int len6 = 7;
    test_largest_difference(array6, len6, 11);
    
    // TEST CASE 777777777777777777
    int array7[] = { 0, 0, 0, -4, -1, -2, -3, 0, 0 };
    int len7 = 9;
    test_largest_difference(array7, len7, 4);
    
    // TEST CASE 888888888888888888
    int array8[] = { 1, 4, -1, 6, -5, 4,2,3,4,4,6,7,8,-10,-11,0,0,};
    int len8 = 17;
    test_largest_difference(array8, len8, 19);
    
    printf("\n"); // Tidy output is easier to use
    
    // ...

    printf("\n");
}

// fill in statements to call largest_partial_sum or largest_difference
// depending on the first input argument
//
int main(int argc, char * * argv)
{
    printf("Welcome to ECE264, we are working on PE01.\n\n");
    
    if (argc < 2) {  // when no arguments are given, we are in test mode

    	test_00_largest_partial_sum();
    	test_01_largest_difference();

    } else { // now, try to parse the arguments and call the correct function

	int return_value = 0;
	int *array = NULL;
	int len = 0;

        // fill in the correct statements to complete the main function
	// we expect two arguments:
	//
	// the first argument is an integer from the sets {0, 1}
	// 0: run largest_partial_sum(int * array, int len)
	// 1: run largest_difference(int * array, int len)
	// otherwise: do nothing;
	// for the cases of first argument being 0 or 1, 
	// store the results in the variable return_value, e.g., return_value = largest_partial_sum(...);
	// for the cases of the first argument not being 0 or 1, return_value
	// should remain as 0 since nothing is done
	// print the return_value using the statement printf("%d\n", return_value);
	// 
	// the second argument is a filename.  The function read_in_Array 
	// is called to fill in the array and to initialize len correctly.

	// check that we have an argument for the filename
	// call the function to fill in the array	

        if (argc == 3) {
	    array = read_in_Array(argv[2], &len); 
		printArray(array, len);
        printf("\n");
	} else {
	    return EXIT_FAILURE;
	} 

        // fill in the rest of the statements here
        // so that the correct function is called based on the first argument
        
        // check if the second element of the array is 0 or 1, and the third element inth array should be NULL 
		// then call corrected functions to the return_value
		if ((argv[1][0] == '0') & (argv[1][1] == '\0'))
        {
        	return_value = largest_partial_sum(array, len);
		}
        else if((argv[1][0] == '1') & (argv[1][1] == '\0'))
        {
			return_value = largest_difference(array, len);
		}
		
		printf("%d\n", return_value);
        // fill in the rest of the statements above this line

	if (array != NULL) {
	   free(array);
	}
    }
    return EXIT_SUCCESS;
}
