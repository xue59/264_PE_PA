#include <stdio.h>
#include <stdlib.h>
// you do not have to include pe02_aux.h here because you are not 
// calling the function function_to_be_integrated here
#include "answer02.h"

// fill in the correct statements to complete the main function
// we expect four arguments:
//
// the first argument is two characters from the sets {"-m", "-t"}
// -m: run mid_point_numerical_integration
// -t: run trapezoidal_numerical_integration
// otherwise: return EXIT_FAILURE
      
// to run any of the two functions, expect the next three arguments
// to be the lower limit of the integration (double), the upper limit
// of the integration (double), and the number of intervals for the
// integration (int)
//
// if the number of intervals is less than 1, set it to 1

// use atof to convert an argument to a double 
// use atoi to convert an argument to an int

// after you have numerically integrated the function, print the 
// return value, and return EXIT_SUCCESS
//

int main(int argc, char * * argv)
{
    double integral = 0.0; // local decleartion	
    double lower; // local decleartion
    double upper; // local decleartion
    double numN; // local decleartion
	
	lower = atof(argv[2]); // asign user inputted number to lower, upper and number or intervals
	upper = atof(argv[3]);
	numN = atof(argv[4]);

    if (argc < 5 || argc > 5) // if there is no enough input return failure
    {
		return EXIT_FAILURE;
    }
    
    else
    {
        if (argv[1][2] == '\0' && argv[1][0] == '-' && argv[1][1] == 'm') // if input -m using the mid point rule
        {
            integral = mid_point_numerical_integration(lower, upper, numN); // call using mid point rule
        }
        
        if (argv[1][2] == '\0' && argv[1][0] == '-' && argv[1][1] == 't') // if input -t use the trapezodial rule
        {
            integral = trapezoidal_numerical_integration(lower, upper, numN); // call function to use the trapezoidial rule
        }
    }
    
    printf("%.10e\n", integral); // print the inegral
    
    return EXIT_SUCCESS;
}
