#pragma once

#include "Ponto.h"

class Linha
{
    float minx, miny, maxx, maxy; // envelope

public:
    float x1, y1, x2, y2;

    void geraLinha(int limite, int TamMax);
    void desenhaLinha();
};
