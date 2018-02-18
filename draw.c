#include <stdio.h>
#include <stdlib.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

/*======== void add_point() ==========
Inputs:   struct matrix * points
         int x
         int y
         int z 
Returns: 
adds point (x, y, z) to points and increment points.lastcol
if points is full, should call grow on points
====================*/
void add_point( struct matrix * points, double x, double y, double z) {
  if (points->lastcol == points->cols) {
    grow_matrix(points, 2 * points->cols);
  }
  points->m[0][points->lastcol] = x;
  points->m[1][points->lastcol] = y;
  points->m[2][points->lastcol] = z;
  points->m[3][points->lastcol] = 1;
  points->lastcol++;
}

/*======== void add_edge() ==========
Inputs:   struct matrix * points
          int x0, int y0, int z0, int x1, int y1, int z1
Returns: 
add the line connecting (x0, y0, z0) to (x1, y1, z1) to points
should use add_point
====================*/
void add_edge( struct matrix * points, 
	       double x0, double y0, double z0, 
	       double x1, double y1, double z1) {
  add_point(points, x0, y0, z0);
  add_point(points, x1, y1, z1);
}

/*======== void draw_lines() ==========
Inputs:   struct matrix * points
         screen s
         color c 
Returns: 
Go through points 2 at a time and call draw_line to add that line
to the screen
====================*/
void draw_lines( struct matrix * points, screen s, color c) {
  int edge;
  for (edge = 0; edge < points->lastcol; edge += 2) {
    draw_line(points->m[0][edge], points->m[1][edge], 
	     points->m[0][edge+1], points->m[1][edge+1], 
	      s, c);
  }
}




//==========================================================
// BRESENHAM'S LINE ALGO


void draw_line(int x0, int y0, int x1, int y1, screen s, color c) {

  int delta_x = x1 - x0;
  int delta_y = y1 - y0;

  //lower quadrants; swap starting point
  if (delta_y < 0) {
    draw_line(x1, y1, x0, y0, s, c);
  }

  //slopes from 0 to 1
  if (delta_y <= delta_x && delta_x*delta_y >= 0) {
      oct_1(x0, y0, x1, y1, s, c);
  }
  //slopes from more than 1 to undefined (kaboom)
  else if (delta_y >= delta_x && delta_x*delta_y >= 0) {
      oct_2(x0, y0, x1, y1, s, c);
  }
  //slopes from less than kaboom to -1
  else if (delta_y >= -1 * delta_x && delta_x*delta_y < 0) {
      oct_3(x0, y0, x1, y1, s, c);
  }
  //slopes from less than -1 to more than 0
  if (delta_y <= -1 * delta_x && delta_x*delta_y < 0) {
    oct_4(x0, y0, x1, y1, s, c);
  }
}


//==========================================================
// OCTANTS 


//slopes 0, 1
//f(x+1, y+.5)
void oct_1(int x, int y, int x1, int y1, screen s, color c) {
  //init values
  int A = y1 - y;
  int B = -1 * (x1 - x);
  int d = 2*A + B;
  
  while (x < x1) {
    plot(s, c, x, y);

    //if midpoint is below the line; bump pixel up
    //less of y; less of B, which is negative; more positive
    if (d > 0) {
      y++;
      d += 2*B;
    }
    x++;
    d += 2*A;
  }
}


//slopes >1 to undefined
//f(x+.5, y+1)
void oct_2(int x, int y, int x1, int y1, screen s, color c) {
  //init values
  int A = y1 - y;
  int B = -1 * (x1 - x);
  int d = A + 2*B;
  
  while (y < y1) {
    plot(s, c, x, y);

    //if midpoint is to left of line; bump pixel to side
    //less of x; less of A, which is positive; more negative
    if (d < 0) {
      x++;
      d += 2*A;
    }
    y++;
    d += 2*B;
  }
}


//slopes from kaboom to -1
//f(x-.5, y+1)
void oct_3(int x, int y, int x1, int y1, screen s, color c) {
  //init values
  int A = y1 - y;
  int B = -1 * (x1 - x);
  int d = 2*B - A;
  
  while (y < y1) {
    plot(s, c, x, y);

    //if midpoint is to right of line; bump pixel to side
    //more x; more A, which is positive; more positive
    if (d > 0) {
      x--; 
      d -= 2*A;
    }
    y++;
    d += 2*B;
  }
}


//slopes from -1 to 0
//f(x-1, y+.5)
void oct_4(int x, int y, int x1, int y1, screen s, color c) {
  //init values
  int A = y1 - y;
  int B = -1 * (x1 - x);
  int d = -2*A + B;

  while (x > x1) {
    plot(s, c, x, y);

    //if midpoint is below line; bump pixel to up
    //y-value is less; less of B, which is positive; more negative
    if (d < 0) {
      y++;
      d += 2*B;
    }
    x--;
    d -= 2*A;
  }
}





