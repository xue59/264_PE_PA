#include "answer02.h"
#include "pe02_aux.h"

// the function performs numerical integration of the function
// double function_to_be_integrated(double) over the 
// range lower_limit to upper_limit using the mid-point rule
//
// The range is divided into n_intervals uniform intervals, where the
// left-most interval has a left boundary of lower_limit and the 
// right-most interval has a right boundary of upper_limit (assuming 
// lower_limit <= upper_limit).  
// If lower_limit >= upper_limit, the right-most interval has a right 
// boundary of lower_limit and the left-most interval has a left boundary
// of upper_limit.
// 
// The mid-point rule is used to perform the integration for each interval.
// In the mid-point rule, the integration is approximated by using the
// area of a rectangle, where the height of the rectange is obtained by
// function_to_be_integrated(mid-point of the interval).  The width of
// the rectangle is (interval boundary closer to upper_limit - interval
// boundary closer to lower_limit).  Note that width could be negative
// if upper_limit < lower_limit
//
// The integral is the sum of the integration over all intervals
//
// The caller function has to make sure that n_intervals >= 1
// Therefore, this function may assume that n_intervals >= 1
//
double mid_point_numerical_integration(double lower_limit, double upper_limit, int n_intervals)
{
	// local decleartion
    double integral = 0.0; 
    double y;
    double midX;
    double area;
    double sumArea = 0;
    double width;
    double switching;
	
	// determine if the lower limt is larger than the upper limit, if it's true switch the value
    if (lower_limit > upper_limit)
    {
        switching = lower_limit;
        lower_limit = upper_limit;
        upper_limit = switching;
    }
    
	// calculate the width of the integral
    width = fabs((upper_limit - lower_limit) / n_intervals);
    
	// if the lower limt is smaller than the upper limit then get into the loop calculte the integral
    while(lower_limit < upper_limit)
    {
        midX = (lower_limit + width + lower_limit) / 2;
        y = function_to_be_integrated(midX);
        area = width * y;
        
        sumArea = sumArea + area;
        
        lower_limit = lower_limit + width;
    }
    
	// assign sum Are to the integral
    integral = sumArea;

	// if the lower limit is larger than the upper limit then change the result to be negative
    if (switching == lower_limit)
	{
		integral = integral * (-1);	
	}

    return integral;
}

// the function performs numerical integration of the function
// double function_to_be_integrated(double) over the 
// range lower_limit to upper_limit using the trapezoidal rule
//
// The range is divided into n_intervals uniform intervals, where the
// left-most interval has a left boundary of lower_limit and the 
// right-most interval has a right boundary of upper_limit (assuming 
// lower_limit <= upper_limit).  
// If lower_limit >= upper_limit, the right-most interval has a right 
// boundary of lower_limit and the left-most interval has a left boundary
// of upper_limit.
// 
// The trapezoidal rule is used to perform the integration for each interval.
// In the trapezoidal rule, the integration is approximated by the area of 
// a trapezoid, where the heights of the parallel boundaries of the trapezoid
// are obtained by 
// function_to_be_integrated(left boundary of the interval) and 
// function_to_be_integrated(right boundary of the interval).  
// The width of the trapezoid is (interval boundary closer to upper_limit - 
// interval boundary closer to lower_limit).  Note that width could be negative
// if upper_limit < lower_limit
// the area of a trapezoid is the average of the two heights multiplied by
// the width
//
// The integral is the sum of the integration over all intervals
//
// The caller function has to make sure that n_intervals >= 1
// Therefore, this function may assume that n_intervals >= 1
//
double trapezoidal_numerical_integration(double lower_limit, double upper_limit, int n_intervals)
{	
	// local decleartion
    double integral = 0.0;
    double y_1;
    double y_2;
    double area;
    double sumArea = 0;
    double width;
    double switching;
    
	// if the upper limit is smaller than the lower limit then switch the values
    if (lower_limit > upper_limit)
    {
        switching = lower_limit;
        lower_limit = upper_limit;
        upper_limit = switching;
    }
    
	// calculate the width of the integral
    width = fabs((upper_limit - lower_limit) / n_intervals);
    
	//if lower limit is smaller than the upper limit then get into the loop for futher calculation
    while(lower_limit < upper_limit)
    {
        y_1 = function_to_be_integrated(lower_limit);
        y_2 = function_to_be_integrated((lower_limit + width));
        
        area = (y_1 + y_2) * width * 0.5;
        
        sumArea = sumArea + area;
        
        lower_limit = lower_limit + width;
    }
    
	// assign result to the integral
    integral = sumArea;
	
	// if the upper limit is smaller than the lower limit then change the sign of the result
	
	if (switching == lower_limit)
	{
		integral = integral *(-1);
	}
    return integral;
}
