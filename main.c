/*Source code:  PerfectNumber.c
|           Author:  Vanessa Velez-Santos
|     Student ID:  4129302  
|    Assignment:  Program #2 Perfect Number
|  
|            Course:  COP 4338 - Programming III  
|           Section:  U03 
|        Instructor:  William Feild  
|        Due Date:  September 25, at the beginning of class
|
|	I hereby certify that this collective work is my own
|	and none of it is the work of any other person or entity.
|	______________________________________ [Signature]
|  
|        Language:  C
|  Compile/Run:  gcc PerfectNumber.c  –o results.out -lm
|               ./results.out
|  +-----------------------------------------------------------------------------  
  
  Description:  Go through numbers from MIN range to MAX range and 
  find the perfect numbers. Perfect numbers will be found if the number
  is equal to its sum of divisors.

If the number is perfect, display 2 square roots:

1. Use the build in C function for square root
2. Find the square root with the babylonian square root

Find the babylonian square root by:
1. Set the perfect number as the initial guess
2. continue calculating a new guess until accuracy is achieved

Print out the square root result and the iterations it took to get this result

Display the amount of iterations it took to find the babylonian square root.           
        Input:  No input.
  
       Output:  The perfect numbers from MIN to MAX range 
       will bre printed along with their proper divisors. The expected square root    
  
     Process:  Loop through the MIN and MAX
                During the loop, check if the number is perfect by storing its 
                proper divisors and adding them together. Compare this sum with
                the number. If equal, return the perfect number. If it isn't equal, return 0.

                if the current number from the loop is perfect, calculate its square root
                with the regular c function, and print.

                Then calculate using the babylonian method. Set the perfect number
                as the initial guess and keep updating initial guess until we get
               the accuracy we want.    
  
   Required Features Not Included:  
                1. Methods are not efficient.
                2. Babylonian square root calculated incorrectly

    Known Bugs:  None
*/
#include <stdio.h>
#include <math.h> //for square root function

#define NO_ERROR 0
//starting and ending range for finding perfect number
#define MIN_RANGE 1 
#define MAX_RANGE 10000 
#define DECIMAL_PLACES 15 //decimal places for square root output

//prototypes START
int findPerfectNumber(int);
void printDivisors(int[],int);
void babylonianRoot(int);
void printExpectedSqrt(int);
//prototypes END

int main(void) 
{
  int currentNumber = 0; //current number to check if it is perfect starting from MIN_RANGE
  int perfect = 0; //store the possibly perfect number here

  for(currentNumber = MIN_RANGE; currentNumber <= MAX_RANGE; currentNumber++)
  {
    perfect = findPerfectNumber(currentNumber); //check if current number is perfect 
    if(perfect != 0) //if it IS perfect-
    {
      printExpectedSqrt(perfect); //print the sqrt using the built in C function
      babylonianRoot(perfect); //print the sqrt using babylonian method
      printf("\n"); //print new line after each result 
    }
  }

  return NO_ERROR;
}

/* Purpose: Print the square root using C's built in sqrt function

Parameters: A perfect number        
Return: Nothing */
void printExpectedSqrt(int perfect)
{
  printf("\n \t Expected square root: %.*lf \n",DECIMAL_PLACES, sqrt(perfect) ); //square root using the function 
}

/* Purpose: To determine if a number is perfect by checking its sum of divisors and comparing it to itself. 

Parameters: A number from MIN range to MAX range 

Return: Either returns 0 if the number is not perfect, or returns the number itself if it is perfect */
int findPerfectNumber(int num)
{
  int divisor = 0; //the current divisor 
  int divisors[num]; //stores all proper divisors
  int perfectNumber = 0; //remains 0 if there is no perfect number
  int numberOfDivisors = 0; //counts how many divisors there are
  int sumOfDivisors = 0; //keep track of the sum of all divisors

  for(divisor = 1; divisor < num; divisor++)
  {
    if(num % divisor == 0)
    {
      divisors[numberOfDivisors] = divisor; //add the current divisor to the array if it is proper
      numberOfDivisors++; //keep track of HOW MANY divisors we are storing
      sumOfDivisors += divisor; //add it to the sum
    }
  }

  //check if the number is equal to its sum of divisors, making it perfect
  if(num == sumOfDivisors)
  {
     printf("\n Perfect number: %d = ", num);
     printDivisors(divisors, numberOfDivisors); //function to loop and print divisors
     perfectNumber = num; //store the perfect number to return it to main
  }

  return perfectNumber;
}

/*
 * Function: approx_pi
 * --------------------


   returns: Nothing */ 
void printDivisors(int list[],int size)
{
  int index = 0;

  for(index = 0; index < size; index++)
  {
    printf("%d", list[index]); //print out the divisor
    if( index < (size - 1) ) //dont print an extra + at the end 
      printf(" + ");
  }
}

/* Purpose: Find the babylonian square root of the perfect
   number passed in and print it and its iterations

Parameters: A perfect number

Return: Nothing */
void babylonianRoot(int perfect)
{
  int negativeDecimal = -1 * DECIMAL_PLACES, //gives the decimal place as a
                                             // negative int to use as an exponent
      iterations = 0; //keep track of each iteration 
  double accuracyLevel = 1.0 * pow(10,negativeDecimal),
         value = 1,
         sqrt = 0,
         initial = (double)perfect; //use perfect number for its inital approx;

  //loop while the square root is not found depending on accuracy 
  while( ((int)initial - (int)value) > accuracyLevel )
  {
    initial = (initial + value) / 2;
    value = (double)perfect/initial;

    iterations++;
  }
  sqrt = initial; //we have found the square root!

  printf("\t Babylonian square root: %.*lf \n \t Iterations: %d", DECIMAL_PLACES, sqrt, iterations);
}