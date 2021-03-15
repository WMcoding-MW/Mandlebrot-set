/***************************************************************               
* Name: William Marks                                                                                                        
* File name: mandlebrot.cpp                                                   
*                                                                              
* Purpose:  Generate a mandlebrot set using the magick++ library in order
            to help visualize and draw the image created to a file.

* Details: The mandlebrot set can be defined as by a set of complex numbers 
           which in our case any number such that a^2+b^2 < 2 is within the
           mandlebrot set. any value of a^2+b^2 > 2 is not within the 
           mandlebrot set and will be coloured accordingly. In my drawings, any
           pixel color of white is within the mandlebrot set. I decided to 
           divide the total depth needed by the max depth, 
           then i normalized the 
           value from that calulcation so that it would work with any data set.
           finally if the absolute value is less that 1, it is coloured 
           accordingly. which makes a very neat symmetric photo. Inputs 
           I would reccomend would be:
           1)
             width: 500x500
             iterations: 1000

           2)
             width: 1000x1000  
             iterations: 30

           3) 
             width: 1000x1000
             iterations: 100

           It's important to note that in order to calculate the mandlebrot 
           set, the "depth" of the image is a very touchy manner. the lower
           the value of the depth the more fuzzy and less accurate the image 
           will be. The greater the number for depth the more accurate
           the image generated will be. Of course having a greater depth means
           more recursion and longer compile times. For more resources on
           fractal geometry which is the mathematical domain in which 
           the mandlebrot set is apart of, I reccomend the book "Fractals and 
           Chaos: The Mandelbrot Set and Beyond" by the founder himself
           Benoit Mandelbrot. This particular program takes the user input for 
           the width of an image which will be size (n x n) and the depth or
           the amount of iterations that will occur when calculating if a
           particular point is within the mandlebrot set. From here a function
           is called that will recursively loop until each pixel has been 
           checked if they do infact exist within the mandlebrot set or do-not.
           for each pixel, they are first converted into the confines of the 
           complex plane given to use. on the real-axis values of -1.5 - 0.5
           and on the imaginary axis values of -1 - 1 are used. After they 
           have been converted to fit within these domains they are then 
           checked to see if they actual exist within the mandlebrot set.
           an equation of f(z) = z^2 + c is used in order to calculate this.
           the amount of times calculated all depends on how deep the depth is.
           as stated earlier the deeper the depth the slower but more accurate.
           the lower the depth the faster but less accurate. Once each pixel
           has been calculated, the user is then asked if they would like to 
           write the image to a file and if so what file name. if <ctrl-d>
           is entered anywhere for the user input, then the program displays
           an appropriate error message and exits.
           
*/
#include "ioutil.h"
#include "mandlebrot.h"

int main(){    
    Image *image = new Image("1x1", "black"); //canvas to be drawn on.
    int i; //y coordinate
    int j; //x coordinate
    int c1 = 0; //used to determine what colour to be printed
    int depth; //number of iterations to calculate the mandlebrot
    int width; //width of the image
    bool eof; //false unless <ctrld-d> is entered for an input
    char file[100]; //file name
    width = readInt(widthPrompt, eof);
    if(eof != true){
	depth = readInt(depthPrompt, eof);
	if(eof != true){
	    image->resize(Geometry(width+1,width+1));
	    i = 0;
	    j = 0;
	    drawMandleY(i, j, image, c1, depth);
	    readString(writePrompt, file, maxLength, minLength, eof);
	    if(eof != true){
		image->write(file);
	    }else{
		std::cout << "\nError: could not be written to file.";
	    }
	    delete image;
	}else{
	    std::cout<< "\nError: could not read depth.";
	}
    }else{
	std::cout << "\nError: could not read width.";
    }
    return 0;
}

complex mandlebrotCheck(complex *z, complex *c, int i, int depth,
			int &numIter){
    if(i == depth){ //base case
        z->x = 0;
        z->y = 0;
    }else if(i < depth){ //recursive case
        i++;
        *z = mandleCalc(mandlebrotCheck(z,c,i,depth,numIter),c,numIter);
    }
    return *z;
}

complex mandleCalc(complex z, complex *c, int &numIter){
    complex o; //(a+bi) used to store the calculations in
    double ans; //stores a^2+b^2 < 2
    ans = pow(z.x,2) + pow(z.y,2);
    if(abs(ans) > 2){
        o = z;
    }else{
	numIter++;
    o.x = (z.x * z.x) - (z.y * z.y) + c->x;
    o.y = 2 * z.x * z.y + c->y;
    }
    return o;
}

void drawMandleY(int i, int j, Image *image, int &c1, int depth){
    drawMandleX(i,j,image,c1,depth);
    if(i == static_cast<int>(image->rows())-1){ 
	
    }else{
	j=0;
	drawMandleY(i+1,j,image,c1,depth);
    }
    return; 
}

void drawMandleX(int i, int j, Image *image, int c1, int depth){
    complex *c = new complex; //(x,y) mapped to (a+bi)                         
    complex *checked = new complex; //updated (a+bi) equation                  
    double *ans = new double; //used to check if a^2+b^2 < 2                   
    complex *z = new complex; //used to store values of updated c in           
    int counter = 0; //counter used to help with the depth
    int numIter = 0; //number of iterations on this loop
    Color dim; //color to be colored
    double q; //coloured answer
    
    if(j != static_cast<int>(image->rows())-1){ //base case if true
	
	convertComplex(static_cast<int>(image->rows()), *c, j, i);
	*checked = mandlebrotCheck(z,c,counter,depth,numIter);
	*ans = pow(checked->x,2) + pow(checked->y,2);
	
	if(abs(*ans) >= 4){ // true then a colour/black is written             
           
	    q = ((double)numIter/depth);
	    q = ((q-checked->x) / (q-checked->y)); //normalize the q value

	    if(abs(q) < 0.5){
		dim = ColorRGB(102,178,205);
	    }else if(abs(q) < 1){
		dim = ColorRGB(0,128,255);
	    }else{
		dim = Color(white);
	    }
	    image->pixelColor(j, i, dim);

	}else if(abs(*ans) > 3){
	    image->pixelColor(j, i, pink);
        }else if(abs(*ans) > 2){
	    image->pixelColor(j, i, orange);
	}else{ //else it's colored black and in the set                        
            c1=0;
            image->pixelColor (j, i, black);
        }
	
        delete ans; // de-allocating from the heap                             
        delete z;
        delete c;
        delete checked;
        drawMandleX(i,j+1,image, c1, depth); //recursive call
    }
	return;
}
void convertComplex(int width, complex &c, int x, int y){
    c.x = re_start + ((double)x / width)
	* (re_end - re_start); //calculates a in (a+bi)
    c.y = im_start + ((double)y / width) *
	(im_end - im_start); //calculates b in (a+bi)
}
