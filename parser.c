#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"
#include "parser.h"


/*======== void parse_file () ==========
  Inputs:   char * filename 
  struct matrix * transform, 
  struct matrix * pm,
  screen s
  Returns: 

  Goes through the file named filename and performs all of the actions listed in that file.
  The file follows the following format:
  Every command is a single character that takes up a line
  Any command that requires arguments must have those arguments in the second line.
  The commands are as follows:
  line: add a line to the edge matrix - 
  takes 6 arguemnts (x0, y0, z0, x1, y1, z1)
  ident: set the transform matrix to the identity matrix - 
  scale: create a scale matrix, 
  then multiply the transform matrix by the scale matrix - 
  takes 3 arguments (sx, sy, sz)
  translate: create a translation matrix, 
  then multiply the transform matrix by the translation matrix - 
  takes 3 arguments (tx, ty, tz)
  rotate: create an rotation matrix,
  then multiply the transform matrix by the rotation matrix -
  takes 2 arguments (axis, theta) axis should be x y or z
  apply: apply the current transformation matrix to the 
  edge matrix
  display: draw the lines of the edge matrix to the screen
  display the screen
  save: draw the lines of the edge matrix to the screen
  save the screen to a file -
  takes 1 argument (file name)
  quit: end parsing

  See the file script for an example of the file format


  IMPORTANT MATH NOTE:
  the trig functions int math.h use radian mesure, but us normal
  humans use degrees, so the file will contain degrees for rotations,
  be sure to conver those degrees to radians (M_PI is the constant
  for PI)
  ====================*/
void parse_file ( char * filename, 
                  struct matrix * transform, 
                  struct matrix * edges,
                  screen s) {

  FILE *f;
  char line[256];
  char *temp;
  color c;
  c.red = 250;
  c.blue = 0;
  c.green = 0;
  clear_screen(s);

  if ( strcmp(filename, "stdin") == 0 ) {
    f = stdin;
  }
  else{
    f = fopen(filename, "r");
  }
  while ( fgets(line, 255, f) != NULL ) {
    line[strlen(line)-1]='\0';
    printf(":%s:\n",line);
    if(!strcmp(line,"line")){
      fgets(line,255,f);
      int a,b,c,d,e,f;
      temp = line;
      a = atoi(strsep(&temp," "));
      b = atoi(strsep(&temp," "));
      c = atoi(strsep(&temp," "));
      d = atoi(strsep(&temp," "));
      e = atoi(strsep(&temp," "));
      f = atoi(strsep(&temp," "));
      add_edge(edges,a,b,c,d,e,f);
      print_matrix(edges);

    }
    else if(!strcmp(line,"ident")){
      ident(transform);
    }
    else if(!strcmp(line,"scale")){
      struct matrix *scale = new_matrix(4,4);
      int a,b,c;
      fgets(line,255,f);
      temp = line;
      a = atoi(strsep(&temp," ")); 
      b = atoi(strsep(&temp," "));
      c = atoi(strsep(&temp," "));
      scale = make_scale(a,b,c);
      matrix_mult(scale,transform);
      print_matrix(transform);
    }
    else if(!strcmp(line,"move")){
      struct matrix *trans = new_matrix(4,4);
      int a,b,c;
      fgets(line,255,f);
      temp = line;
      a = atoi(strsep(&temp," ")); 
      b = atoi(strsep(&temp," "));
      c = atoi(strsep(&temp," "));
      trans = make_translate(a,b,c);
      matrix_mult(trans,transform);
       print_matrix(transform);
    }
    else if(!strcmp(line,"rotate")){
      struct matrix *rot = new_matrix(4,4);
      int a;
      char *b;
      fgets(line,255,f);
      temp = line;
      b = strsep(&temp," "); 
      a = atoi(strsep(&temp," "));
      if(!strcmp(b,"x")){
	rot = make_rotX(a);
      }
      if(!strcmp(b,"y")){
	rot = make_rotY(a);
      }
      if(!strcmp(b,"z")){
	rot = make_rotZ(a);
      }
      matrix_mult(rot,transform);
       print_matrix(transform);
    }
    else if(!strcmp(line,"apply")){
      matrix_mult(transform,edges);
       print_matrix(edges);
    }
    else if(!strcmp(line,"display")){
      clear_screen(s);
      draw_lines(edges,s,c);
      display(s);
    }
    else if(!strcmp(line,"save")){
      fgets(line,255,f);
      clear_screen(s);
      draw_lines(edges,s,c);
      save_extension(s,line);
    }
    else if(!strcmp(line,"quit")){
      return;
    }
  }
}

