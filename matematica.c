#include "matematica.h"

float coord_y_en_recta(float **v, size_t n, float x) {
	float y_inter, x0, x1, y0, y1, m;
	int i;

	for(i = 1; x > *(v[i]) && i < n; i++);

	x0 = v[i-1][0];
	x1 = v[i][0];
	y0 = v[i-1][1];
	y1 = v[i][1];

	m = (y1 - y0)/(x1 - x0);

	y_inter = m*(x - x0) + y0;

	return y_inter;
}

float randomf(float min, float max)
{
	return (float)rand()/RAND_MAX*(max-min)+min;
}
