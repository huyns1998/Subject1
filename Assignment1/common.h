#pragma once
#include<stdbool.h>

bool isTriangle(float* coordinate);
float distance(float x1, float y1, float x2, float y2);
float conner(float a, float b, float c);
float* triangle(float* coordinate);
char* type_triangle(float* connerAndEdge);
float square(float* connerAndEdge);
float* tri_heigh(float* connerAndEdge, float sqr);
float* tri_med(float* connerAndEdge);
float* tri_center(float* coordinate);
void giaima_tamgiac();