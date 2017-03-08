#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"
#include "parser.h"

int main(int argc, char **argv) {

  screen s;
  struct matrix * edges;
  struct matrix * transform;
  struct matrix * _rot1;
  struct matrix * _rot2;
  struct matrix * _rot3;
  edges = new_matrix(4, 4);
  transform = new_matrix(4, 4);
  _rot1 = make_rotX(20);
  _rot2 = make_rotY(20);
  _rot3 = make_rotZ(20);
  printf("rot1 mat:\n");
  print_matrix(_rot1);
  printf("rot2 mat:\n");
  print_matrix(_rot2); 
  printf("rot3 mat:\n");
  print_matrix(_rot3); 
  /*if ( argc == 2 )
    parse_file( argv[1], transform, edges, s );
  else
    parse_file( "stdin", transform, edges, s );
  */
  
  free_matrix( edges );
  free_matrix( transform );
}  
