#include "Temporizador.h"

#include <sys/time.h>

// Inicializa o temporizador
Temporizador::Temporizador()
{
    gettimeofday(&start_time, NULL);
}
// Retorna o tempo decorrido desde a última chamada desta mesma função
double Temporizador::getDeltaT()
{
    double dt;

    // Figure out time elapsed since last call to idle function
    struct timeval end_time;
    gettimeofday(&end_time, NULL);
    dt = (float)(end_time.tv_sec - start_time.tv_sec) + 1.0e-6 * (end_time.tv_usec - start_time.tv_usec);
    start_time = end_time;
    return dt;
}
