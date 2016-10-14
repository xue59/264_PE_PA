#include "answer01.h"

/* Return the largest partial sum of the array */
/* int array[] = { 1, 4, -1, 6, -5, 4} */
/* the (i,j)-th partial sum is the sum from array[i] through array[j], i<=j */
/* the (0,0)-(0,5)-th partial sums are 1, 5, 4, 10, 5, 9 */
/* the (1,1)-(1,5)-th partial sums are 4, 3, 9, 4, 8 */
/* the (2,2)-(2,5)-th partial sums are -1, 5, 0, 4 */
/* the (3,3)-(3,5)-th partial sums are 6, 1, 5 */
/* the (4,4)-(4,5)-th partial sums are -5, -1 */
/* the (5,5)-th partial sum is 4 */
/* the largest partial sum of the array is therefore 10 */
/* if the len is 0, the largest partial sum is 0 */
/* you may assume that array is NULL when len is 0 */
/* but is non-NULL and correct when len is > 0 */
/* you may also assume that none of the partial sums will cause an overflow */

int largest_partial_sum(int * array, int len)
{	
	// intinalize the verables 
    int largestSum = array[0];
    int tempSum = 0;
    int i;
    int startingNum = 0;
    
	// in the while loop, the loop would run twice for the inputted arrays 
	// to calculate the partial sum every time and store the larger number 
	// in the variable called largestSum and the print out at the end
    while (startingNum <= len-1)
    {
        for (i = startingNum; i <= len-1; i++)
        {
            tempSum = tempSum + array[i];
            if (tempSum > largestSum)
            {
                largestSum = tempSum;
            }
        }
        tempSum = 0;
        startingNum++;
    }
    
    if (len == 0)
    {
        largestSum = 0;
        tempSum = 0;
    }
    
    return largestSum;
}

/* Return the largest difference of the array */
/* int array[] = { 1, 4, -1, 6, -5, 4} */
/* the largest difference is 6 - (-5) = 11 */
/* if the len is 0, the largest difference is 0 */
/* if the len is 1, the largest difference is also 0 */
/* you may assume that array is NULL when len is 0 */
/* but is non-NULL and correct when len is > 0 */
/* you may assume that the largest difference will not cause an overflow */

int largest_difference(int * array, int len)
{
	// intinalize the variable used in the function
    int largestNum;
    int smallestNum;
    int i;
    int startingNum = 0;
    int largestDifference;
    
	// first set the largest number and smallest number to be the first 
	// element in the array
    largestNum = array[0];
    smallestNum = array[0];
	
	// check if the length is 0, if it is 0 the difference would be 0
    if (len == 0)
    {
        largestDifference = 0;
    
    }
    
	// in the loops would run the array multiple times to find the largest
	// number and smallest number and at the end the largest difference 
	// would be calculated
    else
    {
        while(startingNum <= len-1)
        {
            for(i = startingNum; i <= len-1; i++)
            {
                if(largestNum < array[i])
                {
                    largestNum = array[i];
                }
                
                if(smallestNum > array[i])
                {
                    smallestNum = array[i];
                }
            }
            startingNum++;
        }
        
        largestDifference = largestNum - smallestNum;
    }
    
    
    return largestDifference;
}










