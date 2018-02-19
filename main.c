#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

int main() {

  screen s;
  color c;
  struct matrix *edges;
  struct matrix *identity;
  struct matrix *mult;

  edges = new_matrix(4, 1);
  identity = new_matrix(4, 4);
  mult = new_matrix(4, 1);

  
  //==================================================
  // Testing matrix methods

  printf("\nADDING TWO EDGES TO OG MATRIX:\n");
  add_edge(edges, 100, 250, 0, 100, 300, 0);
  add_edge(edges, 110, 250, 0, 110, 300, 0);
  print_matrix(edges);

  printf("\nADDING FOUR POINTS TO THE SPARE MATRIX:\n");
  add_point(mult, 2, 2, 0);
  add_point(mult, 3, 0, 0);
  add_point(mult, 5, 3, 0);
  add_point(mult, 4, 3, 0);
  print_matrix(mult);
  
  printf("\nOG * SPARE = SPARE:\n");
  matrix_mult(edges, mult);
  print_matrix(mult);
  
  printf("\nTHIS IS THE IDENTITY MATRIX:\n");
  ident(identity);
  print_matrix(identity);

  printf("\nIDENTITY * OG = OG\n");
  matrix_mult(identity, edges);
  print_matrix(edges);

  
  //==================================================
  // Drawing An Image

  printf("\nCREATING AN IMAGE AND DRAWING...\n");

  srand(time(NULL));
  c.red = 255;
  
  int bottom, randint;
  randint = 300;
  for (bottom = 101; bottom < 400; bottom++) {
    if (!(bottom % 20)) {
      randint += (rand() % 100) - 50;
      draw_lines(edges, s, c);
      free_matrix(edges);
      edges = new_matrix(4, 1);
      c.red = rand() % 256;
      c.blue = rand() % 256;
      c.green = rand() % 256;
    }
    add_edge(edges, bottom, 250, 0, bottom, randint, 0);
  }
  
  save_extension(s, "image.jpg");
  display(s);

  free_matrix( edges );
  free_matrix( identity );
  free_matrix( mult );
}
