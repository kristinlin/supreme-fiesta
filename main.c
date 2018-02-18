#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

int main() {

  screen s;
  color c;
  struct matrix *edges;

  edges = new_matrix(4, 4);

  c.red = 255;

  add_edge(edges, 0, 0, 0, 100, 100, 0);
  add_edge(edges, 100, 100, 0, 300, 100, 0);
  add_edge(edges, 300, 100, 0, 300, 300, 0);
  print_matrix(edges);
  draw_lines(edges, s, c);
  
  display(s);
  free_matrix( edges );
}
