

#ifndef Linha_h
#endif
#define Linha_h

#ifdef __APPLE__
#include <GLUT/glut.h>
#endif

#ifdef __linux__
#include <GL/glut.h>
#endif

// #include "Ponto.h"

class Linha
{
	float minx, miny, maxx, maxy; // envelope

public:
	float x1, y1, x2, y2;

	void geraLinha(int limite, int TamMax);
	void desenhaLinha();
};
