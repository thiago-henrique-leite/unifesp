#ifndef STANDARD_H
#define STANDARD_H

/*
  Arquivo com bibliotecas e variáveis globais utilizadas nos 3 exercícios.
*/

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.141592654

float theta = 0.0;
float right = 0.0;
float up = 0.0;
float zoomIn = 1;

int N = 10;

float CL_BLACK[3]  = {0.00, 0.00, 0.00};
float CL_WHITE[3]  = {1.00, 1.00, 1.00};
float CL_RED[3]    = {1.00, 0.00, 0.00};
float CL_GREEN[3]  = {0.00, 1.00, 0.00};
float CL_BLUE[3]   = {0.00, 0.00, 1.00};
float CL_YELLOW[3] = {1.00, 1.00, 0.00};
float CL_PINK[3]   = {1.00, 0.40, 0.70};
float CL_ORANGE[3] = {1.00, 0.50, 0.00};
float CL_LILAC[3]  = {0.60, 0.40, 0.70};
float CL_BROWN[3]  = {0.50, 0.20, 0.00};
float CL_CYAN[3]   = {0.50, 1.00, 1.00};
float CL_GRAY[3]  = {0.88, 0.88, 0.88};

#endif