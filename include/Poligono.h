#pragma once

#include <iostream>
#include <vector>

#ifdef __APPLE__
#include <glut.h>
#endif

#ifdef __linux__
#include <GL/glut.h>
#endif

#include "Ponto.h"

using namespace std;

class Poligono
{
    vector<Ponto> Vertices;
    Ponto Min, Max;

public:
    Poligono();
    Ponto getVertice(int);
    unsigned long getNVertices();
    void insereVertice(Ponto);
    void insereVertice(Ponto p, int pos);
    void desenhaPoligono();
    void desenhaVertices();
    void pintaPoligono();
    void imprime();
    void atualizaLimites();
    void obtemLimites(Ponto &Min, Ponto &Max);
    void LePoligono(const char *nome);
    void desenhaAresta(int n);
    void getAresta(int i, Ponto &P1, Ponto &P2);
    void alteraVertice(int i, Ponto P);
    void imprimeVertices();
};
