#pragma once

#include <iostream>

using namespace std;

class Temporizador
{
    struct timeval start_time;

public:
    Temporizador();     // Inicializa o temporizador
    double getDeltaT(); // Retorna o tempo decorrido desde a última chamada desta mesma função
};
