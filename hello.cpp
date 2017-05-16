#include <iostream>
#include "console.h"
#include "gwindow.h"
#include <cmath>
#include "gtypes.h"
#include "random.h"
#include "gobjects.h"
#include "set.h"

using namespace std;


/* Constants */

const double SIZE = 200;        // Size of the order 0 fractal in pixels */
const int ORDER = 5;            // Order of the fractal snowflake */


/*Function prototypes */

GPoint drawFractalLine(GWindow & gw, GPoint pt,
                       double r, double theta, int order);

GPoint drawCurvedFractalLine(GWindow & gw, GPoint pt,
                       double r, double theta, int order);

void drawFractal(GWindow & gw, double x, double y,
                 double size, int order);

void drawH(GWindow & gw, double x, double y, double size);

GPoint drawFractalTree(GWindow & gw, GPoint pt,
                     double r, double theta, int order);

void drawTriangle(GWindow & gw, double x, double y, double length);

void drawSierpinskiTriangle(GWindow & gw, double x, double y, double length, int order);

void generateBinaryCode(Set<string> & set, int nBits);


int main() {

  // GWindow gw;
  // double cx = gw.getWidth() / 2;
  // double cy = gw.getHeight() / 2;
  //GPoint pt(cx - SIZE / 2, cy - sqrt(3.0) * SIZE / 6);
  //pt = drawCurvedFractalLine(gw, pt, SIZE, 0, ORDER);
  //  pt = drawFractalLine(gw, pt, SIZE, -120, ORDER);  
  //  pt = drawFractalLine(gw, pt, SIZE, +120, ORDER);

  //drawH(gw, 50, 50, 30);
  //drawFractal(gw, 100, 100, 80, 4);

  //GPoint pt(50, 50);
  //pt = drawFractalTree(gw, pt, 100, 90, 10);

  //drawSierpinskiTriangle(gw, cx, cy, 200, 5);

  Set<string> test;
  generateBinaryCode(test, 3);
  cout << test.toString() << endl;

  
  return 0;
}


/* Function: drawFractalLine
 * Usage:    GPoint end = drawFractalLine(gw, pt, r, theta, order);
 * -----------------------------------------------------------------
 * Draws a fractal edge starting from pt and extending r units in direction
 * theta. 
 */
GPoint drawFractalLine(GWindow & gw, GPoint pt,
                       double r, double theta, int order) {
  if (order == 0) {
    return gw.drawPolarLine(pt, r, theta);
  } else {
    pt = drawFractalLine(gw, pt, r / 3, theta, order - 1);
    pt = drawFractalLine(gw, pt, r / 3, theta + 60, order - 1);
    pt = drawFractalLine(gw, pt, r / 3, theta - 60, order - 1);
    return pt = drawFractalLine(gw, pt, r / 3, theta, order - 1);    
  }
}


GPoint drawCurvedFractalLine(GWindow & gw, GPoint pt,
                             double r, double theta, int order) {
  if (order == 0) {
    return gw.drawPolarLine(pt, r, theta);
  } else {
    pt = drawCurvedFractalLine(gw, pt, r / 3, theta, order - 1);
    if (randomChance(0.5)) {
      pt = drawCurvedFractalLine(gw, pt, r / 3, theta + 60, order - 1);
      pt = drawCurvedFractalLine(gw, pt, r / 3, theta - 60, order - 1);
    } else {
      pt = drawCurvedFractalLine(gw, pt, r / 3, theta - 60, order - 1);
      pt = drawCurvedFractalLine(gw, pt, r / 3, theta + 60, order - 1);
    }
    return pt = drawCurvedFractalLine(gw, pt, r / 3, theta, order - 1);    
  }
}


/* Function: drawFractal
 * Usage:    drawFractal(gw, 10, 10, 20, 3);
 * --------------------------------------------------
 * Problem 16 of the text book
 */
void drawFractal(GWindow & gw, double x, double y,
                 double size, int order) {
  if (order == 0) {
    drawH(gw, x, y, size);
  } else {
    drawH(gw, x, y, size);      // try remove this and see what happens
    drawFractal(gw, x-size/2, y-size/2, size/2, order -1);
    drawFractal(gw, x-size/2, y+size/2, size/2, order -1);
    drawFractal(gw, x+size/2, y-size/2, size/2, order -1);
    drawFractal(gw, x+size/2, y+size/2, size/2, order -1);    
  }

}


/* Function: drawH
 * Usage:    drawH(gw, x, y, size);
 * --------------------------------
 * Helper function for problem 16
 * draws a H shape with center at (x, y)
 */
void drawH (GWindow & gw, double x, double y, double size) {
  gw.drawLine(x-size/2, y, x+size/2, y);
  gw.drawLine(x-size/2, y-size/2, x-size/2, y+size/2);
  gw.drawLine(x+size/2, y-size/2, x+size/2, y+size/2);         
}


GPoint drawFractalTree(GWindow & gw, GPoint pt,
                     double r, double theta, int order) {
  if (order == 0) {
    return gw.drawPolarLine(pt, r, theta);
  } else {
    pt = gw.drawPolarLine(pt, r, theta);
    GPoint temp;
    temp = pt;                  // this is to make sure the two new branches starts from the same point
    if (randomChance(0.9)) {
      pt = drawFractalTree(gw, pt, r / 2, theta - 20, order - 1);
      return pt = drawFractalTree(gw, temp, r / 2, theta + 20, order - 1);      
    } else {
      return pt;
    }
  }
}


/* Function: drawTriangle
 * Usage:    drawTriangle(gw, x, y, length);
 * ------------------------------------------
 * Helper function, draws a triangle with center at (x, y) and
 * side length long
 */
void drawTriangle(GWindow & gw, double x, double y, double length) {
  double newX = x - length / 2;
  double newY = y + sqrt(length*length - (length*length) / 4) / 2;
  GPoint pt (newX, newY);
  pt = gw.drawPolarLine(pt, length, 0);
  pt = gw.drawPolarLine(pt, length, +120);
  pt = gw.drawPolarLine(pt, length, -120);  
  
}


/* Function drawSierpinskiTriangle
 * Usage:   drawSierpinskiTriangle(gw, x, y, length, order)
 * ---------------------------------------------------------
 * Problem 18 of the text book
 */
void drawSierpinskiTriangle(GWindow & gw, double x, double y, double length, int order) {
  if (order == 0) {
    drawTriangle(gw, x, y, length);
  } else {
    drawTriangle(gw, x, y, length);
    drawSierpinskiTriangle(gw, x, y - (sqrt(length*length/4 - length*length/16)) / 2, length / 2, order -1);
    drawSierpinskiTriangle(gw, x - length / 4, y + (sqrt(length*length/4 - length*length/16)) / 2,
                           length / 2, order -1);
    drawSierpinskiTriangle(gw, x + length / 4, y + (sqrt(length*length/4 - length*length/16)) / 2,
                           length / 2, order -1);     
  }
}


/* Function: generateBinaryCode
 * Usage:    generateBinaryCode(3);
 * ---------------------------------
 * Problem nine, old text book
 */
void generateBinaryCode(Set<string> & set, int nBits) {
  if (nBits == 0) {
    set.add("");
  } else {
    generateBinaryCode(set, nBits - 1);

    Set<string> temp;

    for (string str : set) {
      temp.add("1"+str);
      temp.add("0"+str);      
    }

    set = temp;
  }
}
