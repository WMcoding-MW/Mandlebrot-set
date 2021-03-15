#ifndef MANDLEBROT_H
#define MANDLEBROT_H
// save diagnostic state                                                       
#pragma GCC diagnostic push
// turn off specific warnings.                                                 
#pragma GCC diagnostic ignored "-Wall"
#pragma GCC diagnostic ignored "-Wconversion"
#include <Magick++.h>
using namespace Magick;
// turn the warnings back on                                                   
#pragma GCC diagnostic pop

#include <iostream>
#include <cmath>

struct complex{
    double x; //a
    double y; //bi
};

const Color white = "white"; //colour of white
const Color black = "black"; //colour of black
const Color pink = "pink"; //colour of pink
const Color orange = "orange"; //colour of orange

const char widthPrompt[40] = "Please enter the width of the image: ";
const double re_start = -1.5; //starting value for the Real plane in (a+bi)
                              //x-axis
const double re_end = 0.5; //ending value for the Real plane in (a+bi), x-axis
const double im_start = -1; //starting value for the Imaginary plane in (a+bi)
                            // y-axis
const double im_end = 1;  //ending value for the Real plane in (a+bi), y-axis
const char depthPrompt[40] = "Please enter the amount of iterations: ";
const char writePrompt[40] = "Please enter the filename to write to: ";
const int maxLength = 100; //maximum length for a file name
const int minLength = 1; //minimum length for a file name

//************************************************************************
/*
  Name: drawMandle                                                           
                                                                               
  Purpose: To draw the mandlebrot set pixel by pixel onto a canvas using 
           Magick++.
                                                                               
  Details: This function begins by checking if the current values for i and j
           have met the base condition. The base condition is when j
	   is equaled to the canvas size of the image. once this happens the 
	   recursion is ended. Until then, the function checks if the j 
	   value (the x-coordinate) has reached the end of the current
	   row, if so then the function recursion is ended.
	   From here, the current i and j are converted into
	   a complex number that fits the dimenisions of the constants
	   provided for the real and imaginary axis. next, the function then
	   uisng that new complex equation calls another function that will 
	   determine if this specific set of i and j values will fit inside
	   of the mandlebrot set. if so, then the pixel is coloured white, 
	   if not, then the pixel is coloured depending on the depth/maxDepth 
	   value coloured. Which this colouring mechanism creates
	   a symmetric effect. after this has been done the dynamically 
	   allocated
	   variables are deleted from the heap and the function is called 
	   again recurisvely until the inital base case has been hit. 
                                                            
  Input Parameters:                                                            
                    int i; the y coordinate
		    int j; the x coordinate
		    Image image; the current canvas
		    int c1; the variable that will effect which colour is drawn
		    int depth; the amount of iterations of the mandlebrot set
                                                                           
  Output Parameters:                                                           
                    Image image; the updated canvas                   
		    */
void drawMandleX(int i, int j, Image *image, int c1, int depth);

//**************************************************************************** 
/*                                                                             
  Name: drawMandleY                                                            
                                                                               
  Purpose: To increment the y coordinate, to be drawn.                  
                                                                               
  Details: increments the y coordinate to be drawn on the canvas if it does
           not equal the height of the image, if it equals the height of the 
	   image, then the function returns and exits the recursion. if it 
	   does not, it calls upon the drawMandleX function which will 
	   increment and draw each x value in that row.
                                                                               
  input parameters: complex z; set of coordinates                              
                    complex c; set of coordinates                              
                                                                              
 */
void drawMandleY(int i, int j, Image *image, int &c1, int depth);
//*****************************************************************************
/*                                                                             
  Name: convertComplex                                                         
                                                                               
  Purpose: Maps coordinates from R^2 :-> C^2 based on a set axis. 
                                     
  Details: This function preforms the calculations in order to convert an 
           x and y coordinate pair into an a+bi vector. For example 
	   suppose we had x = 0 and y = 0; and suppose width is 100.
	   the function first calculates the a value by using the equation 
	   a = RE_START + (x / width) * (RE_END - RE_START)
             = -1.5 + (0/100) * (0.5 - -1.5)
	     = -1.5 + 0 * 2
	     = -1.5
	   b = IM_START + (y / width) * (IM_END - IM_START)
	     = -1 + (0/100) * (1 - -1)
	     = -1 + 0 * 2
	     = -1
	   therefore (0,0) in R^2 would be equal to the vector of -1.5 - 1i 
	   in C^2 given the specifed plane dimensions.

  Input Parameters: int width; current width of the canvas
                    complex c; the soon to be complex coordinates
		    int x; the x coordinate
		    int y; the y coordinate
                                                                               
  Output Parameters: complex c; the new vector of (a+bi) in C^2         
                     int numIter; updated iteration count
*/
void convertComplex(int width, complex &c, int x, int y);

//****************************************************************************
/*
 Name: mandlebrotCheck 

 Purpose: determines whether a given portion of coordinates is within the 
          mandlebrot set.

 Details: An vector of (a+bi) is said to be in the mandlebrot set if and 
          a^2+b^2 < 2. typically after calculations the value will be 
	  stagnated and not grow as much, but if they are not within the
	  mandlebrot set, the value will exponentially grow until it
	  reaches infinity. Using recursion this function will recusively call
	  upon itself until it has reached the given depth and 
	  recursively calculate the new z value. 

 Input parameters: complex *z; Set of new coordinates in form(a+bi)
                   complex *c; Set of coordinates in form (a+bi)
		   int i; Counter to see when you reach depth
		   int depth; Maxmimum amount of iterations to check
		   int numIter; number of iterations required for a^2+b^2 > 2 
 Output parameters: complex z; updated coordinates
                    complex c; pointer to the coordinates
 */
complex mandlebrotCheck(complex *z, complex *c, int i, int depth,
			int &numIter);

//****************************************************************************
/*
  Name: mandleCalc

  Purpose: To update the coordinates in the complex vector z

  Details: The function first checks if a^2+b^2 < 2, if so then the function 
           will continue with updating z, if z is already greater than 2, then
	   there is no reason for z to be updated as it's already determined 
	   to be unbounded and not within the mandlebrot set. 

  input parameters: complex z; set of coordinates
                    complex c; set of coordinates
		    int numIter; number of iterations required for a^2+b^2 > 2

  output parameters: int numIter; updated iteration count 
                    
 */
complex mandleCalc(complex z, complex *c, int &numIter);

#endif
